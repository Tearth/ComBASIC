#include "generator-expression.h"

void generator_expression_build(string* code, ast_node* root, vector* symbol_table)
{
	if (root->type == N_EXPRESSION) root = root->children.data[0];

}