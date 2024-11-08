//
// Created by c208 on 7/10/22.
//

#ifndef SRC_PROCESS_H
#define SRC_PROCESS_H

#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <string>
#include "iirFilter.h"
#include "iirFilter_terminate.h"


class ProcessEMG
{
public:
    ProcessEMG(ros::NodeHandle& nh);
    ~ProcessEMG();
    void emgRawCallback(const std_msgs::Float32::ConstPtr& raw_msg);
    ros::Publisher emg_pub;
    ros::Subscriber raw_sub;
private:
    ros::NodeHandle nh_;
    std::string name_;
    std_msgs::Float32 emg_;
};
#endif //SRC_PROCESS_H
