#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char buf[512];

char* strcat(char* s1,char *s2)
{
    char *b=s1;
    while(*s1) ++s1;
    while(*s2) *s1++ = *s2++;
    *s1=0;
    return b;
}

int main(int argc,char *argv[])
{
    int fd0,fd1,n;
    if(argc<=2)
    {
        printf(1,"Need 2 arguments!\n");
        exit();
    }
    if((fd0=open(argv[1],O_RDONLY))<0)
    {
        printf("mv: cannot open %s\n",argv[1]);
        exit();
    }
    strcat(argv[2],"/");
    strcat(argv[2],argv[1]);
    if ((fd1=open(argv[2],O_CREATE|O_RDWR))<0)
    {
        printf("mv: cannot open %s\n",argv[2]);
        exit();
    }
    while( (n=read(fd0,buf,sizeof(buff)))>0 )
    {
        write(fd1,buf,n);
    }
    unlink(argv[1]);
    close(fd0);
    close(fd1);
    exit();
}