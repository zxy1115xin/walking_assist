//
// Created by Administrator on 2022/10/29.
//
#include "FD_PID.h"

FD_PID::FD_PID() {
    reset();
}

FD_PID::~FD_PID() {}

void FD_PID::setParam(float Kp, float Ki, float Kd) {
    kp_=Kp;
    ki_=Ki;
    kd_=Kd;
}

void FD_PID::reset() {
    err_ = 0;
    err_sum_ = 0;
    err_last_= 0;
}

float FD_PID::update(float force_des, float force_real, float flag_step,float (&f_cmd)[500]) {

    err_ = force_des - force_real;
    err_sum_ += err_;
    // 积分限制
    float err_sum_max = 5000;
    float err_sum_min = -5000;
    if(err_sum_ > err_sum_max)
        err_sum_ = err_sum_max;
    else if(err_sum_ < err_sum_min)
        err_sum_ = err_sum_min;

    float kl_ = 0.1;
    int No_ = floor(flag_step);
    if (f_cmd[No_]==0) f_cmd[No_]=0.5*1000/30;
    float output =f_cmd[No_] + kp_*err_ + ki_*err_sum_ + kd_*(err_-err_last_);
    if (No_>2) f_cmd[No_-2]=f_cmd[No_-2] + kl_*err_;
    err_last_=err_;

    return output;
}