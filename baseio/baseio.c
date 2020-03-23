#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main()
{
  int fd = -1;
  fd = open("./test.txt",O_RDWR|O_CREAT|O_EXCL,0777);
  if(fd <0)
  {
    perror("open error");
    return -1;
  }

  char* ptr = "make me happy\n";
  int ret = write(fd,ptr,strlen(ptr));


  if(ret<0)
  {
    perror("write error");
    return -1;
  }

  printf("ret: %d\n",ret);
  close(fd);
  
  return 0;
}

