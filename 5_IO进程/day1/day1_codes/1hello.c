#include <stdio.h>
int main(int argc, char const *argv[])
{
    // //1.\n
    // printf("hello world\n");// \n为行缓冲中刷新缓冲的条件

    //2.程序正常结束
    
    //3.缓存区满
    ////方法一：
    // for(int i = 0; i < 300; i++)
    //     printf("%4d",i); //256*4=1024 Byte
    ////方法二
    printf("buf");//作用：开辟缓存区
    printf("%d\n",stdout->_IO_buf_end - stdout->_IO_buf_base);
    // //4.强制刷新
    // printf("hello world");//不加'\n'，用下面的强制刷新
    // fflush(NULL);//强制刷新
    // while (1);
    return 0;
}
    
    
    
    
    
    
    // //1.\n
    // printf("hello world\n");// \n为行缓冲中刷新缓冲的条件

    //2.程序正常结束
    
    //3.缓存区满
    ////方法一：
    // for(int i = 0; i < 300; i++)
    //     printf("%4d",i); //256*4=1024 Byte
    ////方法二
    //printf("buf");//作用：开辟缓存区
    // printf("%d\n",stdout->_IO_buf_end - stdout->_IO_buf_base);