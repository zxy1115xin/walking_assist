#!/usr/bin/env python
# -*-coding:utf-8-*-

import rospy
from rospy import Publisher
from std_msgs.msg import Float32
from unitree_motor.msg import Sensor
from control.msg import Command
import sys, os
from strategy.msg import Fgrf
import math
from sympy import symbols, sympify, lambdify
import sympy as sp
import numpy as np


# import joblib
# from tensorflow.keras.models import load_model


class Strategy:

    def __init__(self):

        file_name = os.path.basename(sys.modules[self.__module__].__file__)
        name = os.path.splitext(file_name)[0]

        self.location = None

        # 参数设计
        self.pre_force = rospy.get_param("~force_pre")  # 获取参数
        self.show_index = 1
        self.server_flag = 0

        self.mode_stance = 0
        self.mode_fight = 0
        self.mode_other = 0
        self.Mode_stance = 0
        self.Mode_fight = 0
        self.Mode_other = 0
        self.pos = 0
        self.adapt_ = 0

        self.F_max = 0  # 辅助力峰值
        self.T_max = 0  # 辅助力峰值时刻占步态的百分比：这里要考虑触地判定延迟大概有20~25ms
        self.t_rise = 0
        self.t_fall = 0
        self.t_start = 0

        self.upstart_time_ = 0
        self.uprise_time_ = 0
        self.upfall_time_ = 0
        self.upforce_max_ = 0

        self.Flag = 0  # 周期计数
        self.touch_time = -10
        self.off_time = -10
        self.Last_flag = 0

        self.Pos = 0  # 腾空相放线
        self.upstart_time = 0
        self.uprise_time = 0
        self.upfall_time = 0
        self.upforce_max = 0
        self.stance_num = 0
        self.gait_num_last2 = 0
        self.gait_num_last = 0
        self.gait_num = 0
        self.gait_T = 100
        self.gait_T_last = 100

        self.update_n = 1  # adapt 降低更新频率

        # 定义发布 “指令” command
        self.cmd_pub = rospy.Publisher(name + '_cmd', Command, queue_size=1000)
        self.cmd_msg = Command()
        # 定义地反力
        self.GRF = Fgrf()

        # self.human_data = {}
        # self.F1_func = {}
        # self.F2_func = {}

    def get_param(self, input_data, output_data):

        self.input_data = input_data
        self.output_data = output_data

        return

    def find_closest_row(self, input_array):
        distances = np.linalg.norm(self.input_data - np.array(input_array), axis=1)
        closest_row_index = np.argmin(distances)
        return self.output_data[closest_row_index]

    def get_model(self, input_scaler, output_scaler, trained_model):

        self.input_scaler = input_scaler
        self.output_scaler = output_scaler
        self.trained_model = trained_model
        return

    def predict_output(self, input_sample):
        """
        使用训练好的模型进行预测，并将输出四舍五入为整数。

        参数：
        input_sample (list): 输入数据，列表形式，长度与训练模型时一致。

        返回：
        np.ndarray: 预测输出，四舍五入为整数后的值。
        """
        # 对输入数据进行归一化
        input_scaled = self.input_scaler.transform([input_sample])

        # 使用模型预测
        predicted_scaled_output = self.trained_model.predict(input_scaled, verbose=0)

        # 将归一化的输出反归一化
        predicted_output = self.output_scaler.inverse_transform(predicted_scaled_output)

        # 对输出进行四舍五入
        rounded_output = np.round(predicted_output).astype(int)

        return rounded_output

    def get_data(self, human_data, F1_func, F2_func):

        self.human_data = human_data
        self.F1_func = F1_func
        self.F2_func = F2_func
        return

    def calculate_f1(self, fmax, Tmax, t_rise, t_fall, T_gait):
        # 生成辅助力曲线
        t_f = np.linspace(0, T_gait, 100)
        f_assist = np.zeros(100)
        tsta = int(np.round((Tmax - t_rise / T_gait) * 100))
        tmax = int(np.round(Tmax * 100))
        tend = int(np.round((Tmax + t_fall / T_gait) * 100))

        # 上升阶段
        x = t_f[tsta:tmax] - t_f[tsta]
        f_assist[tsta:tmax] = 4 * fmax * (x ** 3) / (t_rise ** 3) - 3 * fmax * (x ** 4) / (t_rise ** 4)

        # 下降阶段
        x = t_f[tmax:tend] - t_f[tmax]
        f_assist[tmax:tend] = fmax - 4 * fmax * (x ** 3) / (t_fall ** 3) + 3 * fmax * (x ** 4) / (t_fall ** 4)

        # 辅助力规划
        tx = np.arange(0, 100, 1)
        flexion_ = self.human_data['flexion_']
        inversion_ = self.human_data['inversion_']
        adduction_ = tx * 0

        Mx_ = 0.05 * f_assist * np.array(self.human_data["M_x_d_"]) / (
                np.array(self.human_data["M_x_d_"]) + np.array(self.human_data["M_y_d_"]))
        My_ = 0.05 * f_assist * np.array(self.human_data["M_y_d_"]) / (
                np.array(self.human_data["M_x_d_"]) + np.array(self.human_data["M_y_d_"]))

        F1_func1 = self.F1_func(flexion_, inversion_, adduction_, Mx_, My_)

        # 输出参数
        f_max_1 = np.max(F1_func1)
        t_sta_1 = np.where(F1_func1 > 1)[0][0]
        t_rise_1 = np.argmax(F1_func1) - t_sta_1
        t_fall_1 = np.where(F1_func1 > 1)[0][-1] - np.argmax(F1_func1)

        # print("f_max_1:", f_max_1)
        # print("t_sta_1:", t_sta_1)
        # print("t_rise_1:", t_rise_1)
        # print("t_fall_1:", t_fall_1)

        return f_max_1, t_sta_1, t_rise_1, t_fall_1

    def calculate_f2(self, fmax, Tmax, t_rise, t_fall, T_gait):
        # 生成辅助力曲线
        t_f = np.linspace(0, T_gait, 100)
        f_assist = np.zeros(100)
        tsta = int(np.round((Tmax - t_rise / T_gait) * 100))
        tmax = int(np.round(Tmax * 100))
        tend = int(np.round((Tmax + t_fall / T_gait) * 100))

        # 上升阶段
        x = t_f[tsta:tmax] - t_f[tsta]
        f_assist[tsta:tmax] = 4 * fmax * (x ** 3) / (t_rise ** 3) - 3 * fmax * (x ** 4) / (t_rise ** 4)

        # 下降阶段
        x = t_f[tmax:tend] - t_f[tmax]
        f_assist[tmax:tend] = fmax - 4 * fmax * (x ** 3) / (t_fall ** 3) + 3 * fmax * (x ** 4) / (t_fall ** 4)

        # 辅助力规划
        tx = np.arange(0, 100, 1)
        flexion_ = self.human_data['flexion_']
        inversion_ = self.human_data['inversion_']
        adduction_ = tx * 0

        Mx_ = 0.05 * f_assist * np.array(self.human_data["M_x_d_"]) / (
                np.array(self.human_data["M_x_d_"]) + np.array(self.human_data["M_y_d_"]))
        My_ = 0.05 * f_assist * np.array(self.human_data["M_y_d_"]) / (
                np.array(self.human_data["M_x_d_"]) + np.array(self.human_data["M_y_d_"]))

        F2_func1 = self.F2_func(flexion_, inversion_, adduction_, Mx_, My_)

        # 输出参数
        f_max_2 = np.max(F2_func1)
        t_sta_2 = np.where(F2_func1 > 1)[0][0]
        t_rise_2 = np.argmax(F2_func1) - t_sta_2
        t_fall_2 = np.where(F2_func1 > 1)[0][-1] - np.argmax(F2_func1)

        return f_max_2, t_sta_2, t_rise_2, t_fall_2

    def GRF_Callback(self, msg):
        self.GRF = msg
        # self.server_flag = 1
        return

    def Mode_Callback(self, mode_stance, mode_fight, mode_other, pos_fight):
        self.mode_stance = mode_stance
        self.mode_fight = mode_fight
        self.mode_other = mode_other
        self.pos = pos_fight
        # rospy.loginfo(" RightMed param update --> mode_stance=%d,mode_fight=%d \n\t", self.mode_stance, self.mode_fight)
        return

    def ParamCallback(self, F_max, T_max, t_rise, t_fall, adapt_):
        self.F_max = F_max  # 辅助力峰值
        self.T_max = T_max  # 辅助力峰值时刻占步态的百分比：这里要考虑触地判定延迟大概有20~25ms
        self.t_rise = t_rise
        self.t_fall = t_fall
        self.adapt_ = adapt_
        return

    def update(self, t):
        force, flag, mode, kp, Tsta, Trise, Tfall, Fmax = self.force_curve(t)
        self.cmd_msg.force = force
        self.cmd_msg.mode = mode
        self.cmd_msg.kp = kp
        self.cmd_msg.flag = flag
        self.cmd_msg.Tsta = Tsta
        self.cmd_msg.Trise = Trise
        self.cmd_msg.Tfall = Tfall
        self.cmd_msg.Fmax = Fmax
        self.cmd_pub.publish(self.cmd_msg)
        return

    def timeCallback(self, event):
        t = (event.current_real - self.time0).to_sec()
        # if self.server_flag == 1:
        self.update(t)
        return

    def start_loop(self, value):
        # 100Hz循环
        self.freq = value
        rospy.Timer(rospy.Duration(1. / self.freq), self.timeCallback)
        self.time0 = rospy.Time().now()
        rospy.spin()
        return

    def force_curve(self, t):

        # 判断触地，任务：参数更新
        if self.GRF.stance_flg == 1 and self.Last_flag == 0:

            # 助力曲线时间判定
            if self.show_index == 1:  # 是否展示参数指令，评价力曲线是否达到期望步态百分比
                FmaX_time = self.T_max * 100 / self.Flag + 0.15  # 开始时刻，支撑相占比，是否完成支撑助力曲线
                print(f"{self.__class__.__name__}")
                rospy.loginfo(" --> Tfmax = %f ; Finsh = %d  \t", FmaX_time, self.stance_finsh)

            # 参数在触地阶段更新： 模式+力曲线+其他参数
            # 1.更新模式
            self.touch_time = t  # 触地时刻
            self.Mode_stance = self.mode_stance  # 在这里更新mode是由于中间突变模式会出现不受控现象，尤其在迭代学习支撑相期间
            self.Mode_fight = self.mode_fight
            self.Mode_other = self.mode_other
            self.Pos = self.pos  # 这里把参数传给KP传出

            # 2. 更新力曲线

            if self.Flag > 70:  # 计算步态周期
                self.gait_num_last2 = self.gait_num_last
                self.gait_num_last = self.gait_num
                self.gait_num = self.Flag  # 记录支撑相时间
                self.gait_T = 1 / 3 * (self.gait_num_last2 + self.gait_num_last + self.gait_num)

            if self.adapt_ == 0:
                self.upstart_time = self.T_max * self.gait_T / 100 - self.t_rise  # 辅助力开始相
                self.uprise_time = self.t_rise
                self.upfall_time = self.t_fall
                self.upforce_max = self.F_max
            else:

                if self.update_n == 1:
                    self.update_n = self.update_n + 1
                    T_delay = 5
                    # input_sample = [34, 50, 60, 150]  # 替换为实际的输入数据
                    input_sample = [self.T_max * 100 + T_delay - self.t_rise / self.gait_T * 100 * 100,
                                    self.T_max * 100 + T_delay,
                                    self.T_max * 100 + T_delay + self.t_fall / self.gait_T * 100 * 100,
                                    self.F_max]  # 替换为实际的输入数据
                    output = self.find_closest_row(input_sample)
                    T_delay = 10
                    if self.location == 2:  # 外侧
                        self.upstart_time = (output[4] - T_delay) * self.gait_T / 100 / 100
                        self.uprise_time = output[5] * self.gait_T / 100 / 100 - self.upstart_time
                        self.upfall_time = output[6] * self.gait_T / 100 / 100 - self.uprise_time - self.upstart_time
                        self.upforce_max = output[7]

                    else:
                        self.upstart_time = (output[0] - T_delay) * self.gait_T / 100 / 100
                        self.uprise_time = output[1] * self.gait_T / 100 / 100 - self.upstart_time
                        self.upfall_time = output[2] * self.gait_T / 100 / 100 - self.uprise_time - self.upstart_time
                        self.upforce_max = output[3]

                elif 1 < self.update_n < 10:
                    self.update_n = self.update_n + 1

                else:
                    # self.update_n = 1
                    self.update_n = self.update_n

            # 3.其他
            self.stance_finsh = 0
            self.Flag = 1  # 计数更新

        # 判断离地时刻
        if self.GRF.stance_flg == 0 and self.Last_flag == 1:
            self.off_time = t  # 记录支撑相结束时刻

        # 辅助力预备预备
        self.Last_flag = self.GRF.stance_flg
        kp = 10
        force_pre = self.pre_force
        # 传参
        T_v = 0.05  # 助力结束后学习持续学习时间
        Fmax = self.upforce_max + force_pre
        Tsta = self.upstart_time * 100
        Trise = (self.upstart_time + self.uprise_time) * 100
        Tfall = (self.upstart_time + self.uprise_time + self.upfall_time) * 100
        flag = self.Flag

        self.Flag = self.Flag + 1

        if self.Mode_fight == 11:
            kp = self.Pos  # 将位置参数传给kp

        # 助力曲线设计

        #  正常步态下，支撑相和摆动相助力
        if self.GRF.stance_flg == 1:  # 支撑相
            mode = self.Mode_stance
            # 支撑相
            if (t <= self.touch_time + self.upstart_time) and (t >= self.touch_time):  # 刚刚触地预紧
                force = force_pre

            elif (t >= self.touch_time + self.upstart_time) and (
                    t < self.touch_time + self.upstart_time + self.uprise_time):

                x = (t - self.touch_time - self.upstart_time)

                t1 = self.uprise_time
                force1 = (4 * self.upforce_max * pow(x, 3)) / pow(t1, 3) - (3 * self.upforce_max * pow(x, 4)) / pow(t1,
                                                                                                                    4)
                # self.force_p = self.set_P(t - self.touch_time, self.upstart_time + self.uprise_time,
                #                           self.upstart_time + self.uprise_time + self.upfall_time)
                force = force1

                # force = force_pre + self.upforce_max * math.sin(
                #     3.1415926 / 2 * (t - self.touch_time - self.upstart_time) / (self.uprise_time))

            elif (t >= self.touch_time + self.upstart_time + self.uprise_time) and (
                    t < self.touch_time + self.upstart_time + self.uprise_time + self.upfall_time):
                x = t - self.touch_time - self.upstart_time - self.uprise_time
                t1 = self.upfall_time
                force1 = self.upforce_max - (4 * self.upforce_max * pow(x, 3)) / pow(t1, 3) + (
                        3 * self.upforce_max * pow(x, 4)) / pow(t1, 4)
                # self.force_p = self.set_P(t-self.touch_time, self.upstart_time + self.uprise_time, self.upstart_time + self.uprise_time + self.upfall_time)
                force = force1

                # force = force_pre + self.upforce_max * math.sin(3.1415926 / 2 * (
                #             t - self.touch_time - self.upstart_time - self.uprise_time + self.upfall_time) / self.upfall_time)

            elif (t >= self.touch_time + self.upstart_time + self.uprise_time + self.upfall_time) and (
                    t < self.touch_time + self.upstart_time + self.uprise_time + self.upfall_time + T_v):  # 刚刚助力结束预紧
                force = force_pre
                self.stance_finsh = 1
            # 支撑相内，助力结束，提前进入放线模式
            else:
                mode = self.Mode_fight
                force = force_pre

        # 摆动相
        elif self.GRF.stance_flg == 0 and flag > 30:
            force = force_pre
            if t < self.off_time + 0.5:  # 摆动相持续时间是0.5s
                mode = self.Mode_fight
            else:
                mode = self.Mode_fight

        # 其他未在elif中考虑的情况
        else:
            force = force_pre
            mode = self.Mode_other

        force = max(force, force_pre)

        return force, flag, mode, kp, Tsta, Trise, Tfall, Fmax
