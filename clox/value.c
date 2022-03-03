#include <stdio.h>

#include "memory.h"
#include "value.h"


void initValueArray(ValueArray* valueArray)
{
	valueArray->capacity = 0;
	valueArray->count = 0;
	valueArray->values = NULL;
}

void writeValueArray(ValueArray* valueArray, Value value)
{
	if (valueArray->capacity < valueArray->count + 1)
	{
		int oldCapacity = valueArray->capacity;
		valueArray->capacity = GROW_CAPACITY(oldCapacity);
		valueArray->values = GROW_ARRAY(Value, valueArray->values, oldCapacity, valueArray->capacity);
	}

	valueArray->values[valueArray->count] = value;
	valueArray->count++;
}

void freeValueArray(ValueArray* array)
{
	FREE_ARRAY(Value, array->values, array->capacity);
	initValueArray(array);
}

void printValue(Value value)
{
	printf("%g", value);
}
