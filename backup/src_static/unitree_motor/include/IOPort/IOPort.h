#ifndef z1_lib_IOPORT_H
#define z1_lib_IOPORT_H

#include <stdint.h>
#include <unistd.h>
#include <vector>
#include "unitreeMotor/unitreeMotor.h"
#include <string>
enum class BlockYN{
    YES,
    NO
};

struct FsmCartesianCommand
{
    float x;
    float y;
    float z;
    float rx;
    float ry;
    float rz;

    FsmCartesianCommand(){
        setZero();
    }
    void setZero(){
        x=0;
        y=0;
        z=0;
        rx=0;
        ry=0;
        rz=0;
    }
};

struct FsmJointCtrlCommand
{
    float qDes[6];
    FsmJointCtrlCommand(){
        setZero();
    }
    void setZero(){
        for(int i=0;i<6;i++) qDes[i] = 0;
    }
};


#ifndef SDK2
struct FsmToStateCommand
{
    char labelName[30];
};
struct FsmSaveStateCommand
{
    char labelName[30];

};
#endif

#ifdef SDK2
struct FsmToStateCommand
{
    std::string labelName;
};
struct FsmSaveStateCommand
{
    std::string labelName;
};
#endif

struct sdk1Command
{
    int ToFsm;
    FsmCartesianCommand CartesianCommand;
    FsmSaveStateCommand SaveStateCommand;
    FsmJointCtrlCommand jointCtrlCommand;
    FsmToStateCommand ToStateCommand;
};


struct sdk2Command
{
    int ToFsm;
    FsmCartesianCommand CartesianCommand;
    FsmSaveStateCommand saveStateCommand;
    FsmJointCtrlCommand jointCtrlCommand;
    FsmToStateCommand ToStateCommand; 
};

struct FsmToStateState 
{   
    bool finish;
    FsmToStateState(){
        setZero();
    }
    void setZero(){
        finish = false;
    }

};

struct FsmTrajectoryState 
{   
    bool finish;
    FsmTrajectoryState(){
        setZero();
    }
    void setZero(){
        finish = false;
    }

};

struct sdk2State
{
    int ToFsm;
    FsmToStateState ToStateState;
    FsmTrajectoryState trajectoryState;
};


class IOPort{
public:
    IOPort(BlockYN blockYN, size_t recvLength, size_t timeOutUs){
        resetIO(blockYN, recvLength, timeOutUs);
    }
    virtual ~IOPort(){}
    virtual size_t send(uint8_t *sendMsg, size_t sendLength) = 0;
    virtual size_t recv(uint8_t *recvMsg, size_t recvLength) = 0;
    virtual size_t recv(uint8_t *recvMsg) = 0;
    virtual bool sendRecv(std::vector<MOTOR_send> &sendVec, std::vector<MOTOR_recv> &recvVec) = 0;
    void resetIO(BlockYN blockYN, size_t recvLength, size_t timeOutUs);
protected:
    BlockYN _blockYN = BlockYN::NO;
    size_t _recvLength;
    timeval _timeout;
    timeval _timeoutSaved;
};

inline void IOPort::resetIO(BlockYN blockYN, size_t recvLength, size_t timeOutUs){
    _blockYN = blockYN;
    _recvLength = recvLength;
    _timeout.tv_sec  = timeOutUs / 1000000;
    _timeout.tv_usec = timeOutUs % 1000000;
    _timeoutSaved = _timeout;
}


#endif  // z1_lib_IOPORT_H