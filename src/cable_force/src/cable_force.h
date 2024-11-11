//
// Created by c208 on 6/14/22.
//

#ifndef PROJECT_TALKER_H
#define PROJECT_TALKER_H
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <cable_force/Config.h>
#include <std_msgs/Float32.h>
#include <can_msgs/Frame.h>
#include <string>
#include <deque>

#define CHANNEL_NUM 4
#define FORCE_CAN_ID 0x00081280
//#define CONFIG_CAN_ID 0x601

class CableForce
{
public:
    CableForce(ros::NodeHandle& nh);
    ~CableForce();
    void canRxCallback(const can_msgs::Frame::ConstPtr& can_msg);
    ros::Publisher force_pub[CHANNEL_NUM];
    ros::Subscriber can_sub;
    std::deque<float> force_history[CHANNEL_NUM];

private:
    ros::NodeHandle nh_;
    int channel_;
    std_msgs::Float32 force_[CHANNEL_NUM];
    float prev_force_[CHANNEL_NUM];
};
#endif //PROJECT_TALKER_H
