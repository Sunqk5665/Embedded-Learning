#include "thttpd.h"
#include "custom_handle.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>

int init_server(int _port) //创建监听套接字
{
	int sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		perror("socket failed");
		exit(2);
	}

	//设置地址重用
	int opt=1;                     
	setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

	struct sockaddr_in local;
	local.sin_family=AF_INET;
	local.sin_port=htons(_port);
	local.sin_addr.s_addr=INADDR_ANY;
	
	if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
	{
		perror("bind failed");
		exit(3);
	}
	if(listen(sock,5)<0)
	{
		perror("listen failed");
		exit(4);
	}

	return sock;
}

static int get_line(int sock,char* buf)   //按行读取请求报头
{
	char ch='\0';
	int i=0;
	ssize_t ret=0;
	while(i<SIZE && ch!='\n')
	{
		ret=recv(sock,&ch,1,0);
		if(ret>0&&ch=='\r')
		{
			ssize_t s=recv(sock,&ch,1,MSG_PEEK);
			if(s>0&&ch=='\n')
			{
				recv(sock,&ch,1,0);
			}
			else
			{
				ch='\n';
			}
		}
		buf[i++]=ch;
	}
	buf[i]='\0';
	return i;
}


static void clear_header(int sock)    //清空消息报头
{
	char buf[SIZE];
	int ret=0;
	do
	{
		ret=get_line(sock,buf);
	}while(ret!=1&&(strcmp(buf,"\n")!=0));
}


static void show_404(int sock)      //404错误处理
{
	clear_header(sock);
	char* msg="HTTP/1.0 404	Not Found\r\n";
	send(sock,msg,strlen(msg),0);         //发送状态行
	send(sock,"\r\n",strlen("\r\n"),0);   //发送空行

	struct stat st;
	stat("wwwroot/404.html",&st);
	int fd=open("wwwroot/404.html",O_RDONLY);
	sendfile(sock,fd,NULL,st.st_size); //发送文件
	close(fd);
}

void echo_error(int sock,int err_code)    //错误处理
{
	switch(err_code)
	{
	case 403:
		break;
	case 404:
		show_404(sock);
		break;
	case 405:
		break;
	case 500:
		break;
	defaut:
		break;
	}
}

//处理资源
static int echo_www(int sock,const char * path,size_t s)  //处理非CGI的请求
{
	int fd=open(path,O_RDONLY);
	if(fd<0)
	{
		echo_error(sock,403);
		return 7;
	}

	char* msg="HTTP/1.0 200 OK\r\n";
	send(sock,msg,strlen(msg),0);         //发送状态行
	send(sock,"\r\n",strlen("\r\n"),0);      //发送空行
	
	//sendfile方法可以直接把文件发送到网络对端
	if(sendfile(sock,fd,NULL,s)<0)
	{
		echo_error(sock,500);
		return 8;	
	}
	close(fd);
	return 0;
}


static int handle_request(int sock,const char* method,\
		const char* path,const char* query_string)
{//处理GET和POST有数据的请求
	char line[SIZE];
	int ret=0;
	int content_len=-1;
	if(strcasecmp(method,"GET")==0)
	{
		//清空消息报头
		clear_header(sock);
		//...
	}
	else
	{
		//获取post方法的参数大小
		do
		{
			ret=get_line(sock,line);
			if(strncasecmp(line,"content-length",14)==0)  //post的消息体记录正文长度的字段
			{
				content_len=atoi(line+16);	//求出正文的长度
			}
		}while(ret!=1&&(strcmp(line,"\n")!=0));
	}

	printf("method = %s\n", method);
	printf("query_string = %s\n", query_string);
	printf("content_len = %d\n", content_len);

	char req_buf[4096] = {0};

	//如果是POST方法，那么肯定携带请求数据，那么需要把数据解析出来
	if(strcasecmp(method,"POST")==0)
	{
		int len = recv(sock, req_buf, content_len, 0);
		printf("len = %d\n", len);
		printf("req_buf = %s\n", req_buf);/*req_buf是请求的数据*/
	}

	//先发送状态码
	char* msg="HTTP/1.1 200 OK\r\n\r\n";
	send(sock,msg,strlen(msg),0);

	//请求交给自定义代码来处理，这是业务逻辑
	parse_and_process(sock, query_string, req_buf);

	return 0;
}


int handler_msg(int sock)       //浏览器请求处理函数
{
	char del_buf[SIZE] = {};

	//通常recv()函数的最后一个参数为0，代表从缓冲区取走数据
	//而当为MSG_PEEK时代表只是查看数据，而不取走数据。
	recv(sock,del_buf,SIZE,MSG_PEEK); //拿走还在，只是看看（缓冲区还有数据）

#if 1 //初学者强烈建议打开这个开关，看看tcp实际请求的协议格式
	puts("---------------------------------------");
	printf("recv:%s\n",del_buf);
	puts("---------------------------------------");
#endif

	//接下来method方法判断之前的代码，可以不用重点关注
	//知道是处理字符串，把需要的信息过滤出来即可
	char buf[SIZE];
	int count=get_line(sock,buf);
	int ret=0;
	char method[32];
	char url[SIZE];
	char *query_string=NULL;
	int i=0;
	int j=0;
	int need_handle=0;

	//获取请求方法和请求路径
	while(j<count)
	{
		if(isspace(buf[j]))
		{
			break;
		}
		method[i]=buf[j];	
		i++;
		j++;
	}
	method[i]='\0';
	while(isspace(buf[j])&&j<SIZE)      //过滤空格
	{
		j++;
	}

	/*这里开始就开始判断发过来的请求是GET还是POST了*/
	if(strcasecmp(method,"POST") && strcasecmp(method,"GET"))//忽略大小写比较
	{
		printf("method failed\n");  //如果都不是，那么提示一下
		echo_error(sock,405);
		ret=5;
		goto end;
	}

	if(strcasecmp(method,"POST")==0)
	{
		need_handle=1; //后面需要特殊处理，置1
	}	
	//获取请求路径和数据
	/*此时若是GET请求，还不能确定是否需要处理*/
	/*需要看一下url后面是否有数据*/
	i=0;
	while(j<count)
	{
		if(isspace(buf[j]))
		{
			break;
		}
		if(buf[j]=='?')
		{
			//将资源路径（和附带数据，如果有的话）保存再url中，并且query_string指向附带数据
			query_string=&url[i];
			query_string++;
			url[i]='\0';
		}
		else{
			url[i]=buf[j];
		}
		j++;
		i++;
	}
	url[i]='\0';

	printf("query_string = %s\n", query_string);

	//浏览器通过http://192.168.8.208:8080/?test=1234这种形式请求
	//是携带参数的意思，那么就需要额外处理了
	/*如果是GET请求且url后面有数据，则需要处理*/
	if(strcasecmp(method,"GET")==0&&query_string!=NULL) 
	{
		need_handle=1;
	}

	/*如果url后面不是参数，需给定一个资源路径*/
	//我们把请求资源的路径固定为wwwroot/下的资源，这个自己可以改
	char path[SIZE];
	sprintf(path,"wwwroot%s",url);       
	
	printf("path = %s\n", path);
	
	//如果请求地址没有携带任何资源（只有网址），那么默认返回index.html
	if(path[strlen(path)-1]=='/')  //判断浏览器请求的是不是目录
	{
		strcat(path,"index.html"); //如果请求的是目录，则就把该目录下的首页返回回去
	}

	/*如果请求的资源不存在，就要返回传说中的404页面了*/
	struct stat st;   
	if(stat(path,&st)<0)   //获取客户端请求的资源的相关属性
	{
		printf("can't find file\n");
		echo_error(sock,404);
		ret=6;
		goto end;
	}

	//到这里基本就能确定是否需要自己的程序来处理后续请求了
	printf("need progress handle:%d\n",need_handle);

	//如果是POST请求或者带参数的GET请求，就需要我们自己来处理了
	//这些是业务逻辑，所以需要我们自己写代码来决定怎么处理
	if(need_handle)/*需要对数据进行处理*/
	{   /*处理带参数的GET请求 或 POST请求*/
		ret=handle_request(sock,method,path,query_string); //处理请求
	}
	else /*不需要对数据处理，而资源又存在  是GET请求*/
	{
		clear_header(sock);
		//如果是GET方法，而且没有参数，则直接返回资源	
		ret = echo_www(sock,path,st.st_size);  
	}
	
end:
	close(sock);
	return ret;
}


