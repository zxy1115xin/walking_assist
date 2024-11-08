//
// Created by c208 on 6/22/22.
//

#ifndef SRC_TUNE_H
#define SRC_TUNE_H

#include <ros/ros.h>
#include <unitree_motor/Sensor.h>
#include <unitree_motor/Ctrl.h>

class MotorTuning
{
public:
    MotorTuning(ros::NodeHandle& nh);
    ~MotorTuning();
    void sensorCallback(const unitree_motor::Sensor::ConstPtr& sensor_msg);
    ros::Subscriber sensor_sub;
    ros::Publisher ctrl_pub;
private:
    unitree_motor::Ctrl normal_();
    unitree_motor::Ctrl cascade_();
    float step_(float t);
    float limp_(float t);
    ros::NodeHandle nh_;
    bool start_flag_;
    float state0_;
    float desire_;
    double delay_;
    double error_;
    double time_;
    double k_p_;
    double k_w_;
    unitree_motor::Ctrl ctrl_msg_;
    unitree_motor::Sensor sensor_msg_;
};
#endif //SRC_TUNE_H
