#pragma once
//MyThread：线程类，封装了C++11的thread，每一个线程可以关联一个Task对象，执行其Run方法

#include "Task.h"
#include <thread>


class MyThreadPool;
class Task;
class MyThread
{
	friend bool operator==(MyThread my1, MyThread my2);
	friend bool operator!=(MyThread my1, MyThread my2);
public:
	MyThread(MyThreadPool *pool);
	void Assign(Task *Task);
	void Run();
	void StartThread();
	int getthreadid();
	void setisdetach(bool isdetach);	
private:
	MyThreadPool *mythreadpool_;
	static int  s_threadnumber;
	bool isdetach_;
	Task *task_;
	int threadid_;
	std::thread thread_;
};

/*
MyThread(MyThreadPool *pool)：构造一个MyThread对象，将自己与指定的线程池相关联起来

void Assign(Task *Task)：将一个任务与该线程相关联起来

void Run()：调用了Task的Run方法，同时在Task的Run方法结束后将自己从工作容器移回空闲容器

void StartThread()：执行线程的Run方法，即执行了Task的Run方法

int getthreadid()：获取线程的id号

void setisdetach(bool isdetach)：设置线程在运行的时候是join还是detach的
*/




