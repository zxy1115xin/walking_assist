//
// Created by c208 on 6/23/22.
//

#ifndef SRC_CONTROL_H
#define SRC_CONTROL_H

#include "MotorControl.h"

class MotorControlGroup
{
public:
    MotorControlGroup(ros::NodeHandle& nh);
    ~MotorControlGroup();
private:
    ros::NodeHandle& nh_;
    int motor_num_;
    MotorControl** ctrl_ptr_;
};

#endif //SRC_CONTROL_H
