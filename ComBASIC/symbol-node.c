#include "symbol-node.h"

void symbolnode_init(symbol_node* symbol)
{
	string_init(&symbol->name);
	string_init(&symbol->value);
	symbol->type = 0;
}

void symbolnode_clean(symbol_node* symbol)
{
	string_clean(&symbol->name);
	string_clean(&symbol->value);
}