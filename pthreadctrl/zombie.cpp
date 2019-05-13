/*************************************************************************
> File Name: zombie.cpp
> Author: top-down
> Created Time: 2019年05月03日 星期五 16时44分05秒
************************************************************************/

#include<iostream>
#include<unistd.h>
#include<pthread.h>
using namespace std;


void* func(void* arg)
{
	while(1)
	{
		sleep(1);
		cout << "working" <<endl;
	}
}


int main()
{
	pthread_t tid;
	int res = pthread_create(&tid, NULL, func, NULL);
	if(res != 0)
	{
		cout << "create error!" << endl;
		return -1;
	}
	pthread_exit(NULL);
	return 0;
}
