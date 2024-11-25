/*
 * Created by c208 on 6/23/22
 * 
 * MotorControlGroup 类用于通过 ROS（机器人操作系统）管理和控制多个电机。
 * 此代码旨在动态初始化电机控制器并在控制循环中运行它们。
 */

#include "control.h"  // 包含定义了 MotorControl 和 MotorControlGroup 的头文件

// MotorControlGroup 的构造函数，接收一个 ROS NodeHandle 引用作为输入
MotorControlGroup::MotorControlGroup(ros::NodeHandle& nh):
nh_(nh)  // 使用给定的 NodeHandle 初始化成员变量 nh_
{
    // 从参数服务器获取要控制的电机数量
    // 如果找不到参数 "~motor_num"，则使用默认值 1
    ros::param::param<int>("~motor_num", motor_num_, 1);

    // 动态分配一个指向 MotorControl 对象的指针数组
    ctrl_ptr_ = new MotorControl*[motor_num_];

    // 遍历每个电机以使用特定的电机名称初始化控制指针
    for (int j = 0; j < motor_num_; ++j) {
        std::string motor_name;
        // 从参数服务器获取每个电机的名称，默认使用 "motor1"、"motor2" 等
        ros::param::param<std::string>("~motor" + std::to_string(j + 1), motor_name, "motor" + std::to_string(j + 1));
        // 使用给定的节点句柄和电机名称初始化每个 MotorControl 对象
        ctrl_ptr_[j] = new MotorControl(nh_, motor_name);
    }

    // 设置控制循环频率（100 Hz）
    float freq = 100.0;
    ros::Rate loop_rate(freq);

    // 主控制循环
    while (ros::ok()) {
        // 在每次迭代中更新每个电机控制器
        for (int j = 0; j < motor_num_; ++j) {
            ctrl_ptr_[j]->update();  // 调用每个 MotorControl 实例的 update 函数
        }
        
        // 允许 ROS 处理任何回调（例如，来自其他节点的消息）
        ros::spinOnce();
        // 休眠适当的时间以维持循环频率
        loop_rate.sleep();
    }
}

// MotorControlGroup 的析构函数
MotorControlGroup::~MotorControlGroup()
{
    // 遍历每个电机控制器指针并释放内存
    for (int j = 0; j < motor_num_; ++j) {
        delete ctrl_ptr_[j];  // 删除每个 MotorControl 对象（注意：应使用 delete 而不是 delete[]）
    }
    delete[] ctrl_ptr_;  // 释放指针数组
}

// 主函数
int main(int argc, char** argv)
{
    // 使用名称 "control" 初始化 ROS 节点
    ros::init(argc, argv, "control");
    // 创建一个 NodeHandle 对象以管理与 ROS 的通信
    ros::NodeHandle nh;

    // 创建一个 MotorControlGroup 实例，传入节点句柄
    MotorControlGroup ctrl_group(nh);

    // 保持程序运行以监听 ROS 回调
    ros::spin();
    return 0;
}
