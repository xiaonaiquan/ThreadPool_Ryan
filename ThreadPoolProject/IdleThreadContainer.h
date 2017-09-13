#pragma once
//IdleThreadContainer:空闲容器类，采用std::vector<MyThread*>实现，储存处于空闲状态的线程
#include <vector>

class MyThread;
class MyThreadPool;
class IdleThreadContainer
{
	
public:
	IdleThreadContainer();
	~IdleThreadContainer();
	std::vector<MyThread*>::size_type size();
	void push(MyThread *m);
	void assign(int n,MyThreadPool* m);	
	MyThread* top();
	void pop();
	void erase(MyThread *m);
private:
	std::vector<MyThread*> idle_thread_container_;
	typedef std::vector<MyThread*> Container;
	typedef Container::iterator Iterator;
};

/*
~IdleThreadContainer(); ：负责析构空闲容器中的线程

void push(MyThread *m)：将一个线程放回空闲容器中

void assign(int n,MyThreadPool* m)：创建n个线程与线程池m相关联的线程放入空闲容器中

MyThread* top()：返回位于空闲容器顶端的线程

void pop()：弹出空闲容器顶端的线程

void erase(MyThread *m)：删除一个指定的线程

*/
