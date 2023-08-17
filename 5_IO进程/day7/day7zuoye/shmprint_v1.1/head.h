#ifndef __HEAD_H__
#define __HEAD_H__
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

struct shm
{
    int flag;
    ssize_t s; //read返回值（即终端输入的字符个数）
    char buf[32];
};

#endif