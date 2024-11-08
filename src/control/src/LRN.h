//
// Created by Administrator on 2022/9/28.
//

#ifndef SRC_LRN_H
#define SRC_LRN_H
#include <math.h>
#include <ros/ros.h>

class LRN
{
public:
    LRN();
    ~LRN();
    float update(float force_des,float force_real,float flag_step,float (&f_cmd)[500],float (&f_cmd_last)[500],float Tsta,float Trise,float Tfall,float Fmax,int Mode);

    void setKp(float Kp);
    void setKd(float Kd);
    void reset(float (&f_cmd)[500],float (&f_cmd_last)[500]);
    void recover();
    void setParam(float Kp,float Kd,float Ki);
    void getForce(float other_force);

private:
    float Kp_;
    float Kd_;
    float Ki_;
    float err_;
    float diff_err_;
    bool index_;  // 模式选择
    float err_sum_ ;
    float lastlast_err_ = 0;
    float lastlast_diff_err_ = 0;
    float lastlast_err_sum_ = 0;
    int SNum_;
    int step_;
    float other_force_;  // 传参空位
    int index_new; //是否进入新步态
    float errFmax ; //峰值修正量
    float errFmin ;
    float Fmax_real ;
    float F1err ;
    float F2err ;
    float Fmax_cmd_;
    float Kerrf = 1 ;
    int K_ind ;
    int siga = 0;
};

#endif //SRC_LRN_H
