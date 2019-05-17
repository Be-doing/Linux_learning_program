//1.获取标准输入
//2.对输入字符串进行解析（获取程序名称 + 参数）
//3.创建子进程
//	程序替换
//4.进程等待

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
char buff[1024] = {0};//输入缓冲
char* argv[1024];
int argc = 0;
void menu(char* buff)//输入菜单
{
	printf("[top-down@localhost]$");
	fflush(stdout);
	//判断进行回车判定，防止第一个字符就是回车
	if(scanf("%[^\n]*c",buff) != 1)//^\n正则表达式,遇到\n截至,*c(s)表示抛弃剩下的字符(字符串)
	{
		getchar();
	}
	printf("%s\n",buff);
}
void explain(char* buff)//对输入字符串进行解析
{
	char* ptr = buff;
	while(*ptr != '\0')//不到结尾，一直循环
	{
		//当前位置非空白字符
		if(!isspace(*ptr))//isspace() 检测空白字符，制表符、换行、回车、空格等
		{
			argv[argc++] = ptr;//保存字符串地址
			while(!isspace(*ptr) && *ptr != '\0')
			{
				++ptr;
			}
		}
		else
		{
			*ptr = '\0';
			++ptr;
		}
	}
	argv[argc] = NULL;
	int i;
	for(i = 0; i < argc; ++i)
	{
		printf("[%s]",argv[i]);
	}
	printf("\n");
}
void create()
{
	pid_t pid = fork();
	if(pid < 0)
	{
		exit(-1);
	}
	else if(pid == 0)
	{
		int i = 0;
		int flag = 0;
		char* str = ">>";
		for(i = 0; argv[i] != NULL; ++i)
		{
			if(strcmp(str,argv[i]) == 0)
			{
				flag = 1;
				break;
			}
		}
		argv[i] = NULL;
		int newfd;
		if(flag == 1)
		{
			if(argv[i+1] == NULL)
			{
				printf("ERROR!\n");
				exit(-1);
			}
			else
			{
				newfd = open(argv[i+1],O_RDWR|O_CREAT,0664);
				dup2(newfd,1);
			}
		}
		execvp(argv[0], argv);
		close(newfd);
		//防止程序替换失败，直接退出
		exit(0);
	}
	wait(NULL);
}
int main()
{
	menu(buff);
	explain(buff);
	create();
	return 0;
}
