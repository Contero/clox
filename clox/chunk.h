#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"

typedef enum
{
	OP_RETURN,
} Opcode;

typedef struct
{
	int count;
	int capacity;
	uint8_t* code;
} Chunk;

/*
Initializes a chunk, sets values to 0
Param: pointer to the chunk
*/
void initChunk(Chunk*);

/*
Frees a chunk's dynamic memory allocations
Param: Pointer to the soon to be free chunk
*/
void freeChunk(Chunk*);

/*
Appends a new opcode to a chunk
Param: Pointer to the chunk to append to
Param: The OP_CODE byte to append
*/
void writeChunk(Chunk*, uint8_t);

#endif