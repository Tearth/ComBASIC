#include "symbol-table.h"

void symboltable_init(symbol* symbol)
{
	string_init(&symbol->name);
	string_init(&symbol->value);
	symbol->type = 0;
}

void symboltable_add(vector* symbol_table, symbol* new_symbol)
{
	bool found = false;
	for (int i = 0; i < symbol_table->count; i++)
	{
		symbol* current = symbol_table->data[i];
		if (strcmp(current->name.data, new_symbol->name.data) == 0)
		{
			found = true;
			break;
		}
	}

	if (!found)
	{
		vector_add(symbol_table, new_symbol);
	}
}

void symboltable_dump(vector* symbol_table)
{
	printf("Symbol table:\n");
	for (int i = 0; i < symbol_table->count; i++)
	{
		symbol* symbol_to_print = symbol_table->data[i];
		printf("%d %s %s", symbol_to_print->type, symbol_to_print->name.data, symbol_to_print->value.data);
	}
	printf("End of symbol table.\n");
}