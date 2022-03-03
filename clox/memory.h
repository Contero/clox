#ifndef clox_memory_h
#define clox_memory_h

#include "common.h"
#include "chunk.h"

#define GROW_CAPACITY(capacity) \
	((capacity) < 8 ? 8 : (capacity) * 2);

#define GROW_ARRAY(type, pointer, oldcount, newcount) \
	(type*)reallocate(pointer, sizeof(type) * (oldcount), sizeof(type) * (newcount))

#define FREE_ARRAY(type, pointer, oldCount) \
	reallocate(pointer, sizeof(type) * (oldCount), 0)

/*
Reallocates memory for the newly engorged array
param: Pointer to the array
param: old size of the array
param: new size engorged array
*/
void* reallocate(void*, size_t, size_t);

#endif