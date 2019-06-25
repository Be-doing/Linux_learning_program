/*▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
▩ File Name: tcpserver.cpp
▩ Author: top-down
▩ Description: 
▩ Created Time: 2019年06月25日 星期二 08时28分56秒
▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩*/

#include<iostream>
#include<pthread.h>
#include "tcpsocket.h"
using namespace std;
void* func(void* arg)
{
	TcpSocket* clisocket = ((TcpSocket*)arg);
	while(1)
	{
		string buff;
		clisocket->Recv(buff);
		cout << "client say:" << buff << endl;
		buff.clear();
		cout << "server say:";
		fflush(stdout);
		cin >> buff;
		clisocket->Send(buff);
	}
	clisocket->Close();
	return NULL;
}
int main()
{
	string ip("192.168.138.135");
	uint16_t port_ = 9000;
	TcpSocket socket;
	CHECK_RET(socket.CreateSocket());
	CHECK_RET(socket.Bind(ip,port_));
	CHECK_RET(socket.Listen());
	while(1)
	{
		TcpSocket* clisocket = new TcpSocket();
		if(socket.Accept(*clisocket) == false)
		{
			cout << "someone clienr accept error" << endl;
			continue;
		}
		pthread_t thread;
		pthread_create(&thread,NULL,func,(void*)clisocket);
		pthread_detach(thread);
	}
	socket.Close();
	return 0;	
}
