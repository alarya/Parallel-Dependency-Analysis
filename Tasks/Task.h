#pragma once
///////////////////////////////////////////////////////////////////////
// Task.h - runs function asynchronously then runs callback //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2016         //
///////////////////////////////////////////////////////////////////////

#include "../ThreadPool/QueuedWorkItems.h"
#include "../ThreadPool/BlockingQueue.h"

template<typename task>
class Task
{
public:
	void enqueTasks()
private:
	static ProcessWorkItem<task> task;
};