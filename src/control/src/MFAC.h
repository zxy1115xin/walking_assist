#ifndef SRC_MFAC_H
#define SRC_MFAC_H
#include <math.h>
#include <iostream>
#include <ros/ros.h>

using namespace std;

class MFAC
{
public:
    MFAC();
    ~MFAC();
    void set_epsilon(float epsilon);
    void set_Rho(float (&Rho)[20]);
    void setParam(float Eta,float Mu,float Lambda,int ny,int nx);
    void init_Phi(float (&Phi0)[20]);
    float update(float force_real,float force_pre);
    void getPhi(float (&Phi)[20]);
private:
    int ny_;
    int nx_;
    float Phi0_[20];
    float epsilon_;
    float Eta_;
    float Mu_;
    float Rho_[20];
    float Lambda_;

    float force_real_last;
    float modify_f_last;
    float DH[20];
    float Phi_[20];
};


#endif //SRC_MFAC_H
