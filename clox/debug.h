#ifndef clox_debug_h
#define clox_debug_h

#include "chunk.h"

/*
Prints disassembled bytecode of a chunk
Param: pointer to chunk
*/
void disassembleChunk(Chunk*, const char*);

/*
Prints disassembled instruction of a chunk
Param: pointer to the chunk
Param: offset from beginning of chunk to instruction
Returns: offset of next instruction
*/
int disassembleInstruction(Chunk*, int);

#endif