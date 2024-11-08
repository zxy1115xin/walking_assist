//
// Created by zoukj on 8/25/22.
//

#include "Adapt.h"


float sgn(float x){
    return x/(fabs(x)+0.01);
}


Adapt::Adapt() {
    ts_ = 0.01;
    alpha_ = 5;
    kappa_ = 15;
    delta1_ = 10;
    delta2_ = 10;
    reset();
}

Adapt::~Adapt() {

}


void Adapt::update(float desire, float feedback) {
    desire_ = desire;
    feedback_ = feedback;

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
    //
    omega_ = err_ + alpha_*err_sum_*ts_;
    err_dot_ = (err_ - err1_)/ts_;
    // state equation
    float kai_dot = delta1_ * (kappa_*omega_ + sgn(omega_)*D_ + desire_ + err_dot_/alpha_) * omega_;
    float D_dot = delta2_ * sgn(omega_);
    kai_ += kai_dot*ts_;
    D_ += D_dot*ts_;
}

void Adapt::reset() {
    err_ = 0;
    err_sum_ = 0;
    err1_ = 0;
    err2_ = 0;
    omega_ = 0;
}

float Adapt::getOutput() {
    float output = kai_ * (kappa_*omega_ + sgn(omega_)*D_ + desire_ + err_dot_/alpha_);
    const float max = 120;
    if (output > max)
        output = max;
    else if (output < -max)
        output = -max;
    return output;
}

void Adapt::setParam(float ts, float alpha, float kappa, float delta1, float delta2) {
    if (ts>0 && alpha>0 && kappa>0 && delta1>0 && delta2>0)
    {
        ts_ = ts;
        alpha_ = alpha;
        kappa_ = kappa;
        delta1_ = delta1;
        delta2_ = delta2;
    }
}