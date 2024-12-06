from sympy import symbols, sympify, lambdify
import sympy as sp
import numpy as np
import matplotlib.pyplot as plt


def calculate_f12(fmax,Tmax,t_rise,t_fall, T_gait):

    # 人体数据加载
    human_data={}
    with open('./data/human_data.txt', 'r') as file:
        for line in file:
            # 去除换行符并分割每行
            line = line.strip()
            # 以冒号分割变量名和数组部分
            var_BQname, values = line.split(':')
            # 将字符串中的数字存储为列表
            arr = list(map(float, values.split()))
            human_data[var_BQname] = arr
    # print(human_data.keys())


    # Define symbols
    F1, xp1, yp1, zp1, theta_a, phi_a, theta_s, phi_s, F2, xp2, yp2, zp2 = sp.symbols('F1 xp1 yp1 zp1 theta_a phi_a theta_s phi_s F2 xp2 yp2 zp2')
    flexion, inversion, adduction = sp.symbols('flexion inversion adduction')
    Mx_d, My_d, Ma_d, Ms_d = sp.symbols('Mx_d My_d Ma_d Ms_d')
    Mx, My = sp.symbols('Mx My')
    Mx, My = sp.symbols('Mx My')


    # 数据导入
    equations = {}
    with open('./data/equation.txt', 'r') as f:
        for line in f:
            name, expr_str = line.strip().split('=', 1)
            equations[name] = sympify(expr_str)
    # print(equations.keys())


    # 辅助力曲线生成
    
    t_f = np.linspace(0, T_gait, 100)
    f_assist = np.zeros(100)
    tsta=int(np.round((Tmax-t_rise/T_gait)*100))
    tmax=int(np.round(Tmax*100))
    tend=int(np.round((Tmax+t_fall/T_gait)*100))
    x=t_f[tsta:tmax]-t_f[tsta] # 上升阶段
    f_assist[tsta:tmax]=4*fmax*pow(x,3)/ pow(t_rise,3)-3*fmax*pow(x,4)/pow(t_rise,4)
    x=t_f[tmax:tend]-t_f[tmax] # 下降阶段
    f_assist[tmax:tend]=fmax-4*fmax*pow(x,3)/pow(t_fall,3)+3*fmax*pow(x,4)/pow(t_fall,4)
    # plt.figure()
    # plt.plot(t_f, f_assist)
    # plt.show()# 显示图形


    # 辅助力规划
    theta_a_ = np.deg2rad(6)
    phi_a_ = np.deg2rad(10)
    theta_s_ = np.deg2rad(16)
    phi_s_ = np.deg2rad(42)
    xp1_, yp1_, zp1_ = -0.07, 0.03, -0.11
    xp2_, yp2_, zp2_ = -0.07, -0.03, -0.11
    values_to_substitute = {
        theta_a: theta_a_, phi_a: phi_a_, theta_s: theta_s_, phi_s: phi_s_, xp1: xp1_, yp1: yp1_, zp1: zp1_, xp2: xp2_, yp2: yp2_, zp2: zp2_
        }
    t = np.arange(0, 100, 1)
    flexion_ = human_data['flexion_']
    inversion_ =  human_data['inversion_']
    adduction_ = t * 0

    Mx_=0.05*f_assist*np.array(human_data["M_x_d_"])/(np.array(human_data["M_x_d_"])+np.array(human_data["M_y_d_"])) # x 是距下关节
    My_=0.05*f_assist*np.array(human_data["M_y_d_"])/(np.array(human_data["M_x_d_"])+np.array(human_data["M_y_d_"]))

    F1_expr = equations['F1_j'].subs(values_to_substitute)
    F2_expr = equations['F2_j'].subs(values_to_substitute)
    F1_func = lambdify([flexion, inversion, adduction, Mx_d, My_d], F1_expr, 'numpy')
    F1_func1 = F1_func(flexion_, inversion_, adduction_, Mx_, My_)
    F2_func = lambdify([flexion, inversion, adduction, Mx_d, My_d], F2_expr, 'numpy')
    F2_func1 = F2_func(flexion_, inversion_, adduction_, Mx_, My_)

    # # Plotting the results
    # plt.figure()
    # plt.plot(t, F1_func1, label='F1')
    # plt.plot(t, F2_func1, label='F2')
    # plt.legend()
    # plt.show()# 显示图形

    # 输出参数
    f_max_1 = np.max(F1_func1)
    t_sta_1 = np.where(F1_func1 > 1)[0][0]
    t_rise_1= np.argmax(F1_func1) - np.where(F1_func1 > 1)[0][0]
    t_fall_1= np.where(F1_func1 > 1)[0][-1] - np.argmax(F1_func1)

    print("f_max_1:",f_max_1)
    print("t_sta_1:",t_sta_1)
    print("t_rise_1:",t_rise_1)
    print("t_fall_1:",t_fall_1)

    f_max_2 = np.max(F2_func1)
    t_sta_2 = np.where(F2_func1 > 1)[0][0]
    t_rise_2= np.argmax(F2_func1) - np.where(F2_func1 > 1)[0][0]
    t_fall_2= np.where(F2_func1 > 1)[0][-1] - np.argmax(F2_func1)

    return f_max_1,t_sta_1,t_rise_1,t_fall_1,f_max_2,t_sta_2,t_rise_2,t_fall_2

if __name__ == '__main__': # 判断当前脚本是否是直接执行的主程序，而不是作为模块被导入到其他脚本中
    fmax,Tmax,t_rise,t_fall, T_gait = 150,0.52,0.31,0.11,1.1
    f_max_1,t_sta_1,t_rise_1,t_fall_1,f_max_2,t_sta_2,t_rise_2,t_fall_2 = calculate_f12(fmax,Tmax,t_rise,t_fall, T_gait)

    pass
