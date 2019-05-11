//int sigemptyset(sigset_t *set);				清空信和集合
//int sigfillset(sigset_t *set);				将所有信号添加到集合中
//int sigaddset (sigset_t *set, int signo);		将指定信号添加到集合中
//int sigdelset(sigset_t *set, int signo);		删除指定信号
//int sigismember（const sigset_t *set, int signo);
//int sigprocmask(int how, const sigset_t *set, sigset_t *oset);	返回值:若成功则为0,若出错则为-1
			//SIG_BLOCK ：	阻塞set集合中的信号，将原有阻塞放入old
			//SIG_UNBLOCK：	对set集合中的信号接触阻塞
			//SIG_SETMASK：	将set集合中的信号添加到阻塞集合中
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
void print(sigset_t* p)
{
	int i = 1;
	for(i; i < 32; ++i)
	{
		if(sigismember(p,i))
		{
			printf("1");
		}
		else
		{
			printf("0");
		}
//	sleep(1);
	}
	printf("\n");
}
int main()
{
/*
 *定义一个集合
 *向集合哄添加要阻塞的信号
 *阻塞这个集合中的所有信号
 *获取换行getchar()
 *对集合中的信号进行接触阻塞
 */
	sigset_t newset,oldset,pending;
	sigemptyset(&newset);

	sigfillset(&newset);
	
	sigprocmask(SIG_BLOCK,&newset,NULL);
	raise(5);
	raise(6);
	raise(7);
	raise(8);
	getchar();
	sigpending(&pending);
	print(&pending);
//	sigprocmask(SIG_UNBLOCK,&newset,&oldset);
	return 0;
}
