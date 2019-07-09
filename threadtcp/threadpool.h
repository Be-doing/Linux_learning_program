/*************************************************************************
*> File Name: threadpool.c
*> Author: san
*> Created Time: 2019年04月29日 星期一 21时16分57秒
*> Describe:  线程池的实现
    线程池类
    任务类
*************************************************************************/
#include <iostream>
#include <queue>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include "tcpsocket.h"
typedef bool (*taskCallback)(TcpSocket& client);
class MyTask
{
    private:
	TcpSocket  _data;	
	taskCallback _callback;
    public:
	MyTask(){}
	MyTask(TcpSocket data, taskCallback callback):
	    _data(data), 
	    _callback(callback) {}
	~MyTask() {}
	void setTask(TcpSocket data, taskCallback callback) {
	    _data = data;
	    _callback = callback;
	}
	bool Run() {
	    return _callback(_data);
	}
};

class ThreadPool
{
    private:
	int _thr_max;
	int _thr_cur;
	std::queue<MyTask> _queue;
	int _capacity;
	pthread_mutex_t _mutex;
	pthread_cond_t _cond_pro;
	pthread_cond_t _cond_con;
    private:
	void queueLock();
	void queueUnLock();
	void productorWait();
	void productorWake();
	void consumerWait();
	void consumerWake();
	bool queueIsEmpty();
	bool queueIsFull();
	void queuePop(MyTask *task);
	void queuePush(MyTask &task);
    public:
	ThreadPool(int max, int cap):_thr_max(max), _capacity(cap) {
	    _thr_cur = cap;
	    pthread_mutex_init(&_mutex, NULL);
	    pthread_cond_init(&_cond_pro, NULL);
	    pthread_cond_init(&_cond_con, NULL);
	}
	~ThreadPool() {
	    pthread_mutex_destroy(&_mutex);
	    pthread_cond_destroy(&_cond_con);
	    pthread_cond_destroy(&_cond_pro);
	}
	static void *thr_start(void *arg){
	    ThreadPool *p = (ThreadPool*)arg;

	    while(1) {
		p->queueLock();
		while(p->queueIsEmpty()) {
		    p->consumerWait();
		}
		MyTask task;
		p->queuePop(&task);
		p->productorWake();
		p->queueUnLock();
		task.Run();
	    }
	    return NULL;
	}
	bool threadInit() {
	    int ret;
	    pthread_t tid;
	    for (int i = 0; i < _thr_max; i++) {
		ret = pthread_create(&tid, NULL, thr_start, (void*)this);
		if (ret != 0) {
		    printf("thread create error\n");
		    return false;
		}
		pthread_detach(tid);
	    }
	    return true;
	}
	bool addTask(MyTask &task) {
	    queueLock();
	    while (queueIsFull()) {
		productorWait();
	    }
	    queuePush(task);
	    consumerWake();
	    queueUnLock();
	    return true;
	}
};

bool taskHandler(TcpSocket data)
{
    srand(time(NULL));
    int n = rand() % 5;
    printf("thread:%p  is sleep %d sec\n", pthread_self(), n);
    sleep(n);
    return true;
}
int main()
{
    ThreadPool p(5, 10);
    p.threadInit();

    MyTask task[10];
    for (int i = 0; i < 10; i++) {
	task[i].setTask(i, taskHandler);
	p.addTask(task[i]);
    }
    while(1) {
	sleep(1);
    }
    return 0;
}
