char        motor_id    #Motor ID【电机ID】
int32       Temp        #Temperature【温度】

float32     T           #The output torque of motor【当前实际电机输出力矩】
float32     W           #The motor shaft speed(without filter)【前实际电机速度（无滤波器）】
float32     LW          #The motor shaft speed(with filter)【当前实际电机速度（有滤波器）】
int32       Acc           #The acceleration of motor shaft【电机转子加速度】
float32     Pos         #The motor shaft position(control board zero fixed)【当前电机位置（主控0点修正，电机关节还是以编码器0点为准）】

float32[3]  gyro        #The data of 6 axis inertial sensor on the control board【电机驱动板6轴传感器数据】
float32[3]  acc
