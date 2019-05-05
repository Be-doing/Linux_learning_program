#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main()
{
	int pipefd[2];
	int ret = pipe(pipefd);

	if(ret < 0)
	{
		printf("PIPE ERROR\n");
		return -1;
	}

	int pid = fork();


	if(pid < 0)
	{
		printf("FORK ERROR\n");
		exit(-1);
	}
	else if(pid == 0)
	{
		char buff[1024];
		read(pipefd[0],buff,1023);
		printf("child readed：%s\n",buff);
	}
	else
	{
		char buff[1024] = {0};
		scanf("%s",buff);
		printf("father write：%s\n",buff);
		write(pipefd[1],buff,strlen(buff));
	}
	wait(NULL);

	return 0;
}
