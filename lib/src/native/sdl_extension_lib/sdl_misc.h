#ifndef _sdl_misc_h
#define _sdl_misc_h

#include <dart_api.h>
#include <deque>
#include <atomic>
#include <future>
#include <thread>
#include <mutex>

Dart_Handle HandleError(Dart_Handle handle);

struct TaskValue {
public:
	bool bool_1;
	void* ptr_1;
	void* ptr_2;
	void* ptr_3;
	int64_t integer_1;
	int64_t integer_2;
	int64_t integer_3;
	int64_t integer_4;
	int64_t integer_5;
	const char* string_1;
	const char* string_2;
	const char* string_3;

private:
	void _zero() {
		integer_1 = 0;
		integer_2 = 0;
		integer_3 = 0;
		integer_4 = 0;
		integer_5 = 0;
		string_1 = NULL;
		string_2 = NULL;
		string_3 = NULL;
		ptr_1 = NULL;
		ptr_2 = NULL;
		ptr_3 = NULL;
		bool_1 = false;
	}

public:
	TaskValue() {
		_zero();
	}

	TaskValue(const char* s1) {
		_zero();
		string_1 = s1;
	}

	TaskValue(bool b1) {
		_zero();
		bool_1 = b1;
	}

	TaskValue(void* p1) {
		_zero();
		ptr_1 = p1;
	}

	TaskValue(void* p1, void* p2) {
		_zero();
		ptr_1 = p1;
		ptr_2 = p2;
	}

	TaskValue(void* p1, void* p2, void* p3) {
		_zero();
		ptr_1 = p1;
		ptr_2 = p2;
		ptr_3 = p3;
	}

	TaskValue(int64_t i1) {
		_zero();
		integer_1 = i1;
	}

	TaskValue(int64_t i1, int64_t i2) {
		_zero();
		integer_1 = i1; 
		integer_2 = i2;
	}

	TaskValue(int64_t i1, int64_t i2, int64_t i3) {
		_zero();
		integer_1 = i1;
		integer_2 = i2;
		integer_3 = i3;
	}

	TaskValue(int64_t i1, int64_t i2, int64_t i3, int64_t i4) {
		_zero();
		integer_1 = i1;
		integer_2 = i2;
		integer_3 = i3;
		integer_4 = i4;
	}

	TaskValue(int64_t i1, int64_t i2, int64_t i3, int64_t i4, int64_t i5) {
		_zero();
		integer_1 = i1;
		integer_2 = i2;
		integer_3 = i3;
		integer_4 = i4;
		integer_5 = i5;
	}
};

extern std::deque<std::packaged_task<TaskValue()>> tasks;
extern std::mutex tasks_mutex;
extern std::atomic<bool> events_running;

template<typename Functor>
TaskValue RunOnGuiThread(Functor func, TaskValue args);


#endif // _sdl_misc_h

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