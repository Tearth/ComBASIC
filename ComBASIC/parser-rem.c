#include "parser-rem.h"

bool parser_rem_build(vector* tokens, node* keyword, int* index, vector* symbol_table)
{
	while (((token*)tokens->data[*index])->token_type != T_END_OF_INSTRUCTION) (*index)++;
	return true;
}