/*▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
▩ File Name: httpserver.cpp
▩ Author: top-down
▩ Description: 
▩ Created Time: 2019年06月29日 星期六 19时34分21秒
▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩*/

#include<iostream>
#include"tcpsocket.h"
#include<stdlib.h>
using namespace std;
int main()
{
	int i = 0;
	TcpSocket sersocket;
	string ip = "192.168.138.135";
	uint16_t port = 9000;
	CHECK_RET(sersocket.CreateSocket());
	CHECK_RET(sersocket.Bind(ip,port));
	CHECK_RET(sersocket.Listen());
	while(1)
	{
		TcpSocket client;
		if(sersocket.Accept(client) == false)
		{
			cout << "Accept Error" << endl;
			continue;
		}
		string recv;
		client.Recv(recv);
		cout << "client[" << i++ << "]" << endl;
		cout << recv << endl;
		string resp,bodystr;
		const char* body = "<h1>hello world</h1>";
		char buff[1024];
		sprintf(buff,"HTTP/1.1 200 OK\nContent-Length:%lu\n\n%s",strlen(body),body);
		
		bodystr += buff;
		client.Send(bodystr);
		client.Close();
	}
	sersocket.Close();
	return 0;
}

