#include "common.h"
#include "chunk.h"
#include "debug.h"

int main(int arhc, char* argv[])
{
	Chunk chunk;
	initChunk(&chunk);

	int constant = addConstant(&chunk, 1.2);
	writeChunk(&chunk, OP_CONSTANT, 12);
	writeChunk(&chunk, constant, 12);
	writeChunk(&chunk, OP_RETURN, 13);
	writeChunk(&chunk, OP_RETURN, 13);
	writeChunk(&chunk, OP_RETURN, 14);
	writeChunk(&chunk, OP_RETURN, 14);
	for (int i = 0; i < 270; i++)
		writeConstant(&chunk, i,15);
	disassembleChunk(&chunk, "Test chunk");
	freeChunk(&chunk);

	return 0;
}