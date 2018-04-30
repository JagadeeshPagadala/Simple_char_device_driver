#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
//#include<linux/fcntl.h>
#include <fcntl.h>

int main(int argc,char* argv[])
{
   int sz=1024,i=0;
   int fd,fd1,ret,data=0;
   int rc;
   char *node = "/dev/jk0";
   
   char buf[1024]="ABCDEFGH";
   int count;
   fd = open(node,O_WRONLY);
   if(fd<0){
           perror("error in opening");
           exit(1);
   }

   ret = write(fd,buf,strlen(buf));
   printf("\n  characters ARE WRITTEN %d\n",ret);
   if(ret<=0)
   {
	 printf("\n CAN'T WRITE : %d\n",ret);
	 return ret;
   }
   close(fd);
   exit(0);
}
