//
// Created by c208 on 6/24/22.
//

#ifndef SRC_UNITREEMOTOR_H
#define SRC_UNITREEMOTOR_H
#include <ros/ros.h>
#include "unitree_motor/Ctrl.h"
#include "unitree_motor/Sensor.h"
#include <string>
#include "serialPort/SerialPort.h"
#include <csignal>
#include <iostream>
//The control mode, 0:free, 5:Open loop slow turning, 10:close loop control
// 【电机控制模式，0:空闲, 5:开环缓慢转动, 10:闭环控制】
#define MOTOR_MODE_FREE         0
#define MOTOR_MODE_OPENLOOP     5
#define MOTOR_MODE_CLOSELOOP    10
#define MOTORS_NUM              3
//单位转换：从电机转子到输出轴
#define T_COEFF                 (9.1)
#define POS_COEFF               (1/T_COEFF)
#define W_COEFF                 (1/T_COEFF)

// 单个电机对象
class UnitreeMotor
{
public:
    UnitreeMotor(ros::NodeHandle& nh, SerialPort& serial, int id);
    ~UnitreeMotor();
    void update();
    void stop();
    void ctrlCallback(const unitree_motor::Ctrl::ConstPtr& ctrl_msg);
    ros::Subscriber ctrl_sub;
    ros::Publisher sensor_pub;
private:
    bool sendReceive_();
    ros::NodeHandle nh_;
    int id_;
    std::string name_;
    SerialPort* serial_ptr_;
    MOTOR_send motor_s_;
    MOTOR_recv motor_r_;
};


#endif //SRC_UNITREEMOTOR_H
