#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

typedef struct
{
	Chunk* chunk;
	uint8_t* ip;
	Value stack[STACK_MAX];
	Value* stackTop;
} VM;

typedef enum
{
	INTERPRET_OK,
	INTERPRET_COMPILE_ERROR,
	INTERPRET_RUNTIME_ERROR
} InterpretResult;

/*
Initializes Virtual Machine
*/
void initVM();

/*
Frees VM memory
*/
void freeVM();

/*
Interprets a chunk of bytecode
param: pointer to the chunk
*/
InterpretResult interpret(Chunk* chunk);

/*
Adds value to stack
param: the value to add
*/
void push(Value);

/*
removes value from stack
returns: the value popped
*/
Value pop();
#endif // !clox_vm_h
