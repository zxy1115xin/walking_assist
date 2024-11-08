#!/usr/bin/env python
# -*-coding:utf-8-*-

import rospy
from std_msgs.msg import Float32
from unitree_motor.msg import Sensor
from abstract import Strategy
import math


class RightLat(Strategy):
    def __init__(self):
        super(RightLat, self).__init__()
        self.numm = 0  # 这是一个样例，代表在子类里面定义自己类变量
        # 初始化
        self.mode_stance = 0
        self.mode_fight = 0
        self.mode_other = 0
        self.pos = 0
        self.Flag = 0  # 周期计数
        self.touch_time = -10
        self.off_time = -10
        self.Last_flag = 0
        self.Mode_stance = 0
        self.Mode_fight = 0
        self.Mode_other = 0
        self.Pos = 0
        return

    def Mode_Callback(self, mode_stance, mode_fight, mode_other,pos_fight):
        self.mode_stance = mode_stance
        self.mode_fight = mode_fight
        self.mode_other = mode_other
        self.pos = pos_fight
        rospy.loginfo(" RightLat param update --> mode_stance=%d,mode_fight=%d \n\t", mode_stance, mode_fight)
        return

    def force_curve(self, t):

        # 判断触地，任务：参数更新
        if self.GRF_R.stance_flg == 1 and self.Last_flag == 0:

            if self.show_index == 1:  # 是否展示参数指令，评价力曲线是否达到期望步态百分比
                FmaX_time=(self.F_start +self.F_rise )*100/self.Flag
                rospy.loginfo(" Right --> Tstance= %f; Tfmax=%f ; Finsh = %d  \t",self.stance_time/100,FmaX_time,self.stance_finsh )

            self.touch_time = t  # 触地时刻
            self.Mode_stance = self.mode_stance  # 在这里更新mode是由于中间突变模式会出现不受控现象，尤其在迭代学习支撑相期间
            self.Mode_fight = self.mode_fight
            self.Mode_other = self.mode_other
            self.Pos = self.pos  # 这里把参数传给KP传出

            if self.stance_num_last2 > 0:
                self.F_start = 0.4 * self.stance_TT /100  # 辅助力开始相位
            start_time = self.F_start  # 这里更新力曲线
            rise_time = self.F_rise
            fall_time = self.F_fall
            force_max = self.F_max

            self.Flag = 1  # 计数更新

        # 判断离地时刻
        if self.GRF_R.stance_flg == 0 and self.Last_flag == 1:
            self.off_time = t
            self.stance_num_last2 = self.stance_num_last
            self.stance_num_last = self.stance_num
            self.stance_num = self.Flag   # 记录支撑相时间
            self.stance_TT = 1/3 * (self.stance_num_last2 + self.stance_num_last + self.stance_num)


        # 辅助力预备预备
        self.Last_flag = self.GRF_R.stance_flg
        kp = 10
        mode = 0
        force = 0.0
        force_pre = self.pre_force
        # 传参
        T_v = 0.05  # 助力结束后学习持续学习时间
        Fmax = force_max + force_pre
        Tsta = start_time * 100  # 和采样频率
        Trise = (start_time + rise_time) * 100
        Tfall = (start_time + rise_time + fall_time) * 100
        flag = self.Flag
        self.Flag = self.Flag + 1
        if self.Mode_fight == 11:
            kp = self.Pos  # 将位置参数传给kp

        # 助力曲线设计
        if self.GRF_R.stance_flg == 1:  # 支撑相
            mode = self.Mode_stance

            if (t <= self.touch_time + start_time) and (t >= self.touch_time):  # 刚刚触地预紧
                kp = 10
                force = force_pre
            elif (t >= self.touch_time + start_time) and (t < self.touch_time + start_time + rise_time):
                kp = 10
                force = 0
                force = force_max * math.sin(math.pi / rise_time / 2 * (t - self.touch_time - start_time)) + force_pre
            elif (t >= self.touch_time + start_time + rise_time) and (
                    t < self.touch_time + start_time + rise_time + fall_time):
                kp = 10
                force = force_max * math.sin(
                    math.pi / fall_time / 2 * (t - self.touch_time - start_time - rise_time) + math.pi / 2) + force_pre
            elif (t >= self.touch_time + start_time + rise_time + fall_time) and (
                    t < self.touch_time + start_time + rise_time + fall_time + T_v):  # 刚刚助力结束预紧
                force = force_pre

            else:
                mode = self.Mode_fight
                force = force_pre

        elif self.GRF_R.stance_flg == 0 and flag > 30:  # 如果腾空相时间超过0.5 切换为other模式
            force = force_pre
            if t < self.off_time + 0.5:
                mode = self.Mode_fight
            else:
                mode = self.Mode_other

        else:
            force = force_pre
            mode = self.Mode_other

        return force, flag, mode, kp, Tsta, Trise, Tfall, Fmax

if __name__ == '__main__':
    import os
    file_name = os.path.basename(__file__)
    name = os.path.splitext(file_name)[0]
    rospy.init_node(name)
    RightLat().start_loop(100.0)
    pass
