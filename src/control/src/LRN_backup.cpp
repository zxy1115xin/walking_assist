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
    static float fend1;

    float this_cmd = 0;

    lastlast_err_ = err_;
    lastlast_diff_err_ = diff_err_;
    lastlast_err_sum_ = err_sum_;


    diff_err_=force_real-force_des-err_;
    err_=force_real-force_des;

    if(err_ < 0) err_sum_ = err_sum_ - err_;
    if(err_ >= 0) err_sum_ = err_sum_ + err_;  //误差的绝对值积累

    if(lastlast_err_sum_ = 0)
    {
        diff_err_=force_real-force_des-err_;
        err_=force_real-force_des;
    }

    if(lastlast_err_sum_ != 0 && lastlast_err_sum_ <= err_sum_)
    {
        diff_err_ = lastlast_diff_err_ ;
        err_ = lastlast_err_;
        err_sum_ = lastlast_err_sum_;
    }

    if(lastlast_err_sum_ != 0 && lastlast_err_sum_ > err_sum_)
    {
        diff_err_=force_real-force_des-err_;
        err_=force_real-force_des;
    }



//    if(lastlast_err_sum_ <= err_sum_)
//    {
//        diff_err_ = lastlast_diff_err_ ;
//        err_ = lastlast_err_;
//        err_sum_ = lastlast_err_sum_;
//    }

//    ROS_INFO_STREAM(" err_sum_"<<err_sum_<<"---------------------: "<<err_sum_ );

    float err_sum_max = 4000;
    float err_sum_min = -4000;
    if(err_sum_ > err_sum_max)err_sum_ = err_sum_max;
    if(err_sum_ < err_sum_min)err_sum_ = err_sum_min;


    this_cmd=-Kp_*err_-Kd_*diff_err_-Ki_*err_sum_;

    float output_force=this_cmd;



    SNum_=floor(flag_step);

    if (SNum_<10 & index_new==0 ){

        //if(last_errsum>errsum) //判断是否更新，如果误差比之前小就更新
        //for (int a = SNum_; a < Num_; a++)f_cmd[a] = f_cmd[SNum_-1];

        if (Mode==1) //继承上次学习结果
        {
            for (int a = 0; a < Num_; a++)
            {
                f_cmd_last[a] = f_cmd[a];
            }
                f_cmd_last[0] = f_cmd_last[1];

            if (Fmax_cmd_-Fmax_real > -10  &&  Fmax_cmd_-Fmax_real < 10 &&  step_>10 && K_ind==0 ) {
                Kerrf = 0.5;  //误差较小时，减少修正比例
                K_ind = 1;
                // ROS_INFO_STREAM(" motify the K !!!!!!!!!!!!!!!!!!!!!!!!!!!!");
            }
//            ROS_INFO_STREAM(" Fmax_cmd_"<<Fmax_cmd_<<"---------------Fmax_real: "<<Fmax_real );

        }

        //ROS_INFO_STREAM("errFmax: " <<errFmax<<"errFmin"<<errFmin<<"err1"<<F1err<<"F2err"<<F2err);
        err_sum_=0;  //积分清零
        errFmax=errFmax+( Kerrf)*(Fmax_cmd_-Fmax_real);
        errFmin=errFmin+Kerrf*(F1err+F2err)/2;
        Fmax_real=0;
        Fmax_cmd_=0;
        F1err=0;
        F2err=0;
        index_new=1;  // index=1时代表周期更新
        step_++;  //学习了多少步
        fend1=0;

    }

    if (SNum_>=10) index_new=0;  //防止掉落标志位

    if(step_>-2)  //在第i步之后开始进行迭代学习
    {

        switch (Mode)
        {

            case 1:  {

                int t1=6;  //提前激活时间
                int t2=3;
                int t3=0;

                output_force=f_cmd_last[SNum_]+this_cmd;      //在触地到起始，跟踪寓紧力

                if(SNum_<=Tsta-t1 )
                {
//                    float f_max = 0.5*1000/30;
//                    float f_min = -0.5*1000/30;
//                    if(output_force > f_max)output_force = f_max;
//                    if(output_force < f_min)output_force = f_min;
//
//                    fend1=output_force;
                      output_force = 0.6*1000/30;
                    //ROS_INFO_STREAM("Tsta: " << SNum_<<"force"<<output_force);
                }

                //上升阶段
                else if (SNum_>Tsta-t1 && SNum_<=Trise-t2)
                {

                    float f_min = -0*1000/30;
                    float fmax = Fmax + 150 +  errFmax*0.03*1000/30;
                    output_force=sin(3.1415926/2*(SNum_-Tsta+t1)/(Trise-Tsta+t1-t2))*fmax;
                    if(output_force < f_min)output_force = f_min;
                    //ROS_INFO_STREAM("Trise: " << SNum_<<"force"<<output_force<<"real"<<force_real);
                }

//                //峰值阶段
//                else if (SNum_>Trise-t2 && SNum_<=Trise-t3)
//                {
//                    float fmax =( Fmax+errFmax)*0.015*1000/30;
//                    float f_min =  -0*1000/30;
//                    output_force= 0.5*1000/30+fmax-fmax/(t2-t3)*(SNum_-Trise+t2);
//                    //ROS_INFO_STREAM("Tmax: " << SNum_<<"force"<<output_force);
//                    if(output_force < f_min)output_force = f_min;
//                }

                // 下降阶段
//                else if (SNum_>Trise-t2 && SNum_ <= Tfall)
//                {
////                    float fmin =( Fmax+errFmin)*0.065*1000/30;
////                    output_force=-fmin*sin(3.1415926/2 *(SNum_ + Tfall - 2 * Trise) / ( Tfall - Trise)) ;
//                    float fmin =( Fmax+errFmin)*0.075*1000/30;
//                    output_force=-fmin*(SNum_-Trise+t3)/8;
//
//                    float f_max = 0.5*1000/30;
//                    float f_min = -1*1000/30;
//                    if(output_force > f_max)output_force = f_max;
//                    if(output_force < f_min)output_force = f_min;
//                    // ROS_INFO_STREAM("Tend: " << SNum_<<"force"<<Fmax+errFmin);
//                }

//
//                // 稳定阶段
//                else if (SNum_> Tfall)
//                {
//                    output_force=0.5*1000/30;
//                    //ROS_INFO_STREAM("Tend: " << SNum_<<"force"<<output_force);
//                }

  //下降阶段

                  else if (SNum_>Trise-t2 && SNum_<= Trise+3)
                {
//                    float fmin =( 30)*0.075*1000/30;
//                    output_force=-fmin*(SNum_-Trise+t3)/8;
                    float fmin =( 12)*0.075*1000/30;
                    float fmax = 3*1000/30;
                    float f_min = ( 40)*0.075*1000/30;

                    output_force=-fmin*(SNum_ - Trise + t2) / (Tfall - Trise +t2); // 自下而上的斜线

                    output_force = fmin * sin(3.1415926/2 *(SNum_ - 2*(Trise - t2) + Tfall) / (Tfall -(Trise - t2))) - fmin ;//自下而上的三角函数
                    output_force=(1 - siga) * (-fmin*(SNum_-Trise+t2) / (Tfall - Trise +t2)) + siga * (f_cmd_last[SNum_] + this_cmd);
                    if(output_force > fmax) output_force = fmax;
                    if(output_force < -fmin) output_force = 3*1000/30;
                }


                else if (SNum_>Trise+3 && SNum_<= Tfall-6)
                {


//                    float fmin =( 30)*0.075*1000/30;
//                    output_force=-fmin*(SNum_-Trise+t3)/8;
                    float fmin =( 12)*0.075*1000/30;
                    float fmax = 0;
                    float f_min = ( 40)*0.075*1000/30;

                    output_force=-fmin*(SNum_ - Trise + t2) / (Tfall - Trise +t2); // 自下而上的斜线

                    output_force = fmin * sin(3.1415926/2 *(SNum_ - 2*(Trise - t2) + Tfall) / (Tfall -(Trise - t2))) - fmin ;//自下而上的三角函数
                    output_force=(1 - siga) * (-fmin*(SNum_-Trise+t2) / (Tfall - Trise +t2)) + siga * (f_cmd_last[SNum_] + this_cmd);
                    if(output_force > fmax) output_force = -4*1000/30;
                    if(output_force < -fmin) output_force = -f_min;
                }

                // 稳定阶段
                else if (SNum_>Tfall-6 && SNum_ <= Tfall +4)
                {
                    float fmin =( 25)*0.075*1000/30;
                    float fmax = 0*1000/30;
                    float f_min = 24*1000/30;

                    output_force=-24*1000/30;

                    //output_force = fmin * sin(3.1415926/2 *(SNum_ - 2*(Trise - t2) + Tfall) / (Tfall -(Trise - t2))) - fmin ;//自下而上的三角函数
//                    output_force=(-12*0.075*1000/30) + this_cmd;
                    if(output_force > fmax) output_force = 0;
                    if(output_force < -f_min) output_force = -f_min;
                }

//                else if (SNum_>Tfall +1 && SNum_ <= Tfall +3)
//                {
////                    float fmin =( 25)*0.075*1000/30;
////                    float fmax = 0*1000/30;
////                    float f_min = ( 40)*0.075*1000/30;
//
//                    output_force=-2*1000/30;

//                    //output_force = fmin * sin(3.1415926/2 *(SNum_ - 2*(Trise - t2) + Tfall) / (Tfall -(Trise - t2))) - fmin ;//自下而上的三角函数
//                    output_force=(-12*0.075*1000/30) + this_cmd;
//                    if(output_force > fmax) output_force = fmax;
//                    if(output_force < -fmin) output_force = -f_min;
//                }
//
//                else if (SNum_>Trise-t2 && fo80rce_des>8)
//                {
//                    float fmin =( Fmax+errFmin)*0.075*1000/30;
//                    output_force=-fmin*(SNum_-Trise+t3)/8;
//
//                    float f_max = 0.75*1000/30;
//                    float f_min = -1*1000/30;
//                    if(output_force > f_max)output_force = f_max;
//                    if(output_force < f_min)output_force = f_min;
//                    // ROS_INFO_STREAM("Tend: " << SNum_<<"force"<<Fmax+errFmin);
//                }
//
//                // 稳定阶段
//                else if (SNum_>Trise-t2 && force_des<=10)
//                {
//                    output_force=0.5*1000/30;
//                    //ROS_INFO_STREAM("Tend: " << SNum_<<"force"<<output_force);
//                }


               // 记录周期内力的最大值

                if(SNum_<=Trise && SNum_ >=Trise -1)
                {
                if (force_real > Fmax_real)Fmax_real=force_real;
                }
                if (force_des > Fmax_cmd_)Fmax_cmd_=force_des;

                if (Fmax_cmd_ - Fmax_real <= 5 && Fmax_cmd_ - Fmax_real >= -5 ) {this -> siga = 1;}
                if (Fmax_cmd_ - Fmax_real > 5 || Fmax_cmd_ - Fmax_real < -5 )   {this -> siga = 0;}
//                if (force_real > Fmax_real)Fmax_real=force_real;
//                if (force_des > Fmax_cmd_)Fmax_cmd_=force_des;


                // 记录放绳阶段力误差
                if (SNum_==Tfall-2)
                { F1err=force_real-force_des;
                    //ROS_INFO_STREAM("F1err: " <<F1err<<"force_real"<<force_real<<"force_des"<<force_des);
                }

                if (SNum_==Tfall+2)
                { F2err=force_real-force_des;
                    //ROS_INFO_STREAM("F2err: " <<F2err<<"force_real"<<force_real<<"force_des"<<force_des);
                }

                f_cmd[SNum_]=output_force;  //只覆盖这次，保留未经历的上次结果，防止误判

               // ROS_INFO_STREAM("output_force:" << output_force<<"f_cmd[SNum_+1]"<<f_cmd[SNum_]<<"f_cmd_last[SNum_]"<<f_cmd_last[SNum_]);

                break;
            }


            case 2:{
                // 开环模式
                output_force=f_cmd_last[SNum_];



                //ROS_INFO_STREAM("SNum_" <<SNum_<<"force"<<f_cmd_last[SNum_]<<"cmd"<<f_cmd[SNum_]);
                break;

            }

            case 3:{
                static int istep_index;
                // 迭代学习前馈+PID 闭环模式

                if (istep_index==1)
                {
                    if (this_cmd >  0.75*1000/30) this_cmd=  0.75*1000/30;
                    if (this_cmd < -0.75*1000/30) this_cmd= -0.75*1000/30;
                    output_force=f_cmd_last[SNum_]+this_cmd;
                }
                else output_force=f_cmd_last[SNum_];
                istep_index++;
                if (istep_index==5) istep_index=1;

                // 控制约束
                float f_min = -0.5*1000/30;
                if(output_force < f_min)output_force = f_min;


//                output_force=f_cmd_last[SNum_]+this_cmd;
//                // 控制约束
//                float f_min = -0.5*1000/30;
//                if(output_force < f_min)output_force = f_min;


                break;
            }

            case 4:{
                // 迭代学习前馈+无模型在自适应 闭环模式
                output_force=f_cmd_last[SNum_]+other_force_;
                break;
            }






        }  //输出力

    }

    return output_force;
}

