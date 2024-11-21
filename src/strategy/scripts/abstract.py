#!/usr/bin/env python
# -*-coding:utf-8-*-

import rospy
from rospy import Publisher
from std_msgs.msg import Float32
from unitree_motor.msg import Sensor
from control.msg import Command
import sys, os
from strategy.msg  import Fgrf
import math

class Strategy:

    def __init__(self):

        file_name = os.path.basename(sys.modules[self.__module__].__file__)
        name = os.path.splitext(file_name)[0]

        # 参数设计
        self.pre_force = rospy.get_param("~force_pre")  # 获取参数
        # self.PMode = rospy.get_param('~PMode')

        self.show_index = 1
        # 定义发布 “指令” command
        self.cmd_pub = rospy.Publisher(name + '_cmd', Command, queue_size=1000)
        self.cmd_msg = Command()
        # 定义地反力
        self.GRF_L = Fgrf()
        self.GRF_R = Fgrf()

    def GRFR_Callback(self, msg):
        self.GRF_R = msg
        return

    def GRFL_Callback(self, msg):
        self.GRF_L = msg
        return

    def ParamCallback(self, F_max, F_start, F_rise, F_fall):
        self.F_max = F_max  # 辅助力峰值
        self.F_start = F_start
        self.F_rise = F_rise  # 辅助力峰值时刻占步态的百分比：这里要考虑触地判定延迟大概有20~25ms
        self.F_fall = F_fall
        return

    def update(self, t):
        force, flag,  mode, kp, Tsta, Trise, Tfall, Fmax = self.force_curve(t)
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

    def set_P(self, x,t1,t2 ):

        if self.PMode >= 0:
            P_force = self.PMode
        elif self.PMode == -1:  # 0-1
            if x<t1:
                P_force = x/t1/2
            else:
                P_force = 0.5+(x-t1)/(t2-t1)/2
        elif self.PMode == -2:  # 0-1-1
            if x<t1:
                P_force = 2*x/t1/3
            else:
                P_force = 2/3+(x-t1)/(t2-t1)/3
        return P_force

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
        force = 0.0
        mode = 1
        kp = 20
        flag = 0
        Tsta = 0
        Trise = 0
        Tfall = 0
        Fmax = 0
        return force, flag,  mode, kp, Tsta, Trise, Tfall, Fmax
