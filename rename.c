#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"
char*
strcat(char *d,char *s)
{
    char *temp=d;
    while(*d) ++d;
    while(*s) *d++=*s++;
    *d=0;
    return temp;
}
char *strncpy(char *s, const char *t, int n)
{
  int i;
  char *os;
  os = s;
  for (i = 0; i < n; i++)
  {
    s[i] = t[i];
  }
  return os;
}
void rename(char *argv1, char *argv2)
{
  if(argv1[0]=='.' && argv1[1]=='.') return;
  char buf[512];
  int fd0, fd1, n;
  if ((fd0 = open(argv1, O_RDONLY)) < 0)
  {
    printf(2, "mv: cannot open %s\n", argv1);
    exit();
  }
  char temp[512];
  strncpy(temp, argv1, strlen(argv1));
  if (unlink(argv1) < 0)
  {
    printf(2, "error moving %s\n", argv1);
    exit();
  }
  if ((fd1 = open(argv2, O_CREATE | O_RDWR)) < 0)
  {
    printf(2, "mv: cannot open %s\n", argv2);
    exit();
  }
  while ((n = read(fd0, buf, sizeof(buf))) > 0)
  {
    write(fd1, buf, n);
  }
  close(fd0);
  close(fd1);
}
void
mv_rek(char *from,char *ext1,char *ext2)
{
    //char buff[1024];
    int fd0;
    struct dirent de;
    struct stat st;
    printf(1,"%s %s\n",ext1,ext2);
    if((fd0=open(from,0))<0)
    {
        printf(2,"mv: cannot open '%s' No such file or directory\n",from);
        exit();
    }
    if(fstat(fd0,&st)<0)
    {
        printf(2,"mv: cannot stat '%s' No such file or directory\n",from);
        exit();
    }
    //char temp[512],temp2[512];
    int a;
    switch(st.type)
    {
        case T_FILE:
        {
            rename(ext1,ext2);
            break;
        }
        case T_DIR:
        {
		int flag=0;
		while(read(fd0,&de,sizeof(de))==sizeof(de)){
			if(de.inum==0 || de.name[0]=='.') continue;
			int idx=strlen(ext1)-1;
			//printf(1,"%d\n",strlen(de.name));
			for(a=strlen(de.name)-1;a>strlen(de.name)-strlen(ext1);a--){
			//printf(1,"%d\n",a);
				if(de.name[a]!=ext1[idx]){
					flag=1;
					break;
				}
			}
			idx--;
		if(flag)continue;
		printf(1,"%s\n",de.name);
		}
            break;
	}
    }
    close(fd0);
}
int main(int argc,char *argv[]){
	//rename 's\.ext1\/.ext2/' namafile1 namafile2 ...
	char *ext1,*ext2;
    ext1=(char*)malloc(100*sizeof(char));
    ext2=(char*)malloc(100*sizeof(char));
	//int s=0,y=0;
	int idx=0,a,b;
	//if(argv[1][1]=='s') s=1;
	//if(argv[1][1]=='y') y=1;
	for(a=3;a<strlen(argv[1]);a++){
		if(argv[1][a]=='\\') break;
		ext1[idx++]=argv[1][a];
	}
	a+=2;
	idx=0;
	for(;a<strlen(argv[1]);a++){
		if(argv[1][a]=='/') break;
		ext2[idx++]=argv[1][a];
	}
	if(argv[2][0]=='*'){
		mv_rek(".",ext1,ext2);	
	}
	printf(1,"%s %s\n",ext1,ext2);
	for(a=2;a<argc;a++){
		char *tmp;
        tmp=(char*)malloc(100*sizeof(char));
		strcpy(tmp,argv[a]);
		int len=strlen(ext1);
		int len2=strlen(argv[a]);
		idx=0;
		for(b=len2-len;;b++){
			tmp[b]=ext2[idx];
			idx++;
			if(idx==strlen(ext2)) break;
		}
		for(;idx<strlen(ext1);idx++){
			tmp[++b]=0;	
		}
		rename(argv[a],tmp);
        free(tmp);
	}
    free(ext1);
    free(ext2);
	exit();
}
