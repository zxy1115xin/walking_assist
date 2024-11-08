//
// Created by c208 on 6/23/22.
//

#include "control.h"

MotorControlGroup::MotorControlGroup(ros::NodeHandle& nh):
nh_(nh)
{
    // 获取参数：电机个数（一共需要控制几个电机？）
    ros::param::param<int>("~motor_num", motor_num_, 1);
    // 动态创建控制器指针数组
    ctrl_ptr_ = new MotorControl*[motor_num_];
    // 对每个控制器指针赋予名称 （默认：ctrl_ptr_[0]->name_ = "motor1")
    for (int j = 0; j < motor_num_; ++j) {
        std::string motor_name;
        ros::param::param<std::string>("~motor"+std::to_string(j+1), motor_name, "motor"+std::to_string(j+1));
        ctrl_ptr_[j] = new MotorControl(nh_, motor_name);
    }
    // 循环控制
    float freq = 100.0;
    ros::Rate loop_rate(freq);
    int count = 0;
    while (ros::ok()){
        for (int j = 0; j < motor_num_; ++j) {
            ctrl_ptr_[j]->update();
        }
        ros::spinOnce();
        loop_rate.sleep();
    }
}

MotorControlGroup::~MotorControlGroup()
{
    for (int j = 0; j < motor_num_; ++j) {
        delete[] ctrl_ptr_[j];
    }
    delete[] ctrl_ptr_;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "control");
    ros::NodeHandle nh;

    MotorControlGroup ctrl_group(nh);

    ros::spin();
    return 0;
}
