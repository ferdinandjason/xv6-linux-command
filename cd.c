#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"

int main(int argc,char *argv[])
{
    if(argc<2)
    {
        exit(0);
    }
    if(chdir(argv[1])!= 0)
    {
        exit(0);
    }
}