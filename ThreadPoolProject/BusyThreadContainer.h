#pragma once
//BusyThreadContainer:工作容器类，采用std::list<MyThread*>实现，储存工作状态的线程

#include <list>

class MyThread;

class BusyThreadContainer
{
	
public:
	BusyThreadContainer();
	~BusyThreadContainer();
	void push(MyThread *m);
	std::list<MyThread*>::size_type size();
	void erase(MyThread *m);

private:
	std::list<MyThread*> busy_thread_container_;
	typedef std::list<MyThread*> Container;
	typedef Container::iterator Iterator;
};

/*
void push(MyThread *m)：将一个线程放入工作容器中

void erase(MyThread *m)：删除一个指定的线程

std::list<MyThread*>::size_type size()：返回工作容器的大小
*/

