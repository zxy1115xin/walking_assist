//
// 把迭代学习结果作为前馈，针对每一步的位置为误差来调整输出力矩
//



#include "ForwardPID.h"


ForwardPID:: ForwardPID() {}

ForwardPID:: ~ForwardPID() {}

void ForwardPID:: setKp(float Kp)
{
    Kp_=Kp;
}

void ForwardPID:: setKd(float Kd)
{
    Kd_=Kd;
}

void ForwardPID:: setParam(float Kp,float Kd,float Ki)
{
    Kp_=Kp;
    Kd_=Kd;
}


float ForwardPID:: update(float pos_des,float pos_real,float flag_step,float (&f_cmd)[500],float Tsta,float Trise,float Tfall,float Fmax)
{
    // 参数预备
    float  output_force;
    int Num_=500;
    Tsta=floor(Tsta);
    Trise=floor(Trise);
    Tfall=floor(Tfall);
    SNum_=floor(flag_step);

    diff_err_=pos_real-pos_des-err_;
    err_=pos_real-pos_des;
    err_sum_ += err_;
    float err_sum_max = 4000;
    float err_sum_min = -4000;
    if(err_sum_ > err_sum_max)err_sum_ = err_sum_max;
    if(err_sum_ < err_sum_min)err_sum_ = err_sum_min;

    float this_cmd=-Kp_*err_-Kd_*diff_err_-Ki_*err_sum_;


    if (SNum_>Tsta && SNum_<=Trise)
    {
//        // -----------方法1 : 多步一控制 限制最大调整力矩------------
//        static int istep_index;
//        if (istep_index==1)
//        {
//            if (this_cmd >  0.75*1000/30) this_cmd=  0.75*1000/30;
//            if (this_cmd < -0.75*1000/30) this_cmd= -0.75*1000/30;
//            output_force=f_cmd[SNum_]+this_cmd;
//        }
//        else output_force=f_cmd[SNum_];
//        istep_index++;
//        if (istep_index==5) istep_index=1;

        // ---------方法2 : 加入权重函数  限制最大调整力矩-------------
        if (this_cmd >  0.1) this_cmd=  0.1;
        if (this_cmd < -0.1) this_cmd= -0.1;
        float Kn=0.01;
            output_force=Kn*SNum_*this_cmd;
    }


    // 控制约束
    float f_min = -0.5;
    if(output_force < f_min)output_force = f_min;

    return output_force;
}




