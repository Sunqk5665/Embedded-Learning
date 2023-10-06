/***********************************************************************************
Copy right:	    Coffee Tech.
Author:         jiaoyue
Date:           2022-03-24
Description:    http请求自定义处理部分
***********************************************************************************/

#ifndef CUSTOM_HANDLE_H
#define CUSTOM_HANDLE_H

#include <stdio.h>
#include <string.h>

int parse_and_process(int sock, const char *query_string, const char *input);

#endif  // CUSTOM_HANDLE_H
