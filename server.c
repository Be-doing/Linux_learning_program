#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
int main()
{
	//int mkfifo(const char *pathname, mode_t mode);
	//成功返回 0 ，失败返回 -1；
	//
	umask(0);//保证权限是664
	char* filename = "./my_fifo.fifo";
	int ret = mkfifo(filename,0664);
	if(ret < 0)
	{
		if(errno != EEXIST)
		{
			printf("FIFO ERROR\n");
			return -1;
		}
	}

	int fd = open(filename,O_RDONLY);
	if(fd < 0)
	{
		printf("OPEN ERROR\n");
		return -1;
	}
	printf("open successful\n");
	while(1)
	{
		char buff[1024] = {0};
		read(fd,buff,1023);
		printf("client say: %s \n",buff);
	}
	return 0;
}
