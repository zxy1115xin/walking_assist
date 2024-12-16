//
// Created by Administrator on 2022/9/28.
//

#include "LRN.h"

LRN::LRN() {
    err_=0;
    K_ind = 0;
    step_ = 0;
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

void LRN::setParam(float Kp, float Kd, float Ki) {
    Kp_=Kp;
    Kd_=Kd;
    Ki_=Ki;
    return;
}

void LRN::reset(float (&f_cmd)[500],float (&f_cmd_last)[500]) {
    for(int a =0; a<500;a++){
        f_cmd[a]=0;
        f_cmd_last[a]=0;
    }
    errFmax=0;
    errFmin=0;
    return;
}

void LRN::recover() {
    Fmax_real=0;
    Fmax_cmd_=0;
    F1err=0;
    F2err=0;
}

void LRN::getForce(float other_force) {
    other_force_=other_force;
}


float LRN::update(float force_des, float force_real, float flag_step, float (&f_cmd)[500], float (&f_cmd_last)[500],
                  float Tsta, float Trise, float Tfall, float Fmax, int Mode , float touch_time) {

    // 参数预备
    int Num_=500;
    Tsta=floor(Tsta);
    Trise=floor(Trise);
    Tfall=floor(Tfall);

    ros::Time current_time = ros::Time::now();
    double tt = current_time.toSec(); // 获取秒数
    double t = tt -touch_time;

    diff_err_=force_real-force_des-err_;
    err_=force_real-force_des;
    err_sum_ += err_;
    // 设计积分上下届
    float err_sum_max = 400;
    float err_sum_min = -400;
    if(err_sum_ > err_sum_max)err_sum_ = err_sum_max;
    if(err_sum_ < err_sum_min)err_sum_ = err_sum_min;

    float this_cmd=-Kp_*err_-Kd_*diff_err_-Ki_*err_sum_;
    float output_force=this_cmd;


    SNum_=floor(flag_step);

    if (SNum_<10 & index_new==0 ){

        if (Mode==1) //继承上次学习结果，只执行一次
        {
            for (int a = 0; a < Num_; a++)
            {
                f_cmd_last[a] = f_cmd[a];
            }
                f_cmd_last[0] = f_cmd_last[1];

            if (Fmax-Fmax_real > -10  &&  Fmax-Fmax_real < 10 &&  step_>10 && K_ind==0 )
            {
                Kerrf = 0.5;  //误差较小时，减少修正比例
                K_ind = 1;
                // ROS_INFO_STREAM(" motify the K !!!!!!!!!!!!!!!!!!!!!!!!!!!!");
            }
        }
        err_sum_=0;  //积分清零
        errFmax=errFmax+Kerrf*(Fmax-Fmax_real);
        errFmin=errFmin+Kerrf*(F1err+F2err)/2;

        // 信息重置
        Fmax_real=0;
        Fmax_cmd_=0;
        F1err=0;
        F2err=0;
        index_new=1;  // index=1时代表周期更新
        step_++;  //学习了多少步


    }

    if (SNum_>=10) index_new=0;  //防止掉落标志位

    if(step_>-2)  //在第i步之后开始进行迭代学习
    {
        ROS_INFO_STREAM("!!!!!!!!!!!!!!!!!!!!1 T " << t <<"touch_time"<<touch_time <<"SNum_"<<SNum_);

        switch (Mode)
        {

            case 1:  // 迭代学习
            {

                int t1=2/100;  //提前激活时间
                int t2=2/100;
                int t3=0/100;

                output_force=f_cmd_last[SNum_]+this_cmd;
                float force_pre = 0.7*1000/30;
                if(t<=Tsta-t1 )
                {
//                    float f_max = 0.5*1000/30;
//                    float f_min = -0.5*1000/30;
//                    if(output_force > f_max)output_force = f_max;
//                    if(output_force < f_min)output_force = f_min;
                      output_force = force_pre;
                    //ROS_INFO_STREAM("Tsta: " << SNum_<<"force"<<output_force);
                }

                //上升阶段
                else if (t > Tsta-t1 && t<=  Trise-t2)
                {

                    float f_min = -0*1000/30;
                    float fmax = ( 0.5*Fmax+errFmax)*0.03*1000/30;
                    output_force= force_pre + sin(3.1415926/2*(t-Tsta+t1)/(Trise-Tsta+t1-t2))*fmax;
                    if(output_force < f_min)output_force = f_min;
                    //ROS_INFO_STREAM("Trise: " << SNum_<<"force"<<output_force<<"real"<<force_real);
                }

                //峰值阶段
                  else if (t >= Trise-t2 && t<=  Trise + t3)
                {

                    //float fmin =( 12)*0.075*1000/30;
                    //output_force=-fmin*(t- Trise + t2) / (Tfall - Trise +t2); // 自下而上的斜线
                    float fmax = ( 0.5*Fmax+errFmax)*0.03*1000/30;
                    output_force= force_pre + fmax;
                }

                // 下降阶段
                else if (t >=  Trise + t3  && force_des>10)
                {

                    float f_min =( 0.5*Fmax+0.5*errFmin)*0.075*1000/30;
                    output_force=-f_min*(t- Trise - t3) / (Tfall - Trise - t3 -2); // 自下而上的斜线
                    float fmin =( -50)*0.075*1000/30;
                    float fmax = 0;
                    if(output_force > fmax) output_force = fmax;
                    if(output_force < fmin) output_force = fmin;
                }

                // 下降到稳定阶段
                else if (t >= Trise + t3  && force_des<=10)
                {
                    output_force= 0.5*1000/30;

                }

                //记录周期内力的最大值
                if (force_real > Fmax_real)Fmax_real=force_real;


                // 记录放绳阶段力误差
                if (t >= Tfall-2 && t_last<= Tfall-2 && !std::isnan(force_real))
                {
                    if (force_real<0.2) force_real=-10;

                    F1err=force_real-force_des;
                }

                if (t>Tfall+5 && t_last<=Tfall+5 && !std::isnan(force_real))
                {
                    if (force_real<0.2) force_real=-6;
                    F2err=force_real-force_des;
                }


                //只覆盖这次，保留未经历的上次结果，防止误判
                f_cmd[SNum_]=output_force;




              break;
            }


            case 2: // 停止学习，始终沿用以及学好的控制
            {

                output_force=f_cmd_last[SNum_];
                break;
            }


            case 3: // 迭代学习前馈 + PID闭环模式
            {

                if (istep_index==1)
                {
                    if (this_cmd >  0.75*1000/30) this_cmd=  0.75*1000/30;
                    if (this_cmd < -0.75*1000/30) this_cmd= -0.75*1000/30;
                    output_force=f_cmd_last[SNum_]+this_cmd;
                }
                else output_force=f_cmd_last[SNum_];
                istep_index++;
                if (istep_index==5) istep_index=1;  // 每5步修正一次


                break;
            }

            case 4:{
                // 迭代学习前馈+无模型在自适应 闭环模式
                output_force=f_cmd_last[SNum_]+other_force_;
                break;
            }

        }  //输出力

    }
    SNum_last=SNum_;
    t_last=t;
    return output_force;
}
