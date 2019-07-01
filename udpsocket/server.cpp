/*▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
▩ File Name: server.cpp
▩ Author: top-down
▩ Description: 
▩ Created Time: 2019年06月30日 星期日 11时42分18秒
▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩*/

#include<iostream>
#include<stdio.h>
#include"udpsocket.h"
using namespace std;

int main()
{
	string ip = "192.168.138.135";
	uint16_t port = 9000;
	UdpSocket sock;
	CHECK_RET(sock.CreateSocket());
	CHECK_RET(sock.Bind(ip,port));
	while(1)
	{
		struct sockaddr_in client;
		string buff;
		sock.Recv(buff,&client);
		cout << "client say: " << buff << endl;

		cout << "server.say: ";
		fflush(stdout);
		cin >> buff;
		sock.Send(buff,client);
	}
	sock.Close();
	return 0;
}
