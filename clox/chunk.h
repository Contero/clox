#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum
{
	OP_CONSTANT,
	OP_CONSTANT_LONG,
	OP_RETURN,
} Opcode;

typedef struct
{
	int line;
	int offset;
} Line;

typedef struct
{
	int count;
	int capacity;
	uint8_t* code;
//	int* lines;
	Line* lines;
	int lineCount;
	int lineCapacity;
	ValueArray constants;
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
Param: The line number from source code
*/
void writeChunk(Chunk*, uint8_t, int);

/*
Adds a constant to the constant pool
Writes load instruction to chunk
Param: pointer to the chunk
Param: the value to add
Param: the line number of source code
*/
void writeConstant(Chunk*, Value, int);

/*Adds a constant to the chunck's constant pool
param: pointer to the chunk
param: the value to add
returns: the index of the added constant
*/
int addConstant(Chunk*, Value);

/*
* gets a linenumber from a chunk from offset
* param: pointer to the chunk
* param: the offset
*/
int getLine(Chunk*, int);

#endif