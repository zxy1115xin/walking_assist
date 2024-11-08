//
// Created by c208 on 2022/10/30.
//

#ifndef SRC_FEEDFORWARD_H
#define SRC_FEEDFORWARD_H
#include <math.h>
#include <ros/ros.h>

class Feedforward{
public:
    Feedforward();
    ~Feedforward();
    float update(float flag_step,float (&f_cmd)[500]);

};


#endif //SRC_FEEDFORWARD_H
