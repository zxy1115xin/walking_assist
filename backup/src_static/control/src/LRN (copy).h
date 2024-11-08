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
    float update(float force_des,float force_real,float flag_step,float (&f_cmd)[500],float (&f_cmd_last)[500],float Tsta,float Tend);
    void setKp(float Kp);
    void setKd(float Kd);
    void setKl(float Kl);
    void setBeta(float Beta);
    void setKfit(float Kfit);
    void setNum(int Num);
    void setTDelay(int TDelay);
    void setParam(float Kp,float Kd,float Ki,float Kl,float Beta,float Kfit,int Num,int TDelay);
    int getSnum();



private:
    float Kp_;
    float Kd_;
    float Ki_;   
    float Kl_;
    float Kfit_;
    float beta_;
    float last_cmd_;
    float err_;
    float diff_err_;
    bool index_;
    int Num_;
    int TDelay_;
    int ssnum_;
    float err_sum_ ;


};

#endif //SRC_LRN_H
