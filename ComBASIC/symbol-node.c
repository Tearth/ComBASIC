#include "symbol-node.h"

void symbolnode_init(symbol_node* symbol, symbol_type type, const char* name, const char* value)
{
	string_init(&symbol->name);
	string_init(&symbol->value);
	
	symbol->type = type;
	string_append_s(&symbol->name, name);
	string_append_s(&symbol->value, value);
}

void symbolnode_clean(symbol_node* symbol)
{
	string_clean(&symbol->name);
	string_clean(&symbol->value);
}