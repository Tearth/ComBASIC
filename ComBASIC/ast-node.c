#include "ast-node.h"

void astnode_init(ast_node* node)
{
	string_init(&node->value);
	vector_init(&node->children);
}

void astnode_clean(ast_node* node)
{
	string_clean(&node->value);
	vector_clean(&node->children);
}