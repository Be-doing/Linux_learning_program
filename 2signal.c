/*************************************************************************
> File Name: 2signal.c
> Author: top-down
> Created Time: 2019年04月26日 星期五 13时12分05秒
************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<signal.h>

int main()
{
	sigset_t newset;
	sigset_t oldset;

	sigemptyset(&newset);

	sigfillset(&newset);

	sigprocmask(SIG_BLOCK,&newset,&oldset);
	printf("bolck………………………………");
	getchar();
	printf("bolck………………………………");
//	sigprocmask(SIG_UNBLOCK,&newset,NULL);
	return 0;
}
