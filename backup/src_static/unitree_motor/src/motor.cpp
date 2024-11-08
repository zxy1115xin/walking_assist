//
// Created by c208 on 6/17/22.
//
#include "motor.h"


UnitreeMotorGroup::UnitreeMotorGroup(ros::NodeHandle& nh, SerialPort& serial, bool enable[MOTORS_NUM]):
nh_(nh), serial_ptr_(&serial)
{
    // 初始化，只对使能的ID生成实例
    for (int j = 0; j < MOTORS_NUM; ++j) {
        if (enable[j])
            motor_ptr_[j] = new UnitreeMotor(nh_, *serial_ptr_, j);
    }
    // 循环控制
    ros::Rate loop_rate(1000);
    // turn for 3 second
    while (ros::ok()){
        update();
        ros::spinOnce();
        loop_rate.sleep();
    }
    // stop the motor
    stop();

}

UnitreeMotorGroup::~UnitreeMotorGroup()
{
    // 删除所有生成的实例，归还内存空间
    for (int j = 0; j < MOTORS_NUM; ++j) {
        if (motor_ptr_[j])
            delete[] motor_ptr_[j];
    }
}

void UnitreeMotorGroup::update() {
    for (int j = 0; j < MOTORS_NUM; ++j) {
        if (motor_ptr_[j])
            motor_ptr_[j]->update();
    }
}

void UnitreeMotorGroup::stop() {
    for (int j = 0; j < MOTORS_NUM; ++j) {
        if (motor_ptr_[j])
            motor_ptr_[j]->stop();
    }
}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "unitree_motor");
    ros::NodeHandle nh("");
    //用户从外部设定USB名称
    std::string device;
    ros::param::param<std::string>("~usb_device", device, "USB0");
    std::string dev_path = "/dev/tty";
    dev_path += device;
    ROS_INFO_STREAM("usb_device: " << dev_path);
    SerialPort serial((char*)dev_path.c_str());  // set the serial port name
    //用户从外部设定电机使能
    std::string enable_str;
    ros::param::param<std::string>("~enable", enable_str, "000");
    ROS_INFO_STREAM("enable: " << enable_str);
    bool enable[MOTORS_NUM];
    for (int j = 0; j < MOTORS_NUM; ++j) {
        if (enable_str.c_str()[j] != '0')
            enable[j] = true;
        else
            enable[j] = false;
    }
    // 电机组控制的最终实现
    UnitreeMotorGroup motor_group(nh, serial, enable);

    ros::spin();
    return 0;
}