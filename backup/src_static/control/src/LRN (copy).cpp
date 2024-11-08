//
// Created by Administrator on 2022/9/28.
// 这是一个正儿八经的迭代学习
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

void LRN::setTDelay(int TDelay) {
    TDelay_=TDelay;
    return;
}

void LRN::setParam(float Kp, float Kd, float Ki,float Kl, float Beta, float Kfit, int Num, int TDelay) {
    Kp_=Kp;
    Kd_=Kd;
    Ki_=Ki;
    Kfit_=Kfit;
    Kl_=Kl;
    beta_=Beta;
    Num_=Num;
    TDelay_=TDelay;
    return;
}

int LRN::getSnum() {
    return  ssnum_;
}

float LRN::update(float force_des,float force_real,float flag_step,float (&f_cmd)[500],float (&f_cmd_last)[500],float Tsta,float Tend) {
    float last_errFit,theta_LRN;
    static int SNum_ = 0;
    static int step_ = 0;
    static float last_cmd = 0;
    static float last_errsum = 0;
    static float errsum = 0;
    
    static int Tdel=2;
    static float errsum_fast = 0;


    diff_err_=force_real-force_des-err_;
    err_=force_real-force_des;
    err_sum_ += err_;
    float err_sum_max = 4000;
    float err_sum_min = -4000;
    if(err_sum_ > err_sum_max)err_sum_ = err_sum_max;
    if(err_sum_ < err_sum_min)err_sum_ = err_sum_min;  
    
    
    float errFit=(1-Kfit_)*last_errFit+Kfit_*err_;
    float C_theta_LRN=beta_*theta_LRN-Kl_*errFit;
    C_theta_LRN=0;
    float this_cmd=-Kp_*err_-Kd_*diff_err_-Ki_*err_sum_+C_theta_LRN;

    theta_LRN+=C_theta_LRN;
    last_errFit=errFit;

    float output_force=this_cmd;



    if (flag_step>0.8 ){
    
	  	 if (flag_step>1.8 )
	  	 {
	  		//pass;
	  	  }
	  	 else
	  	 {
                  if(last_errsum>errsum)
                    {
                      //for (int a = SNum_; a < Num_; a++)f_cmd[a] = f_cmd[SNum_-1];
                      for (int a = SNum_; a < Num_; a++)f_cmd[a] = 0;
                      for (int a = 0; a < Num_; a++)f_cmd_last[a]=f_cmd[a];
                      f_cmd_last[0]=f_cmd_last[1];
                    }
		  }
        last_errsum=errsum;
        err_sum_=0;
        SNum_=0;
        errsum=0;
        step_++;
        

    }
    
    if(step_>2){
        output_force=f_cmd_last[SNum_+Tdel]+this_cmd;
        errsum += fabs(err_);
    }

   if(output_force-last_cmd>4)output_force=last_cmd+4;
   if(output_force-last_cmd<-10)output_force=last_cmd-10;
    
    ROS_INFO_STREAM("enable: " << this_cmd);
    //ROS_INFO_STREAM("Tend: " << Tend <<"Tsta: "<<Tsta);



    if(SNum_<Tsta-6 && force_des <7)
    {
        float f_max = 0.5*1000/30;
        float f_min = -0*1000/30;
        if(output_force > f_max)output_force = f_max;
        if(output_force < f_min)output_force = f_min;

    }
    
    if(SNum_>Tsta+25 )
    {
	if(output_force-last_cmd>1)output_force=last_cmd+1;

    }
    
    
    if(SNum_==Tsta+3)
    {
    	if(force_real-force_des>-2)Tdel=0;
    	ROS_INFO_STREAM("enable: TdelTdel........" << Tdel<<"----real"<<force_real<<".....des"<<force_des);
    	if(force_real-force_des<2)Tdel=2;
    
    }
    

    last_cmd=  output_force;
    f_cmd[SNum_]=output_force;
    SNum_++;
//
    ssnum_=SNum_;
    
//

    //ROS_INFO_STREAM("enable: " << flag_step);
    return output_force;
}

