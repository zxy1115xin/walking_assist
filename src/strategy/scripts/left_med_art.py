#!/usr/bin/env python
# -*-coding:utf-8-*-

import rospy
from abstract import Strategy
import math


# 测试adapt 代码


class LeftMed_art(Strategy):
    def __init__(self):
        super().__init__()
        self.location = 1
        self.num = 5
        self.sta_index = 0

    def force_curve(self, t):

        if t > 5 and self.Last_t < self.num <= t:  # 判定新周期


            # 1.更新模式
            self.Mode_stance = self.mode_stance  # 在这里更新mode是由于中间突变模式会出现不受控现象，尤其在迭代学习支撑相期间
            self.Mode_fight = self.mode_fight
            self.Mode_other = self.mode_other
            self.Pos = self.pos  # 这里把参数传给KP传出

            # 2. 更新力曲线
            self.gait_T = 120
            if self.adapt_ == 0:
                self.upstart_time = self.T_max * self.gait_T / 100 - self.t_rise  # 辅助力开始相
                self.uprise_time = self.t_rise
                self.upfall_time = self.t_fall
                self.upforce_max = self.F_max

            else:
                if self.location == 2:
                    f_max_1,t_sta_1,t_rise_1,t_fall_1 = self.calculate_f2( self.F_max/2, self.T_max+0.25, self.t_rise, self.t_fall, self.gait_T / 100)
                    self.upstart_time = t_sta_1 * self.gait_T / 100 /100 -t_rise_1 * self.gait_T / 100 /100
                    self.uprise_time = t_rise_1 * self.gait_T / 100 /100
                    self.upfall_time = t_fall_1 * self.gait_T / 100 /100
                    self.upforce_max = f_max_1
                else:
                    f_max_1,t_sta_1,t_rise_1,t_fall_1 = self.calculate_f1( self.F_max/2, self.T_max+0.25, self.t_rise, self.t_fall, self.gait_T / 100)
                    self.upstart_time = t_sta_1 * self.gait_T / 100 /100 -t_rise_1 * self.gait_T / 100 /100
                    self.uprise_time = t_rise_1 * self.gait_T / 100 /100
                    self.upfall_time = t_fall_1 * self.gait_T / 100 /100
                    self.upforce_max = f_max_1

            # 3.其他

            self.Flag = 1
            self.num = t + 3
            self.touch_time = t  # 触地时刻,,t 是窗口执行时间




        self.Last_t = t

        # 辅助力预备预备
        kp = 3
        force_pre = self.pre_force
        T_v = 0.05  # 助力结束后学习持续学习时间
        Fmax = self.upforce_max + force_pre
        Tsta = self.upstart_time
        Trise = (self.upstart_time + self.uprise_time)
        Tfall = (self.upstart_time + self.uprise_time + self.upfall_time)
        touch_time = self.touch_time
        flag = self.Flag
        self.Flag = self.Flag + 1

        if (self.Flag < 5):
            print(["LeftMed_art  :  self.Flag", self.Flag, "Tsta", Tsta, "---Fmax ", Fmax , "Trise", Trise, "Tfall ",Tfall ])
            print(["LeftMed_art  :  t",t, "touch_time", touch_time,'Tsta ',Tsta  ])

        # 助力曲线设计
        if 1:
            mode = self.Mode_stance
            # 支撑相
            if (t <= self.touch_time + self.upstart_time) and (t >= self.touch_time):  # 刚刚触地预紧
                force = force_pre

            elif (t >= self.touch_time + self.upstart_time) and (
                    t < self.touch_time + self.upstart_time + self.uprise_time):

                x = (t - self.touch_time - self.upstart_time)

                t1 = self.uprise_time
                force1 = (4 * self.upforce_max * pow(x,3)) / pow(t1,3) -( 3 * self.upforce_max * pow(x,4) ) / pow(t1,4)
                # self.force_p = self.set_P(t - self.touch_time, self.upstart_time + self.uprise_time,
                #                           self.upstart_time + self.uprise_time + self.upfall_time)
                force = force1 + force_pre

                # force = force_pre + self.upforce_max * math.sin(
                #     3.1415926 / 2 * (t - self.touch_time - self.upstart_time) / (self.uprise_time))

            elif (t >= self.touch_time + self.upstart_time + self.uprise_time) and (
                    t < self.touch_time + self.upstart_time + self.uprise_time + self.upfall_time):
                x = t - self.touch_time - self.upstart_time-self.uprise_time
                t1 = self.upfall_time
                force1 = self.upforce_max - (4 * self.upforce_max * pow(x, 3)) / pow(t1, 3) + (3 * self.upforce_max * pow(x, 4)) / pow(t1, 4)
                # self.force_p = self.set_P(t-self.touch_time, self.upstart_time + self.uprise_time, self.upstart_time + self.uprise_time + self.upfall_time)
                force =  force1 + force_pre

                # force = force_pre + self.upforce_max * math.sin(3.1415926 / 2 * (
                #             t - self.touch_time - self.upstart_time - self.uprise_time + self.upfall_time) / self.upfall_time)

            elif (t >= self.touch_time + self.upstart_time + self.uprise_time + self.upfall_time) and (
                    t < self.touch_time + self.upstart_time + self.uprise_time + self.upfall_time + T_v):  # 刚刚助力结束预紧
                force = force_pre
                self.stance_finsh = 1
            # 支撑相内，助力结束，提前进入放线模式
            else:
                mode = self.Mode_other
                force = force_pre

        else:
            force = force_pre
            mode = self.Mode_stance

        return force, flag, mode, kp, Tsta, Trise, Tfall, Fmax, touch_time


if __name__ == '__main__':
    import os
    file_name = os.path.basename(__file__)
    name = os.path.splitext(file_name)[0]
    rospy.init_node(name)
    LeftMed_art().start_loop(100.0)
    pass
