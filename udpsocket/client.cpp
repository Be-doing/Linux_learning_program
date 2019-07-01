/*▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
▩ File Name: client.cpp
▩ Author: top-down
▩ Description: 
▩ Created Time: 2019年06月30日 星期日 11时56分23秒
▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩*/

#include<iostream>
#include<stdio.h>
#include"udpsocket.h"
using namespace std;


int main()
{
	string ip = "192.168.138.135";
	UdpSocket client;
	CHECK_RET(client.CreateSocket());
	struct sockaddr_in seraddr;
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(9000);
	seraddr.sin_addr.s_addr = inet_addr(ip.c_str());
	while(1)
	{
		string msg;
		cout << "client say: ";
		fflush(stdout);
		cin >> msg;
		client.Send(msg,seraddr);
		
		client.Recv(msg);
		cout << "server say: " << msg << endl;
	}
	client.Close();
	return 0;
}
