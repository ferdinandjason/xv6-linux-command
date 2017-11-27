#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

int main()
{
    char cwd[100];
    int err=open("/temp.pwd",O_RDONLY);
    if(err<0) 
    {
        printf(1,"/\n");
        exit();
    }
    int red=read(err,cwd,sizeof(cwd));
    if(red<0)
    {
        printf(2,"ERROR\n");
        exit();
    }
    close(err);
    printf(1,"%s\n",cwd);
    exit();
}