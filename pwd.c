#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

void 
help(){
    printf(1,"Usage:\n");
    printf(1,"pwd [OPTION]\n");
    printf(1,"Options:\n");
    printf(1,"-L : Menampilkan alamat meskipun terdapat symlinks\n");
    printf(1,"-P : Menampilkan alamat tanpa mengandung symlinks\n\n");
    printf(1,"--help : Memperlihatkan bantuan lalu exit\n");
    printf(1,"--versi : Menunjukkan informasi tentang versi lalu exit\n");
    printf(1,"Dikarenakan pada xv6 tidak terdapat synmlinks, maka fungsi dari opsi -L dan -P menjadi sama\n");
    exit();
}

void
prog(){
    printf(1,"pwd version 1.00\n");
    printf(1,"Dibuat oleh Ferdinand Jason, Nurlita Dhuha, Alvin Tanuwijaya, Bagus Aji Sinto\n");
    exit();
}

int main(int argc,char *argv[])
{
    char cwd[100];
    int logical=0,physical=1;
    int err=open("/temp.pwd",O_RDONLY);
    if(argv[1][0]=='-')
    {
        if(strcmp(argv[1],"-L")==0) {logical=1;physical=0;}
        if(strcmp(argv[1],"-P")==0) physical=1;
        if(strcmp(argv[1],"--help")==0) help();
        if(strcmp(argv[1],"--versi")==0) prog();
	else 
	{
		printf(1,"pwd: invalid opsi %s\nCoba ketik 'pwd --help' untuk info lebih lanjut\n",argv[1]);
		exit();
	}
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
