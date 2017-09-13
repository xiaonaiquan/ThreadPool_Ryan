#include "MyThreadPool.h"
#include <iostream>
using namespace std;
MyThreadPool::MyThreadPool(int number)// 创建number个空闲线程与空闲容器中，同时创建管理线程thread_this，用于进行线程池中线程的调度
{
	issurvive_ = true;
	number_of_thread_ = number;
	idle_thread_container_.assign(number, this);
	thread_this_ =thread(&MyThreadPool::Start, this);
	thread_this_.detach();
}
MyThreadPool::~MyThreadPool()
{

}
void MyThreadPool::EndMyThreadPool()
{
	issurvive_ =false;
}

void  MyThreadPool::AddIdleThread(int n)
{
	idle_mutex_.lock();
	idle_thread_container_.assign(n, this);
	number_of_thread_ += n;
	idle_mutex_.unlock();
}
void MyThreadPool::Start()
{
	/*
	管理线程对应的Start方法，内有一个死循环，不停的判断任务容器中是否有任务，和是否有空闲线程来执行任务，若有，则将任务从

任务容器中提出，从空闲线程中提取出一个空闲线程与其绑定，执行该任务，同时将该线程从空闲容器移动到工作容器中。

当线程池想要结束运行时，即survive为false时，首先要判断工作容器是否为空，若不为空，则代表还有任务正在被线程执行，线程池不能结束运行

否则可以结束线程池的运行，跳出死循环
	*/
	
	while (true)
	{
		if (issurvive_==false)
		{
			busy_mutex_.lock();
			if (busy_thread_container_.size()!=0)
			{
				busy_mutex_.unlock();
				continue;
			}
			busy_mutex_.unlock();
			break;
		}
		idle_mutex_.lock();
		if (idle_thread_container_.size() == 0)
		{
			idle_mutex_.unlock();
			continue;
		}
		idle_mutex_.unlock();
		task_mutex_.lock();
		if (task_container_.size() == 0)
		{
			task_mutex_.unlock();
			continue;
		}
		Task *b = task_container_.top();;
		task_container_.pop();
		task_mutex_.unlock();
		
		idle_mutex_.lock();
		MyThread *mythread = idle_thread_container_.top();;
		idle_thread_container_.pop();
		mythread->Assign(b);
		idle_mutex_.unlock();

		busy_mutex_.lock();
		busy_thread_container_.push(mythread);
		busy_mutex_.unlock();
		mythread->StartThread();
	}
}
void MyThreadPool::AddTask(Task *Task, int priority = (PRIORITY::NORMAL))
{
	
	Task->SetPriority(priority);
	task_mutex_.lock();
	task_container_.push(Task);
	task_mutex_.unlock();
}
void MyThreadPool::RemoveThreadFromBusy(MyThread *myThread) //将一个线程从任务容器中移除，并将其放回空闲容器中，使用busy_mutex_和idle_mutex_进行加锁和解锁，确保数据的一致性
{

	busy_mutex_.lock();
	cout << "Thread:" << myThread->getthreadid()<< " remove from busylist" << endl;
	busy_thread_container_.erase(myThread);
	busy_mutex_.unlock();

	idle_mutex_.lock();
	idle_thread_container_.push(myThread);
	idle_mutex_.unlock();
}