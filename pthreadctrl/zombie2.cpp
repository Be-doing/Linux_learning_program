/*▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
▩ File Name: zombie2.cpp
▩ Author: top-down
▩ Description: 
▩ Created Time: 2019年05月04日 星期六 23时33分43秒
▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩*/

#include<iostream>
#include<unistd.h>
#include<pthread.h>
using namespace std;
void* func(void* arg)
{
	cout << "zombie" << endl;
	sleep(3);
	return NULL;
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
	while(1)
	{
		sleep(1);
		cout << "main working" << endl;
	}
	return 0;
}
