#include "serialPort/SerialPort.h"

SerialPort::SerialPort
          (const std::string &portName,
                      size_t recvLength,
                      uint32_t baudrate,
                      size_t timeOutUs,
                      BlockYN blockYN,
                      bytesize_t bytesize,
                      parity_t parity,
                      stopbits_t stopbits,
                      flowcontrol_t flowcontrol)
                     :IOPort(blockYN, recvLength, timeOutUs),
                      _portName(portName),
                      _baudrate(baudrate),
                      _bytesize(bytesize),
                      _parity(parity),
                      _stopbits(stopbits),
                      _flowcontrol(flowcontrol) {

    // _timeout.tv_sec  = timeOutUs / 1000000;
    // _timeout.tv_usec = timeOutUs % 1000000;
    // _blockYN = blockYN;
    // _recvLength = recvLength;

    _open();
    _set();
}

SerialPort::~SerialPort(){
    _close();
}

size_t SerialPort::send(uint8_t *sendMsg, size_t sendLength){
    size_t len;
    //len = write(_fd, sendMsg, sendLength);
    //std::cout<<"send: "<<std::endl;
   // for(int i=0;i<sendLength;i++)
    //printf("%x\n",sendMsg[i]);
    //std::cout<<std::endl;
    if(len != sendLength){
        perror("[ERROR] SerialPort::sendMsg failed");
    }
    return len;
}

size_t SerialPort::_nonBlockRecv(uint8_t *recvMsg, size_t readLen){
    size_t receivedLen;
    timeval timeout = _timeout;

    FD_ZERO(&_rSet);
    FD_SET(_fd, &_rSet);
    switch ( select(_fd+1, &_rSet, NULL, NULL, &timeout) ){
    case -1:
        std::cout << "[WARNING] SerialPort::recv, unblock version, receive error" << std::endl;
        tcflush(_fd, TCIOFLUSH);
        return 0;
    case 0:
        std::cout << "[WARNING] SerialPort::recv, unblock version, wait time out" << std::endl;
        tcflush(_fd, TCIOFLUSH);
        return 0;
    default:
        receivedLen = read(_fd, recvMsg, readLen);
//         if(receivedLen != _recvLength){
//             std::cout << "[WARNING] SerialPort::recv, unblock version, received " << receivedLen << " bytes, but not " << _recvLength << " bytes, " << strerror(errno) << std::endl;
//         }
        // tcflush(_fd, TCIOFLUSH);
        return receivedLen;
    }
}

size_t SerialPort::recv(uint8_t *recvMsg){
    return recv(recvMsg, _recvLength);
}

size_t SerialPort::recv(uint8_t *recvMsg, size_t recvLength){
    size_t receivedLen = 0;

    if(_blockYN == BlockYN::NO){
        receivedLen = _nonBlockRecv(recvMsg, recvLength);
        if((receivedLen != recvLength) && (receivedLen != 0)){
            receivedLen += _nonBlockRecv(recvMsg+receivedLen, recvLength-receivedLen);
            if(receivedLen != recvLength){
                std::cout << "[WARNING] SerialPort::recv, unblock version, received " << receivedLen << " bytes, but not " << recvLength << " bytes." << std::endl;
                tcflush(_fd, TCIOFLUSH);
            }
        }
    }
    else if(_blockYN == BlockYN::YES) {
        std::cout << "[STATE] SerialPort start block receiving" << std::endl;
        receivedLen = read(_fd, recvMsg, recvLength);
        tcflush(_fd, TCIOFLUSH);
    }

    return receivedLen;
}

bool SerialPort::sendRecv(uint8_t *sendMsg, uint8_t *recvMsg, size_t sendLength){
    if(send(sendMsg, sendLength) == sendLength){
        if(recv(recvMsg) != _recvLength){
            return false;
        }
    }else{
        return false;
    }

    return true;
}

bool SerialPort::sendRecv(MOTOR_send* sendMsg, MOTOR_recv* recvMsg) {
    if(sendMsg->motorType != recvMsg->motorType) {
        std::cout << "[WARNING] SerialPort::sendRecv. The motorType of sendMsg and recvMsg are different" << std::endl;
    }

    if(sendMsg->motorType == MotorType::A1Go1) {
        resetSerial(recvMsg->hex_len,
                    4800000,
                    20000,
                    BlockYN::NO,
                    bytesize_t::eightbits,
                    parity_t::parity_none,
                    stopbits_t::stopbits_one,
                    flowcontrol_t::flowcontrol_none);
    }
    else if(sendMsg->motorType == MotorType::B1) {
        resetSerial(recvMsg->hex_len,
                    6000000,
                    20000,
                    BlockYN::NO,
                    bytesize_t::eightbits,
                    parity_t::parity_none,
                    stopbits_t::stopbits_one,
                    flowcontrol_t::flowcontrol_none);
    }

    modify_data(sendMsg);
    if(sendRecv((uint8_t*)&sendMsg->motor_send_data, (uint8_t*)&recvMsg->motor_recv_data, sendMsg->hex_len)){
        if(extract_data(recvMsg)){
            return true;
        }
        std::cout << "[WARNING] motor id=" << sendMsg->id << " failed on CRC, data broken" << std::endl;
    }

    std::cout << "[WARNING] motor id=" << sendMsg->id << " does not reply" << std::endl;
    return false;
}

bool SerialPort::sendRecv(std::vector<MOTOR_send> &sendVec, std::vector<MOTOR_recv> &recvVec){
    if(sendVec.size() != recvVec.size()){
        std::cout << "[ERROR] SerialPort::sendRecv, the sizes of sendVec and recvVec are different" << std::endl;
        return false;
    }

    bool commYN = true;
    bool motorCommYN;

    for(size_t i(0); i<sendVec.size(); ++i){
        motorCommYN = sendRecv(&sendVec.at(i), &recvVec.at(i));
        commYN = commYN && motorCommYN;

        // usleep(50000);
    }

    return commYN;
}

void SerialPort::resetSerial(size_t recvLength,
                                uint32_t baudrate,
                                size_t timeOutUs,
                                BlockYN blockYN,
                                bytesize_t bytesize,
                                parity_t parity,
                                stopbits_t stopbits,
                                flowcontrol_t flowcontrol){
    if((_recvLength   != recvLength) ||
        (_baudrate    != baudrate) ||
        (_bytesize    != bytesize) ||
        (_parity      != parity) ||
        (_stopbits    != stopbits) ||
        (_flowcontrol != flowcontrol) ){

std::cout << "[STATE] Reset serial" << std::endl;
        _recvLength  = recvLength;
        _baudrate    = baudrate;
        _bytesize    = bytesize;
        _parity      = parity;
        _stopbits    = stopbits;
        _flowcontrol = flowcontrol;
    }
    _timeout.tv_sec  = timeOutUs / 1000000;
    _timeout.tv_usec = timeOutUs % 1000000;
    _blockYN = blockYN;

    _set();
}


void SerialPort::_close(){
    close(_fd);
}

void SerialPort::_open(){
std::cout << "*********open serial************" << std::endl;
    _fd = open(_portName.c_str(), O_RDWR | O_NOCTTY);

    if (_fd == -1) {
        switch (errno) {
        case EINTR:
        // Recurse because this is a recoverable error.
            _open();
            return;
        case ENFILE:
        case EMFILE:
            THROW (IOException, "Too many file handles open.");
        default:
            THROW (IOException, errno);
        }
    }

}

void SerialPort::_set(){
    termios options;

    if (tcgetattr(_fd, &options) == -1) {
        THROW (IOException, "::tcgetattr");
    }

    options.c_cflag |= (CLOCAL | CREAD);
    options.c_lflag &= (tcflag_t) ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL |
                                    ISIG | IEXTEN); //|ECHOPRT
    options.c_oflag &= ~(OPOST|ONLCR);
    options.c_iflag &= ~(IXON|IXOFF|IXANY);
    options.c_iflag |= IGNPAR;
    options.c_iflag &= ~INPCK;
	options.c_iflag &= ~ICRNL;

    /* set baudrate */
    bool setinBaud = true;
    speed_t baud;

    switch (_baudrate) {
    #ifdef B0
    case 0: baud = B0; break;
    #endif
    #ifdef B50
    case 50: baud = B50; break;
    #endif
    #ifdef B75
    case 75: baud = B75; break;
    #endif
    #ifdef B110
    case 110: baud = B110; break;
    #endif
    #ifdef B134
    case 134: baud = B134; break;
    #endif
    #ifdef B150
    case 150: baud = B150; break;
    #endif
    #ifdef B200
    case 200: baud = B200; break;
    #endif
    #ifdef B300
    case 300: baud = B300; break;
    #endif
    #ifdef B600
    case 600: baud = B600; break;
    #endif
    #ifdef B1200
    case 1200: baud = B1200; break;
    #endif
    #ifdef B1800
    case 1800: baud = B1800; break;
    #endif
    #ifdef B2400
    case 2400: baud = B2400; break;
    #endif
    #ifdef B4800
    case 4800: baud = B4800; break;
    #endif
    #ifdef B7200
    case 7200: baud = B7200; break;
    #endif
    #ifdef B9600
    case 9600: baud = B9600; break;
    #endif
    #ifdef B14400
    case 14400: baud = B14400; break;
    #endif
    #ifdef B19200
    case 19200: baud = B19200; break;
    #endif
    #ifdef B28800
    case 28800: baud = B28800; break;
    #endif
    #ifdef B57600
    case 57600: baud = B57600; break;
    #endif
    #ifdef B76800
    case 76800: baud = B76800; break;
    #endif
    #ifdef B38400
    case 38400: baud = B38400; break;
    #endif
    #ifdef B115200
    case 115200: baud = B115200; break;
    #endif
    #ifdef B128000
    case 128000: baud = B128000; break;
    #endif
    #ifdef B153600
    case 153600: baud = B153600; break;
    #endif
    #ifdef B230400
    case 230400: baud = B230400; break;
    #endif
    #ifdef B256000
    case 256000: baud = B256000; break;
    #endif
    #ifdef B460800
    case 460800: baud = B460800; break;
    #endif
    #ifdef B500000
    case 500000: baud = B500000; break;
    #endif
    #ifdef B576000
    case 576000: baud = B576000; break;
    #endif
    #ifdef B921600
    case 921600: baud = B921600; break;
    #endif
    #ifdef B1000000
    case 1000000: baud = B1000000; break;
    #endif
    #ifdef B1152000
    case 1152000: baud = B1152000; break;
    #endif
    #ifdef B1500000
    case 1500000: baud = B1500000; break;
    #endif
    #ifdef B2000000
    case 2000000: baud = B2000000; break;
    #endif
    #ifdef B2500000
    case 2500000: baud = B2500000; break;
    #endif
    #ifdef B3000000
    case 3000000: baud = B3000000; break;
    #endif
    #ifdef B3500000
    case 3500000: baud = B3500000; break;
    #endif
    #ifdef B4000000
    case 4000000: baud = B4000000; break;
    #endif
    case 4800000:
    case 6000000:
        baud = B38400;  // Linux 不支持原生4.8M波特率，首先设置为原生38400波特率，再分频
        setinBaud = false;
        break;
    default:
        THROW (IOException, "Baudrate error");
    }

    cfsetispeed(&options, baud);
    cfsetospeed(&options, baud);

    /* set char len */
    options.c_cflag &= (tcflag_t) ~CSIZE;
    if (_bytesize == bytesize_t::eightbits)
        options.c_cflag |= CS8;
    else if (_bytesize == bytesize_t::sevenbits)
        options.c_cflag |= CS7;
    else if (_bytesize == bytesize_t::sixbits)
        options.c_cflag |= CS6;
    else if (_bytesize == bytesize_t::fivebits)
        options.c_cflag |= CS5;
    else
        throw std::invalid_argument ("invalid char len");

    /* set stopbits */
    if (_stopbits == stopbits_t::stopbits_one)
        options.c_cflag &= (tcflag_t) ~(CSTOPB);
    else if (_stopbits == stopbits_t::stopbits_one_point_five)
        // ONE POINT FIVE same as TWO.. there is no POSIX support for 1.5
        options.c_cflag |=  (CSTOPB);
    else if (_stopbits == stopbits_t::stopbits_two)
        options.c_cflag |=  (CSTOPB);
    else
        throw std::invalid_argument ("invalid stop bit");

    /* setup parity */
    options.c_iflag &= (tcflag_t) ~(INPCK | ISTRIP);
    if (_parity == parity_t::parity_none) {
        options.c_cflag &= (tcflag_t) ~(PARENB | PARODD);
    } else if (_parity == parity_t::parity_even) {
        options.c_cflag &= (tcflag_t) ~(PARODD);
        options.c_cflag |=  (PARENB);
    } else if (_parity == parity_t::parity_odd) {
        options.c_cflag |=  (PARENB | PARODD);
    }
    else if (_parity == parity_t::parity_mark) {
        options.c_cflag |=  (PARENB | CMSPAR | PARODD);
    }
    else if (_parity == parity_t::parity_space) {
        options.c_cflag |=  (PARENB | CMSPAR);
        options.c_cflag &= (tcflag_t) ~(PARODD);
    }
    else {
        throw std::invalid_argument ("invalid parity");
    }

    /* setup flow control */
    if (_flowcontrol == flowcontrol_t::flowcontrol_none) {
        _xonxoff = false;
        _rtscts = false;
    }
    if (_flowcontrol == flowcontrol_t::flowcontrol_software) {
        _xonxoff = true;
        _rtscts = false;
    }
    if (_flowcontrol == flowcontrol_t::flowcontrol_hardware) {
        _xonxoff = false;
        _rtscts = true;
    }
    // xonxoff
    #ifdef IXANY
    if (_xonxoff)
        options.c_iflag |=  (IXON | IXOFF); //|IXANY)
    else
        options.c_iflag &= (tcflag_t) ~(IXON | IXOFF | IXANY);
    #else
    if (_xonxoff)
        options.c_iflag |=  (IXON | IXOFF);
    else
        options.c_iflag &= (tcflag_t) ~(IXON | IXOFF);
    #endif
    // rtscts
    #ifdef CRTSCTS
    if (_rtscts)
        options.c_cflag |=  (CRTSCTS);
    else
        options.c_cflag &= (unsigned long) ~(CRTSCTS);
    #elif defined CNEW_RTSCTS
    if (_rtscts)
        options.c_cflag |=  (CNEW_RTSCTS);
    else
        options.c_cflag &= (unsigned long) ~(CNEW_RTSCTS);
    #else
        #error "OS Support seems wrong."
    #endif

    /* 阻塞模式接收，select水平触发时代表有足够数据读取，不会阻塞 */
        // options.c_cc[VMIN] = _recvLength;
    /* 实践中发现在miniPC+Ubuntu16.04时出现了阻塞，设置为options.c_cc[VMIN] = 0才解决，但是偶尔出现包收不全的情况 */
    /* 更严重的是在Ubuntu20.04中，设置读78字节，只能读出64字节，原因不明 */
    /* 为了防止阻塞，将串口彻底设置为非阻塞模式，并且当包不全时接收两次 */
    /* 需要注意的是，接收两次需要双倍耗时，对ft232芯片，即从1ms变为2ms */
    options.c_cc[VTIME] = 0;
    options.c_cc[VMIN] = 0;

    /* 写入设置 */
    tcsetattr (_fd, TCSANOW, &options);

    /* 设置低延迟，非标准波特率 */
    serial_struct sc;
    if (-1 == ioctl(_fd, TIOCGSERIAL, &sc)){
        THROW (IOException, errno);
    }
    sc.flags |= ASYNC_LOW_LATENCY;

    if(!setinBaud){
        //根据基波特率修改
        //例如ft232h芯片的基波特率为24M，令custom divisor=5， 24/5=4.8
        sc.flags &= ~ASYNC_SPD_MASK;   // 后添加
        sc.flags |= ASYNC_SPD_CUST;
        sc.custom_divisor = (sc.baud_base/_baudrate);
    }

    if (-1 == ioctl(_fd, TIOCSSERIAL, &sc)){
        THROW (IOException, errno);
    }

    // 清空输入输出缓存
    tcflush(_fd, TCIOFLUSH);

}
