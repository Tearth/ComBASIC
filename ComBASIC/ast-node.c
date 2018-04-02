#include "ast-node.h"

void astnode_init(ast_node* node, ast_node_type type, const char* value)
{
	string_init(&node->value);
	vector_init(&node->children);

	node->type = type;
	string_append_s(&node->value, value);
}

void astnode_clean(ast_node* node)
{
	string_clean(&node->value);
	vector_clean(&node->children);
}