//
// Created by c208 on 6/24/22.
//


// ！！！！！ 在本系统中，力矩为负，收线，拉力增加

#include "MotorControl.h"

MotorControl::MotorControl(ros::NodeHandle& nh, std::string name):
        nh_(nh), name_(name)
{
    ros::param::param<float>("~force_desire", cmd_msg_.force, 4.0);
    ros::param::param<float>("~art_index", art_index_, 0);
    force_sub_flag_ = false;
    sensor_sub_flag_ = false;
    cmd_sub_flag_ = false;

    //cable系统刚度：单位（N/mm)
    //ros::param::param<float>("~cable_stiff", k_, 10);
    ctrl_msg_.enable = true;
    ctrl_msg_.T = 0.0;
    ctrl_msg_.Pos = 0.0;
    ctrl_msg_.W = 0.0;
    ctrl_msg_.K_P = 0.2;
    ctrl_msg_.K_W = 3;

    //订阅force，初始化
    force_sub = nh_.subscribe<std_msgs::Float32>(name_ + "_force", 1000, &MotorControl::forceCallback, this);
    //订阅sensor，初始化
    sensor_sub = nh_.subscribe<unitree_motor::Sensor>(name_ + "_sensor", 1000, &MotorControl::sensorCallback, this);
    //订阅command，初始化
    if (art_index_ == 1)
        cmd_sub = nh_.subscribe<control::Command>(name_ + "_art_cmd", 1000, &MotorControl::cmdCallback, this);
    else
        cmd_sub = nh_.subscribe<control::Command>(name_ + "_cmd", 1000, &MotorControl::cmdCallback, this);

    //发布control，初始化
    ctrl_pub = nh_.advertise<unitree_motor::Ctrl>(name_ + "_ctrl", 1000);

}

MotorControl::~MotorControl(){}

void MotorControl::forceCallback(const std_msgs::Float32::ConstPtr& force_msg)
{
    if (!force_sub_flag_)
        force_sub_flag_ = true;
    force_msg_.data = force_msg->data;
}


void MotorControl::sensorCallback(const unitree_motor::Sensor::ConstPtr& sensor_msg)
{
    if (!sensor_sub_flag_)
        sensor_sub_flag_ = true;
    sensor_msg_.Pos = sensor_msg->Pos;
    sensor_msg_.T = sensor_msg->T;
}

void MotorControl::cmdCallback(const control::Command::ConstPtr& cmd_msg)
{
    if (!cmd_sub_flag_)
        cmd_sub_flag_ = true;
    cmd_msg_.force= cmd_msg->force;
    cmd_msg_.kp = cmd_msg->kp;
    cmd_msg_.mode = cmd_msg->mode;
    cmd_msg_.flag = cmd_msg->flag;
    cmd_msg_.Tsta = cmd_msg->Tsta;   
    cmd_msg_.Trise = cmd_msg->Trise;
    cmd_msg_.Tfall = cmd_msg->Tfall;
    cmd_msg_.Fmax = cmd_msg->Fmax;


//    if( cmd_msg_.mode != 8 && mode_last_== 8 )
//    {
////      pos_fight_=sensor_msg_.Pos ;
//        flag_fight_=cmd_msg_.flag;
//
//    }



    if( cmd_msg_.mode == 15 && mode_last_!= 15 )
    {
        pos_now=sensor_msg_.Pos ;
    }


}

void MotorControl::update()
{
    if (force_sub_flag_ && sensor_sub_flag_ && cmd_sub_flag_)
    {

        switch (cmd_msg_.mode)
        {
             case 0:  //起始状态,位置控制：Kp=8，Fdes=2
            {
                LRN_.reset(F_cmd,F_cmd_last); //迭代学习结果清零
                ctrl_msg_.T = 0;
                ctrl_msg_.K_P = 0.2;
                ctrl_msg_.K_W = 3;               
                float kp=7;
                float pos_error = -(2-force_msg_.data)/kp/MOTOR_OUT_RADIUS;
                ctrl_msg_.Pos = pos_error + sensor_msg_.Pos;
                break;
            }
        
            case 1:  //位置积分控制
            {
                ctrl_msg_.T = 0;
                ctrl_msg_.K_P = 0.2;
                ctrl_msg_.K_W = 3;
                float pos_error = -(cmd_msg_.force-force_msg_.data)/20/MOTOR_OUT_RADIUS;
                ctrl_msg_.Pos = pos_error + sensor_msg_.Pos;
                break;
            }

            case 2:  //速度模式 +为放线
            {
                ctrl_msg_.T = 0;
                ctrl_msg_.K_P = 0;
                ctrl_msg_.K_W = 3;
                //ctrl_msg_.W = cmd_msg_.vel;
                ctrl_msg_.W = 2;
                break;
            }

            case 3:  //位置模式
            {
                ctrl_msg_.T = 0;
                ctrl_msg_.K_P = 0.2;
                ctrl_msg_.K_W = 3;
                //ctrl_msg_.Pos = cmd_msg_.pos;
                ctrl_msg_.Pos = cmd_msg_.force;
                break;
            }

            case 4:  //力矩模式
            {
                ctrl_msg_.K_P = 0;
                ctrl_msg_.K_W = 0;
//                ctrl_msg_.T = -cmd_msg_.force*MOTOR_OUT_RADIUS/1000;
                ctrl_msg_.T = 0;
                break;
            }

            case 5:  // pid 力矩模式
            {
                ctrl_msg_.K_P = 0;
                ctrl_msg_.K_W = 0;
                pid_.setKp(cmd_msg_.kp);
                pid_.setKi(cmd_msg_.ki);
                pid_.setKd(cmd_msg_.kd);
                if ((force_msg_.data>2) && (last_force_data<=2))
                {
                    pid_.reset();
                    ROS_INFO_STREAM("reset: "<< force_msg_.data << "  " << last_force_data);
                }

                pid_.update(cmd_msg_.force, force_msg_.data);
                ctrl_msg_.T = -pid_.getOutput()*MOTOR_OUT_RADIUS/1000;
                last_force_data = force_msg_.data;
                break;
            }

            case 6:  // pid 位置
            {
//            static float last_force_data = 0.0;
                ctrl_msg_.T = 0;
                ctrl_msg_.K_P = 0.2;
                ctrl_msg_.K_W = 3;
                pid_.setKp(cmd_msg_.kp);
                pid_.setKi(cmd_msg_.ki);
                pid_.setKd(cmd_msg_.kd);

                pid_.update(cmd_msg_.force, force_msg_.data);
                float pos_error = -pid_.getDelta()/MOTOR_OUT_RADIUS;
                ctrl_msg_.Pos = pos_error + sensor_msg_.Pos;
//            last_force_data = force_msg_.data;
                break;
            }

            case 7:
            {
                // adaptive control
                ctrl_msg_.K_P = 0;
                ctrl_msg_.K_W = 0;
                adapt_.setParam(0.01, 0.5, 1.5, 1.0, 1.0);
                if ((force_msg_.data>2) && (last_force_data<=2))
                {
                    pid_.reset();
                }

                adapt_.update(cmd_msg_.force, force_msg_.data);
                ctrl_msg_.T = -adapt_.getOutput()*MOTOR_OUT_RADIUS/1000;
                last_force_data = force_msg_.data;

                // 根据反馈的保护
                if (force_msg_.data > 40)
                    ctrl_msg_.T = 0;
                // 力矩限制保护
                const float T_max = 5;
                if (ctrl_msg_.T > T_max)
                    ctrl_msg_.T = T_max;
                else if (ctrl_msg_.T < -T_max)
                    ctrl_msg_.T = -T_max;

                break;
            }

            case 8: // LRN 迭代学习
            {
                // 力矩模式
                ctrl_msg_.K_P = 0;
                ctrl_msg_.K_W = 0;
                // LRN 迭代学习 更新参数
                LRN_.setParam(0.5,0.8,0);
                int Mode_=1;  // LRN 迭代学习进行模式 mode == 1
                if (cmd_msg_.flag>400) cmd_msg_.flag=400;  // 防止超出数组大小
                float force_ctrl = LRN_.update(cmd_msg_.force,force_msg_.data,cmd_msg_.flag,F_cmd,F_cmd_last,cmd_msg_.Tsta,cmd_msg_.Trise,cmd_msg_.Tfall,cmd_msg_.Fmax,Mode_);
                ctrl_msg_.T =-force_ctrl*MOTOR_OUT_RADIUS/1000;

//                ROS_INFO_STREAM("=="<<name_<<"fight"<<ctrl_msg_.T<<"fmax"<< cmd_msg_.Fmax);

                // 根据反馈的保护
                if (force_msg_.data > 180)
                    ctrl_msg_.T = 0;
                if (force_msg_.data <= 2 && ctrl_msg_.T > 0)  //防止过渡放线
                    ctrl_msg_.T = 0;
                float cmd_T_last=ctrl_msg_.T;

                const float T_max = 50;
                if (ctrl_msg_.T > 24) // 力矩限制保护
                        ctrl_msg_.T = 24;
                if (ctrl_msg_.T < -T_max)
                        ctrl_msg_.T = -T_max;

                // 记录当前时刻电机位置，--一般只在迭代学习中更新
                Pos_cmd[cmd_msg_.flag]= sensor_msg_.Pos;
                
                // mode10 防线参考位置参考
                if (last_force_data < 5 && force_msg_.data >= 5){
                     pos_fight_=sensor_msg_.Pos;
                }
                flag_fight_=cmd_msg_.flag;
                last_force_data = force_msg_.data;

                break;

            }


            case 9:{  //利用迭代学习的结果作为前馈（迭代学习结果+前馈2/闭环3/无模型自适应4）
                ctrl_msg_.K_P = 0;
                ctrl_msg_.K_W = 0;
                int Mode_=2;  //开环模式
//              int Mode_=3;  //闭环模式
                //int Mode_=4;  //无模型自适应

                if (Mode_==4){  //无模型自适应4，但是实用范围不行，延迟
                    static int flag_mfac;
                    if (flag_mfac==0) //初始化只执行一次
                    {
                        float phi[20] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
                        float rho[20] = {0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7};
                        MFAC_.setParam(0.2, 1, 0.001, 3, 3);
                        MFAC_.set_Rho(rho);
                        MFAC_.init_Phi(phi);
                        flag_mfac=1;
                    }
                    float force_MFAC = MFAC_.update(force_msg_.data,cmd_msg_.force);
                    LRN_.getForce(force_MFAC);
                }

                float force_ctrl = LRN_.update(cmd_msg_.force,force_msg_.data,cmd_msg_.flag,F_cmd,F_cmd_last,cmd_msg_.Tsta,cmd_msg_.Trise,cmd_msg_.Tfall,cmd_msg_.Fmax,Mode_);
                ctrl_msg_.T =-force_ctrl*MOTOR_OUT_RADIUS/1000;

                // 根据反馈的保护
                if (force_msg_.data > 180)
                    ctrl_msg_.T = 0;
                if (force_msg_.data <= 2 && ctrl_msg_.T > 0)  //防止过渡放线
                    ctrl_msg_.T = 0;

                const float T_max = 50;
                if (ctrl_msg_.T > 24) // 力矩限制保护
                        ctrl_msg_.T = 24;
                if (ctrl_msg_.T < -T_max)
                        ctrl_msg_.T = -T_max;

                break;
            }

            case 10:  // 学习放线,位置控制
            {
                ctrl_msg_.T = 0;
                ctrl_msg_.K_P = 0.2;
                ctrl_msg_.K_W = 3;

                // 根据上个周期力误差的最大(8个数据点之后的数值),修正这个周期
               if (cmd_msg_.flag - flag_fight_>8){

                  if (force_msg_.data< 0.5) force_msg_.data=-4;
                  float err_force_=force_msg_.data -cmd_msg_.force;
                  if (force_err_max_<err_force_) force_err_max_= err_force_;
             }

                if( mode_last_!=10 ){

                    // 当误差小于一定数值时不再修正
                    if (force_err_max_<3 && force_err_max_>-2 ){}
                    else{ errsum=errsum+force_err_max_;}


                    pos_change_=pos_change_+ (force_err_max_) * 0.007 + errsum * 0.002;

//                    ROS_INFO_STREAM("errsum_=="<<errsum<<name_<<"---pos_chang"<< pos_change_<<"  force_err_max_=="<<force_err_max_);

                    if (pos_change_ > 2.5) pos_change_ = 2.5 ;  //防线
                    if (pos_change_ < -1) pos_change_ = -1 ;
                    force_err_max_last=force_err_max_;
                    force_err_max_=-10;

                }

                float numf = cmd_msg_.flag-flag_fight_;  // 在15个控制信号完成收线
                if (numf>10) numf=10;
                ctrl_msg_.Pos = pos_fight_ + pos_change_ *(numf)/10;



                break;
            }

            case 11:  // 放线+手动pos_change2_
            {
                ctrl_msg_.T = 0;
                ctrl_msg_.K_P = 0.2;
                ctrl_msg_.K_W = 3;

                float pos_change2_ = cmd_msg_.kp;

                float numf = cmd_msg_.flag-flag_fight_;
                if (numf>15) numf=15;
                ctrl_msg_.Pos = pos_fight_ + pos_change2_ *(numf)/15;
                break;
            }

            case 12:  // 维持当前位置
            {
                ctrl_msg_.T = 0;
                ctrl_msg_.K_P = 0.2;
                ctrl_msg_.K_W = 3;
                ctrl_msg_.Pos = sensor_msg_.Pos ;

                break;
            }

            case 13:
            {
                // Feedforward 前馈 + 力PID
                //电机力矩控制模式
                ctrl_msg_.K_P = 0;
                ctrl_msg_.K_W = 0;

                //float force_ctrl =Feedforward_.update(cmd_msg_.flag,F_cmd);  // F_cmd 是前馈量
                FD_PID_.setParam(0.8,0,0.01);
                float force_ctrl=FD_PID_.update(cmd_msg_.force,force_msg_.data,cmd_msg_.flag,F_cmd);
                ctrl_msg_.T =-force_ctrl*MOTOR_OUT_RADIUS/1000;

                // 电机的力保护
                // 根据反馈的保护
                if (force_msg_.data > 170)
                    ctrl_msg_.T = 0;
                // 力矩限制保护
                const float T_max = 15;
                if (ctrl_msg_.T > 1.5)
                    ctrl_msg_.T = 1.5;
                else if (ctrl_msg_.T < -T_max)
                    ctrl_msg_.T = -T_max;
                break;

            }


            case 14:  // 前馈+位置PID
            {
                // 力矩模式
                ctrl_msg_.K_P = 0;
                ctrl_msg_.K_W = 0;

                // 前馈+PID 控制
                ForwardPID_.setParam(0.02,0.001,0);  // PID 参数
                if (cmd_msg_.flag>400) cmd_msg_.flag=400;  // 防止超出数组大小
                float T_ctrl = ForwardPID_.update(Pos_cmd[cmd_msg_.flag],sensor_msg_.Pos,cmd_msg_.flag,F_cmd,cmd_msg_.Tsta,cmd_msg_.Trise,cmd_msg_.Tfall,cmd_msg_.Fmax);
                ctrl_msg_.T =-F_cmd[cmd_msg_.flag]*MOTOR_OUT_RADIUS/1000-T_ctrl;

                // 根据反馈的保护
                if (force_msg_.data > 150)
                    ctrl_msg_.T = 0;
                // 力矩限制保护
                const float T_max = 15;
                if (ctrl_msg_.T > 1.5)
                    ctrl_msg_.T = 1.5;
                else if (ctrl_msg_.T < -T_max)
                    ctrl_msg_.T = -T_max;
                break;

            }


            case 15:  // 位置控制 ！！！！将力数据传给位置，所以 力峰值不能过大：  0.5以下
            {
                ctrl_msg_.T = 0;
                ctrl_msg_.K_P = 0.2;
                ctrl_msg_.K_W = 3;

                ctrl_msg_.Pos = pos_now - cmd_msg_.force;
                break;
            }

            case 16:  // 力矩模式
            {
                ctrl_msg_.K_P = 0;
                ctrl_msg_.K_W = 0;
                ctrl_msg_.T = -cmd_msg_.force;
                break;

            }


            
        }

       ctrl_pub.publish(ctrl_msg_);
       mode_last_=cmd_msg_.mode;

    }
}