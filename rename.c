#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"
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
  // printf(2,"MASUK\n");
  // printf(1,"1 %s\n",argv1);
  // printf(1,"2 %s\n",argv2);
  // printf(1,"mv : %s %s\n",argv1,argv2);
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
int main(int argc,char *argv[]){
	char oldname[1000],newname[1000];
	strcpy(oldname,argv[1]);
	strcpy(newname,argv[2]);
	rename(oldname,newname);
	exit();
}
