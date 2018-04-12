#include "symbol-node.h"

void symbolnode_init(symbol_node* symbol, symbol_node_type type, const char* name, const char* value)
{
	string_init(&symbol->name);
	string_init(&symbol->value);
	
	symbol->type = type;
	string_append_s(&symbol->name, name);
	string_append_s(&symbol->value, value);
}

void symbolnode_clear(symbol_node* symbol)
{
	string_clear(&symbol->name);
	string_clear(&symbol->value);
}