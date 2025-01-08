## *********************************************************
##
## File autogenerated for the book_dynamic_param package
## by the dynamic_reconfigure package.
## Please do not edit.
##
## ********************************************************/

from dynamic_reconfigure.encoding import extract_params

inf = float('inf')

config_description = {'name': 'Default', 'type': '', 'state': True, 'cstate': 'true', 'id': 0, 'parent': 0, 'parameters': [], 'groups': [{'name': 'Assist_force_Group', 'type': 'hide', 'state': True, 'cstate': 'true', 'id': 1, 'parent': 0, 'parameters': [{'name': 'show', 'type': 'bool', 'default': False, 'level': 1, 'description': '显示步态参数', 'min': False, 'max': True, 'srcline': 10, 'srcfile': '/home/c208/walking_assist/src/strategy/cfg/DynamicParam.cfg', 'edit_method': '', 'ctype': 'bool', 'cconsttype': 'const bool'}, {'name': 'F_max', 'type': 'double', 'default': 150.0, 'level': 0, 'description': 'A Double Parameter,', 'min': 0.0, 'max': 250.0, 'srcline': 11, 'srcfile': '/home/c208/walking_assist/src/strategy/cfg/DynamicParam.cfg', 'edit_method': '', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 't_rise', 'type': 'double', 'default': 0.35, 'level': 0, 'description': 'A Double Parameter', 'min': 0.0, 'max': 0.5, 'srcline': 12, 'srcfile': '/home/c208/walking_assist/src/strategy/cfg/DynamicParam.cfg', 'edit_method': '', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 't_fall', 'type': 'double', 'default': 0.11, 'level': 0, 'description': 'A Double Parameter', 'min': 0.0, 'max': 0.5, 'srcline': 13, 'srcfile': '/home/c208/walking_assist/src/strategy/cfg/DynamicParam.cfg', 'edit_method': '', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'T_max_r', 'type': 'double', 'default': 0.42, 'level': 0, 'description': 'A Double Parameter', 'min': 0.0, 'max': 0.5, 'srcline': 14, 'srcfile': '/home/c208/walking_assist/src/strategy/cfg/DynamicParam.cfg', 'edit_method': '', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'T_max_l', 'type': 'double', 'default': 0.42, 'level': 0, 'description': 'A Double Parameter', 'min': 0.0, 'max': 0.5, 'srcline': 15, 'srcfile': '/home/c208/walking_assist/src/strategy/cfg/DynamicParam.cfg', 'edit_method': '', 'ctype': 'double', 'cconsttype': 'const double'}], 'groups': [], 'srcline': 124, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'class': 'DEFAULT::ASSIST_FORCE_GROUP', 'parentclass': 'DEFAULT', 'parentname': 'Default', 'field': 'DEFAULT::assist_force_group', 'upper': 'ASSIST_FORCE_GROUP', 'lower': 'assist_force_group'}, {'name': 'Mode_Group', 'type': 'hide', 'state': True, 'cstate': 'true', 'id': 2, 'parent': 0, 'parameters': [{'name': 'update_Mode', 'type': 'bool', 'default': False, 'level': 0, 'description': 'A Bool Parameter', 'min': False, 'max': True, 'srcline': 19, 'srcfile': '/home/c208/walking_assist/src/strategy/cfg/DynamicParam.cfg', 'edit_method': '', 'ctype': 'bool', 'cconsttype': 'const bool'}, {'name': 'Start_update', 'type': 'bool', 'default': False, 'level': 0, 'description': '停止学习', 'min': False, 'max': True, 'srcline': 20, 'srcfile': '/home/c208/walking_assist/src/strategy/cfg/DynamicParam.cfg', 'edit_method': '', 'ctype': 'bool', 'cconsttype': 'const bool'}, {'name': 'Stop_update', 'type': 'bool', 'default': False, 'level': 0, 'description': '停止学习', 'min': False, 'max': True, 'srcline': 21, 'srcfile': '/home/c208/walking_assist/src/strategy/cfg/DynamicParam.cfg', 'edit_method': '', 'ctype': 'bool', 'cconsttype': 'const bool'}, {'name': 'Mode0', 'type': 'bool', 'default': False, 'level': 0, 'description': '快速放松', 'min': False, 'max': True, 'srcline': 22, 'srcfile': '/home/c208/walking_assist/src/strategy/cfg/DynamicParam.cfg', 'edit_method': '', 'ctype': 'bool', 'cconsttype': 'const bool'}, {'name': 'Start_measure', 'type': 'bool', 'default': False, 'level': 0, 'description': '开始记录', 'min': False, 'max': True, 'srcline': 23, 'srcfile': '/home/c208/walking_assist/src/strategy/cfg/DynamicParam.cfg', 'edit_method': '', 'ctype': 'bool', 'cconsttype': 'const bool'}, {'name': 'StrDyParam', 'type': 'str', 'default': 'Mode=8 支撑学习；Mode=9支撑停止学习 ；Mode=10 摆动学习；Mode=11摆动停止学习', 'level': 0, 'description': '备注', 'min': '', 'max': '', 'srcline': 24, 'srcfile': '/home/c208/walking_assist/src/strategy/cfg/DynamicParam.cfg', 'edit_method': '', 'ctype': 'std::string', 'cconsttype': 'const char * const'}], 'groups': [{'name': 'fight_phase', 'type': 'hide', 'state': True, 'cstate': 'true', 'id': 3, 'parent': 2, 'parameters': [{'name': 'Mode_fight_All', 'type': 'int', 'default': 10, 'level': 1, 'description': '摆动相，请 Mode =10 or 11', 'min': 0, 'max': 20, 'srcline': 27, 'srcfile': '/home/c208/walking_assist/src/strategy/cfg/DynamicParam.cfg', 'edit_method': '', 'ctype': 'int', 'cconsttype': 'const int'}, {'name': 'Mode_fight_right_lat', 'type': 'int', 'default': 10, 'level': 1, 'description': 'A Double Parameter', 'min': 0, 'max': 20, 'srcline': 28, 'srcfile': '/home/c208/walking_assist/src/strategy/cfg/DynamicParam.cfg', 'edit_method': '', 'ctype': 'int', 'cconsttype': 'const int'}, {'name': 'Mode_fight_right_Med', 'type': 'int', 'default': 10, 'level': 1, 'description': 'A Double Parameter', 'min': 0, 'max': 20, 'srcline': 29, 'srcfile': '/home/c208/walking_assist/src/strategy/cfg/DynamicParam.cfg', 'edit_method': '', 'ctype': 'int', 'cconsttype': 'const int'}, {'name': 'Mode_fight_left_lat', 'type': 'int', 'default': 10, 'level': 1, 'description': 'A Double Parameter', 'min': 0, 'max': 20, 'srcline': 30, 'srcfile': '/home/c208/walking_assist/src/strategy/cfg/DynamicParam.cfg', 'edit_method': '', 'ctype': 'int', 'cconsttype': 'const int'}, {'name': 'Mode_fight_left_Med', 'type': 'int', 'default': 10, 'level': 1, 'description': 'A Double Parameter', 'min': 0, 'max': 20, 'srcline': 31, 'srcfile': '/home/c208/walking_assist/src/strategy/cfg/DynamicParam.cfg', 'edit_method': '', 'ctype': 'int', 'cconsttype': 'const int'}], 'groups': [{'name': 'release', 'type': 'hide', 'state': False, 'cstate': 'false', 'id': 4, 'parent': 3, 'parameters': [{'name': 'fight_pos_right_lat', 'type': 'double', 'default': 1.0, 'level': 1, 'description': 'A Double Parameter', 'min': -0.1, 'max': 1.5, 'srcline': 35, 'srcfile': '/home/c208/walking_assist/src/strategy/cfg/DynamicParam.cfg', 'edit_method': '', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'fight_pos_right_Med', 'type': 'double', 'default': 1.0, 'level': 1, 'description': 'A Double Parameter', 'min': -0.1, 'max': 1.5, 'srcline': 36, 'srcfile': '/home/c208/walking_assist/src/strategy/cfg/DynamicParam.cfg', 'edit_method': '', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'fight_pos_left_lat', 'type': 'double', 'default': 1.0, 'level': 1, 'description': 'A Double Parameter', 'min': -0.1, 'max': 1.5, 'srcline': 37, 'srcfile': '/home/c208/walking_assist/src/strategy/cfg/DynamicParam.cfg', 'edit_method': '', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'fight_pos_left_Med', 'type': 'double', 'default': 1.0, 'level': 1, 'description': 'A Double Parameter', 'min': -0.1, 'max': 1.5, 'srcline': 38, 'srcfile': '/home/c208/walking_assist/src/strategy/cfg/DynamicParam.cfg', 'edit_method': '', 'ctype': 'double', 'cconsttype': 'const double'}], 'groups': [], 'srcline': 124, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'class': 'DEFAULT::MODE_GROUP::FIGHT_PHASE::RELEASE', 'parentclass': 'DEFAULT::MODE_GROUP::FIGHT_PHASE', 'parentname': 'fight_phase', 'field': 'DEFAULT::MODE_GROUP::FIGHT_PHASE::release', 'upper': 'RELEASE', 'lower': 'release'}], 'srcline': 124, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'class': 'DEFAULT::MODE_GROUP::FIGHT_PHASE', 'parentclass': 'DEFAULT::MODE_GROUP', 'parentname': 'Mode_Group', 'field': 'DEFAULT::MODE_GROUP::fight_phase', 'upper': 'FIGHT_PHASE', 'lower': 'fight_phase'}, {'name': 'stance_phase', 'type': 'hide', 'state': True, 'cstate': 'true', 'id': 5, 'parent': 2, 'parameters': [{'name': 'Mode_stance_All', 'type': 'int', 'default': 8, 'level': 1, 'description': '支撑相，请 Mode =8 or 9', 'min': 0, 'max': 20, 'srcline': 41, 'srcfile': '/home/c208/walking_assist/src/strategy/cfg/DynamicParam.cfg', 'edit_method': '', 'ctype': 'int', 'cconsttype': 'const int'}, {'name': 'Mode_stance_right_lat', 'type': 'int', 'default': 8, 'level': 1, 'description': 'A Double Parameter', 'min': 0, 'max': 20, 'srcline': 42, 'srcfile': '/home/c208/walking_assist/src/strategy/cfg/DynamicParam.cfg', 'edit_method': '', 'ctype': 'int', 'cconsttype': 'const int'}, {'name': 'Mode_stance_right_Med', 'type': 'int', 'default': 8, 'level': 1, 'description': 'A Double Parameter', 'min': 0, 'max': 20, 'srcline': 43, 'srcfile': '/home/c208/walking_assist/src/strategy/cfg/DynamicParam.cfg', 'edit_method': '', 'ctype': 'int', 'cconsttype': 'const int'}, {'name': 'Mode_stance_left_lat', 'type': 'int', 'default': 8, 'level': 1, 'description': 'A Double Parameter', 'min': 0, 'max': 20, 'srcline': 44, 'srcfile': '/home/c208/walking_assist/src/strategy/cfg/DynamicParam.cfg', 'edit_method': '', 'ctype': 'int', 'cconsttype': 'const int'}, {'name': 'Mode_stance_left_Med', 'type': 'int', 'default': 8, 'level': 1, 'description': 'A Double Parameter', 'min': 0, 'max': 20, 'srcline': 45, 'srcfile': '/home/c208/walking_assist/src/strategy/cfg/DynamicParam.cfg', 'edit_method': '', 'ctype': 'int', 'cconsttype': 'const int'}], 'groups': [], 'srcline': 124, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'class': 'DEFAULT::MODE_GROUP::STANCE_PHASE', 'parentclass': 'DEFAULT::MODE_GROUP', 'parentname': 'Mode_Group', 'field': 'DEFAULT::MODE_GROUP::stance_phase', 'upper': 'STANCE_PHASE', 'lower': 'stance_phase'}], 'srcline': 124, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'class': 'DEFAULT::MODE_GROUP', 'parentclass': 'DEFAULT', 'parentname': 'Default', 'field': 'DEFAULT::mode_group', 'upper': 'MODE_GROUP', 'lower': 'mode_group'}], 'srcline': 246, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'class': 'DEFAULT', 'parentclass': '', 'parentname': 'Default', 'field': 'default', 'upper': 'DEFAULT', 'lower': 'groups'}

min = {}
max = {}
defaults = {}
level = {}
type = {}
all_level = 0

#def extract_params(config):
#    params = []
#    params.extend(config['parameters'])
#    for group in config['groups']:
#        params.extend(extract_params(group))
#    return params

for param in extract_params(config_description):
    min[param['name']] = param['min']
    max[param['name']] = param['max']
    defaults[param['name']] = param['default']
    level[param['name']] = param['level']
    type[param['name']] = param['type']
    all_level = all_level | param['level']

