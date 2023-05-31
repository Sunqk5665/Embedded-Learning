C_plus day2



static初始化时要定义一个常量（确定的值）

## 函数

1.定义：函数是一个完成特定功能的代码模块，其程序代码独立

2.格式：

```c
(存储类型) 数据类型 函数名（形式参数）
{

	函数体；
	return 常量、变量或表达式；
}

int add(int a, int b)
{
	return a + b;
}
```

3.调用：

​	函数名(实参)；

4.声明：

​	数据类型 函数名（形式参数）；

​	int add(int a, int b);

​	int add(int, int);

> 函数声明时存储类型后面的形参可以省略
>
> 如已经写好一个函数int fun(int a,int b)，则在程序开头声名此函数时可以写为int fun(int,int);

5.函数的传参：

1）值传递：只是将值进行传递，对传递的值不会产生影响(复制传递)

2）地址传递：将地址进行传递，在子函数中改变地址中的内容时，会对主函数的变量的值产生影响

3）数组传递：例如 int array(int a[], int n)，进行数组传递时，并没有将整个数组进行传递，而是传递的是数组的首地址

## 指针函数

 本质：函数，函数的返回值为指针

格式：

```
数据类型 *函数名(参数)
{
	return 地址；//return NULL;
	//return 0；
	//return -1；
}
```

[![p9W5yRO.png](https://s1.ax1x.com/2023/05/17/p9W5yRO.png)](https://imgse.com/i/p9W5yRO)

常用到的两个函数：

 void *malloc(size_t size);

- 功能：手动申请空间，申请的空间在堆区

- 参数：申请的空间大小

- 返回值：任意类型指针

void free(void *ptr);

- 功能：释放空间
- 参数：要释放的空间
- 返回值：无  

## 函数指针

> 在实际嵌入式开发中，自己写函数指针的情况比较少，主要是用系统的比较多，可以根据系统所定义的函数的函数指针参数来还原其函数，格式要会写。

本质：指针，指向函数的指针

> char st[] = "hello";
> char *p = st;
> 用指针(p)代替st，st
>
> 什么类型的指针指向什么类型的数👇
> int a;int *p;
> char ch,char *q;

格式🚨：**数据类型 (*函数指针变量名)（参数）；**

用法：

1）当一个函数指针指向了一个函数，就可以通过这个指针来调用该函数，

[![p9W52sH.png](https://s1.ax1x.com/2023/05/17/p9W52sH.png)](https://imgse.com/i/p9W52sH)

2）函数指针可以 **将函数作为参数** 传递给其他函数调用。

[![p9W5hdI.png](https://s1.ax1x.com/2023/05/17/p9W5hdI.png)](https://imgse.com/i/p9W5hdI)

异步通信方式（进程之间）

异步通信方式（进程之间）→进程间通信方式

​	ctrl+c → 触发一个信号

​	Linux底层收到信号后，对进程进行一些动作（终止（杀死））。

​	signal(int signum, void (*handler)(int))；

![img](https://cdn.nlark.com/yuque/0/2023/png/26080541/1680246209512-f63c6462-05d5-4a8b-8541-c66347eb5f31.png)

![img](https://cdn.nlark.com/yuque/0/2023/png/26080541/1680246195422-39a46b6c-3f66-4ea3-9d5e-dce04ffbd807.png)

​	kill -l

![img](https://cdn.nlark.com/yuque/0/2023/png/26080541/1680246229789-14499005-d55f-4000-8018-c7571b90ae3a.png)

![img](https://cdn.nlark.com/yuque/0/2023/png/26080541/1680246322260-6b55b69e-1efa-438f-b190-7574133ae3e3.png)

![1684330448993](C:\Users\Sunqker\AppData\Roaming\Typora\typora-user-images\1684330448993.png)

​	异步通信方式；

![img](https://cdn.nlark.com/yuque/0/2023/png/26080541/1680246336364-7a4fda0b-c3f8-49f8-8542-c8d0f72aaff4.png)

![img](https://cdn.nlark.com/yuque/0/2023/png/26080541/1680246255697-86bf4dd1-9091-47ce-a7d9-ed4ae71734af.png)

问题：指针函数和函数指针分别在什么地方用🚨？

当需要这个函数返回地址时，用指针函数。

函数指针：

- signal函数参数 （信号处理函数）
- pthread_create函数的参数 （线程的处理函数）

![img](https://cdn.nlark.com/yuque/0/2023/png/26080541/1680246202253-1074c5e2-a3ad-4400-bfdc-b87566504385.png)

​	底层（file_operations结构体里成员（））

要求：

1：知道函数指针，能倒退还原函数

2：有函数，要让指针指向这个函数，要能定义出函数指针

​	注意：数据类型（包括返回值的数据类型，参数的数据类型）



## 函数指针数组

本质：是数组，数组的内容为函数指针（即函数地址）

格式：数据类型 (*函数指针数组名[下标])（参数）;

![1684330980503](C:\Users\Sunqker\AppData\Roaming\Typora\typora-user-images\1684330980503.png)

函数指针数组用的比较少，因为该数组中的元素全部为定义好的同类函数（具有相同返回值，函数参数个数及函数参数类型）的首地址，所以在使用时有一定的限制。



## 代码调试

> 常用调试方式
>
> - GDB调试
> - printf 打印

### GDB调试

在用GDB调试之前确定你的代码没有语法错误。设置断点的时候，必须让主函数运行 (run🏃) 起来。第一次断点设置，设置在主函数当中的某一行，这样编译器才能从入口函数进来。在gcc编译选项中一定要加入‘-g’。只有在代码处于“运行”或“暂停”状态时才能查看变量值。设置断点后程序在指定行之前停止。 

多用于段错误（因为所写程序如果有段错误，在运行的时候终端不提示段错误是在哪一行）

GDB调试方式（举例说明）

例子：

先制造一个产生段错误的代码👇

![1684331541287](C:\Users\Sunqker\AppData\Roaming\Typora\typora-user-images\1684331541287.png)

1)  gcc -g test.c 将要调试的程序加上“-g”进行调试，使生成的可执行文件能够进行gdb调试。

2)  gdb a.out 开始gdb调试

3)（gdb）l：列出源文件内容（l是非必要命令，可以不执行，可用cat看）

4）（gdb）b 10：设置断点在第10行（注意🚨断点要设置在主函数）

![img](https://cdn.nlark.com/yuque/0/2023/png/26080541/1680246370617-9aa7052c-7de0-4e16-b430-efc060c8c952.png)

5）（gdb）r :运行（设置断点后一定要先运行，才能进行单步调试往下）

![img](https://cdn.nlark.com/yuque/0/2023/png/26080541/1680246376726-23604d89-597f-4733-82b6-515d77643bc1.png)

6）（gdb）n:单步调试（断点行是不被运行的，n单步调试的时候不进子函数）

![img](https://cdn.nlark.com/yuque/0/2023/png/26080541/1680246381905-877750b5-fb44-4e7f-a01e-e6b282ff8c86.png)

![img](https://cdn.nlark.com/yuque/0/2023/png/26080541/1680246400747-0947a711-f376-4f78-8266-0aecef6b591a.png)

![img](https://cdn.nlark.com/yuque/0/2023/png/26080541/1680246388501-58c0e9b5-57c8-4e37-a592-02661a674176.png)

7）（gdb）s:单步运行（断点行是不被运行的，s单步调试的时候进子函数）

单步调试时：（s进入子函数，16版本的虚拟机有问题，想进入系统函数）

![img](https://cdn.nlark.com/yuque/0/2023/png/26080541/1680246473552-f2915763-0e07-4cc8-bb96-41001da943d1.png)

在Ubuntu12中可以，如下👇（16版本是32位版的最后一个版本，部分功能不太稳定）

![img](https://cdn.nlark.com/yuque/0/2023/png/26080541/1680246505198-47f195f3-7373-4a33-9fbf-115218136601.png)

8)（gdb）p 变量名 ：查看调试过程中的变量值

9）q：退出调试界面

![MP4(2I21(ES3GYSJE_~7K)U.png](https://cdn.nlark.com/yuque/0/2023/png/26080541/1680246410905-e1738ea5-7e25-42a3-b96e-8ae9354c818d.png?x-oss-process=image%2Fresize%2Cw_1237%2Climit_0)

10）info b：查看断点的情况（执行该命令会在下面显示你所设置的所有断点）![image.png](https://cdn.nlark.com/yuque/0/2023/png/26080541/1684313117223-bf91c23a-e105-4f7d-8099-c1a6112b9e96.png?x-oss-process=image%2Fresize%2Cw_1237%2Climit_0)

11）clear 行号：删除断点

![image.png](https://cdn.nlark.com/yuque/0/2023/png/26080541/1684313099019-3e25156d-5814-4767-a254-5a3e7ef0f2f4.png?x-oss-process=image%2Fresize%2Cw_1237%2Climit_0)



### printf 打印调试

格式：

```c
printf("%s,%s,%d\n",__FILE__,__func__,__LINE__);
```

这种方式只是大概定位，缩小寻找错误的范围。

作用：定位错误

- 如果这一行打印了，那么引起错误的代码肯定在这一行之后
- 如果这一行没有打印，那么引起错误的代码肯定在这一行之前









总结：

网络问题

连接方式 ：桥接，net，首选桥接

net设置注意  

设置完重启

还原网络设置，要退出安全软件，还原还不行，

固定IP，公司网线，

Windows查看IP->ipconfig

linux查看。。。设置。。。ifconfig。。。重启

apt-get三条指令

指针函数

函数指针，自己写少，用系统的多，可以根据系统的还原函数，格式要会写

函数指针数组 用的少

昨天笔试题

调试







