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
                  float Tsta, float Trise, float Tfall, float Fmax, int Mode) {

    // 参数预备
    int Num_=500;
    Tsta=floor(Tsta);
    Trise=floor(Trise);
    Tfall=floor(Tfall);


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

              if (Fmax-Fmax_real > 20  &&  Fmax-Fmax_real < 20 &&  step_>10 && K_ind==1 )
            {
                Kerrf = 1;  //误差较大时，增加修正比例
                K_ind = 0;
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

        int t1=3;  //提前激活时间
        if (Fmax <80){  t1=2; }

        int t2=3;
        int t3=1;

        switch (Mode)

        {

            case 1:  // 迭代学习
            {



                output_force=f_cmd_last[SNum_]+this_cmd;
                float force_pre = 0.1*1000/30;
                if(SNum_<=Tsta-t1 )
                {
//                    float f_max = 0.5*1000/30;
//                    float f_min = -0.5*1000/30;
//                    if(output_force > f_max)output_force = f_max;
//                    if(output_force < f_min)output_force = f_min;
                      output_force = force_pre;
                    //ROS_INFO_STREAM("Tsta: " << SNum_<<"force"<<output_force);
                }

                //上升阶段
                else if (SNum_>Tsta-t1 && SNum_<=Trise-t2)
                {

                    float f_min = -0*1000/30;
                    float fmax = ( 0.5*Fmax+errFmax)*0.03*1000/30;

                    // 三角函数
                    output_force= force_pre + sin(3.1415926/2*(SNum_-Tsta+t1)/(Trise-Tsta+t1-t2))*fmax;

                    // 指数
                   //float x = SNum_-(Tsta-t1);
                   //float t1 = Trise-t2 - (Tsta-t1);
                   //output_force = fmax * (4 * pow(x, 3)/ pow(t1, 3) - 3 * pow(x, 4) / pow(t1,4));

                    if(output_force < f_min)output_force = f_min;
                    //ROS_INFO_STREAM("Trise: " << SNum_<<"force"<<output_force<<"real"<<force_real);
                }

                //峰值阶段
                  else if (SNum_>Trise-t2 && SNum_<= Trise-t3)
                {

                    float fmin =( 12)*0.075*1000/30;
                    float fmax = 3*1000/30;
                    float f_min = ( 40)*0.075*1000/30;

                    //output_force=-fmin*(SNum_ - Trise + t2) / (Tfall - Trise +t2); // 自下而上的斜线

                    output_force= fmax*(SNum_ - Trise + t2) / ( t2-t3 ); // 自下而上的斜线

                }

                // 下降阶段  相对于峰值，要提前下降
                else if (SNum_>Trise-t3  && force_des>10)
                {

                    float f_min =( 0.5*Fmax+0.5*errFmin)*0.075*1000/30;

                   // 自下而上的斜线
                   output_force=-f_min*(SNum_ - Trise - t3) / (Tfall - Trise - t3 -2);

                   // 指数
                   // float x = SNum_-Trise-t3;
                   // float t1 = Tfall - (Trise-t3);
                   // output_force = -f_min *( 1-  4 * pow(x, 3) / pow(t1, 3) + ( 3 * pow(x, 4)) / pow(t1, 4));

                    float fmin =( -50)*0.075*1000/30;
                    float fmax = 0;
                    if(output_force > fmax) output_force = fmax;
                    if(output_force < fmin) output_force = fmin;

                }

                // 稳定阶段
                else if (SNum_>Trise-t3 && force_des<=10)
                {
                    output_force= 0.5*1000/30;

                }

                //记录周期内力的最大值
                if (force_real > Fmax_real)Fmax_real=force_real;


                // 记录放绳阶段力误差,有金
                if (SNum_>Tfall-2 && SNum_last<= Tfall-2 && !std::isnan(force_real))
                {
                    if (force_real<0.2) force_real=-10;

                    F1err=force_real-force_des;
                }

                if (SNum_>Tfall+5 && SNum_last<=Tfall+5 && !std::isnan(force_real))
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


            case 3: // 迭代学习前馈 +  峰值误差调整
            {

                if ( SNum_>Tsta-t1 && SNum_<=Trise-3)
                {
                    if (this_cmd >  0.75*1000/30) this_cmd=  0.75*1000/30;
                    if (this_cmd < -0.75*1000/30) this_cmd= -0.75*1000/30;

                    output_force=f_cmd_last[SNum_]+this_cmd*100/30;

                }
                else output_force=f_cmd_last[SNum_];



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
    return output_force;
}
