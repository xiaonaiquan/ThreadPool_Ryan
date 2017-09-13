#pragma once

#include "Task.h"

class MyTask :public Task
{
	friend bool operator<(MyTask  &lv,MyTask &rv)
	{
		return lv.priority_ < rv.priority_;
	}
public:
	MyTask();
	~MyTask();
	virtual void Run();
	void setdata(int d);
private:
	int data_;
};

/*
friend bool operator<(MyTask &lv,MyTask &rv) ：用于确定任务在任务容器中的位置

Run：自定义的Run方法

void setdata(int d)：设置数据
*/
