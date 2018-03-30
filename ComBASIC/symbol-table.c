#include "symbol-table.h"

int anonymous_variables_count = 0;

void symboltable_add(vector* symbol_table, symbol_node* symbol)
{
	bool found = false;
	for (int i = 0; i < symbol_table->count; i++)
	{
		symbol_node* current = symbol_table->data[i];
		if (symbol->name.count > 0 && strcmp(current->name.data, symbol->name.data) == 0)
		{
			found = true;
			break;
		}
	}

	if (!found)
	{
		if (symbol->name.count == 0)
		{
			char variable_name[64];

			sprintf(variable_name, "%s%d", "var", anonymous_variables_count);
			string_append_s(&symbol->name, variable_name);

			anonymous_variables_count++;
		}

		vector_add(symbol_table, symbol);
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
	while(symbol_table->count > 0)
	{
		symbol_node* s = symbol_table->data[0];
		symbolnode_clean(s);

		vector_remove(symbol_table, 0);
		free(s);
	}

	vector_clean(symbol_table);
}