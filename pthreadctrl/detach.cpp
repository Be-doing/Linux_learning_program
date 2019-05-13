/*************************************************************************
> File Name: join.cpp
> Author: top-down
> Created Time: 2019年05月03日 星期五 15时28分39秒
************************************************************************/

#include<iostream>
#include<unistd.h>
#include<pthread.h>
using namespace std;

void* func(void* arg)
{
	pthread_detach(pthread_self());
	sleep(3);
	pthread_exit((void*)"liu le~");
}

int main()
{
	pthread_t tid;
	int res = pthread_create(&tid,NULL,func,NULL);
	if(res != 0)
	{
		cout << "create error!" << endl;
		return -1;
	}
//	char* ret = NULL;
//	pthread_join(tid,(void**)&ret);
//	cout << "rerun：" << *(&ret) << endl;;
	return 0;
}

