#ifndef _SHM_H_
#define _SHM_H_
/*
两个进程实现通信，一个进程循环从终端输入，另一个进程循环打印，当输入quit时结束。共享内存实现。
建议大家先用标志位的方式实现，不建议使用信号量。
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

struct ff
{
    int flag;
    char buf[32];
};

#endif