//
// Created by c208 on 6/14/22.
//

#include "cable_force.h"

CableForce::CableForce(ros::NodeHandle& nh): nh_(nh)
{
    std::string channel_name = "channel";
    for (int j = 0; j < CHANNEL_NUM; ++j) {
        std::string name = channel_name + std::to_string(j+1);
        force_pub[j] = nh_.advertise<std_msgs::Float32>(name, 1000);
        // 初始化窗口数据
        force_history[j] = std::deque<float>(3, 0.0);  // 假设窗口大小为3
    }
    can_sub = nh_.subscribe<can_msgs::Frame>("can_rx", 1000, &CableForce::canRxCallback, this);
}

CableForce::~CableForce(){}

void CableForce::canRxCallback(const can_msgs::Frame::ConstPtr &can_rx_msg) {
    const float threshold = 0.1;  // 限幅阈值
    const int window_size = 3;    // 窗口大小

    if (can_rx_msg->id == FORCE_CAN_ID && can_rx_msg->dlc == 8 && !can_rx_msg->is_error) {
        // 获取原始数据
        float raw_force[CHANNEL_NUM] = {
            (float)(can_rx_msg->data[0] << 8 | can_rx_msg->data[1]) / 10,
            (float)(can_rx_msg->data[2] << 8 | can_rx_msg->data[3]) / 10,
            (float)(can_rx_msg->data[4] << 8 | can_rx_msg->data[5]) / 10,
            (float)(can_rx_msg->data[6] << 8 | can_rx_msg->data[7]) / 10
        };

        for (int j = 0; j < CHANNEL_NUM; ++j) {
            // 更新滑动窗口
            force_history[j].push_back(raw_force[j]);
            if (force_history[j].size() > window_size) {
                force_history[j].pop_front();
            }

            // 加权移动平均计算
            float weighted_sum = 0.0;
            float weight_sum = 0.0;
            int weight = 1;
            for (auto it = force_history[j].rbegin(); it != force_history[j].rend(); ++it) {
                weighted_sum += (*it) * weight;
                weight_sum += weight;
                weight++;
            }
            float weighted_average = weighted_sum / weight_sum;

            // 限幅滤波：如果与上一次发布的值差异小于阈值，则保持上次值
            if (std::abs(weighted_average - force_[j].data) < threshold) {
                // 保持上次值
                force_[j].data = force_[j].data;
            } else {
                // 更新平滑后的数据
                force_[j].data = weighted_average;
            }

            // 发布滤波后的数据
            force_pub[j].publish(force_[j]);
        }
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "cable_force"); // 初始化节点并设置名称
    ros::NodeHandle n; // 创建NodeHandle对象，用来与ROS系统通讯

    CableForce cable_force(n);  
    ros::spin();

    return 0;
}
