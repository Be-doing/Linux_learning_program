/*▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
▩ File Name: tcpsocket.h
▩ Author: top-down
▩ Description: 
▩ Created Time: 2019年06月24日 星期一 18时37分08秒
▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩*/

#include<iostream>
#include<sys/socket.h>
#include<string>
#include<unistd.h>
#include <arpa/inet.h>//htons的头文件
#include<string.h>
using namespace std;
#define CHECK_RET(q) if((q) == false){ return -1; }
class TcpSocket
{
public:
	//int socket(int domain, int type, int protocol)
	//domain:地址域，AF_INET表示IP v4
	//type:套接字类型——
			//SOCK_STREAM 流式套接字---默认协议TCP
			//SOCK_DGRAM  数据报套接字-默认协议UDP
	//prorocol:协议类型，与前面套接字类型对应
	//		0   使用默认协议
	//		IPPROTO_TCP 6   TCP协议
	//		IPPROTO_UDP 17  UDP协议
	//返回值：成功则是套接字，失败返回 -1
	int CreateSocket()
	{
		socket_ = socket(AF_INET, SOCK_STREAM, 6);
		if(socket_ < 0)
		{
			cout << "create error!" << endl;
			return -1; 
		}
		return socket_;
	}
	bool Listen(int lisMax = 5)
	{
		//int listen(int sockfd, int backlog);
		//sockfd:   套接字描述符
		//backlog： backlog设置内核中已完成连接队列的最大节点数量
		int ret = listen(socket_,lisMax);
		if(ret < 0)
		{
			cout << "listen error" << endl;
			return false;
		}
		return true;
	}
	bool SetFd(int fd)
	{
		socket_ = fd;
		return true;
	}
	bool Accept(TcpSocket& socket,struct sockaddr_in *addr = nullptr)
	{
		//int accept(int sockfd, sockaddr *addr,socklen_t *addrlen);
		//  sockfd: 套接字描述符
		//  addr：  用于存储客户端地址信息
		//  addrlen：用于设置想要的地址长度和保存实际的地址长度
		//返回值：为客户算连接新建的socket描述符，  失败-1
		//接下来与客户端的通信都是通过这个socket描述符实现的
		sockaddr_in add;
		socklen_t len = sizeof(sockaddr_in);
		int ret = accept(socket_,(sockaddr*)&add, &len);
		if(ret < 0)
		{
			cout << "accept error" << endl;
			return false;
		}
		socket.SetFd(ret);
		if(addr)
		{
			memcpy(addr, &add, len);
		}
		return true;
	}
	bool Bind(string& ip,uint16_t&  port)
	{
		//bind(int sockfd,struct sockaddr*addr,socklen_t addrlen);)
		//  sockfd: 创建套接字返回的套接字描述符
		//  addr：  要绑定的地址信息
		//  addrlen：   地址信息长度
		//  返回值：0       失败：-1
		struct sockaddr_in  addr;
		addr.sin_family = AF_INET;
		//因为网络通信使用网络字节序，因此端口和ip地址信息都需要被
		//转换为网络字节序的数据
		//uint16_t htons(uint16_t hostshort)
		//  将16位的数据从主机字节序转换为网络字节序
		//uint32_t htonl(uint32_t hostshort)
		//  将32位的数据从主机字节序转换为网络字节序
		addr.sin_port = htons(port);
		//in_addr_t inet_addr(const char *cp);
		//将字符串点分十进制IP地址转换为网络字节序的整数IP地址
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
	bool Recv(string& buff)
	{	
			//ssize_t recv(int sockfd, void *buf, size_t len, int flags)
			//sockfd:   套接字描述符
			//buf：     存储接收的数据
			//len：     想要接收的长度
			//flags:    0-阻塞接收   
			//          MSG_PEEK-接收数据但是数据不从接收缓冲区移除
			//返回值：实际接收的字节数/对端关闭连接返回0    错误：-1
		char buf[1024] = {0};
		//struct sockaddr_in addr;
		//socklen_t len = sizeof(sockaddr_in);
		int ret = recv(socket_, buf, 1023, 0);
		if(ret < 0)
		{
			cout << "recive error!" << endl;
			return false;
		}
		else if(ret == 0)
		{
			cout << "peer down" << endl;
			return false;
		}
		buff.assign(buff);
		return true;
	}
	bool Send(string& buff)
	{
		//ssize_t send(int sockfd, void *buf, size_t len, int flags)
		//返回值：实际发送的字节数      失败：-1
		//若连接已经断开，发送会触发异常)
		int ret = send(socket_, buff.c_str(), buff.size(), 0);
		if(ret < 0)
		{
			cout << "send error" << endl;
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
	TcpSocket operator=(const TcpSocket& socket)
	{
		socket_ = socket.socket_;
		return *this;
	}
	private:
	int socket_ = -1;
};
