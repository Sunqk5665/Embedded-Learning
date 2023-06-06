#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
#if 0
/**********创建子进程之前打开文件************/
    FILE *fp = fopen("a.txt","r");
    if(fp == NULL)
    {
        perror("fopen err");
        return -1;
    }
    char buf1[32]={0};
    char buf2[32]={0};
    pid_t pid = fork();
    if(pid<0){
        perror("fork err");
        return -1;
    }
    else if(pid == 0){
        fread(buf1,sizeof(char),4,fp);
        printf("child read:%s\n",buf1);
        //while(1);
    }
    else{
        fread(buf2,sizeof(char),4,fp);
        printf("parent read:%s\n",buf2);
        //while(1);
    }
    //fclose(fp);
    return 0;
#endif
#if 1
/**********创建子进程之后打开文件************/
    char buf1[32]={0};
    //char buf2[32]={0};
    pid_t pid = fork();
    if(pid<0){
        perror("fork err");
        return -1;
    }
    else if(pid == 0){
        FILE *fp = fopen("a.txt","r");
        if(fp == NULL)
        {
            perror("fopen err");
            return -1;
        }
        fread(buf1,sizeof(char),4,fp);
        printf("child read:%s\n",buf1);
        fclose(fp);
        //while(1);
    }
    else{
        FILE *fp = fopen("a.txt","r");
        if(fp == NULL)
        {
            perror("fopen err");
            return -1;
        }
        fread(buf1,sizeof(char),4,fp);
        printf("parent read:%s\n",buf1);
        fclose(fp);
        //while(1);
    }
    return 0;
#endif
}
