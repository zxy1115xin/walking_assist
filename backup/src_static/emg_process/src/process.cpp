//
// Created by c208 on 7/10/22.
//

#include "process.h"

ProcessEMG::ProcessEMG(ros::NodeHandle& nh): nh_(nh)
{
    ros::param::param<std::string>("~EMG_name", name_, "processed_EMG");
    emg_pub = nh_.advertise<std_msgs::Float32>("processed_" + name_, 1000);
    raw_sub = nh_.subscribe<std_msgs::Float32>(name_, 1000, &ProcessEMG::emgRawCallback, this);
    iirFilter_init();
}

ProcessEMG::~ProcessEMG()
{
    iirFilter_terminate();
}

void ProcessEMG::emgRawCallback(const std_msgs::Float32::ConstPtr& raw_msg) {
    emg_.data = iirFilter(raw_msg->data);
    emg_pub.publish(emg_);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "emg_process");
    ros::NodeHandle n;

    ProcessEMG emg(n);
    ros::spin();

    return 0;
}