#!/usr/bin/env python
# -*-coding:utf-8-*-

import rospy
from abstract import Strategy
import math


class LeftMed(Strategy):
    def __init__(self):
        super(LeftMed, self).__init__()
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
        self.Pos = 0  # 腾空相放线
        return

    def Mode_Callback(self, mode_stance, mode_fight, mode_other,pos_fight):
        self.mode_stance = mode_stance
        self.mode_fight = mode_fight
        self.mode_other = mode_other
        self.pos = pos_fight
        rospy.loginfo(" LeftMed param update --> mode_stance=%d,mode_fight=%d \n\t", mode_stance, mode_fight)
        return

    def force_curve(self, t):

        # 判断触地，任务：参数更新
        if self.GRF_L.stance_flg == 1 and self.Last_flag == 0:

            # 助力曲线时间判定
            if self.show_index == 1:  # 是否展示参数指令，评价力曲线是否达到期望步态百分比
                FmaX_time=(self.F_start +self.F_rise )*100/self.Flag # 支撑相时间 ，支撑相占比，是否完成支撑助力曲线
                rospy.loginfo(" Left --> Tstance= %f; Tfmax=%f ; Finsh = %d  \t",self.stance_time/100,FmaX_time,self.stance_finsh )

            # 参数在触地阶段更新： 模式+力曲线+其他参数
            #更新模式
            self.touch_time = t  # 触地时刻
            self.Mode_stance = self.mode_stance  # 在这里更新mode是由于中间突变模式会出现不受控现象，尤其在迭代学习支撑相期间
            self.Mode_fight = self.mode_fight
            self.Mode_other = self.mode_other
            self.Pos = self.pos  # 这里把参数传给KP传出
            # 更新力曲线
            if self.stance_num_last2 > 0: # 助力开始时间确定
                self.F_start = 0.35 * self.stance_TT /100  # 辅助力开始相位
            start_time = self.F_start
            rise_time = self.F_rise
            fall_time = self.F_fall
            force_max = self.F_max
            # 其他
            self.stance_finsh = 0
            self.Flag = 1  # 计数更新

            # 判断离地时刻
        if self.GRF_L.stance_flg == 0 and self.Last_flag == 1:
            self.off_time = t
            self.stance_num_last2 = self.stance_num_last
            self.stance_num_last = self.stance_num
            self.stance_num = self.Flag   # 记录支撑相时间
            self.stance_TT = 1/3 * (self.stance_num_last2 + self.stance_num_last + self.stance_num)

        # 辅助力预备预备
        self.Last_flag = self.GRF_L.stance_flg
        kp = 10
        mode = 0
        force = 0.0
        force_pre = self.pre_force
        # 传参
        T_v = 0.05  # 助力结束后学习持续学习时间
        Fmax = force_max + force_pre
        Tsta = start_time * 100
        Trise = (start_time + rise_time) * 100
        Tfall = (start_time + rise_time + fall_time) * 100
        flag = self.Flag
        self.Flag = self.Flag + 1
        if self.Mode_fight == 11:
            kp = self.Pos  # 将位置参数传给kp

        # 助力曲线设计

        #  正常步态下，支撑相和摆动相助力
        if self.GRF_L.stance_flg == 1:
            mode = self.Mode_stance
            # 支撑相
            if (t <= self.touch_time + start_time) and (t >= self.touch_time):  # 刚刚触地预紧
                force = force_pre

            elif (t >= self.touch_time + start_time) and (t < self.touch_time + start_time + rise_time):
                x = (t - self.touch_time - start_time)
                t1 = rise_time
                force = (4 * force_max * pow(x,3)) / pow(t1,3) -( 3 * force_max * pow(x,4) ) / pow(t1,4) + force_pre

            elif (t >= self.touch_time + start_time + rise_time) and (t < self.touch_time + start_time + rise_time + fall_time):
                x = (t - self.touch_time - start_time-rise_time)
                t1 = fall_time
                force =force_max - (4 * force_max * pow(x, 3)) / pow(t1, 3) + (3 * force_max * pow(x, 4)) / pow(t1, 4) + force_pre

            elif (t >= self.touch_time + start_time + rise_time + fall_time) and (
                    t < self.touch_time + start_time + rise_time + fall_time + T_v):  # 刚刚助力结束预紧
                force = force_pre
                self.stance_finsh = 1
            # 腾空相内，助力结束，进入放线模式
            else:
                mode = self.Mode_fight
                force = force_pre

        # 摆动相
        elif self.GRF_L.stance_flg == 0 and flag > 30:
            force = force_pre
            if t < self.off_time + 0.5: # 摆动相持续时间是0.5s
                mode = self.Mode_fight
            else:
                mode = self.Mode_other

        # 其他未在elif中考虑的情况
        else:
            force = force_pre
            mode = self.Mode_other

        return force, flag,  mode, kp, Tsta, Trise, Tfall, Fmax


if __name__ == '__main__':
    import os
    file_name = os.path.basename(__file__)
    name = os.path.splitext(file_name)[0]
    rospy.init_node(name)
    LeftMed().start_loop(100.0)
    pass
