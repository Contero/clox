#include <stdlib.h>
#include "chunk.h"
#include "memory.h"

void initChunk(Chunk* chunk)
{
	chunk->capacity = 0;
	chunk->count = 0;
	chunk->code = NULL;
	chunk->lines = NULL;
	chunk->lineCapacity = 0;
	chunk->lineCount = 0;
	initValueArray(&chunk->constants);
}

void freeChunk(Chunk* chunk)
{
	FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
	FREE_ARRAY(int, chunk->lines, chunk->capacity);
	freeValueArray(&chunk->constants);
	initChunk(chunk);
}

void writeChunk(Chunk* chunk, uint8_t byte, int line)
{
	if (chunk->capacity < chunk->count + 1)
	{
		int oldCapacity = chunk->capacity;
		chunk->capacity = GROW_CAPACITY(oldCapacity);
		chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
		// chunk->lines = GROW_ARRAY(int, chunk->lines, oldCapacity, chunk->capacity);
	}

	if (chunk->lineCapacity < chunk->lineCount + 1)
	{
		int oldCapacity = chunk->lineCapacity;
		chunk->lineCapacity = GROW_CAPACITY(oldCapacity); 
		chunk->lines = GROW_ARRAY(Line, chunk->lines, oldCapacity, chunk->lineCapacity);
	}

	chunk->code[chunk->count] = byte;
	//chunk->lines[chunk->count] = line;
	if (chunk->lines[chunk->lineCount - 1].line != line)
	{
		chunk->lines[chunk->lineCount].line = line;
		chunk->lines[chunk->lineCount].offset = chunk->count;
		chunk->lineCount++;
	}
	chunk->count++;
}

void writeConstant(Chunk* chunk, Value value, int line)
{
	if (chunk->constants.count < 256)
	{
		writeValueArray(&chunk->constants, value);
		writeChunk(chunk, OP_CONSTANT, line);
		writeChunk(chunk, chunk->constants.count - 1, line);
	}
	else
	{
		uint8_t ops[3];
		int index = chunk->constants.count;

		ops[0] = index & 0xff;
		ops[1] = (index >> 8) & 0xff;
		ops[2] = (index >> 16) & 0xff;

		writeValueArray(&chunk->constants, value);
		writeChunk(chunk, OP_CONSTANT_LONG, line);
		writeChunk(chunk, ops[0], line);
		writeChunk(chunk, ops[1], line);
		writeChunk(chunk, ops[2], line);
	}

}

int addConstant(Chunk* chunk, Value value)
{
	writeValueArray(&chunk->constants, value);
	return chunk->constants.count - 1;
}

int getLine(Chunk* chunk, int offset)
{
	int i;
	for (i = 0; i < chunk->lineCount; i++)
	{
		if (chunk->lines[i].offset == offset)
		{
			return chunk->lines[i].line;
		}
		else if (chunk->lines[i].offset > offset)
		{
			return chunk->lines[i-1].line;
		}
	}

	return chunk->lines[i].line;
}