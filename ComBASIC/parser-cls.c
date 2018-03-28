#include "parser-cls.h"

bool parser_cls_build(vector* tokens, node* keyword, int* index)
{
	return ((node*)tokens->data[*index])->node_type == T_END_OF_INSTRUCTION;
}