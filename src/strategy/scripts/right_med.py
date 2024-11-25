#!/usr/bin/env python
# -*-coding:utf-8-*-

import rospy
from abstract import Strategy
import math


class RightMed(Strategy):
    def __init__(self):
        super().__init__()
        self.numm = 0  # 这是一个样例，代表在子类里面定义自己类变量
        # 初始化


        # self.touch_time = -10
        # self.off_time = -10
        # self.Last_flag = 0
        # self.Mode_stance = 0
        # self.Mode_fight = 0
        # self.Mode_other = 0
        # self.Pos = 0  # 腾空相放线
        # self.upstart_time = 0
        # self.uprise_time = 0
        # self.upfall_time = 0
        # self.upforce_max = 0
        # self.stance_num = 0
        # self.gait_num_last2 = 0
        # self.gait_num_last = 0
        # self.gait_num = 0
        # self.t_start = 0



    # def force_curve(self, t):Number of plugins loaded:
    #
    #     # 判断触地，任务：参数更新
    #     if self.GRF.stance_flg == 1 and self.Last_flag == 0:
    #
    #         # 助力曲线时间判定
    #         if self.show_index == 1:  # 是否展示参数指令，评价力曲线是否达到期望步态百分比
    #             FmaX_time = self.T_max * 100 / self.Flag + 0.15  # 开始时刻，支撑相占比，是否完成支撑助力曲线
    #             rospy.loginfo(" Right med--> Tfmax = %f ; Finsh = %d  \t",  FmaX_time, self.stance_finsh)
    #
    #         # 参数在触地阶段更新： 模式+力曲线+其他参数
    #         # 1.更新模式Number of plugins loaded:
    #         self.touch_time = t  # 触地时刻
    #         self.Mode_stance = self.mode_stance  # 在这里更新mode是由于中间突变模式会出现不受控现象，尤其在迭代学习支撑相期间
    #         self.Mode_fight = self.mode_fight
    #         self.Mode_other = self.mode_other
    #         self.Pos = self.pos  # 这里把参数传给KP传出
    #
    #         # 2. 更新力曲线
    #         if self.Flag > 70:
    #             self.gait_num_last2 = self.gait_num_last
    #             self.gait_num_last = self.gait_num
    #             self.gait_num = self.Flag  # 记录支撑相时间
    #             self.gait_T = 1 / 3 * (self.gait_num_last2 + self.gait_num_last +  self.gait_num)
    #
    #         if self.gait_num_last2 > 0:  # 助力开始时间确定
    #             self.t_start = self.T_max  * self.gait_T / 100 - self.t_rise # 辅助力开始相位
    #         else:
    #             self.t_start = 0.2
    #
    #         self.upstart_time = self.t_start
    #         self.uprise_time = self.t_rise
    #         self.upfall_time = self.t_fall
    #         self.upforce_max = self.F_max
    #
    #         # 3.其他
    #         self.stance_finsh = 0
    #         self.Flag = 1  # 计数更新
    #
    #         # 判断离地时刻
    #     if self.GRF.stance_flg == 0 and self.Last_flag == 1:
    #         self.off_time = t  # 记录支撑相结束时刻
    #
    #
    #     # 辅助力预备预备
    #     self.Last_flag = self.GRF.stance_flg
    #     kp = 10
    #     force_pre = self.pre_force
    #     # 传参
    #     T_v = 0.05  # 助力结束后学习持续学习时间
    #     Fmax = self.upforce_max + force_pre
    #     Tsta = self.upstart_time * 100
    #     Trise = (self.upstart_time + self.uprise_time) * 100
    #     Tfall = (self.upstart_time + self.uprise_time + self.upfall_time) * 100
    #     flag = self.Flag
    #     self.Flag = self.Flag + 1
    #     if self.Mode_fight == 11:
    #         kp = self.Pos  # 将位置参数传给kp
    #
    #     # 助力曲线设计
    #
    #     #  正常步态下，支撑相和摆动相助力
    #     if self.GRF.stance_flg == 1:  # 支撑相
    #         mode = self.Mode_stance
    #         # 支撑相
    #         if (t <= self.touch_time + self.upstart_time) and (t >= self.touch_time):  # 刚刚触地预紧
    #             force = force_pre
    #
    #         elif (t >= self.touch_time + self.upstart_time) and (t < self.touch_time + self.upstart_time + self.uprise_time):
    #             # x = (t - self.touch_time - self.upstart_time)
    #             # t1 = self.uprise_time
    #             # force1 = (4 * self.upforce_max * pow(x,3)) / pow(t1,3) -( 3 * self.upforce_max * pow(x,4) ) / pow(t1,4)
    #             # self.force_p = self.set_P(t - self.touch_time, self.upstart_time + self.uprise_time,
    #             #                           self.upstart_time + self.uprise_time + self.upfall_time)
    #             # force =  self.force_p * force1 + force_pre
    #             force = force_pre + self.upforce_max * math.sin(3.1415926/2 * (t - self.touch_time - self.upstart_time) / (self.uprise_time))
    #
    #         elif (t >= self.touch_time + self.upstart_time + self.uprise_time) and (t < self.touch_time + self.upstart_time + self.uprise_time + self.upfall_time):
    #             # x = t - self.touch_time - self.upstart_time-self.uprise_time
    #             # t1 = self.upfall_time
    #             # force1 = self.upforce_max - (4 * self.upforce_max * pow(x, 3)) / pow(t1, 3) + (3 * self.upforce_max * pow(x, 4)) / pow(t1, 4)
    #             # self.force_p = self.set_P(t-self.touch_time, self.upstart_time + self.uprise_time, self.upstart_time + self.uprise_time + self.upfall_time)
    #             # force =  self.force_p * force1 + force_pre
    #             force = force_pre + self.upforce_max * math.sin(3.1415926/2 * (t - self.touch_time - self.upstart_time - self.uprise_time + self.upfall_time) / self.upfall_time)
    #
    #         elif (t >= self.touch_time + self.upstart_time + self.uprise_time + self.upfall_time) and (
    #                 t < self.touch_time + self.upstart_time + self.uprise_time + self.upfall_time + T_v):  # 刚刚助力结束预紧
    #             force = force_pre
    #             self.stance_finsh = 1
    #         # 支撑相内，助力结束，提前进入放线模式
    #         else:
    #             mode = self.Mode_fight
    #             force = force_pre
    #
    #     # 摆动相
    #     elif self.GRF.stance_flg == 0 and flag > 30:
    #         force = force_pre
    #         if t < self.off_time + 0.5: # 摆动相持续时间是0.5s
    #             mode = self.Mode_fight
    #         else:
    #             mode = self.Mode_other
    #
    #     # 其他未在elif中考虑的情况
    #     else:
    #         force = force_pre
    #         mode = self.Mode_other
    #
    #     return force, flag,  mode, kp, Tsta, Trise, Tfall, Fmax


if __name__ == '__main__':
    import os
    file_name = os.path.basename(__file__)
    name = os.path.splitext(file_name)[0]
    rospy.init_node(name)
    RightMed().start_loop(100.0)
    pass
