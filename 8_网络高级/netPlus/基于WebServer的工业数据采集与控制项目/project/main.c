#include "thttpd.h"
#include <sys/types.h>
#include <sys/wait.h>


static void* msg_request(void *arg)
{
	//这里客户端描述符通过参数传进来了
	int sock=(int)arg;
 
	// 一般情况下，线程终止后，其终止状态一直保留到其它线程调用pthread_join获取它的状态为止。
	//但是线程也可以被置为detach状态，这样的线程一旦终止就立刻回收它占用的所有资源，而不保留终止状态。
	pthread_detach(pthread_self());	

	//handler_msg作为所有的请求处理入口
	return (void*)handler_msg(sock);
	// //类似于下面
	// int ret = handler_msg(sock);
	// return (void *)ret;
}

int main(int argc,char* argv[])
{

	//如果不传递端口，那么使用默认端口80
	int port = 80;

	if(argc > 1) //指定端口
	{
		port = atoi(argv[1]);
	}

	//初始化服务器
	int lis_sock=init_server(port);

	while(1) //通过多线程实现并发服务器
	{
		struct sockaddr_in peer;
		socklen_t len=sizeof(peer);
		
		int sock=accept(lis_sock,(struct sockaddr*)&peer,&len);
		
		if(sock<0)
		{
			perror("accept failed");
			continue;
		}
		
		//每次接收一个连接后，会自动创建一个线程，这实际上就是线程服务器模型的应用
		pthread_t tid;
		if(pthread_create(&tid,NULL,msg_request,(void *)sock)>0)
		{
			perror("pthread_create failed");
			close(sock);
		}
	}
	return 0;
}
