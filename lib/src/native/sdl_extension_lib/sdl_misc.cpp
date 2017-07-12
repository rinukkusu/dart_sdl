#include "sdl_misc.h"

std::deque<std::packaged_task<TaskValue()>> tasks;
std::mutex tasks_mutex;
std::atomic<bool> events_running;
std::thread ethread;

Dart_Handle HandleError(Dart_Handle handle) {
	if (Dart_IsError(handle)) Dart_PropagateError(handle);
	return handle;
}
