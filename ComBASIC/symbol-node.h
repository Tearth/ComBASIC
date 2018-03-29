#pragma once
#include "string.h"

typedef enum symbol_type
{
	S_INTEGER,
	S_STRING
} symbol_type;

typedef struct symbol_node
{
	symbol_type type;
	string name;
	string value;
} symbol_node;

void symbolnode_init(symbol_node* symbol);
void symbolnode_clean(symbol_node* symbol);