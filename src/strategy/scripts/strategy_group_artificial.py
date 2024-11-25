#!/usr/bin/env python
# -*-coding:utf-8-*-

import rospy
from strategy_group import StrategyGroup


if __name__ == '__main__':
    import os

    file_name = os.path.basename(__file__)
    name = os.path.splitext(file_name)[0]
    rospy.init_node(name)

    from left_lat_art import LeftLat_art
    from left_med_art import LeftMed_art
    from right_med_art import RightMed_art
    from right_lat_art import RightLat_art

    strategy_list = [
        LeftLat_art(),
        LeftMed_art(),
        RightMed_art(),
        RightLat_art(),
    ]
    StrategyGroup(strategy_list).start_loop(100.0)

    pass
