#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  //memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

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

void mv(char *argv1,char *argv2)
{
    //printf(1,"%s %s\n",argv1,argv2);
    char buf[512];
    int fd0,fd1,n;
    if((fd0=open(argv1,O_RDONLY))<0)
    {
        printf(2,"mv: cannot open %s\n",argv1);
        exit();
    }
    char temp[512];
    strncpy(temp,argv1,strlen(argv1));
    if(unlink(argv1)<0)
    {
        printf(2,"error moving %s\n",argv1);
        exit();
    }
    strcat(argv2,temp);
    if ((fd1=open(argv2,O_CREATE|O_RDWR))<0)
    {
        printf(2,"mv: cannot open %s\n",argv2);
        exit();
    }
    while( (n=read(fd0,buf,sizeof(buf)))>0 )
    {
        write(fd1,buf,n);
    } 
    close(fd0);
    close(fd1);
}

void
ls(char *path,char *argv2)
{
  char buf[512],temp[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    printf(2, "ls: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    printf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type){
  case T_FILE:
    //printf(1, "%s %d %d %d\n", fmtname(path), st.type, st.ino, st.size);
    break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf(1, "ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      memset(temp,'\0',sizeof(temp));
      strcpy(temp,argv2);
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf(1, "ls: cannot stat %s\n", buf);
        continue;
      }
      if(strcmp(fmtname(buf),".")==0 || strcmp(fmtname(buf),"..")==0) continue;
      mv(fmtname(buf),temp);
    }
    break;
  }
  close(fd);
}


int main(int argc,char *argv[])
{
    if(argc<=2)
    {
        printf(1,"Need 2 arguments!\n");
        exit();
    }
    if(strcmp(argv[1],"*")==0)
    {
        printf(1,"hehe\n");
        ls(".",argv[2]);
    }
    else
    {
        mv(argv[1],argv[2]);
    }
    exit();
}