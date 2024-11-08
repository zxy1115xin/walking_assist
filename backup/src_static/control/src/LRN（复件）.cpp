//
// Created by Administrator on 2022/9/28.
//

#include "LRN.h"

LRN::LRN() {
    
    err_=0;
}

LRN::~LRN() {}

void LRN::setKp(float Kp) {
    Kp_=Kp;
    return;
}

void LRN::setKd(float Kd) {
    Kd_=Kd;
    return;
}

void LRN::setBeta(float Beta) {
    beta_=Beta;
    return;
}

void LRN::setKfit(float Kfit) {
    Kfit_=Kfit;
    return;
}

void LRN::setKl(float Kl) {
    Kl_=Kl;
    return;
}

void LRN::setNum(int Num) {
    Num_=Num;
    return;
}


void LRN::setParam(float Kp, float Kd, float Ki,float Kl, float Beta, float Kfit, int Num) {
    Kp_=Kp;
    Kd_=Kd;
    Ki_=Ki;
    Kfit_=Kfit;
    Kl_=Kl;
    beta_=Beta;
    Num_=Num;

    return;
}

void LRN::reset(float (&f_cmd)[1000],float (&f_cmd_last)[1000]) {
    for(int a =0; a<1000;a++){
        f_cmd[a]=0;
        f_cmd_last[a]=0;
    }
    return;

}

int LRN::getSnum() {
    return  ssnum_;
}

void LRN::getForce(float other_force) {
    other_force_=other_force;
}

float LRN::update(float force_des,float force_real,float flag_step,float (&f_cmd)[1000],float (&f_cmd_last)[1000],float Tsta,float Trise,float Tfall,float Fmax,int Mode) {

    static int SNum_ = 0;
    static int step_ = 0;
    static float last_cmd = 0;

    static float errFmax = 0;
    static float errFmin = 0;
    static float Fmax_real = 0;
    static float F1err = 0;
    static float F2err = 0;
    static int index =0;
    
    Tsta=floor(Tsta);
    Trise=floor(Trise);
    Tfall=floor(Tfall);

    diff_err_=force_real-force_des-err_;
    err_=force_real-force_des;
    err_sum_ += err_;
    float err_sum_max = 4000;
    float err_sum_min = -4000;
    if(err_sum_ > err_sum_max)err_sum_ = err_sum_max;
    if(err_sum_ < err_sum_min)err_sum_ = err_sum_min;  
    

    float this_cmd=-Kp_*err_-Kd_*diff_err_-Ki_*err_sum_;

    float output_force=this_cmd;

    SNum_=floor(flag_step);

    if (SNum_<10 & index==0 ){

        //if(last_errsum>errsum) //判断是否更新，如果误差比之前小就更新
        //for (int a = SNum_; a < Num_; a++)f_cmd[a] = f_cmd[SNum_-1];

        if (Mode==1) {
            //for (int a = SNum_; a < Num_; a++)f_cmd[a] = 0;
            for (int a = 0; a < Num_; a++)f_cmd_last[a] = f_cmd[a];
            f_cmd_last[0] = f_cmd_last[1];
        }

        
        err_sum_=0;  //积分清零

        step_++;
        errFmax=errFmax+Fmax-Fmax_real;
        errFmin=errFmin+(F1err+F2err)/2;

        Fmax_real=0;
        F1err=0;
        F2err=0;
        index=1;  // 开启新周期

    }

    if (SNum_>=10) index=0;

    if(step_>-2)  //在第i步之后开始进行迭代学习
    {
        output_force=f_cmd_last[SNum_]+this_cmd;


        int t1=5;
        int t2=2;
        switch (Mode)
        {

            case 1:  {

                // 起始阶段，每次修改区间,迭代参数要随之变化
                if(SNum_<=Tsta-t1 )
                {
                    float f_max = 0.5*1000/30;
                    float f_min = -0*1000/30;
                    if(output_force > f_max)output_force = f_max;
                    if(output_force < f_min)output_force = f_min;
                    //ROS_INFO_STREAM("Tsta: " << SNum_<<"force"<<output_force);
                }

                //上升阶段
                else if (SNum_>Tsta-t1 && SNum_<=Trise-t2)
                {

                    float f_min = -0*1000/30;
                    float fmax =( Fmax+errFmax)*0.025*1000/30;
                    output_force=0.5*1000/30+(SNum_-Tsta+t1)/(Trise-Tsta+t1-t2)*fmax;

                    if(output_force < f_min)output_force = f_min;

                    ROS_INFO_STREAM("Trise: " << SNum_<<"force"<<output_force);
                }

                //峰值阶段
                else if (SNum_>Trise-t2 && SNum_<=Trise+t2)
                {
                    float fmax =( Fmax+errFmax)*0.015*1000/30;
                    float f_min = -0*1000/30;
                    output_force=0.5*1000/30+fmax-fmax/(t2+t2)*(SNum_-Trise+t2);
                    //ROS_INFO_STREAM("Tmax: " << SNum_<<"force"<<output_force);

                    if(output_force < f_min)output_force = f_min;
                }

                // 下降阶段
                else if (SNum_>Trise+t2 && force_des>8)
                {
                    float fmin =( Fmax+errFmin)*0.05*1000/30;
                    output_force=-fmin*(SNum_-Trise-t2)/8;
                    float f_min = -0.5*1000/30;
                    if(output_force < f_min)output_force = f_min;

                }

                // 稳定阶段
                else if (SNum_>Trise+t2 && force_des<=12)
                {
                    output_force=0.5*1000/30;
                    //ROS_INFO_STREAM("Tend: " << SNum_<<"force"<<output_force);
                }

                //记录周期内力的最大值
                if (force_real>Fmax_real)Fmax_real=force_real;

                if (SNum_==Tfall-2)
                { F1err=force_real-force_des;
                    //ROS_INFO_STREAM("F1err: " <<F1err<<"force_real"<<force_real<<"force_des"<<force_des);
                }

                if (SNum_==Tfall+1)
                { F2err=force_real-force_des;
                    //ROS_INFO_STREAM("F2err: " <<F2err<<"force_real"<<force_real<<"force_des"<<force_des);
                }

                f_cmd[SNum_]=output_force;

                break;
            }

            case 2:{
                // 开环模式
                output_force=f_cmd_last[SNum_];
                //ROS_INFO_STREAM("SNum_" <<SNum_<<"force"<<f_cmd_last[SNum_]<<"cmd"<<f_cmd[SNum_]);
                break;

            }

            case 3:{
                // 迭代学习前馈+PID 闭环模式
                output_force=f_cmd_last[SNum_]+this_cmd;
                break;
            }

            case 4:{
                // 迭代学习前馈+无模型在自适应 闭环模式

                output_force=f_cmd_last[SNum_]+other_force_;

                break;
            }


        }


    }

    if (index==1)
    {
        output_force=f_cmd_last[SNum_];
    }


   // ssnum_=SNum_;


    return output_force;
}

