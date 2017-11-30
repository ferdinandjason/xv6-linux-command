#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

int delete(char *argv){
    return unlink(argv);
}

int main(int argc,char *argv[]){
    int i;
    if(argc < 2){
        printf(2,"Usage: rm files...\n");
    }
    for(i=1;i<argc;i++){
        if(delete(argv[i])<0){
            printf(2,"rm: %s failed to delete\n",argv[i]);
            exit();
        }
    }
    exit()
}
