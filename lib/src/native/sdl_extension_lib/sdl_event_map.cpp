#include <Windows.h>
#include <string>
#include "SDL.h"
#include "sdl_event_map.h"
#include "json.h"


void EncodeWindowEvent(json_object* o, SDL_WindowEvent* event) {
	o->add("type", SDL_WINDOWEVENT);
	o->add("event", event->event);
	o->add("data1", event->data1);
	o->add("data2", event->data2);
	o->add("timestamp", event->timestamp);
}


const char* EncodeEvent(SDL_Event* event) {
	json_object o = json_object_t;
	o.init();

	switch (event->type)
	{
	case SDL_WINDOWEVENT:
		EncodeWindowEvent(&o, &event->window);
		break;
	default:
		break;
	}
	
	return o.serialize();
}

