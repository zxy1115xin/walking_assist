//
// Created by c208 on 2022/10/30.
//

#include "Feedforward.h"

Feedforward::Feedforward() {}

Feedforward::~Feedforward() {}

float Feedforward::update(float flag_step,float (&f_cmd)[500]) {

    int No_ = floor(flag_step);
    float output=f_cmd[No_ ];
    return output;
}
