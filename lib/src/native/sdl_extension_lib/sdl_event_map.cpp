#include <Windows.h>
#include <string>
#include "SDL.h"
#include "sdl_event_map.h"
#include "json.h"


void EncodeSubEvent(json_object* o, SDL_WindowEvent* event) {
	o->add("event", event->event);
	o->add("data1", event->data1);
	o->add("data2", event->data2);
	o->add("timestamp", event->timestamp);
}

void EncodeSubEvent(json_object* o, SDL_QuitEvent* event) {
	o->add("timestamp", event->timestamp);
}

void EncodeSubEvent(json_object* o, SDL_MouseMotionEvent* event) {
	o->add("x", event->x);
	o->add("xrel", event->xrel);
	o->add("y", event->y);
	o->add("yrel", event->yrel);
	o->add("state", event->state);
	o->add("which", event->which);
	o->add("timestamp", event->timestamp);
}


const char* EncodeEvent(SDL_Event* event) {
	json_object o = json_object_t;
	o.init();

	o.add("type", event->type);

	switch (event->type)
	{
	case SDL_WINDOWEVENT:
		EncodeSubEvent(&o, &event->window);
		break;
	case SDL_MOUSEMOTION:
		EncodeSubEvent(&o, &event->motion);
		break;
	case SDL_QUIT:
		EncodeSubEvent(&o, &event->quit);
		break;
	default:
		break;
	}
	
	const char* value = o.serialize();
	o.free();

	return value;
}

