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
#include "ForwardPID.h"
#include <cstring>


#define MOTOR_OUT_RADIUS 27.7     //(mm) //可以考虑27（实验数据比例），有部分损耗  //30 是绕线轮半径
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

    float art_index_;
    float pos_fight_;
    float pos_now;
    float flag_fight_;
    float mode_last_;
    float flag_last_;
    float Ngait_= 10;
    float Nfight_= 10;
    float delete_cmd = 0;

    // 放线
    float pos_fight_last_ = 0;
    float last_force_data = 0.0;
    float pos_change_=0.2;
    float errsum=0;
    float force_err_max_=0;
    float pos_change1_=0;
    float errsum1=0;
    float force_err_max1_=0;

    // 导入控制算法
    PID pid_;
    Adapt adapt_;
    LRN LRN_;
    float F_cmd[500];
    float F_cmd_last[500];  //放在这里定义是由于多种模式下，可以将其作为前馈进行调用
    float Pos_cmd[500];  //放在这里定义是由于多种模式下，可以将其作为前馈进行调用
    MFAC MFAC_;
    FD_PID FD_PID_;
    Feedforward Feedforward_;
    ForwardPID ForwardPID_;

    void TCallback(const std_msgs::Float32_<std::allocator<void>>::ConstPtr &T_msg);
};


#endif //SRC_MOTORCONTROL_H
