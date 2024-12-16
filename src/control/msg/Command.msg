int32 mode  #mode 1 力位控制 mode 2  速度模式 mode 3 位置模式
float32 force
float32 kp    #刚度 N/mm 或 PID的比例
float32 ki    
float32 kd   
int32 flag    #标志触地
double  Tsta    #助力开始时刻
double Trise    #助力结束时刻
double  Tfall    #助力开始时刻
float32 Fmax    #助力结束时刻
double touch_time