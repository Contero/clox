#include "common.h"
#include "chunk.h"
#include "debug.h"

int main(int arhc, char* argv[])
{
	Chunk chunk;
	initChunk(&chunk);
	writeChunk(&chunk, OP_RETURN);
	disassembleChunk(&chunk, "Test chunk");
	freeChunk(&chunk);

	return 0;
}