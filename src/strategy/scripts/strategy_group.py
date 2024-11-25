#!/usr/bin/env python
# -*-coding:utf-8-*-

import rospy
from dynamic_reconfigure.server import Server
from strategy.cfg import drConfig
from ground_reaction_force.msg import GRF_Data
from strategy.msg import Fgrf


class StrategyGroup:
    def __init__(self, strategy_list):

        self.strategy_list = strategy_list

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


    def GRFL_Callback(self, msg):
        if self.param_flag == 1:
            self.GRF_L = msg

            # 发布数据
            self.GRF_Ls.all_force = self.GRF_L.all_force
            self.GRF_Ls.stance_flg = self.GRF_L.stance_flg

            self.strategy_list[0].GRF_Callback(self.GRF_Ls)
            self.strategy_list[1].GRF_Callback(self.GRF_Ls)

            if self.GRF_L.stance_flg == 1 and self.Last_flagL == 0:
                self.strategy_list[0].force_update()
                self.strategy_list[1].force_update()

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

            if self.GRF_R.stance_flg == 1 and self.Last_flagR == 0:
                self.strategy_list[2].force_update()
                self.strategy_list[3].force_update()

            self.Last_flagR =  self.GRF_R.stance_flg  # 上次触地标志位


        return

    def ParamCallback(self, config, level):  # level为参数的掩码（，表征到底哪个参数是否被改变
        if self.param_flag == 0:  # 只有在参数服务器更新后再执行其他函数
            config.groups.groups.Mode_Group.groups.fight_phase.groups.release.state=False #隐藏位置修正
            self.param_flag = 1
        # 更新提示
        # rospy.loginfo("which parameter is changed::%d\n\t", level + 1)

        # 1.地反力参数更新
        self.gain_GRFL = config.gain_GRFL
        self.offset_GRFL = config.offset_GRFL
        self.gain_GRFR = config.gain_GRFR
        self.offset_GRFR = config.offset_GRFR

        # 2.助力更新
        # Left
        self.strategy_list[0].ParamCallback(config.F_max,config.T_max_l,config.t_rise,config.t_fall)
        self.strategy_list[1].ParamCallback(config.F_max,config.T_max_l,config.t_rise,config.t_fall)
        # Right
        self.strategy_list[2].ParamCallback(config.F_max,config.T_max_r,config.t_rise,config.t_fall)
        self.strategy_list[3].ParamCallback(config.F_max,config.T_max_r,config.t_rise,config.t_fall)


        # 3.是否显示参数，位于 def force_curve(self, t): 中，选择是否显示参数更新
        for strategy in self.strategy_list:
            strategy.show_index = config.show 


        # 4.mode处理与更新
        if config.Mode0 == 1:  # Mode0 是bool 选择是否快速防线
            config.Mode_fight_All = 0
            config.Mode_stance_All = 0

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
