//
// Created by c208 on 7/11/22.
//

#include "imu.h"

IMU::IMU(ros::NodeHandle& nh): nh_(nh)
{
    ros::param::param<std::string>("~usb_device", usb_, "USB0");
    try
    {
        //串口设置
        ser_.setPort("/dev/tty" + usb_);
        ser_.setBaudrate(BAUD_RATE);
        serial::Timeout to = serial::Timeout::simpleTimeout(1000);
        ser_.setTimeout(to);
        ser_.open();
    }
    catch (serial::IOException& e)
    {
        ROS_ERROR_STREAM("Unable to open Serial Port !");
        return;
    }
    ros::param::param<std::string>("~name", name_, "IMU");
    imu_pub = nh_.advertise<sensor_msgs::Imu>(name_, 1000);

    ros::Rate loop_rate(100);
    while (ros::ok())
    {
        if (ser_.available()) {
            size_t bytes_read;
            bytes_read = ser_.read(r_buffer_, ser_.available());
//            ROS_INFO_STREAM("bytes: " << bytes_read);
            //接收到数据后处理
            for (int j = 0; j < bytes_read - sizeof(rec_data_); ++j) {
                if(r_buffer_[j] == FRAME_HEADER)
                {
                    memcpy(&rec_data_, &r_buffer_[j], sizeof(rec_data_));
                    if(rec_data_.sum == (char)((char)std::accumulate(&r_buffer_[j], &r_buffer_[j]+sizeof(rec_data_)-1, 0)&0xFF))
                    {
                        switch (rec_data_.type)
                        {
                            case TYPE_ACC:
//                                ROS_INFO_STREAM("a");
                                imu_msg_.linear_acceleration.x = (float)rec_data_.data[0]/32768.0*16.0;
                                imu_msg_.linear_acceleration.y = (float)rec_data_.data[1]/32768.0*16.0;
                                imu_msg_.linear_acceleration.z = (float)rec_data_.data[2]/32768.0*16.0;
                                break;
                            case TYPE_GYRO:
//                                ROS_INFO_STREAM("w");
                                imu_msg_.angular_velocity.x = (float)rec_data_.data[0]/32768.0*2000.0;
                                imu_msg_.angular_velocity.y = (float)rec_data_.data[1]/32768.0*2000.0;
                                imu_msg_.angular_velocity.z = (float)rec_data_.data[2]/32768.0*2000.0;
                                break;
//                            case TYPE_ANGLE:
////                                ROS_INFO_STREAM("A");
//                                imu_msg_.orientation = tf::createQuaternionMsgFromRollPitchYaw(
//                                        (float)rec_data_.data[0]/32768.0*180.0,
//                                        (float)rec_data_.data[1]/32768.0*180.0,
//                                        (float)rec_data_.data[2]/32768.0*180.0
//                                );
//                                break;
                            case TYPE_QUAT:
                                imu_msg_.orientation.w = (float)rec_data_.data[0]/32768.0;
                                imu_msg_.orientation.x = (float)rec_data_.data[1]/32768.0;
                                imu_msg_.orientation.y = (float)rec_data_.data[2]/32768.0;
                                imu_msg_.orientation.z = (float)rec_data_.data[3]/32768.0;
                                break;
                        }
                    }
                }
                imu_pub.publish(imu_msg_);
            }
        }
        ros::spinOnce();
        loop_rate.sleep();
    }
    ser_.close();
}

IMU::~IMU(){
    ser_.close();
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "usb_imu");
    ros::NodeHandle n;

    IMU imu(n);
    ros::spin();

    return 0;
}