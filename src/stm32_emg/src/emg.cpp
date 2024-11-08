//
// Created by c208 on 7/8/22.
//

#include "emg.h"


EMG::EMG(ros::NodeHandle& nh): nh_(nh)
{
    std::string channel_name = "channel";
    for (int j = 0; j < CHANNEL_NUM; ++j) {
        std::string name = channel_name + std::to_string(j+1);
        emg_pub[j] = nh_.advertise<std_msgs::Float32>(name, 1000);
    }
    can_sub = nh_.subscribe<can_msgs::Frame>("can_rx", 1000, &EMG::canRxCallback, this);
}

EMG::~EMG(){}

void EMG::canRxCallback(const can_msgs::Frame::ConstPtr &can_rx_msg) {
    if (can_rx_msg->dlc==8 && !can_rx_msg->is_error)
    {
        switch (can_rx_msg->id) {
            case EMG_CAN_ID1:
                //收到前四个通道的EMG
                emg_[0].data = (float) (can_rx_msg->data[0] << 8 | can_rx_msg->data[1]);
                emg_[1].data = (float) (can_rx_msg->data[2] << 8 | can_rx_msg->data[3]);
                emg_[2].data = (float) (can_rx_msg->data[4] << 8 | can_rx_msg->data[5]);
                emg_[3].data = (float) (can_rx_msg->data[6] << 8 | can_rx_msg->data[7]);
                //发布前四个通道的数据
                for (int j = 0; j < 4; ++j) {
                    emg_pub[j].publish(emg_[j]);
                }
                break;
            case EMG_CAN_ID2:
                //收到后四个通道的EMG
                emg_[4].data = (float) (can_rx_msg->data[0] << 8 | can_rx_msg->data[1]);
                emg_[5].data = (float) (can_rx_msg->data[2] << 8 | can_rx_msg->data[3]);
                emg_[6].data = (float) (can_rx_msg->data[4] << 8 | can_rx_msg->data[5]);
                emg_[7].data = (float) (can_rx_msg->data[6] << 8 | can_rx_msg->data[7]);
                //发布后四个通道的数据
                for (int j = 4; j < CHANNEL_NUM; ++j) {
                    emg_pub[j].publish(emg_[j]);
                }
                break;
        }
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "stm32_emg");
    ros::NodeHandle n;

    EMG emg(n);    //********n是指？
    ros::spin();

    return 0;
}