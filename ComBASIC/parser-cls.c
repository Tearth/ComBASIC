#include "parser-cls.h"

bool parser_cls_build(vector* tokens, node* keyword, int* index)
{
	return tokens->data[*index] == T_END_OF_INSTRUCTION;
}