#include "debug.h"
#include "value.h"

void disassembleChunk(Chunk* chunk, const char* name)
{
	printf("== %s ==\n", name);
	for (int offset = 0; offset < chunk->count;)
	{
		offset = disassembleInstruction(chunk, offset);
	}
}

int disassembleInstruction(Chunk* chunk, int offset)
{
	printf("%04d ", offset);

	int line = getLine(chunk, offset);

	if (offset > 0 && line == getLine(chunk, offset - 1))
	{
		printf("   | ");
	}
	else
	{
		printf("%4d ", /*chunk->lines[offset]*/ line);
	}

	uint8_t instruction = chunk->code[offset];

	switch (instruction)
	{
	case OP_CONSTANT:
		return constantInstruction("OP_CONSTANT", chunk, offset);
	case OP_CONSTANT_LONG:
		return constantInstruction("OP_CONSTANT_LONG", chunk, offset);
	case OP_RETURN:
		return simpleInstruction("OP_RETURN", offset);
	default:
		printf("Unknown opcode %d\n", instruction);
		return offset + 1;
	}

	// not needed but the complier doesn't know it
	return 0;
}

static int constantInstruction(const char* name, Chunk* chunk, int offset)
{
	if (name == "OP_CONSTANT")
	{
		// constant here is the index of where to find the constant
		uint8_t constant = chunk->code[offset + 1];
		printf("%-16s % 4d '", name, constant);
		printValue(chunk->constants.values[constant]);
		printf("'\n");

		return offset + 2;
	}
	else
	{
		// constant here is the index of where to find the constant
		int constant = (int)(chunk->code[offset + 3] << 16) | (int)(chunk->code[offset + 2]) << 8 | chunk->code[offset + 1];
		printf("%-16s % 4d '", name, constant);
		printValue(chunk->constants.values[constant]);
		printf("'\n"); 
		
		return offset + 4;
	}
}

static int simpleInstruction(const char* name, int offset)
{
	printf("%s\n", name);
	return offset + 1;
}