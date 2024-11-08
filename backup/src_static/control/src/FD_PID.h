
#ifndef SRC_FD_PID_H
#define SRC_FD_PID_H
#include <algorithm>
#include <math.h>
#include <ros/ros.h>

class FD_PID{
public:
    FD_PID();
    ~FD_PID();
    void setParam(float Kp,float Ki,float Kd);
    void reset();
    float update(float force_des,float force_real,float flag_step,float (&f_cmd)[500]);
private:
    float kp_;
    float ki_;
    float kd_;
    float err_;
    float err_sum_;
    float err_last_;

};

#endif //SRC_FD_PID_H
