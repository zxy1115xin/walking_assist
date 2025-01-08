//
// Created by c208 on 6/24/22.
//

#include "UnitreeMotor.h"

UnitreeMotor::UnitreeMotor(ros::NodeHandle& nh, SerialPort& serial, int id):
        nh_(nh), serial_ptr_(&serial), id_(id)
{
    // 初始化
    motor_s_.id = id;                   // set the id of motor
    motor_s_.motorType = MotorType::A1Go1;    // set the motor type, A1Go1 or B1
    motor_s_.mode = MOTOR_MODE_CLOSELOOP;
    motor_s_.T = 0.0;

//    std::string vel_key2 = "TO";
//    ros::param::param<float>("~"+vel_key2+std::to_string(id_), motor_s_.T, 0.0);


    // initial velocity
    std::string vel_key = "W0";
    ros::param::param<float>("~"+vel_key+std::to_string(id_), motor_s_.W, 0.0);
    motor_s_.Pos = 0.0;
    motor_s_.K_P = 0;
    motor_s_.K_W = 3;
    std::string default_name = "motor";
    default_name += std::to_string(id);
    ros::param::param<std::string>("~"+default_name, name_, default_name);
    //订阅控制指令，初始化
    ctrl_sub = nh_.subscribe<unitree_motor::Ctrl>(name_ + "_ctrl", 1000, &UnitreeMotor::ctrlCallback, this);
    //发布传感器消息，初始化
    sensor_pub = nh_.advertise<unitree_motor::Sensor>(name_ + "_sensor", 1000);
}

UnitreeMotor::~UnitreeMotor(){}

void UnitreeMotor::update()
{
    //串口发送并接收信息：包含发送数据的生成和接收数据的提取
    sendReceive_();
//    ROS_INFO_STREAM("w: " << motor_r_.W);
    //发布电机传感器信息
    unitree_motor::Sensor sensor_msg;
    sensor_msg.motor_id = motor_r_.motor_id;
    sensor_msg.Temp = motor_r_.Temp;
    sensor_msg.Pos = motor_r_.Pos * POS_COEFF;    //POS_COEFF =1/9.1
//    sensor_msg.W = motor_r_.W * W_COEFF;          //W_COEFF = 1/9.1
//    sensor_msg.LW = motor_r_.LW;
//    sensor_msg.Acc = motor_r_.Acc;
    sensor_msg.T = motor_r_.T * T_COEFF;          //T_COEFF = 9.1
//    for (int j = 0; j < 3; ++j) {
//        sensor_msg.acc[j] = motor_r_.acc[j];
//        sensor_msg.gyro[j] = motor_r_.gyro[j];
//    }
    sensor_pub.publish(sensor_msg);
}

void UnitreeMotor::stop()
{
    motor_s_.mode = MOTOR_MODE_FREE;
    motor_s_.T = 0.0;
    motor_s_.W = 0.0;
    motor_s_.Pos = 0.0;
    motor_s_.K_P = 0.0;
    motor_s_.K_W = 0.0;
    sendReceive_();
}

// 控制指令回调函数
void UnitreeMotor::ctrlCallback(const unitree_motor::Ctrl::ConstPtr& ctrl_msg)
{
    if (ctrl_msg->enable)
    {
        motor_s_.mode = MOTOR_MODE_CLOSELOOP;
        motor_s_.T = ctrl_msg->T / T_COEFF;       //T_COEFF = 9.1
        motor_s_.W = ctrl_msg->W / W_COEFF;       //W_COEFF =  1/9.1
        motor_s_.Pos = ctrl_msg->Pos / POS_COEFF; //POS_COEFF = 1/9.1
        motor_s_.K_P = ctrl_msg->K_P;
        motor_s_.K_W = ctrl_msg->K_W;
    }
    else
        motor_s_.mode = MOTOR_MODE_FREE;
}

//串口发送并接收信息：包含发送数据的生成和接收数据的提取
bool UnitreeMotor::sendReceive_()
{
    modify_data(&motor_s_);
    bool flag = serial_ptr_->sendRecv(&motor_s_, &motor_r_);
    extract_data(&motor_r_);
    return flag;
}