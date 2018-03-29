#include "parser-cls.h"

bool parser_cls_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table)
{
	return ((ast_node*)tokens->data[*index])->type == T_END_OF_INSTRUCTION;
}