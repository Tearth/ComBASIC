#include "symbol-table.h"

int anonymous_variables_count = 0;

symbol_node* symboltable_add(vector* symbol_table, symbol_type type, const char* name, const char* value)
{
	bool found = false;
	for (int i = 0; i < symbol_table->count; i++)
	{
		symbol_node* current = symbol_table->data[i];
		if (strcmp(current->name.data, name) == 0)
		{
			return current;
		}
	}

	symbol_node* symbol = (symbol_node*)malloc(sizeof(symbol_node));
	symbolnode_init(symbol, type, name, value);

	if (symbol->name.count == 0)
	{
		char variable_name[64];

		sprintf_s(variable_name, 64, "%s%d", "var", anonymous_variables_count);
		string_append_s(&symbol->name, variable_name);

		anonymous_variables_count++;
	}

	vector_add(symbol_table, symbol);
	return symbol;
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