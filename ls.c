#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

int lo=0;
int dot=0;
int help=0;

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
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

void
ls(char *path)
{
  char buf[512], *p;
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
    printf(1, "%s %d %d %d\n", fmtname(path), st.type, st.ino, st.size);
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
      if(dot==0 && de.name[0]=='.')
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf(1, "ls: cannot stat %s\n", buf);
        continue;
      }
      if(lo==1)
      {
        if(st.type==T_DIR) printf(1, "\033[1m\x1B[34m%s\x1B[0m %d %d %d\n", fmtname(buf), st.type, st.ino, st.size);
        else if(st.type==T_DEV) printf(1, "\033[1m\x1B[31m%s\x1B[0m %d %d %d\n", fmtname(buf), st.type, st.ino, st.size);
        else printf(1, "%s %d %d %d\n", fmtname(buf), st.type, st.ino, st.size);
      }
      else
      {
        if(st.type==T_DIR) printf(1, "\033[1m\x1B[34m%s\x1B[0m\n", fmtname(buf));
        else if(st.type==T_DEV) printf(1, "\033[1m\x1B[31m%s\x1B[0m\n", fmtname(buf));
        else printf(1, "%s\n", fmtname(buf));
      }
    }
    break;
  }
  close(fd);
}

int
main(int argc, char *argv[])
{
  int i;
  for(i=1;i<argc;i++)
  {
    if(argv[i][0]=='-')
    {
      if(strcmp(argv[i],"-l")==0) lo=1;
      else if(strcmp(argv[i],"-a")==0) dot=1;
      else if(strcmp(argv[i],"--help")==0) help=1;
      else printf(1,"invalid OPTIONS try 'ls --help' for more information ");
    }
  }
  if(help)
  {
    printf(1,"Usage : \033[1mls\x1B[0m [OPTION]... [FILE]...\n");
    printf(1,"List information about the FILEs (the current directory by default).\n");
    printf(1,"OPTION:\n");
    printf(1,"\t\033[1m-a\x1B[0m do not ignore entries starting with .\n");
    printf(1,"\t\033[1m-l\x1B[0m use a long listing format\n");
  }
  if(argc < 2)
  {
    ls(".");
    exit();
  }
  else if((lo==1 || dot==1 || help==1) && argc < 3)
  {
    ls(".");
    exit();
  }
  else if((lo==1 || dot==1 || help==1) && argc < 4)
  {
    ls(argv[2]);
    exit();
  }
  else
  {
    ls(argv[1]);
    exit();
  }
  exit();
}
