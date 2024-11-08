//
// Created by c208 on 6/17/22.
//

#ifndef SRC_MOTOR_H
#define SRC_MOTOR_H

#include "UnitreeMotor.h"

// 一组电机对象：共用同一USB接口
class UnitreeMotorGroup
{
public:
    UnitreeMotorGroup(ros::NodeHandle& nh, SerialPort& serial, bool enable[MOTORS_NUM]);
    ~UnitreeMotorGroup();
    void update();
    void stop();
private:
    ros::NodeHandle nh_;
    SerialPort* serial_ptr_;
    UnitreeMotor* motor_ptr_[MOTORS_NUM];
};

#endif //SRC_MOTOR_H
