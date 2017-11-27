#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc,char *argv[])
{
    if(argc<2)
    {
        printf(2,"Usage: touch files...\n");
        return 0;
    }
    int i,err;
    for(i=1;i<argc;i++)
    {
        err=open(argv[i],O_RDWR|O_CREAT,0644);
        if(err==-1)
        {
            printf(2,"Error where creating %s\n",argv[i]);
            return -1;
        }
        close(err);
    }
    return 0;
}