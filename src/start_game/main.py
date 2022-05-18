#! /usr/bin/env python2
# -*- coding: utf-8 -*-
# 
# Python2 Python 2 Python2 重要的事情说三遍！
# ROS Melodic 不支持 Python3，使用 Python3 调用 ROS 提供的 API 有可能报错（如本程序）

from __future__ import print_function

import os
import time
from interactive import show, get_bool_ans, get_str_ans, save
from initialize import init, uninit
from ros_module import ROSNavNode

def open_terminal(commands):
    '''
    打开一个新的终端并执行命令
    未作参数检查，不要试图在传入的命令字符串中添加多余的引号，可能会引发错误
    '''
    cmd_list = []
    for cmd in commands:
        cmd_list.append(""" gnome-terminal --tab -e "bash -c '%s;exec bash'" >/dev/null  2>&1 """ %cmd)

    os.system(';'.join(cmd_list))

def launch_pkg():
    '''
    启动必要的程序
    '''

    nav_cmd = [
        'roslaunch gazebo_pkg race.launch', 
        'sleep 5; roslaunch gazebo_nav nav_teb.launch'
    ]
    open_terminal(nav_cmd)


    # open_terminal(cmd)
    time.sleep(10)

    while not get_bool_ans('Begin?'):
        show('')

def main():
    md5_result1 = init()                                             # 初始化
   

    launch_pkg()                                                     # 启动必要的程序



    # start = time.time()                                              # 开始比赛计时
    
    node = ROSNavNode()                                              # 启动节点
    start = node.curr_time.secs
    n_start = node.curr_time.nsecs
    show('begin...')
    node.send_goal()
    
    period = 30                                                      # 记录周期 30s
    log_start = node.curr_time.secs - period                                 # 保证刚开始导航时记录一次 Topic list
    while not node.get_state():
        if int(node.curr_time.secs - log_start) > period:                    # 每隔一个 period 记录一次 Topic list
            show(node.get_topic())
            save(node.get_topic())
            log_start = node.curr_time.secs
        # print(node.client.get_goal_status_text())
        time.sleep(0.1)

    end = node.curr_time.secs
    n_end = node.curr_time.nsecs
    cost = end - start
    if n_end>n_start:
        n_cost = n_end - n_start
    else:
        n_cost = n_end + 1000000000 - n_start

    n_cost = float(n_cost) / 1000000000.0

    show('共' + str(cost+n_cost) + ' 秒')
    save(str(cost+n_cost) + ' 秒 完成仿真')



    md5_result2 = uninit()                                           # 收尾工作
    
    if cmp(md5_result1, md5_result2) == 0:

        save('文件 MD5 校验通过')
    else:

        save('文件 MD5 校验失败，禁止修改资源文件！')

    get_str_ans('exit.')


if __name__  == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print('\node')
        show('操作已取消')
        exit(0)
