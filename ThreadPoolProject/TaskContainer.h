#pragma once
//TaskContainer:任务容器类，采用priority_queue<Task*>实现,储存所有用户添加未执行的任务
#include <queue>
class Task;
class TaskContainer
{
public:
	TaskContainer();
	~TaskContainer();
	void push(Task *);
	Task* top();
	void pop();
	std::priority_queue<Task*>::size_type size();
private:
	std::priority_queue<Task*> task_container_;
};

/*
void push(Task *)：将一个任务放入任务容器中

Task* top()：返回任务容器顶端的任务

void pop()：将任务容器顶端的线程弹出

std::priority_queue<Task*>::size_type size()：返回任务容器的大小
*/

