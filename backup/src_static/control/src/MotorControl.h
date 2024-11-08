//PID
// Created by c208 on 6/24/22.
//

#ifndef SRC_MOTORCONTROL_H
#define SRC_MOTORCONTROL_H


#include <ros/ros.h>
#include <string>
#include <unitree_motor/Sensor.h>
#include <unitree_motor/Ctrl.h>
#include <std_msgs/Float32.h>
#include <control/Command.h>
#include <math.h>
#include "PID.h"
#include "Adapt.h"
#include "LRN.h"
#include "MFAC.h"
#include "FD_PID.h"
#include "Feedforward.h"

#define MOTOR_OUT_RADIUS 30     //(mm)
#define DISPLACEMENT_LIMIT 5

class MotorControl
{
public:
    MotorControl(ros::NodeHandle& nh, std::string name);
    ~MotorControl();
    void forceCallback(const std_msgs::Float32::ConstPtr& force_msg);
    void sensorCallback(const unitree_motor::Sensor::ConstPtr& sensor_msg);
    void cmdCallback(const control::Command::ConstPtr& cmd_msg);
    void update();
    ros::Subscriber force_sub;
    ros::Subscriber sensor_sub;
    ros::Subscriber T_sub;
    ros::Publisher ctrl_pub;
    ros::Subscriber cmd_sub;
private:
    ros::NodeHandle& nh_;
    std::string name_;
    float k_;
    std_msgs::Float32 force_msg_;
    std_msgs::Float32 T_msg_;
    unitree_motor::Sensor sensor_msg_;
    unitree_motor::Ctrl ctrl_msg_;
    control::Command cmd_msg_;
    bool force_sub_flag_;
    bool sensor_sub_flag_;
    bool cmd_sub_flag_;

    float pos_fight_;
    float flag_fight_;
    float mode_last_;
    float flag_mode;
    float pos_change_=0.2;

    PID pid_;

    Adapt adapt_;

    LRN LRN_;

    float F_cmd[500];
    float F_cmd_last[500];  //放在这里定义是由于多种模式下，可以将其作为前馈进行调用

    MFAC MFAC_;

    FD_PID FD_PID_;
    
    Feedforward Feedforward_;
    void TCallback(const std_msgs::Float32_<std::allocator<void>>::ConstPtr &T_msg);
};


#endif //SRC_MOTORCONTROL_H
