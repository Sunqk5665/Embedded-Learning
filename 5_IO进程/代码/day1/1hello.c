#include <stdio.h>
int main(int argc, char const *argv[])
{
    /**行缓冲刷新条件**/
#if 0
    // 1.\n
    printf("hello world\n");// '\n'为行缓冲中刷新缓冲的条件
    while(1);
#endif
#if 0
    //2.程序正常结束
    printf("hello");
    return 0;
#endif
#if 0
    //3.缓存区满
    /**测试缓冲区大小（如下两种方法）**/
    //方法一：//这里要不断缩小i的范围，试出合理的范围
    for(int i = 0; i < 300; i++)
        printf("%4d",i); //256*4=1024 Byte
    while(1);
    //方法二
    printf("buf=");//作用：开辟缓存区（不用不会开辟）
    //缓冲区的结束地址-缓冲区的其实地址
    printf("%d\n",stdout->_IO_buf_end - stdout->_IO_buf_base);
#endif
#if 1
    //4.强制刷新
    printf("hello world");//不加'\n'，用下面的强制刷新
    fflush(NULL);//强制刷新
    while (1);
#endif
}