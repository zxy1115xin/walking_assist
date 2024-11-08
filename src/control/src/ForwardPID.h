//
// Created by c208 on 2023/5/12.
//

#ifndef CATKIN_WS_FORWARDPID_H
#define CATKIN_WS_FORWARDPID_H
#include <math.h>
#include <ros/ros.h>

class ForwardPID
{
public:
    ForwardPID();
    ~ForwardPID();
    float update(float pos_des,float pos_real,float flag_step,float (&f_cmd)[500],float Tsta,float Trise,float Tfall,float Fmax);
    void setKp(float Kp);
    void setKd(float Kd);
    void setParam(float Kp,float Kd,float Ki);


private:
    float Kp_;
    float Kd_;
    float Ki_;
    float err_;
    float diff_err_;
    float err_sum_ ;

    int SNum_;
    int step_;

};

#endif //CATKIN_WS_FORWARDPID_H
