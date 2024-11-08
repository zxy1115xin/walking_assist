//
// Created by c208 on 2022/8/5.
//

#include "PID.h"

PID::PID(){
    reset();
}

PID::~PID() {}

void PID::setKp(float kp) {
    if (kp > 0)
        kp_ = kp;
    else
        return;
}
void PID::setKi(float ki) {
    if (ki > 0)
        ki_ = ki;
    else
        return;
}
void PID::setKd(float kd) {
    if (kd > 0)
        kd_ = kd;
    else
        return;
}

void PID::update(float desire, float feedback) {
    err2_ = err1_;
    err1_ = err_;
    err_ = desire - feedback;
    err_sum_ += err_;
//    积分限制
    float err_sum_max = 5000;
    float err_sum_min = -5000;
    if(err_sum_ > err_sum_max)
        err_sum_ = err_sum_max;
    else if(err_sum_ < err_sum_min)
        err_sum_ = err_sum_min;
}

void PID::reset() {
    err_ = 0;
    err_sum_ = 0;
    err1_ = 0;
    err2_ = 0;
}

float PID::getOutput(){
    float kp = kp_;
    float ki = ki_;
    float kd = kd_;
    float output = kp*err_ + ki*err_sum_ + kd*(err_-err1_);

    return output;
}

float PID::getDelta(){
    float kp = kp_;
    float ki = ki_;
    float kd = kd_;
    float delta = kp*(err_-err1_) + ki*err_ + kd*(err_-2*err1_+err2_);

    return delta;
}