//
// Created by zoukj on 8/25/22.
//

#ifndef SRC_ADAPT_H
#define SRC_ADAPT_H

#include <math.h>


float sgn(float x);

// Real-time enhancement of tracking performances for cable-conduit mechanisms-driven flexible robots
class Adapt {
public:
    Adapt();
    ~Adapt();
    void setParam(float ts, float alpha, float kappa, float delta1, float delta2);
    void update(float desire, float feedback);
    void reset();
    float getOutput();
private:
    // params
    float ts_;
    float alpha_;
    float kappa_;
    float delta1_;
    float delta2_;
    // state vars
    float kai_;
    float D_;

    float desire_;
    float feedback_;
    // error
    //    e(n)
    float err_;
    //    Σe(i)
    float err_sum_;
    //    e(n-1)
    float err1_;
    //    e(n-2)
    float err2_;

    float omega_;
    float err_dot_;
};


#endif //SRC_ADAPT_H
