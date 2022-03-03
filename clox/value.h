#ifndef clox_value_h
#define clox_value_h

#include "common.h"

typedef double Value;

typedef struct
{
	int capacity;
	int count;
	Value* values;
} ValueArray;

/*
initializes a value array, sets count and capacity to 0
param: pointer to the value array
*/
void initValueArray(ValueArray*);

/*
writes a value to the value array, expanding as needed
param: pointer to the value array
param: the value to add to the array
*/
void writeValueArray(ValueArray*, Value);

/*
frees the memory of a value array
param: pointer to the value array
*/
void freeValueArray(ValueArray*);

/*
prints a value
param: the value to print
*/
void printValue(Value value);
#endif