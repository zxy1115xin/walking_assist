//
// Created by c208 on 2022/8/5.
//

#ifndef SRC_PID_H
#define SRC_PID_H

#include <cstdint>
#include <algorithm>
#include <math.h>
#include <ros/ros.h>

// output = kp * { e(n) + T/Ti*Σe(i) + Td/T*[e(n)-e(n-1)] }
// delta = kp * { [e(n)-e(n-1)] + T/Ti*e(n) + Td/T*[e(n)-2*e(n-1)+e(n-2)] }
class PID
{
public:
    PID();
    ~PID();
    void setKp(float kp);
    void setKi(float ki);
    void setKd(float kd);
    void update(float desire, float feedback);
    void reset();
    float getOutput();
    float getDelta();
private:
    float kp_;
    float ki_;
    float kd_;
//    e(n)
    float err_;
//    Σe(i)
    float err_sum_;
//    e(n-1)
    float err1_;
//    e(n-2)
    float err2_;
};

#endif //SRC_PID_H
