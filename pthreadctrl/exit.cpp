/*************************************************************************
> File Name: exit.cpp
> Author: top-down
> Created Time: 2019年05月03日 星期五 14时40分48秒
************************************************************************/

#include<iostream>
#include<unistd.h>
#include<pthread.h>
using namespace std;

void* func(void* arg)
{
	pthread_t tid = pthread_self();
	while(1)
	{
		cout << "创建线程的id是: " << tid << endl;
		sleep(1);
		pthread_exit(NULL);
	}
}

void* func2(void* arg)
{
	pthread_t tid = pthread_self();
	while(1)
	{
		cout << "创建线程的id是: " << tid << endl;
		sleep(1);
	}
}

int main()
{
	pthread_t tid;
	int res = pthread_create(&tid,NULL,func2,NULL);
	if(res != 0)
	{
		cout << "create error!" << endl;
		return -1;
	}
	while(1)
	{
		cout << "i am major thread~" << endl;
		sleep(1);
		pthread_cancel(tid);
	}	
	return 0;
}
