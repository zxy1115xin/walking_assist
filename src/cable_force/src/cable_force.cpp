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
    }
    can_sub = nh_.subscribe<can_msgs::Frame>("can_rx", 1000, &CableForce::canRxCallback, this);
}

CableForce::~CableForce(){}

void CableForce::canRxCallback(const can_msgs::Frame::ConstPtr &can_rx_msg) {
    if (can_rx_msg->id == FORCE_CAN_ID && can_rx_msg->dlc==8 && !can_rx_msg->is_error)
    {
        force_[0].data = (float)(can_rx_msg->data[0]<<8 | can_rx_msg->data[1]) / 10;
        force_[1].data = (float)(can_rx_msg->data[2]<<8 | can_rx_msg->data[3]) / 10;
        force_[2].data = (float)(can_rx_msg->data[4]<<8 | can_rx_msg->data[5]) / 10;
        force_[3].data = (float)(can_rx_msg->data[6]<<8 | can_rx_msg->data[7]) / 10;
        for (int j = 0; j < CHANNEL_NUM; ++j) {
            force_pub[j].publish(force_[j]);
        }
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "cable_force");
    ros::NodeHandle n;

    CableForce cable_force(n);    //********n是指？
    ros::spin();

    return 0;
}