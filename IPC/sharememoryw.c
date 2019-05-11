#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<sys/shm.h>
#define IPC_KEY 0x123456
#define SHM_SIZE 4096
int main()
{
//int shmget(size_t key, size_t size, int shmflg)
//key：共享内存的标识符/名称
//size：共享内存的大小
//shmflg：与mode_t权限类似	IPC_CREAT|IPC_EXCL
//成功返回shmid，失败返回-1
//创建共享内存
//key_t ftok(const char* pathname, int proj_id);
//通过文件名与一个proj_id生成一个key值
	int shmid = shmget(IPC_KEY,SHM_SIZE,IPC_CREAT|0664);
	if(shmid < 0)
	{
		perror("CREATE ERROR\n");
		return -1;
	}
//void* shmat(int shmid, const void* shmaddr, int shmflg)
//shmid：共享内存标识符
//shmaddr：指定连接的地址，通常是NULL
//shmflg：SHM_RND\SHM_RDONLY 0可读可写	
//成功返回共享内存首地址	失败返回 -1

//映射首地址
	char* address = (char*)shmat(shmid,NULL,0);
	if(address ==(void*)-1)
	{
		perror("CONECT ERROR\n");
		return -1;
	}
//进行内存操作
	
	int i = 0;
	while(1)
	{
		sprintf(address,"------%d",++i);
		//++i;
		sleep(1);
	}
	//int shmdt(const void *shmaddr);
//shmaddr: 由shmat所返回的指针
//返回值：成功返回0；失败返回-1
	//接触映射关系
	shmdt(address);
//int shmctl(int shmid, int cmd, struct shmid_ds *buf);
//shmid:由shmget返回的共享内存标识码
//cmd:将要采取的动作（有三个可取值）IPC_RMIP 删除
//buf:指向⼀个保存着共享内存的模式状态和访问权限的数据结构
//返回值：成功返回0；失败返回-1
	//释放共享内IPIP存
	shmctl(shmid,IPC_RMID,NULL);
	return 0;
}
