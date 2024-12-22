#!/usr/bin/env python
# -*-coding:utf-8-*-

import rospy
from dynamic_reconfigure.server import Server
from strategy.cfg import drConfig
from ground_reaction_force.msg import GRF_Data
from strategy.msg import Fgrf
import math
from sympy import symbols, sympify, lambdify
import sympy as sp
import numpy as np

import joblib
from tensorflow.keras.models import load_model


class StrategyGroup:
    def __init__(self, strategy_list):

        self.strategy_list = strategy_list
        self.lat = rospy.get_param("~lat")
        self.med = rospy.get_param("~med")

        # 初始参数
        self.Last_flagL = 0 #上次触地标志位
        self.Last_flagR = 0
        self.Last_mode_fight = 0
        self.Last_mode_stance = 0


        # 参数服务器，ParamCallback 的执行时机是 当参数服务器中的参数被修改时，它会被立即触发。在rqt中执行一次
        self.param_flag = 0 # 参数服务器标志位
        self.server = Server(drConfig, self.ParamCallback)
        # 订阅“地反力反馈RL”，任何时候只要相应主题发布了新的数据，回调函数都会被执行一次
        rospy.Subscriber('pub_grf_L', GRF_Data, self.GRFL_Callback)
        self.GRF_L = GRF_Data()
        rospy.Subscriber('pub_grf_R', GRF_Data, self.GRFR_Callback)
        self.GRF_R = GRF_Data()
        # 定义发布 更新后“GRF”
        # self.GRFR_pub = rospy.Publisher('GRF_R', Fgrf, queue_size=1000)
        # self.GRFL_pub = rospy.Publisher('GRF_L', Fgrf, queue_size=1000)
        self.GRF_Ls = Fgrf()
        self.GRF_Rs = Fgrf()  # 减少数据量

        if self.lat > 3:
            self.human_data = self.load_human_data()
            self.equations = self.load_equations()
            self.prepare_functions()
            self.out_data()

        if  self.lat > 1:
            self.prepare_model()

    def prepare_model(self):

        # 加载模型和缩放器
        input_scaler = joblib.load('/home/c208/walking_assist/src/strategy/scripts/model/input_scaler.save')
        output_scaler = joblib.load('/home/c208/walking_assist/src/strategy/scripts/model/output_scaler.save')
        trained_model = load_model( '/home/c208/walking_assist/src/strategy/scripts/model/neural_network_model.keras')

        for strategy in self.strategy_list:
            strategy.get_model(input_scaler, output_scaler, trained_model)
        return

    def load_human_data(self):
        data = {}
        file_path = '/home/c208/walking_assist/src/strategy/scripts/data/human_data.txt'
        with open(file_path, 'r') as file:
            for line in file:
                line = line.strip()
                var_BQname, values = line.split(':')
                arr = list(map(float, values.split()))
                data[var_BQname] = arr
        return data

    def load_equations(self):
        file_path = '/home/c208/walking_assist/src/strategy/scripts/data/equation.txt'
        eqs = {}
        with open(file_path, 'r') as f:
            for line in f:
                name, expr_str = line.strip().split('=', 1)
                eqs[name] = sympify(expr_str)
        return eqs

    def prepare_functions(self):
        # Define symbols
        F1, xp1, yp1, zp1, theta_a, phi_a, theta_s, phi_s, F2, xp2, yp2, zp2 = sp.symbols('F1 xp1 yp1 zp1 theta_a phi_a theta_s phi_s F2 xp2 yp2 zp2')
        flexion, inversion, adduction = sp.symbols('flexion inversion adduction')
        Mx_d, My_d, Ma_d, Ms_d = sp.symbols('Mx_d My_d Ma_d Ms_d')
        Mx, My = sp.symbols('Mx My')

        # Substitute values
        theta_a_ = np.deg2rad(6)
        phi_a_ = np.deg2rad(10)
        theta_s_ = np.deg2rad(16)
        phi_s_ = np.deg2rad(42)
        xp1_, yp1_, zp1_ = -0.07, 0.03, -0.11
        xp2_, yp2_, zp2_ = -0.07, -0.03, -0.11
        self.values_to_substitute = {
            theta_a: theta_a_, phi_a: phi_a_, theta_s: theta_s_, phi_s: phi_s_,
            xp1: xp1_, yp1: yp1_, zp1: zp1_, xp2: xp2_, yp2: yp2_, zp2: zp2_
        }

        # Lambdify functions
        F1_expr = self.equations['F1_j'].subs(self.values_to_substitute)
        F2_expr = self.equations['F2_j'].subs(self.values_to_substitute)
        self.F1_func = lambdify([flexion, inversion, adduction, Mx_d, My_d], F1_expr, 'numpy')
        self.F2_func = lambdify([flexion, inversion, adduction, Mx_d, My_d], F2_expr, 'numpy')

        return

    def out_data(self):

        for strategy in self.strategy_list:
            strategy.get_data(self.human_data, self.F1_func, self.F2_func)

        return


    def GRFL_Callback(self, msg):
        if self.param_flag == 1:
            self.GRF_L = msg

            # 发布数据
            self.GRF_Ls.all_force = self.GRF_L.all_force
            self.GRF_Ls.stance_flg = self.GRF_L.stance_flg

            self.strategy_list[0].GRF_Callback(self.GRF_Ls)
            self.strategy_list[1].GRF_Callback(self.GRF_Ls)


            self.Last_flagL = self.GRF_L.stance_flg  # 上次触地标志位

        return
        self.show_index = 0

    def GRFR_Callback(self, msg):
        if self.param_flag == 1:
            self.GRF_R = msg
            # self.GRF_R.all_force = self.GRF_R.all_force * self.gain_GRFR + self.offset_GRFR

            # 发布数据
            self.GRF_Rs.all_force = self.GRF_R.all_force
            self.GRF_Rs.stance_flg = self.GRF_R.stance_flg

            self.strategy_list[2].GRF_Callback(self.GRF_Rs)
            self.strategy_list[3].GRF_Callback(self.GRF_Rs)

            self.Last_flagR =  self.GRF_R.stance_flg  # 上次触地标志位


        return

    def ParamCallback(self, config, level):  # level为参数的掩码（，表征到底哪个参数是否被改变
        if self.param_flag == 0:  # 只有在参数服务器更新后再执行其他函数
            config.groups.groups.Mode_Group.groups.fight_phase.groups.release.state = False #隐藏位置修正
            self.param_flag = 1
        # 更新提示
        # rospy.loginfo("which parameter is changed::%d\n\t", level + 1)

        # # 1.地反力参数更新
        # self.gain_GRFL = config.gain_GRFL
        # self.offset_GRFL = config.offset_GRFL
        # self.gain_GRFR = config.gain_GRFR
        # self.offset_GRFR = config.offset_GRFR

        # 2.助力更新
        if self.lat <2:
            # Left
            self.strategy_list[0].ParamCallback(self.lat*config.F_max,config.T_max_l,config.t_rise,config.t_fall,0)
            self.strategy_list[1].ParamCallback(self.med*config.F_max,config.T_max_l,config.t_rise,config.t_fall,0)
            # Right
            self.strategy_list[2].ParamCallback(self.med*config.F_max,config.T_max_r,config.t_rise,config.t_fall,0)
            self.strategy_list[3].ParamCallback(self.lat*config.F_max,config.T_max_r,config.t_rise,config.t_fall,0)
        else: #当前是自适应控制
            # Left
            self.strategy_list[0].ParamCallback(config.F_max,config.T_max_l,config.t_rise,config.t_fall,1)
            self.strategy_list[1].ParamCallback(config.F_max,config.T_max_l,config.t_rise,config.t_fall,1)
            # Right
            self.strategy_list[2].ParamCallback(config.F_max,config.T_max_r,config.t_rise,config.t_fall,1)
            self.strategy_list[3].ParamCallback(config.F_max,config.T_max_r,config.t_rise,config.t_fall,1)


        # 3.是否显示参数，位于 def force_curve(self, t): 中，选择是否显示参数更新
        for strategy in self.strategy_list:
            strategy.show_index = config.show 


        # 4.mode处理与更新
        if config.Mode0 == 1:  # Mode0 是bool 选择是否快速防线
            config.Mode_fight_All = 0
            config.Mode_stance_All = 0

        if config.Stop_update == 1:  # Mode0 是bool 选择是否快速防线
            config.Mode_fight_All = 12
            config.Mode_stance_All = 9

        if config.Mode_fight_All != self.Last_mode_fight:
            config.Mode_fight_left_lat = config.Mode_fight_All
            config.Mode_fight_left_Med = config.Mode_fight_All
            config.Mode_fight_right_lat = config.Mode_fight_All
            config.Mode_fight_right_Med = config.Mode_fight_All
            self.Last_mode_fight = config.Mode_fight_All

        if config.Mode_stance_All != self.Last_mode_stance:
            config.Mode_stance_left_lat = config.Mode_stance_All
            config.Mode_stance_left_Med = config.Mode_stance_All
            config.Mode_stance_right_lat = config.Mode_stance_All
            config.Mode_stance_right_Med = config.Mode_stance_All
            self.Last_mode_stance = config.Mode_stance_All
            
        # mode = 11 ，pos 的展开与取消
        mode_pos = 11
        if config.Mode_fight_left_lat == mode_pos or config.Mode_fight_left_Med == mode_pos or \
                config.Mode_fight_right_lat == mode_pos or config.Mode_fight_right_Med == mode_pos:
            # 四个策略模式中的任何一个是否处于 mode_pos 状态 ，就展开 Group_Mode_pos 可选项
            config.groups.groups.Mode_Group.groups.fight_phase.groups.release.state = True
        else:
            config.groups.groups.Mode_Group.groups.fight_phase.groups.release.state = False


        # mode更新
        if config.update_Mode == 1 or config.Mode0 == 1:
            mode_other = 1  # 位置积分控制
            # LeftLat
            # 即可以统一改变参数，可以单独调节一个绳子的变化
            mode_stance = config.Mode_stance_left_lat  
            mode_fight = config.Mode_fight_left_lat
            pos_fight = config.fight_pos_left_lat
            self.strategy_list[0].Mode_Callback( mode_stance,mode_fight,mode_other,pos_fight)
            # LeftMed
            mode_stance = config.Mode_stance_left_Med
            mode_fight = config.Mode_fight_left_Med
            pos_fight = config.fight_pos_left_Med
            self.strategy_list[1].Mode_Callback( mode_stance,mode_fight,mode_other,pos_fight)
            # RightLat
            mode_stance = config.Mode_stance_right_lat
            mode_fight = config.Mode_fight_right_lat
            pos_fight = config.fight_pos_right_lat
            self.strategy_list[3].Mode_Callback(mode_stance,mode_fight,mode_other,pos_fight)
            # RightMed
            mode_stance = config.Mode_stance_right_Med
            mode_fight = config.Mode_fight_right_Med
            pos_fight = config.fight_pos_right_Med
            self.strategy_list[2].Mode_Callback(mode_stance,mode_fight,mode_other,pos_fight)


        return config

    def update(self, t):
        for strategy in self.strategy_list:
            strategy.update(t)  # 更新辅助力曲线
            pass
        return

    def timeCallback(self, event): # 是一个基于 ROS 定时器触发的回调函数，定时器可以按照设定的时间间隔周期性地触发回调函数执行
        t = (event.current_real - self.time0).to_sec()
        self.update(t)
        return

    def start_loop(self, value):
        # 100Hz循环
        self.freq = value
        rospy.Timer(rospy.Duration(1. / self.freq), self.timeCallback)
        self.time0 = rospy.Time().now()
        rospy.spin()
        return


if __name__ == '__main__':
    import os

    file_name = os.path.basename(__file__)
    name = os.path.splitext(file_name)[0]
    rospy.init_node(name)

    from left_lat import LeftLat
    from left_med import LeftMed
    from right_med import RightMed
    from right_lat import RightLat


    strategy_list = [
        LeftLat(),
        LeftMed(),
        RightMed(),
        RightLat(),

    ]
    StrategyGroup(strategy_list).start_loop(100.0)
    pass
