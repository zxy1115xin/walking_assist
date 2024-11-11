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
        self.footL_up = 0 #判断触地
        self.footR_up = 0
        self.footL_down = 0
        self.footR_down = 0
        self.Last_mode_fight = 0
        self.Last_mode_stance = 0
        self.index_R_off = 0
        self.index_R_on = 0
        self.index_L_off = 0
        self.index_L_on = 0
        self.grf_r_on = 0
        self.grf_l_on = 0


        # 参数服务器标志位
        self.param_flag = 0

        # 参数服务器
        self.server = Server(drConfig, self.ParamCallback)

        # 订阅“地反力反馈RL”
        rospy.Subscriber('pub_grf_L', GRF_Data, self.GRFL_Callback)
        self.GRF_L = GRF_Data()
        rospy.Subscriber('pub_grf_R', GRF_Data, self.GRFR_Callback)
        self.GRF_R = GRF_Data()
        # 定义发布 更新后“GRF”3
        self.GRFR_pub = rospy.Publisher('GRF_R', Fgrf, queue_size=1000)
        self.GRFL_pub = rospy.Publisher('GRF_L', Fgrf, queue_size=1000)
        self.GRF_Ls = Fgrf()
        self.GRF_Rs = Fgrf()  # 减少数据量

    # def GRFL_Callback(self, msg):
    #     if self.param_flag == 1:
    #         self.GRF_L = msg
    #         self.GRF_L.all_force = self.GRF_L.all_force * self.gain_GRFL + self.offset_GRFL
    #         grf_bot = self.GRF_L.bot_Med + self.GRF_L.bot_lat-200
    #         grf_up = self.GRF_L.midtop_mid
    #         self.GRF_L.stance_flg = 1
    #
    #
    #         # 判断触地
    #         if grf_bot > 200 and self.Last_flagL == 0:
    #             self.grf_l_on = self.grf_l_on + 1
    #         else:
    #             self.grf_l_on = 0
    #         if self.grf_l_on > 2:
    #             self.index_L_on = 1
    #
    #
    #         # 判断蹬地
    #         # 登地
    #         if grf_up > 200 and self.index_L_on == 1:
    #             self.footL_up = self.footL_up + 1
    #         else:
    #             self.footL_up = 0
    #         if self.footL_up > 2:
    #             self.index_L_off = 1
    #
    #         # rospy.loginfo("grf_bot :%d\n\t", grf_bot )
    #         # rospy.loginfo("grf_bot :%d\n\t", grf_bot)
    #
    #
    #         # 离地
    #         if grf_up < 200 and self.index_L_on == 1 and self.index_L_off == 1:
    #             self.footL_down = self.footL_down + 1
    #         else:
    #             self.footL_down = 0
    #         if self.footL_down == 3:
    #             self.index_L_off = 0
    #             self.index_L_on = 0
    #
    #         if self.index_L_off == 0 and self.index_L_on == 0:
    #             self.GRF_L.stance_flg = 0
    #
    #         self.Last_flagL = self.GRF_L.stance_flg
    #
    #         # 发布数据
    #         self.GRF_Ls.all_force = self.GRF_L.all_force
    #         self.GRF_Ls.stance_flg = self.GRF_L.stance_flg
    #         self.GRFL_pub.publish(self.GRF_Ls)
    #         for strategy in self.strategy_list:
    #             strategy.GRFL_Callback(self.GRF_Ls)
    #
    #     return

    # def GRFR_Callback(self, msg):
    #     if self.param_flag == 1:
    #
    #         self.GRF_R = msg
    #         self.GRF_R.all_force = self.GRF_R.all_force * self.gain_GRFR + self.offset_GRFR
    #         grf_bot = (self.GRF_R.bot_Med + self.GRF_R.bot_lat-1000) * self.gain_GRFR + self.offset_GRFR
    #         self.GRF_R.stance_flg = 1
    #
    #         # 判断触地
    #         if grf_bot > 400 and self.Last_flagR == 0:
    #             self.grf_r_on = self.grf_r_on + 1
    #         else:
    #             self.grf_r_on = 0
    #         if self.grf_r_on == 3:
    #             self.index_R_on = 1
    #
    #         # 判断蹬地
    #         # 登地
    #         if self.GRF_R.all_force > 400 and self.index_R_on == 1:
    #             self.footR_up = self.footR_up + 1
    #         else:
    #             self.footR_up = 0
    #         if self.footR_up == 5:
    #             self.index_R_off = 1
    #         # 离地
    #         if self.GRF_R.all_force < 400 and self.index_R_on == 1 and self.index_R_off == 1:
    #             self.footR_down = self.footR_down + 1
    #         else:
    #             self.footR_down = 0
    #         if self.footR_down == 5:
    #             self.index_R_off = 0
    #             self.index_R_on = 0
    #
    #         if self.index_R_off == 0 and self.index_R_on == 0:
    #             self.GRF_R.stance_flg = 0
    #
    #         self.Last_flagR = self.GRF_R.stance_flg
    #
    #
    #         # 发布数据
    #         self.GRF_Rs.all_force = self.GRF_R.all_force
    #         self.GRF_Rs.stance_flg = self.GRF_R.stance_flg
    #         self.GRFR_pub.publish(self.GRF_Rs)
    #         for strategy in self.strategy_list:
    #             strategy.GRFR_Callback(self.GRF_Rs)
    #     return

    def GRFL_Callback(self, msg):
        if self.param_flag == 1:
            self.GRF_L = msg
            self.GRF_L.all_force = self.GRF_L.all_force * self.gain_GRFL + self.offset_GRFL
            self.GRF_L.stance_flg = 0

            # 判断触地，条件：a.连续n次 b.>300 c.脚后跟力大于前侧力
            backupl = 1  # 脚后跟力大于前侧力v
            if self.GRF_L.bot_Med + self.GRF_L.bot_lat - self.GRF_L.midtop_mid > 10:
                backupl = 1

            if self.GRF_L.all_force > 200 and self.Last_flagL == 0 and backupl == 1:
                self.footL_up = self.footL_up + 1
            else:
                self.footL_up = 0
            if self.Last_flagL == 0 and self.footL_up == 12:
                self.GRF_L.stance_flg = 1

            # 判断支撑相阶段
            if self.GRF_L.all_force > 200 and self.Last_flagL == 1:
                self.GRF_L.stance_flg = 1

            # 判断蹬地
            if self.GRF_L.all_force < 200 and self.Last_flagL == 1:
                self.footL_down = self.footL_down + 1
            else:
                self.footL_down = 0
            if self.Last_flagL == 1 and self.footL_down == 40:
                self.GRF_L.stance_flg = 0

            self.Last_flagL = self.GRF_L.stance_flg

            # 发布数据
            self.GRF_Ls.all_force = self.GRF_L.all_force
            self.GRF_Ls.stance_flg = self.GRF_L.stance_flg
            self.GRFL_pub.publish(self.GRF_Ls)
            for strategy in self.strategy_list:
                strategy.GRFL_Callback(self.GRF_Ls)

        return


    def GRFR_Callback(self, msg):
        if self.param_flag == 1:
            self.GRF_R = msg
            self.GRF_R.all_force = self.GRF_R.all_force * self.gain_GRFR + self.offset_GRFR

            backupr = 1   # 脚后跟力大于前侧力v
            if self.GRF_R.bot_Med + self.GRF_R.bot_lat - self.GRF_R.midtop_mid > 10:
                backupr = 1

            if self.GRF_R.all_force > 200 and self.Last_flagR == 0:
                self.footR_up = self.footR_up + 1
            else:
                self.footR_up = 0

            if self.Last_flagR == 0 and self.footR_up == 12:
                self.GRF_R.stance_flg = 1

            # 持续
            if self.GRF_R.all_force > 200 and self.Last_flagR == 1:
                self.GRF_R.stance_flg = 1

            # 判断蹬地
            if self.GRF_R.all_force < 200 and self.Last_flagR == 1:
                self.footR_down = self.footR_down + 1
            else:
                self.footR_down = 0
            if self.Last_flagR == 1 and self.footR_down == 40:
                self.GRF_R.stance_flg = 0

            self.Last_flagR = self.GRF_R.stance_flg

            # 发布数据
            self.GRF_Rs.all_force = self.GRF_R.all_force
            self.GRF_Rs.stance_flg = self.GRF_R.stance_flg
            self.GRFR_pub.publish(self.GRF_Rs)
            for strategy in self.strategy_list:
                strategy.GRFR_Callback(self.GRF_Rs)
        return

    def ParamCallback(self, config, level):  # level为参数的掩码（，表征到底哪个参数是否被改变
        if self.param_flag == 0:  # 只有在参数服务器更新后再执行其他函数
            config.groups.groups.Mode_Group.groups.fight_phase.groups.release.state=False #隐藏位置修正
            self.param_flag = 1
        # 更新提示
        # rospy.loginfo("which parameter is changed::%d\n\t", level + 1)

        # 地反力参数更新
        self.gain_GRFL = config.gain_GRFL
        self.offset_GRFL = config.offset_GRFL
        self.gain_GRFR = config.gain_GRFR
        self.offset_GRFR = config.offset_GRFR

        # 助力更新
        # Left
        strategy_list[0].ParamCallback(config.F_max,config.F_start_l,config.F_rise,config.F_fall)
        strategy_list[1].ParamCallback(config.F_max,config.F_start_l,config.F_rise,config.F_fall)
        # Right
        strategy_list[2].ParamCallback(config.F_max,config.F_start_r,config.F_rise,config.F_fall)
        strategy_list[3].ParamCallback(config.F_max,config.F_start_r,config.F_rise,config.F_fall)
        # 扰动
        strategy_list[4].ParamCallback(config.F_max,config.F_start_r,config.F_rise,config.F_fall)

        #是否显示参数
        for strategy in self.strategy_list:
            strategy.show_index = config.show


        # mode处理
        if config.Mode0 == 1:
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
            config.groups.groups.Mode_Group.groups.fight_phase.groups.release.state = True
        else:
            config.groups.groups.Mode_Group.groups.fight_phase.groups.release.state = False


        # mode更新
        if config.update_Mode == 1 or config.Mode0 == 1:
            mode_other = 1
            # LeftLat
            mode_stance = config.Mode_stance_left_lat
            mode_fight = config.Mode_fight_left_lat
            pos_fight = config.fight_pos_left_lat
            strategy_list[0].Mode_Callback( mode_stance,mode_fight,mode_other,pos_fight)
            # LeftMed
            mode_stance = config.Mode_stance_left_Med
            mode_fight = config.Mode_fight_left_Med
            pos_fight = config.fight_pos_left_Med
            strategy_list[1].Mode_Callback( mode_stance,mode_fight,mode_other,pos_fight)
            # RightLat
            mode_stance = config.Mode_stance_right_lat
            mode_fight = config.Mode_fight_right_lat
            pos_fight = config.fight_pos_right_lat
            strategy_list[3].Mode_Callback(mode_stance,mode_fight,mode_other,pos_fight)
            # RightMed
            mode_stance = config.Mode_stance_right_Med
            mode_fight = config.Mode_fight_right_Med
            pos_fight = config.fight_pos_right_Med
            strategy_list[2].Mode_Callback(mode_stance,mode_fight,mode_other,pos_fight)
            # Disturb
            mode_stance = config.Mode_stance_right_Med
            mode_fight = config.Mode_fight_right_Med
            pos_fight = config.fight_pos_right_Med
            strategy_list[4].Mode_Callback(mode_stance, mode_fight, mode_other, pos_fight)

        return config

    def update(self, t):
        for strategy in self.strategy_list:
            strategy.update(t)
            pass
        return

    def timeCallback(self, event):
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
    from right_med_art import RightMed_art
    from right_lat_art import RightLat_art
    from disturb import Disturb

    strategy_list = [
        LeftLat(),
        LeftMed(),
        RightMed_art(),
        RightLat_art(),
        Disturb(),
    ]
    StrategyGroup(strategy_list).start_loop(100.0)
    pass
