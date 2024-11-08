//
// Created by c208 on 7/8/22.
//

#ifndef SRC_EMG_H
#define SRC_EMG_H
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32.h>
#include <can_msgs/Frame.h>
#include <string>

#define CHANNEL_NUM 8
#define EMG_CAN_ID1 0x001
#define EMG_CAN_ID2 0x002
//#define CONFIG_CAN_ID 0x601

class EMG
{
public:
    EMG(ros::NodeHandle& nh);
    ~EMG();
    void canRxCallback(const can_msgs::Frame::ConstPtr& can_msg);
    ros::Publisher emg_pub[CHANNEL_NUM];
    ros::Subscriber can_sub;
private:
    ros::NodeHandle nh_;
    std_msgs::Float32 emg_[CHANNEL_NUM];
};
#endif //SRC_EMG_H
