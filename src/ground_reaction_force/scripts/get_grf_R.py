#!/usr/bin/env python
# -*-coding:utf-8-*-


import rospy
from std_msgs.msg import Float32
from ground_reaction_force.msg import GRF_Data
from can_msgs.msg import Frame
import sys, os
import numpy as np
from scipy import signal
# from IIR2Filter import IIR2Filter


class GRF_fit:
    def __init__(self):
        self.grf_msg = GRF_Data()


        self.GRF_CAN_ID1 = 0x50
        self.GRF_CAN_ID2 = 0x60
        self.GRF_CAN_ID3 = 0x70
        self.GRF_CAN_ID4 = 0x80
        rospy.loginfo('get_grf_R')

        # 订阅“GRF”
        rospy.Subscriber("can1_rx", Frame, self.canGrfCallback)
        self.can_grf = Frame()
        # 定义发布 “grf的数据"
        self.grf_pub = rospy.Publisher("pub_grf", GRF_Data, queue_size=1000)
        self.grf = GRF_Data()
        return

    def canGrfCallback(self, msg):
        self.can_grf = msg
        return

    def update(self, t):
        #rospy.loginfo(self.can_grf.id)
        if self.can_grf.dlc == 8 and not self.can_grf.is_error:

            if self.can_grf.id == self.GRF_CAN_ID1:
                self.grf.midtop_Med = float(((self.can_grf.data[0] << 8 | self.can_grf.data[1]) / 10 ))
                self.grf.top_Med = float(((self.can_grf.data[2] << 8 | self.can_grf.data[3]) / 10 ))
                self.grf.midtop_mid = float(((self.can_grf.data[4] << 8 | self.can_grf.data[5]) / 10 ))
                self.grf.mid_Med = float(((self.can_grf.data[6] << 8 | self.can_grf.data[7]) / 10))

            elif self.can_grf.id == self.GRF_CAN_ID2:
                self.grf.bot_Med = float(((self.can_grf.data[0] << 8 | self.can_grf.data[1]) / 10 ))
                self.grf.midbot_Med = float(((self.can_grf.data[2] << 8 | self.can_grf.data[3]) / 10 ))
                self.grf.top_mid = float(((self.can_grf.data[4] << 8 | self.can_grf.data[5]) / 10 ))
                self.grf.midtop_midlat = float(((self.can_grf.data[6] << 8 | self.can_grf.data[7]) / 10 ))

            elif self.can_grf.id == self.GRF_CAN_ID3:
                self.grf.mid_mid = float(((self.can_grf.data[0] << 8 | self.can_grf.data[1]) / 10 ))
                self.grf.bot_lat = float(((self.can_grf.data[2] << 8 | self.can_grf.data[3]) / 10 ))
                self.grf.midbot_lat = float(((self.can_grf.data[4] << 8 | self.can_grf.data[5]) / 10 ))
                self.grf.top_midlat = float(((self.can_grf.data[6] << 8 | self.can_grf.data[7]) / 10 ))

            elif self.can_grf.id == self.GRF_CAN_ID4:
                self.grf.midtop_lat = float(((self.can_grf.data[0] << 8 | self.can_grf.data[1]) / 10))
                self.grf.mid_latDO = float(((self.can_grf.data[2] << 8 | self.can_grf.data[3]) / 10 ))
                self.grf.mid_latUP = float(((self.can_grf.data[4] << 8 | self.can_grf.data[5]) / 10))
                self.grf.top_lat = float(((self.can_grf.data[6] << 8 | self.can_grf.data[7]) / 10 ))

        self.grf.all_force = self.grf.midtop_Med + self.grf.top_Med + self.grf.midtop_mid + self.grf.mid_Med + self.grf.bot_Med + self.grf.midbot_Med + self.grf.top_mid + self.grf.midtop_midlat + self.grf.mid_mid + self.grf.bot_lat + self.grf.midbot_lat + self.grf.top_midlat + self.grf.midtop_lat + self.grf.mid_latDO + self.grf.mid_latUP + self.grf.top_lat
        self.grf.stance_flg = 0
        self.grf_pub.publish(self.grf)

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

    rospy.init_node("get_grf")
    GRF_fit().start_loop(100.0)
