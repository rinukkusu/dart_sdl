#ifndef _json_h
#define _json_h


#include <SDL.h>
#include <string>

enum json_value_type {
	STRING,
	NUMBER
};

struct json_value {
	int type;

	const char* string;
	int number;

	void set_string(const char* s) {
		type = json_value_type::STRING;
		string = s;
	}

	void set_number(int n) {
		type = json_value_type::NUMBER;
		number = n;
	}

	char* value() {
		char* value = (char*)SDL_calloc(sizeof(char), 1000);

		switch (type) {
		case json_value_type::STRING:
			strcat(value, "\"");
			strcat(value, string);
			strcat(value, "\"");
			break;
		case json_value_type::NUMBER:
			itoa(number, value, 10);
			break;
		}

		return value;
	}
} json_value_t;

struct json_object {
	const char** keys;
	json_value* values;
	int count;

	void init() {
		count = 0;
		keys = (const char**)SDL_calloc(sizeof(const char*), 100);
		values = (json_value*)SDL_calloc(sizeof(json_value), 100);
	}

	void add(const char* key, const char* s) {
		keys[count] = key;

		json_value value = json_value_t;
		value.set_string(s);
		values[count] = value;

		count++;
	}

	void add(const char* key, int i) {
		keys[count] = key;

		json_value value = json_value_t;
		value.set_number(i);
		values[count] = value;

		count++;
	}

	const char* serialize() {
		char* str = (char*)SDL_calloc(sizeof(char), 1000);

		strcat(str, "{");

		for (int i = 0; i < count; i++) {
			const char* key = keys[i];
			json_value j_value = values[i];

			strcat(str, "\"");
			strcat(str, key);
			strcat(str, "\"");

			strcat(str, ":");

			char* value = j_value.value();
			strcat(str, value);
			SDL_free(value);

			if (i != count - 1)
				strcat(str, ",");
		}

		strcat(str, "}");


		return str;
	}

	void free() {
		SDL_free(keys);
		SDL_free(values);
	}
} json_object_t;


#endif // _json_h