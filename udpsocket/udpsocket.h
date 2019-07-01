/*▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
▩ File Name: udpsocket.h
▩ Author: top-down
▩ Description: 
▩ Created Time: 2019年06月30日 星期日 10时56分41秒
▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩*/

#include<iostream>
#include<sys/socket.h>//创建套接字的头文件
#include<netinet/in.h>//地址信息结构体、IP字节序转换头文件
#include<arpa/inet.h>//端口号字节序转换
#include<string>
#include<string.h>
#include<unistd.h>//close的头文件
using namespace std;

#define CHECK_RET(q) if((q) == false){return -1;}
class UdpSocket
{
	public:
		UdpSocket()
			:socket_(-1)
		{
			//创建套接字不放在构造中，因为创建失败后无法处理
		}
		bool CreateSocket()
		{

			socket_ = socket(AF_INET,SOCK_DGRAM,0);
			if(socket_ < 0)
			{
				cout << "create error" << endl;
				return false;
			}
			return true;
		}
		bool Bind(string& ip, uint16_t& port)
		{
			struct sockaddr_in addr;
			addr.sin_family = AF_INET;
			addr.sin_port = htons(port);
			addr.sin_addr.s_addr = inet_addr(ip.c_str());
			socklen_t len = sizeof(addr);
			int ret = bind(socket_,(sockaddr*)&addr,len);
			if(ret < 0)
			{
				cout << "bind error" << endl;
				return false;
			}
			return true;
		}
		bool Recv(string& retmsg, struct sockaddr_in* cliaddr = NULL)
		{
			char buff[1024];
			struct sockaddr_in addr;
			socklen_t len = sizeof(addr);
			int ret = recvfrom(socket_,buff,1023,0,(struct sockaddr*)&addr,&len);
			if(ret < 0)
			{
				cout << "recv error" << endl;
				return false;
			}
			if(ret == 0)
			{
				cout << "peer down" << endl;
				return false;
			}
			retmsg.assign(buff);
			if(cliaddr != NULL)
			{
				memcpy(cliaddr,&addr,len);
			}
			return true;
		}
		bool Send(string& buff, struct sockaddr_in& destaddr)
		{
			socklen_t len = sizeof(destaddr);
			int ret = sendto(socket_,buff.c_str(),buff.size(),0,(struct sockaddr*)&destaddr,len);
			if(ret < 0)
			{
				cout << "sned error" << endl;
				return false;
			}
			return true;
		}
		bool Close()
		{
			close(socket_);
			socket_ = -1;
			return true;
		}
	private:
		int socket_;
};
