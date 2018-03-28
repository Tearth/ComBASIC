#pragma once
#include "vector.h"
#include "string.h"

typedef enum symbol_type
{
	S_INTEGER,
	S_STRING
} symbol_type;

typedef struct symbol
{
	symbol_type type;
	string name;
	string value;
} symbol;

void symboltable_init(symbol* symbol);
void symboltable_add(vector* symbol_table, symbol* new_symbol);
void symboltable_dump(vector* symbol_table);