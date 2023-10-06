#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int fd = open("c.txt",O_RDWR);
    if(fd < 0)
    {
        perror("open err");
        return -1;
    }
    lseek(fd, 5, SEEK_SET);
    write(fd,"m",1);

    lseek(fd,-2, SEEK_CUR);
    write(fd,"Sunqk",5);

    lseek(fd,30,SEEK_CUR);
    write(fd,"dadada", 6);

    off_t len = lseek(fd,0,SEEK_END);
    printf("file len = %ld\n",len);
    close(fd);
    return 0;
}
