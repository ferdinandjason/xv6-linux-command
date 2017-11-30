#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

char buf[512];

char *
fmtname(char *path)
{
  static char buf[DIRSIZ + 1];
  char *p;
  // Find first character after last slash.
  for (p = path + strlen(path); p >= path && *p != '/'; p--);
  p++;
  // Return blank-padded name.
  if (strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  //memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

char *strcat(char *s1, char *s2)
{
  char *b = s1;
  while (*s1)
    ++s1;
  while (*s2)
    *s1++ = *s2++;
  *s1 = 0;
  return b;
}

void
cat(int fd1, int fd2)
{
  int n;

  while((n = read(fd1, buf, sizeof(buf))) > 0) {
    //write(1, buf, n);
    printf(fd2, "%s", buf);
  }
  if(n < 0){
    printf(1, "copy: read error\n");
    exit();
  }
}

void copy(char argv1[512],char argv2[512]){
  if(argv1[0]=='.' && argv1[1]=='.') return;
  int fd1;
  if((fd1 = open(argv1, 0)) < 0){
    printf(1, "copy: cannot open %s\n", argv1);
    exit();
  }
  char temp[512];
  strcpy(temp, argv1);
  int fd2;
  if(temp[0]=='.' && temp[strlen(temp)-1]!='/' && argv2[strlen(argv2)-1]=='/' ) strcat(argv2,temp+2);
  else if(temp[strlen(temp)-1]!='/' && argv2[strlen(argv2)-1]=='/') strcat(argv2, temp);
  if ((fd2 = open(argv2, O_CREATE | O_RDWR)) < 0) {
    printf(1, "copy: error initializing file: %s\n", argv2);
    exit();
  }
  cat(fd1,fd2);
  close(fd1);
  close(fd2);
}

void ls(char path[512], char argv2[512], int longz, char hehe[512])
{
  char buf[512], temp[512], *p;
  int fd;
  struct dirent de;
  struct stat st;
  if ((fd = open(path, 0)) < 0)
  {
    printf(2, "ls: cannot open %s\n", path);
    return;
  }
  if (fstat(fd, &st) < 0)
  {
    printf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }
  switch (st.type)
  {
  case T_FILE:
    //printf(1, "%s %d %d %d\n", fmtname(path), st.type, st.ino, st.size);
    break;

  case T_DIR:
    if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf)
    {
      printf(1, "ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf + strlen(buf);
    *p++ = '/';
    while (read(fd, &de, sizeof(de)) == sizeof(de))
    {
      if (de.inum == 0)
        continue;
      memset(temp, '\0', sizeof(temp));
      strcpy(temp, argv2);
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if (stat(buf, &st) < 0)
      {
        printf(1, "ls: cannot stat %s\n", buf);
        continue;
      }
      if(st.type==T_DIR) continue;
      if (strcmp(fmtname(buf), ".") == 0 || strcmp(fmtname(buf), "..") == 0)
        continue;
      if (strcmp(fmtname(buf) + (strlen(fmtname(buf)) - longz), hehe) == 0)
      {
        //printf(1,"%s\n",fmtname(buf));
        copy(fmtname(buf), temp);
      }
      //
    }
    break;
  }
  close(fd);
}


void rekursi(char path[512],char desti[512])
{
  //printf(1,"hmm ... %s %s\n",path,desti);
  char buf[512],*p;
  int fd;
  struct dirent de;
  struct stat st;
  if((fd=open(path,0))<0){
    printf(2,"rek: cannot open %s\n",path);
    exit();
  }
  if(fstat(fd,&st)<0){
    printf(2,"rek: cannot stat %s\n",path);
    close(fd);
    exit();
  }
  switch(st.type){
    case T_FILE:
      //mv(buf,desti);
      break;
    case T_DIR:
      strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      //memset(temp,'\0',sizeof(temp));
      //strcpy(temp,argv2);
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf(1, "rek: cannot stat %s\n", buf);
        continue;
      }
      if(buf[strlen(buf)-1]=='.') continue;
      if(strcmp(fmtname(buf),".")==0 || strcmp(fmtname(buf),"..")==0) continue;
      if(st.type==T_DIR){
        char tempe[512],he[512],he2[512];
        strcpy(tempe,desti);
        //printf(1,"%s\n",tempe);
        mkdir(strcat(tempe,buf+2));
        strcpy(he,buf);
        strcpy(he2,desti);
        //printf(1,"%s %s\n",tempe,desti);
        //printf(1,"%s-> %s\n",buf,desti);
        rekursi(he,he2);
      }
      else if(st.type==T_FILE){
        //printf(1,"file %s with tujuan %s\n",buf,desti);
        char hehe[512],hehe2[512];
        strcpy(hehe,buf);
        //printf(1,"%s \n",hehe);
        strcpy(hehe2,desti);
        //printf(1,"%s\n",hehe2);
        copy(hehe,hehe2);
        //printf(1,"mvnya selesai\n");
      }
      //if(strcmp(fmtname(buf),".")==0 || strcmp(fmtname(buf),"..")==0) continue;
      //if(strcmp(fmtname(buf)+(strlen(fmtname(buf))-longz),hehe)==0)
      //{
        //printf(1,"%s\n",fmtname(buf));
        //mv(fmtname(buf),temp);
      //}
      //
    }
    break;
  }
  close(fd);
}


int
main(int argc, char *argv[])
{
  if(argc < 3){
    printf(1, "copy : read error\n");
    exit();
  }
  if(argv[1][0]=='*'){
    int longz = strlen(argv[1]) - 1;
    char hehe[10];
    strcpy(hehe, argv[1] + 1);
    ls(".", argv[2], longz, hehe);
  }
  if(strcmp(argv[1],"-R")==0){
    char temp[512],temp2[512];
    strcpy(temp,argv[2]);
    strcpy(temp2,argv[3]);
    mkdir(strcat(temp2,temp));
    rekursi(argv[2],argv[3]);
  }
  
  exit();
}

