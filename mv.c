#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char buf[512];

char* strncpy(char *s, const char *t, int n)
{
  int i;
  char *os;
  os = s;
  for(i=0;i<n;i++) {s[i]=t[i];}
  return os;
}

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
    printf(1,"%s\n",argv[1]);
    if((fd0=open(argv[1],O_RDONLY))<0)
    {
        printf(2,"mv: cannot open %s\n",argv[1]);
        exit();
    }
    char temp[512];
    strncpy(temp,argv[1],strlen(argv[1]));
    if(unlink(strcat("/",argv[1]))<0)
    {
        printf(2,"gagal %s\n",strcat("/",argv[1]));
    }
    strcat(argv[2],temp);
    if ((fd1=open(argv[2],O_CREATE|O_RDWR))<0)
    {
        printf(2,"mv: cannot open %s\n",argv[2]);
        exit();
    }
    while( (n=read(fd0,buf,sizeof(buf)))>0 )
    {
        write(fd1,buf,n);
    }
    close(fd0);
    close(fd1);
    exit();
}