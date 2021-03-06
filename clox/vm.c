#include <stdio.h>
#include "common.h"
#include "complier.h"
#include "debug.h"
#include "vm.h"

VM vm;

static void resetStack()
{
	vm.stackTop = vm.stack;
}

void initVM()
{
	resetStack();
}

void freeVM()
{

}

Value readConstantLong()
{
	int b1, b2, b3, bc;
	b1 = *vm.ip++;
	b2 = (int)(*vm.ip++) << 8;
	b3 = (int)*vm.ip++ << 16;
	bc = b1 | b2 | b3;

	return vm.chunk->constants.values[bc];
}

static InterpretResult run()
{
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define BINARY_OP(op) do {\
						double b = pop(); \
						double a = pop(); \
						push (a op b); \
					} while (false)

	while (true)
	{
#ifdef DEBUG_TRACE_EXECUTION
		printf("        ");
		for (Value* slot = vm.stack; slot < vm.stackTop; slot++)
		{
			printf("[ ");
			printValue(*slot);
			printf(" ]");
		}
		printf("\n");

		disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif
		uint8_t instruction;
		switch (instruction = READ_BYTE())
		{
		case OP_CONSTANT:
		{
			Value constant = READ_CONSTANT();
			push(constant);
			break;
		}
		case OP_CONSTANT_LONG:
		{
			Value constant = readConstantLong();
			push(constant);
			break;
		}
		case OP_ADD:
		{
			BINARY_OP(+);
			break;
		}
		case OP_SUBTRACT:
			BINARY_OP(-);
			break;
		case OP_MULTIPLY:
			BINARY_OP(*);
			break;
		case OP_DIVIDE:
			BINARY_OP(/);
			break;
		case OP_NEGATE:
		{
			// push(-pop());
			*(vm.stackTop - 1) = -*(vm.stackTop - 1);
			break;
		}
		case OP_RETURN:
		{
			printValue(pop());
			printf("\n");
			return INTERPRET_OK;
		}

		}
	}
#undef READ_BYTE
#undef READ_CONSTANT
#undef BINARY_OP
}

InterpretResult interpret(const char* source)
{
	compile(source);
	return INTERPRET_OK;
}

void push(Value value)
{
	*vm.stackTop = value;
	vm.stackTop++;
}

Value pop()
{
	vm.stackTop--;
	return *vm.stackTop;
}