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
        self.num = 5
        return

    def Mode_Callback(self, mode_stance, mode_fight, mode_other,pos_fight):
        self.mode_stance = mode_stance
        self.mode_fight = mode_fight
        self.mode_other = mode_other
        self.pos = pos_fight
        rospy.loginfo(" RightLat param update --> mode_stance=%d,mode_fight=%d \n\t", mode_stance, mode_fight)
        return

    def force_curve(self, t):

        if t > 5 and self.Last_t < self.num <= t:
            # t 是窗口执行时间
            self.Flag = 1
            self.num = self.num + 5
            self.touch_time = t  # 触地时刻
            self.Mode_stance = self.mode_stance  # 在这里更新mode是由于中间突变模式会出现不受控现象，尤其在迭代学习支撑相期间
            self.Mode_other = self.mode_other

        self.Last_t = t

        # 预备
        kp = 3
        mode = 0
        # 时间
        start_time = self.F_start  # 从触地到开始助力时间
        rise_time = self.F_rise
        fall_time = self.F_fall
        T_v = 0.05  # 助力结束后学习持续学习时间
        # 力
        force = 0.0
        force_max = self.F_max
        force_pre = self.pre_force
        # 传参
        Fmax = force_max + force_pre
        Tsta = start_time * 100
        Trise = (start_time + rise_time) * 100
        Tfall = (start_time + rise_time + fall_time) * 100
        flag = self.Flag
        self.Flag = self.Flag + 1

        # 助力曲线设计
        if 1:

            mode = self.Mode_stance

            if (t <= self.touch_time + start_time) and (t >= self.touch_time):  # 刚刚触地预紧
                force = force_pre

            elif (t >= self.touch_time + start_time) and (t < self.touch_time + start_time + rise_time):
                force = force_max * math.sin(math.pi / rise_time / 2 * (t - self.touch_time - start_time)) + force_pre

            elif (t >= self.touch_time + start_time + rise_time) and (
                    t < self.touch_time + start_time + rise_time + fall_time):
                force = force_max * math.sin(
                    math.pi / fall_time / 2 * (t - self.touch_time - start_time - rise_time) + math.pi / 2) + force_pre

            elif (t >= self.touch_time + start_time + rise_time + fall_time) and (
                    t < self.touch_time + start_time + rise_time + fall_time + T_v):  # 刚刚助力结束预紧
                force = force_pre

            else:
                mode =  self.Mode_other
                force = force_pre

        else:
            force = force_pre
            mode = self.Mode_other

        return force, flag,  mode, kp, Tsta, Trise, Tfall, Fmax

if __name__ == '__main__':
    import os
    file_name = os.path.basename(__file__)
    name = os.path.splitext(file_name)[0]
    rospy.init_node(name)
    RightLat().start_loop(100.0)
    pass
