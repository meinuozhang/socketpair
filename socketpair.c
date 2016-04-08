#include<stdio.h>
#include<stdlib.h>
#include<sys/select.h>
#include<sys/socket.h>
#include<string.h>
#include<errno.h>
int main()
{
	int fd[2]={0,0};
	if(socketpair(PF_LOCAL,SOCK_STREAM,0,fd)<0)
	{
		perror("socketpair");
		exit(1);
	}
	pid_t  id=fork();
	if(id<0)
	{
		perror("fork");
		exit(1);
	}
	else if(id==0)//child  read  from 0-->write to  pipe-->read from pipe
	{
		close(fd[0]);
		char buf[1024];
		while(1)
		{
			memset(buf,'\0',sizeof(buf));
			ssize_t _size=read(0,buf,sizeof(buf)-1);
			if(_size>0)
			{
			buf[_size]='\0';
			write(fd[1],buf,strlen(buf));
            ssize_t _s=read(fd[1],buf,sizeof(buf)-1);
			if(_s>0)
			{
				printf("server:%s",buf);
			}
			}
		}
	}
	else//father  read from pipe-->read from 0-->write to pipe
	{
		close(fd[1]);
	    char buf[1024];
		while(1)
		{
			memset(buf,'\0',sizeof(buf));
			ssize_t _s=read(fd[0],buf,sizeof(buf)-1);
			if(_s>0)
			{
				printf("client:%s",buf);
		    ssize_t _size=read(0,buf,sizeof(buf)-1);
			if(_size>0)
			{
           write(fd[0],buf,strlen(buf));
		   printf("%s\n",buf);
			}
			}
		}
	}
		return 0;
}

