#pragma once
////////////////////////////////////////////////////////////////////////////////
// QueuedWorkItems.h - child threads processes enqueued work items             //
//                                                                            //
// Original Author: Jim Fawcett, CSE687 - Object Oriented Design, Spring 2016 //
// Modified by: Alok Arya													  //
////////////////////////////////////////////////////////////////////////////////

/* Package Operations:
* -------------------
* This package maintains two blocking queues. on one queue the work items (callable objects)
* are enqueued. There are a limited number of reusable child threads started which start
* dequeing and executes the work items and enques the result in the results queue.
*
* Required Files:
* ---------------
* BlockingQueue.h
*
* Build Process:
* --------------
* devenv Cpp11-BlockingQueue.sln /rebuild debug
*
* Maintenance History:
* --------------------
* ver 1.1 : 14th April
*   -Now there are multiple child threads to deque
* ver 1.0 : unknown
* - first release
*
*/
#include <thread>
#include <functional>
#include "BlockingQueue.h"

template<typename Result>
using WorkItem = std::function<Result()>;


//--- class to process work items
//----each work item is processed sequentially on a single child thread
template<typename Result>
class ThreadPool
{
public:
	void start();
	void doWork(WorkItem<Result>* pWi);
	Result result();
	void wait();
	size_t resultsQueueSize();
	~ThreadPool();
private:
	std::vector<std::thread> Threads;
	BlockingQueue<WorkItem<Result>*> _workItemQueue;
	BlockingQueue<Result> _resultsQueue;
};

//----Wait for child thread to terminate---------------------------
template<typename Result>
void ThreadPool<Result>::wait()
{
	for (auto& thread : Threads)
		thread.join();
}

//-------return size of results queue------------------------------
template<typename Result>
size_t ThreadPool<Result>::resultsQueueSize()
{
	return _resultsQueue.size();
}

//----enqueue work item--------------------------------------------
template<typename Result>
void ThreadPool<Result>::doWork(WorkItem<Result>* pWi)
{
	_workItemQueue.enQ(pWi);
}

//----retrieve results with blocking call--------------------------
template<typename Result>
Result ThreadPool<Result>::result()
{
	return _resultsQueue.deQ();
}

//----start child thread that dequeus work items-------------------
template<typename Result>
void ThreadPool<Result>::start()
{
	std::function<void()> threadProc =
		[&]() {
		while (true)
		{
			WorkItem<Result>* pWi = _workItemQueue.deQ();
			if (pWi == nullptr)
			{
				//std::cout << "\n  shutting down work item processing";
				return;
			}
			Result result = (*pWi)();
			_resultsQueue.enQ(result);
		}
	};
	//add 4 threads
	Threads.push_back(std::thread(threadProc));
	Threads.push_back(std::thread(threadProc));
	Threads.push_back(std::thread(threadProc));
	Threads.push_back(std::thread(threadProc));
}


//----clean up heap------------------------------------------------
template<typename Result>
ThreadPool<Result>::~ThreadPool()
{

}


