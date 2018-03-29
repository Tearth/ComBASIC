#include "symbol-table.h"

void symboltable_add(vector* symbol_table, symbol_node* new_symbol)
{
	bool found = false;
	for (int i = 0; i < symbol_table->count; i++)
	{
		symbol_node* current = symbol_table->data[i];
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
		symbol_node* symbol_to_print = symbol_table->data[i];
		printf("%d %s %s\n", symbol_to_print->type, symbol_to_print->name.data, symbol_to_print->value.data);
	}
	printf("End of symbol table\n");
}

void symboltable_clean(vector* symbol_table)
{
	for (int i = 0; i < symbol_table->count; i++)
	{
		symbol_node* s = symbol_table->data[i];
		symbolnode_clean(s);

		vector_remove(symbol_table, i);
		free(s);
	}

	vector_clean(symbol_table);
}