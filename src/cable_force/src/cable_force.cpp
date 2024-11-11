//
// Created by c208 on 6/14/22.
//

#include "cable_force.h"
#include <deque>
#include <cmath>
#include <iostream> // 添加用于输出调试信息

// 加权移动平均和限幅滤波器类
class WeightedMovingAverageFilter {
public:
    // 构造函数：接收窗口大小和限幅阈值参数
    WeightedMovingAverageFilter(int window_size, double threshold)
        : window_size(window_size), threshold(threshold), previous_output(0.0) {}

    // 滤波函数：输入新数据，返回经过加权移动平均和限幅滤波后的结果
    double filter(double new_value) {
        // 将新数据添加到窗口
        values.push_back(new_value);
        if (values.size() > window_size) {
            values.pop_front();  // 如果窗口已满，移除最早的数据
        }

        // 计算加权移动平均
        double weighted_sum = 0.0;
        double weight_sum = 0.0;
        int weight = 1; // 初始权重
        for (auto it = values.rbegin(); it != values.rend(); ++it) {
            weighted_sum += (*it) * weight; // 倒序遍历，给越新的数据越高的权重
            weight_sum += weight;
            weight++;
        }
        double weighted_average = weighted_sum / weight_sum; // 计算加权平均

        // 限幅滤波：检查加权平均与前一个输出值的差异是否超过阈值
        if (std::abs(weighted_average - previous_output) < threshold) {
            // 若差异小于阈值，保持输出值不变
            return previous_output;
        } else {
            // 否则，更新输出值为加权平均值
            previous_output = weighted_average;
            return weighted_average;
        }
    }

private:
    int window_size;               // 滤波窗口大小
    double threshold;              // 限幅阈值
    double previous_output;        // 前一个滤波输出值
    std::deque<double> values;     // 保存窗口内的数值
};

// 修改后的 CableForce 类
CableForce::CableForce(ros::NodeHandle& nh): nh_(nh)
{
    std::string channel_name = "channel";
    for (int j = 0; j < CHANNEL_NUM; ++j) {
        // 发布器，用于发布每个通道的滤波后数据
        std::string name = channel_name + std::to_string(j+1);
        force_pub[j] = nh_.advertise<std_msgs::Float32>(name, 1000);
        
        // 初始化滤波器，窗口大小为3，限幅阈值为0.1
        filters[j] = WeightedMovingAverageFilter(3, 0.1);
    }
    // 订阅 "can_rx" 主题，并指定回调函数 canRxCallback
    can_sub = nh_.subscribe<can_msgs::Frame>("can_rx", 1000, &CableForce::canRxCallback, this);
}

CableForce::~CableForce() {}

void CableForce::canRxCallback(const can_msgs::Frame::ConstPtr &can_rx_msg) {
    // 检查 CAN 消息的 ID 和数据长度，以确保是有效的力数据
    if (can_rx_msg->id == FORCE_CAN_ID && can_rx_msg->dlc == 8 && !can_rx_msg->is_error)
    {
        // 提取原始数据，并将其转换为力值
        force_[0].data = (float)(can_rx_msg->data[0] << 8 | can_rx_msg->data[1]) / 10;
        force_[1].data = (float)(can_rx_msg->data[2] << 8 | can_rx_msg->data[3]) / 10;
        force_[2].data = (float)(can_rx_msg->data[4] << 8 | can_rx_msg->data[5]) / 10;
        force_[3].data = (float)(can_rx_msg->data[6] << 8 | can_rx_msg->data[7]) / 10;

        for (int j = 0; j < CHANNEL_NUM; ++j) {
            // 对每个通道的数据进行加权移动平均和限幅滤波
            float filtered_value = filters[j].filter(force_[j].data);

            // // 输出调试信息：显示原始数据和滤波后的数据
            // std::cout << "Channel " << (j + 1) 
            //           << " | Raw Data: " << force_[j].data 
            //           << " | Filtered Data: " << filtered_value << std::endl;

            // 发布滤波后的数据
            std_msgs::Float32 filtered_msg;
            filtered_msg.data = filtered_value;
            force_pub[j].publish(filtered_msg);
        }
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "cable_force"); // 初始化节点并设置名称，所有ROS节点必须有这句
    ros::NodeHandle n; // 创建NodeHandle对象，用来与ROS系统通讯

    CableForce cable_force(n);  
    ros::spin();

    return 0;
}
