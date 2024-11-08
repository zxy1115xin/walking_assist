//
// Created by c208 on 7/12/22.
//

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32.h>
#include <sensor_msgs/Imu.h>
#include <tf/tf.h>
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include <string>

tf2::Quaternion q0;
tf2::Quaternion q1;
tf2::Vector3 omega0;
tf2::Vector3 omega1;
tf2::Vector3 omega;

void imu0Callback(const sensor_msgs::Imu::ConstPtr &msg)
{
    tf2::convert(msg->angular_velocity, omega0);
    tf2::convert(msg->orientation, q0);
}
void imu1Callback(const sensor_msgs::Imu::ConstPtr &msg)
{
    tf2::convert(msg->angular_velocity, omega1);
    tf2::convert(msg->orientation, q1);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "test_omega");
    ros::NodeHandle n;

    ros::Subscriber imu_sub0 = n.subscribe<sensor_msgs::Imu>("IMU0", 1000, imu0Callback);
    ros::Subscriber imu_sub1 = n.subscribe<sensor_msgs::Imu>("IMU1", 1000, imu1Callback);
    ros::Publisher omega_pub = n.advertise<std_msgs::Float32>("omega", 1000);
    std_msgs::Float32 omega_msg;
    ros::Rate loop_rate(100);
    while (ros::ok())
    {
        omega = tf2::quatRotate(tf2::inverse(q1), omega1) - tf2::quatRotate(tf2::inverse(q0), omega0);
//        ROS_INFO_STREAM("w: " << omega.length());
        omega_msg.data = omega.length();
        omega_pub.publish(omega_msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
    ros::spin();
    return 0;
}