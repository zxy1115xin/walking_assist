//
// Created by c208 on 6/22/22.
//

#include <unitree_motor/Ctrl.h>
#include <unitree_motor/Sensor.h>
#include "tune.h"

MotorTuning::MotorTuning(ros::NodeHandle& nh):
nh_(nh)
{
    start_flag_ = false;
    ros::param::get("~delay", delay_);
    ROS_INFO_STREAM("delay: " << delay_);
    ros::param::get("~error", error_);
    ROS_INFO_STREAM("error: " << error_);
    ros::param::get("~time", time_);
    ROS_INFO_STREAM("time: " << time_);
    ros::param::get("~kp", k_p_);
    ROS_INFO_STREAM("kp: " << k_p_);
    ros::param::get("~kw", k_w_);
    ROS_INFO_STREAM("kw: " << k_w_);
    //订阅sensor，初始化
    std::string sub_name = "motor_sensor";
    sensor_sub = nh_.subscribe<unitree_motor::Sensor>(sub_name, 1000, &MotorTuning::sensorCallback, this);
    //发布control，初始化
    std::string pub_name = "motor_ctrl";
    ctrl_pub = nh_.advertise<unitree_motor::Ctrl>(pub_name, 1000);
    //等待第一次接收电机反馈
    ROS_INFO_STREAM("wait for first feedback");
    while (!start_flag_ && ros::ok())
    {
        ros::spinOnce();
    }
    ros::Duration(delay_).sleep();

    // 循环控制
    ROS_INFO_STREAM("start control");
    float freq = 100.0;
    ros::Rate loop_rate(freq);
    int count = 0;
    // turn for 3 second
    while (ros::ok()){
        // 计算当前时间占比
        float t = count / freq / time_;
        // 计算时间饱和
        if (count / freq < time_)
            count++;
        step_(t);
        normal_();
//        cascade_();
        ctrl_pub.publish(ctrl_msg_);
        ros::spinOnce();
        loop_rate.sleep();

    }
}

MotorTuning::~MotorTuning(){}

void MotorTuning::sensorCallback(const unitree_motor::Sensor::ConstPtr& sensor_msg)
{
    if (!start_flag_)
    {
        ROS_INFO_STREAM("receive first feedback");
        state0_ = sensor_msg->Pos;
        start_flag_ = true;
    }
    sensor_msg_.Pos = sensor_msg->Pos;
}

unitree_motor::Ctrl MotorTuning::normal_()
{
    ctrl_msg_.enable = true;
    ctrl_msg_.T = 0.0;
    ctrl_msg_.Pos = desire_;
    ctrl_msg_.W = 0.0;
    ctrl_msg_.K_P = k_p_;
    ctrl_msg_.K_W = k_w_;
    return ctrl_msg_;
}

unitree_motor::Ctrl MotorTuning::cascade_()
{
    ctrl_msg_.enable = true;
    ctrl_msg_.T = 0.0;
    ctrl_msg_.Pos = desire_;
    ctrl_msg_.W = k_p_ * (desire_ - sensor_msg_.Pos);
    ctrl_msg_.K_P = 0.0;
    ctrl_msg_.K_W = k_w_;
    return ctrl_msg_;
}

float MotorTuning::step_(float t)
{
    desire_ = error_ + state0_;
    return desire_;
}
float MotorTuning::limp_(float t)
{
    desire_ = error_ * t + state0_;
    return desire_;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "tune");
    ros::NodeHandle nh;
    MotorTuning tuning(nh);

    ros::spin();
    return 0;
}