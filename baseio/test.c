#include<stdio.h>
#include<string.h>
int main()
{
  FILE* fp = NULL;

  fp = fopen("./test.txt","r+");
  if(fp == NULL)
  {
    perror("fopen error");//打印上一个系统调用接口的使用错误原因
    return -1;
  }

  fseek(fp,0,SEEK_END);
  
  char* ptr  = "howtoexchangeourselves\n";
  int ret = fwrite(ptr,strlen(ptr),1,fp);//数据，块大小，块个数，数据流
  if(ret == 0)
  {
    perror("fwrite error");
    return -1;
  }

  //fseek
  printf("write ret:%d\n",ret);
 
  fseek(fp,0,SEEK_SET);
  char tmp[1024] = {0};
  ret = fread(tmp,1,1023,fp);
  if(ret == 0)
  {
    printf("have no data or error\n");
  }

  printf("ret: %d -[%s]\n",ret,tmp);
  
  fclose(fp);
  return 0;
}
