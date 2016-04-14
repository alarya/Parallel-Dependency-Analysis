/*---------------------------------------------------------------------
 * QueuedWorkItems.cpp - child thread processes enqueued work items   *
 *                                                                    *
 * Jim Fawcett, CSE687 - Object Oriented Design, Spring 2016          *
 *--------------------------------------------------------------------*
/*

/* A single child thread processes work items equeued by main thread */
#include <string>
#include <iostream>
#include <conio.h>
#include "QueuedWorkItems.h"
#include "../Utilities/Utilities.h"

//----demonstrate ProcessWorkItem class----------------------------
using Util = Utilities::StringHelper;
using WorkResult = std::string;


#ifdef TEST_QUEUEDWORKITEMS
int main()
{
	Util::Title("Enqueued Work Items");

	std::cout << "\n  main thread id = " << std::this_thread::get_id();

	ProcessWorkItem<WorkResult> processor;

	WorkItem<WorkResult> wi1 = []() {
		//std::cout << "\n  working on thread " << std::this_thread::get_id();
		return "Hello from wi1";
	};

	WorkItem<WorkResult> wi2 = []() {
		std::cout << "\n  working on thread " << std::this_thread::get_id();
		return "Hello from wi2";
	};

	WorkItem<WorkResult> wi3 = []() {
		std::cout << "\n  working on thread " << std::this_thread::get_id();
		return "Hello from wi3";
	};

	WorkItem<WorkResult> wi4 = []() {
		std::cout << "\n  working on thread " << std::this_thread::get_id();
		return "Hello from wi4";
	};

	WorkItem<WorkResult> wi5 = []() {
		std::cout << "\n  working on thread " << std::this_thread::get_id();
		return "Hello from wi5";
	};

	WorkItem<WorkResult> wi6 = []() {
		std::cout << "\n  working on thread " << std::this_thread::get_id();
		return "Hello from wi6";
	};

	WorkItem<WorkResult> wi7 = []() {
		std::cout << "\n  working on thread " << std::this_thread::get_id();
		return "Hello from wi7";
	};

	WorkItem<WorkResult> wi8 = []() {
		std::cout << "\n  working on thread " << std::this_thread::get_id();
		return "Hello from wi8";
	};

	WorkItem<WorkResult> wi9 = []() {
		std::cout << "\n  working on thread " << std::this_thread::get_id();
		return "Hello from wi9";
	};

	WorkItem<WorkResult> wi10 = []() {
		std::cout << "\n  working on thread " << std::this_thread::get_id();
		return "Hello from wi10";
	};

	WorkItem<WorkResult> wi11 = []() {
		std::cout << "\n  working on thread " << std::this_thread::get_id();
		return "Hello from wi11";
	};

	WorkItem<WorkResult> wi12 = []() {
		std::cout << "\n  working on thread " << std::this_thread::get_id();
		return "Hello from wi12";
	};

	WorkItem<WorkResult> wi13 = []() {
		std::cout << "\n  working on thread " << std::this_thread::get_id();
		return "Hello from wi13";
	};

	WorkItem<WorkResult> wi14 = []() {
		std::cout << "\n  working on thread " << std::this_thread::get_id();
		return "Hello from wi14";
	};

	WorkItem<WorkResult> wi15 = []() {
		std::cout << "\n  working on thread " << std::this_thread::get_id();
		return "Hello from wi15";
	};

	processor.doWork(&wi1);
	processor.doWork(&wi2);
	processor.doWork(&wi3);
	processor.doWork(&wi4);
	processor.doWork(&wi5);
	processor.doWork(&wi6);
	processor.doWork(&wi7);
	processor.doWork(&wi8);
	processor.doWork(&wi9);
	processor.doWork(&wi10);
	processor.doWork(&wi11);
	processor.doWork(&wi12);
	processor.doWork(&wi13);
	processor.doWork(&wi14);
	processor.doWork(&wi15);


	processor.start();

	for (int i = 0; i < 15; i++)
		std::cout << "\n  " << processor.result();

	processor.doWork(nullptr);
	processor.doWork(nullptr);
	processor.doWork(nullptr);
	processor.doWork(nullptr);

	// wait for child thread to complete

	processor.wait();
	std::cout << "\n\n";
}
#endif