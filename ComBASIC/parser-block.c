#include "parser-block.h"

bool parser_block_build(vector* tokens, ast_node* root, vector* symbol_table)
{
	for (int i = 0; i < tokens->count; i++)
	{
		ast_node* line_number = parser_linenumber_build(tokens, &i);
		if (line_number == NULL)
		{
			lexical_token* current_token = tokens->data[i];

			printf("ERROR: Line number not found: %s\n", current_token->value.data);
			exit(-1);
		}

		ast_node* keyword = parser_keyword_build(tokens, &i);
		if (keyword == NULL)
		{
			lexical_token* current_token = tokens->data[i];

			printf("ERROR: Keyword not found: %s\n", current_token->value.data);
			exit(-1);
		}

		if (!ast_parsearguments(tokens, keyword, &i, symbol_table))
		{
			lexical_token* current_token = tokens->data[i];

			printf("ERROR: Invalid argument: %s\n", current_token->value.data);
			exit(-1);
		}

		vector_add(&root->children, line_number);
		vector_add(&line_number->children, keyword);
	}
}

bool ast_parsearguments(vector* tokens, ast_node* keyword, int* index, vector* symbol_table)
{
	bool result = true;
	switch (keyword->type)
	{
		case N_CLS: { result = parser_cls_build(tokens, keyword, index, symbol_table); break; }
		case N_REM: { result = parser_rem_build(tokens, keyword, index, symbol_table); break; }
		case N_PRINT: { result = parser_print_build(tokens, keyword, index, symbol_table); break; }
		case N_LET: { result = parser_let_build(tokens, keyword, index, symbol_table); break; }
		case N_END: { result = parser_end_build(tokens, keyword, index, symbol_table); break; }
		case N_IF: { result = parser_if_build(tokens, keyword, index, symbol_table); break; }
		case N_GOTO: { result = parser_goto_build(tokens, keyword, index, symbol_table); break; }
		case N_WHILE: { result = parser_while_build(tokens, keyword, index, symbol_table); break; }
		case N_INPUT: { result = parser_input_build(tokens, keyword, index, symbol_table); break; }
	}

	return result;
}