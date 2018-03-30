#include "parser-print.h"

bool parser_print_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table)
{
	token* end_of_instruction_token;
	
	parser_string_build(tokens, keyword, index, symbol_table);

	end_of_instruction_token = tokens->data[*index];
	if (end_of_instruction_token->token_type != T_END_OF_INSTRUCTION) return false;

	return true;
}