#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

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

int delete(char *argv){
    return unlink(argv);
}

void rekursi(char path[512])
{
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
      delete(path);
      break;
    case T_DIR:
      strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf(1, "rek: cannot stat %s\n", buf);
        continue;
      }
      if(buf[strlen(buf)-1]=='.') continue;
      if(strcmp(fmtname(buf),".")==0 || strcmp(fmtname(buf),"..")==0) continue;
      if(st.type==T_DIR){
        char he[512];
        strcpy(he,buf);
        rekursi(he);
        delete(buf);
      }
      else if(st.type==T_FILE){
        char hehe[512];
        strcpy(hehe,buf);
        delete(hehe);
      }
    }
    break;
  }
  close(fd);
}

int main(int argc,char *argv[]){
    int i;
    if(argc < 2){
        printf(2,"Usage: rm files...\n");
    }
    int rekursif=0,idx=-1;
    for(i=1;i<argc;i++){
        if(strcmp(argv[i],"-rf")==0){
            rekursif=1;
            idx=i+1;
        }
    }
    if(idx>=argc){
      printf(2,"Usage: rm -rf files...\n");
    }
    if(rekursif==1){
      for(i=idx;i<argc;i++){
          rekursi(argv[i]);
          delete(argv[i]);
      }
    }
    else{
      for(i=1;i<argc;i++){
          if(delete(argv[i])<0){
              printf(2,"rm: %s failed to delete\n",argv[i]);
              exit();
          }
      }
    }
    exit();
}
