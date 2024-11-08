#include "MFAC.h"

MFAC::MFAC() {
    epsilon_=1e-12;
}

MFAC::~MFAC() {}

void MFAC::set_epsilon(float  epsilon) {
    epsilon_=epsilon;
}

void MFAC::setParam(float  Eta, float  Mu, float  Lambda, int ny,int nx) {


    if (Eta>0 & Eta<=2)Eta_=Eta; // 取值范围（0,2]
    else if (Eta<=0){
        Eta_=0.0001;
       // ROS_INFO_STREAM("The range of Eta is （0,2], please enter again");
    }
    else{
        Eta_=2;
       // ROS_INFO_STREAM("The range of Eta is （0,2], please enter again");
    }

    Mu_=Mu;   //大于0
    Lambda_=Lambda;  //大于0
    nx_=nx;  // 小于10 系统伪阶数
    ny_=ny;  // 小于10
    return;
}

void MFAC::set_Rho(float(&Rho)[20]) {

    for(int a=0;a<20;a++){
        Rho_[a]=Rho[a];
    }
}

void MFAC::init_Phi(float(&Phi0)[20]){
    for(int a=0;a<ny_+nx_;a++){
        Phi_[a]=Phi0[a];
        Phi0_[a]=Phi0[a];
    }
    return;
}

void MFAC::getPhi(float(&Phi)[20]) {

    for(int a=0;a<20;a++){
        Phi[a]=Phi_[a];
    }
}


float MFAC::update( float force_real,float force_pre) {

    // 数据初始化
    float Square_DH=0,Square_Phi=0,Dph_=0,modify_1=0,modify_2=0; // 每次调用都重置
    float phi[20];



    //计算 DH & Square_DH
    for(int a=0;a<ny_+nx_;a++) // y部分
    {
        Square_DH+=DH[a]*DH[a];
        Dph_+=Phi_[a]*DH[a];
    }

    // 控制率更新
    for (int a=0;a<ny_+nx_;a++)  // 计算Phi_
    {
        Phi_[a];
        Phi_[a]=Phi_[a]+Eta_*DH[a]*(force_real-force_real_last-Dph_)/(Mu_+Square_DH);
        Square_Phi+=Phi_[a]*Phi_[a];
    }
    if ( Square_Phi<epsilon_  | signbit(Phi_[ny_])!= signbit(Phi0_[ny_]) )  //防止趋于0
    {
        for(int a=0;a<ny_+nx_;a++){
            Phi_[a]=Phi0_[a];
        }
    }

    // 控制更新

    modify_1+=Phi_[ny_]*Rho_[0]*Phi_[0]*(force_real-force_real_last);
    for (int a=0;a<ny_;a++)
    {
        modify_1+=Phi_[ny_]*Rho_[a]*Phi_[a+1]*DH[a];
    }

    for(int a=ny_;a<ny_+nx_-1;a++)
    {
        modify_2+=Phi_[ny_]*Rho_[a]*Phi_[a+1]*DH[a];
    }

    float modify_f = modify_f_last+(Rho_[ny_]*Phi_[ny_]*(force_pre-force_real)-modify_1-modify_2)/(Lambda_+Phi_[ny_]*Phi_[ny_]);


    // 数据更新
    float DH_old[20];
    for (int a=0;a<ny_+nx_;a++)DH_old[a]=DH[a];
    for (int a=1;a<ny_+nx_;a++)DH[a]=DH_old[a-1];
    DH[0]=force_real-force_real_last;
    DH[ny_]=modify_f-modify_f_last;

    modify_f_last=modify_f;
    force_real_last=force_real;

    return modify_f;

}
