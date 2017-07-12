// thread_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <deque>
#include <atomic>
#include <future>
#include <thread>
#include <mutex>

using namespace std;

struct TaskValue {
public:

private:
	void _zero() {

	}

public:
	TaskValue() {
		_zero();
	}
};

#define EVENT_COUNT 10

std::deque<std::packaged_task<TaskValue()>> tasks;
std::mutex tasks_mutex;
std::atomic<bool> events_running;
std::thread ethread;
std::atomic<size_t> eventThreadId;

template<typename Functor>
inline TaskValue RunOnGuiThread(Functor func, TaskValue args);

void event_thread();
void add_thread();


int main() {

	events_running = true;
	ethread = std::thread(event_thread);

	for (int i = 0; i < EVENT_COUNT; i++) {
		RunOnGuiThread([](TaskValue val) {

			auto threadId = std::hash<std::thread::id>()(std::this_thread::get_id());
			if (eventThreadId != threadId)
				cout << "change in thread: " << threadId << " (should be: " << eventThreadId << ")" << "\r\n";

			return TaskValue();
		}, TaskValue());
	}

	std::thread addThread = std::thread(add_thread);

	addThread.join();

	ethread.join();
	

	cout << "Done.";
	char test[10];
	cin >> test;
	return 0;
}

void add_thread() {
	for (int i = 0; i < EVENT_COUNT; i++) {
		RunOnGuiThread([](TaskValue val) {

			auto threadId = std::hash<std::thread::id>()(std::this_thread::get_id());
			if (eventThreadId != threadId)
				cout << "change in thread: " << threadId << " (should be: " << eventThreadId << ")" << "\r\n";

			return TaskValue();
		}, TaskValue());
	}
}

void event_thread()
{
	int eventsDone = 0;
	eventThreadId = std::hash<std::thread::id>()(std::this_thread::get_id());

	while (eventsDone < EVENT_COUNT*2) {
		// process messages
		{
			// using mutex here costs us 100fps (500 -> 400)
			std::unique_lock<std::mutex> lock(tasks_mutex);
			while (!tasks.empty()) {
				auto task(std::move(tasks.front()));
				tasks.pop_front();

				auto threadId = std::hash<std::thread::id>()(std::this_thread::get_id());
				if (eventThreadId != threadId)
					cout << "change in thread: " << threadId << " (should be: " << eventThreadId << ")" << "\r\n";

				// unlock during the task
				//lock.unlock();
				task();
				//lock.lock();

				eventsDone++;
			}
		}

		// sleeping here drops fps from 500 to 45
		// std::this_thread::sleep_for(std::chrono::microseconds(1));
	}
}

// Implementation of template :)
template<typename Functor>
inline TaskValue RunOnGuiThread(Functor func, TaskValue args) {
	std::packaged_task<TaskValue()> task(std::bind<TaskValue>(func, args));

	auto future = task.get_future();

	{
		std::lock_guard<std::mutex> lock(tasks_mutex);
		tasks.push_back(std::move(task));
	}

	return future.get();
}