#ifndef _sdl_ptrlist_h
#define _sdl_ptrlist_h

#include <SDL.h>

struct PtrNode {
	PtrNode* previous;
	PtrNode* next;

	void* data;
};

struct PtrList {
	int count;
	PtrNode* head;
	PtrNode* tail;

	void Init() {
		PtrNode* node = (PtrNode*)SDL_calloc(1, sizeof(PtrNode));
		node->previous = NULL;
		node->next = NULL;

		head = node;
		tail = node;

		count = 0;
	}

	void Add(void* data) {
		PtrNode* node = (PtrNode*)SDL_calloc(1, sizeof(PtrNode));
		node->data = data;
		node->previous = tail;
		node->next = NULL;

		tail->next = node;
		tail = node;

		count++;
	}

	PtrNode* Find(void* data) {
		PtrNode* node = head;

		while (node->data != data) {
			node = node->next;

			if (!node) return NULL;
		}

		return node;
	}

	void Delete(void* data) {
		PtrNode* node = Find(data);
		if (!node || node == head) return;

		PtrNode* next = node->next;
		PtrNode* previous = node->previous;

		if (next) next->next = previous;
		if (previous) previous->previous = next;

		if (head == node)
			head = next;

		if (tail == node)
			tail = previous;

		free(node);

		count--;
	}
} PtrList_t;

#endif // _sdl_ptrlist_h