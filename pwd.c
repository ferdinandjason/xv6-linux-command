#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

int main(int argc,char *argv[])
{
    char cwd[100];
    int logical=0,physical=1;
    int err=open("/temp.pwd",O_RDONLY);
    if(argv[1][0]=='-')
    {
        if(strcmp(argv[1],"-L")==0) {logical=1;physical=0;}
        if(strcmp(argv[1],"-P")==0) physical=1;
        if(strcmp(argv[1],"-H")==0) ;// version function
        if(strcmp(argv[1],"-V")==0) ;// help function
    }
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
    // di xv6 tidak ada symlink.    
    if(logical==1 || physical==1 || logical==0)
        printf(1,"%s\n",cwd);
    exit();
}
