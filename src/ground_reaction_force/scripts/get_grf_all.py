#!/usr/bin/env python
# -*-coding:utf-8-*-


import rospy
from std_msgs.msg import Float32
from ground_reaction_force.msg import GRF_Data
from can_msgs.msg import Frame
import sys, os
from scipy import signal


class GRF_fit:
    def __init__(self):
        self.grf_msg = GRF_Data()
        self.Last_flagL = 0
        self.Last_flagR = 0
        self.foot_upL = 0
        self.foot_upR = 0
        self.foot_downL = 0
        self.foot_downR = 0

        self.foot_index = rospy.get_param('~Foot')
        if self.foot_index == 0:
            self.GRF_CAN_ID1 = 0x200
            rospy.loginfo('get_grf_R')

        if self.foot_index == 1:
            self.GRF_CAN_ID1 = 0x100
            rospy.loginfo('get_grf_L')


        # 订阅“GRF”
        rospy.Subscriber("can_rx", Frame, self.canGrfCallback)
        self.can_grf = Frame()
        # 定义发布 “grf的数据"
        self.grf_pub = rospy.Publisher("pub_grf", GRF_Data, queue_size=1000)
        self.grf = GRF_Data()


    def canGrfCallback(self, msg):
        self.can_grf = msg
        return

    def update(self, t):
        if self.can_grf.dlc == 8 and not self.can_grf.is_error:
            if self.can_grf.id == self.GRF_CAN_ID1:
                self.grf.fore = float(((self.can_grf.data[0] << 8 | self.can_grf.data[1])/ 1))
                self.grf.mid = float(((self.can_grf.data[2] << 8 | self.can_grf.data[3]) / 1 ))
                self.grf.hind = float(((self.can_grf.data[4] << 8 | self.can_grf.data[5]) / 1 ))
                self.grf.xcop = self.can_grf.data[6] / 3
                self.grf.ycop = self.can_grf.data[7]
                self.grf.all_force = self.grf.fore + self.grf.mid + self.grf.hind
        self.grf.stance_flg = 0

        backupl = 0  # 脚后跟力大于前侧力v

        if self.grf.hind / (self.grf.mid + 0.001) > 1.1:
            backupl = 1


        if self.foot_index == 0:  #R
            grf_index = 250
            # 1. 判断触地
            if self.grf.all_force > grf_index and self.Last_flagR == 0 and backupl == 1:  # 脚后跟力大于前侧力v 且 地反力大于阈值
                self.foot_upR = self.foot_upR + 1
            else:
                self.foot_upR = 0

            if self.Last_flagR == 0 and self.foot_upR == 12:  # 地反力连续12个采样点大于阈值，则判定为支撑相开始
                self.grf.stance_flg = 1

            # 2. 判断支撑相阶段，保持处触地
            if self.grf.all_force > grf_index and self.Last_flagR == 1:
                self.grf.stance_flg = 1

            # 3. 判断离地
            if self.grf.all_force < grf_index and self.Last_flagR == 1:
                self.foot_downR = self.foot_downR + 1
            else:
                self.foot_downR = 0

            if self.Last_flagR == 1 and self.foot_downR == 33:
                self.grf.stance_flg = 0

            self.Last_flagR = self.grf.stance_flg

        if self.foot_index == 1:  #L
            grf_index = 250
            # 1. 判断触地
            if self.grf.all_force > grf_index and self.Last_flagL == 0 and backupl == 1:  # 脚后跟力大于前侧力v 且 地反力大于阈值
                self.foot_upL = self.foot_upL + 1
            else:
                self.foot_upL = 0

            if self.Last_flagL == 0 and self.foot_upL == 12:  # 地反力连续12个采样点大于阈值，则判定为支撑相开始
                self.grf.stance_flg = 1

            # 2. 判断支撑相阶段，保持处触地
            if self.grf.all_force > grf_index and self.Last_flagL == 1:
                self.grf.stance_flg = 1

            # 3. 判断离地
            if self.grf.all_force < grf_index and self.Last_flagL == 1:
                self.foot_downL = self.foot_downL + 1
            else:
                self.foot_downL = 0

            if self.Last_flagL == 1 and self.foot_downL == 33:
                self.grf.stance_flg = 0

            self.Last_flagL = self.grf.stance_flg

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
