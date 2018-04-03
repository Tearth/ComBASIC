#pragma once
#include "string.h"

typedef enum symbol_node_type
{
	S_INTEGER,
	S_STRING
} symbol_node_type;

typedef struct symbol_node
{
	symbol_node_type type;
	string name;
	string value;
} symbol_node;

void symbolnode_init(symbol_node* symbol, symbol_node_type type, const char* name, const char* value);
void symbolnode_clean(symbol_node* symbol);