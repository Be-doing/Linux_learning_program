/*************************************************************************
  > File Name: sigaction.c
  > Author: top-down
  > Created Time: 2019年04月26日 星期五 14时22分00秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<signal.h>


//int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact)

void fun(int num)
{
	printf("action !! %d\n",num);
}
int main()
{

	struct sigaction act;
	struct sigaction old;
	sigemptyset(&act.sa_mask);
	act.sa_handler = fun;
	act.sa_flags = 0;

	sigaction(2,&act,&old);
	sigaction(SIGRTMIN+5,&act,&old);
	sigset_t newset;
	sigset_t oldset;
	sigemptyset(&newset);
	sigfillset(&newset);
	sigprocmask(SIG_BLOCK,&newset,&oldset);
	printf("bolck………………………………\n");
	getchar();
	sigprocmask(SIG_UNBLOCK,&newset,NULL);
}
