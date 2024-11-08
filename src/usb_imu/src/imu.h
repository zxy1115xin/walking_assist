//
// Created by c208 on 7/11/22.
//

#ifndef SRC_IMU_H
#define SRC_IMU_H

#include <ros/ros.h>
#include <serial/serial.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32.h>
#include <sensor_msgs/Imu.h>
#include <tf/tf.h>
#include <string>
#include <stdio.h>
#include <numeric>

#define BAUD_RATE       115200
#define FRAME_HEADER    0x55
#define TYPE_ACC        0x51
#define TYPE_GYRO       0x52
#define TYPE_ANGLE      0x53
#define TYPE_QUAT       0x59

#define S_BUFFERSIZE 1000 // send buffer size串口发送缓存长度
#define R_BUFFERSIZE 1000 // receive buffer size 串口接收缓存长度

#pragma pack(1)

struct RecData{
    char header;
    char type;
    signed short data[4];
    char sum;
};

class IMU
{
public:
    IMU(ros::NodeHandle& nh);
    ~IMU();
    ros::Publisher imu_pub;
private:
    ros::NodeHandle nh_;
    std::string usb_;
    std::string name_;
    serial::Serial ser_;
    uint8_t s_buffer_[S_BUFFERSIZE]; //发送缓存
    uint8_t r_buffer_[R_BUFFERSIZE]; //接收缓存
    struct RecData rec_data_;
    sensor_msgs::Imu imu_msg_;
};

#endif //SRC_IMU_H
