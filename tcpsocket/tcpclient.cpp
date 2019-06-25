/*▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
▩ File Name: tcpclient.cpp
▩ Author: top-down
▩ Description: 
▩ Created Time: 2019年06月25日 星期二 10时22分01秒
▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩*/

#include<iostream>
#include"tcpsocket.h"
using namespace std;
int main()
{
	TcpSocket client;	
	CHECK_RET(client.CreateSocket());
	string ip("192.168.138.135");
	uint16_t port = 9000;
	CHECK_RET(client.Connect(ip,port));
	while(1)
	{
		string buff;
		cout << "client say: ";
		fflush(stdout);
		cin >> buff;
		client.Send(buff);
		buff.clear();
		client.Recv(buff);
		cout << "server say: " << buff << endl;

	}
	client.Close();
	return 0;
}
