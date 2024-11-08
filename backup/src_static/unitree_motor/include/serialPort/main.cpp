#include "serialPort/SerialPort.h"
#include "unitreeMotor/unitreeMotor.h"
#include "time/timeMarker.h"

#include <vector>


/* direct send receive */
// int main(){
//     MOTOR_send cmd;
//     MOTOR_recv state;
//     SerialPort serialPort("/dev/ttyUSB0");

//     cmd.id = 2;
//     cmd.mode = 0x05;

//     modify_data(&cmd);
//     serialPort.sendRecv((uint8_t*)&cmd.motor_send_data, (uint8_t*)&state.motor_recv_data, cmd.hex_len);
//     extract_data(&state);

//     return 0;
// }

/* motor vector send receive */
int main(){
    std::vector<MOTOR_send*> sendVec;
    std::vector<MOTOR_recv*> recvVec;

    for(int i(0); i<1; ++i){
        sendVec.push_back(new MOTOR_send);
        recvVec.push_back(new MOTOR_recv);
    }

    sendVec.at(0)->id = 0;
    sendVec.at(0)->mode = 5;

    // sendVec.at(1)->id = 1;
    // sendVec.at(1)->mode = 5;

    // sendVec.at(2)->id = 2;
    // sendVec.at(2)->mode = 5;

    long long pastTime = getSystemTime();
    SerialPort serialPort("/dev/ttyUSB0");
std::cout << "setting cost time: " << getSystemTime() - pastTime << std::endl;

    for(int i(0); i<sendVec.size(); ++i){
        pastTime = getSystemTime();
        serialPort.sendRecv(sendVec.at(i), recvVec.at(i));
        std::cout << "cost time: " << getSystemTime() - pastTime << std::endl;
    }

    return 0;
}