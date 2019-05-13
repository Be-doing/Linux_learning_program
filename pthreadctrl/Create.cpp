/*************************************************************************
> File Name: ceate.cpp
> Author: top-down
> Created Time: 2019年05月03日 星期五 11时05分26秒
************************************************************************/

#include<iostream>
#include<pthread.h>
#include<unistd.h>
using namespace std;

void* func(void* arg)
{
	cout << "child pid: " << getpid();
	pthread_t tid = pthread_self();
	while(1)
	{
		cout << "child pid: " << getpid() << endl;
		cout << "child tid: " << tid << endl;
		cout << endl;
		sleep(1);
	}
	
}
int main()
{
	pthread_t tid;
	int res = pthread_create(&tid,NULL,func,NULL);
	if(res != 0)
	{
		cout << "create error" << endl;
		return -1;
	}
	pthread_t maintid;
	maintid = pthread_self();
	while(1)
	{
		cout << "main pid: " << getpid() << endl;
		cout << "main tid :" << maintid << endl;
		sleep(1);
		cout << endl;
	}
	return 0;
}
