#include "ast-node.h"

void astnode_init(ast_node* node, ast_node_type type, const char* value)
{
	string_init(&node->value);
	vector_init(&node->children);

	node->type = type;
	string_append_s(&node->value, value);
}

void astnode_clear(ast_node* node)
{
	string_clear(&node->value);
	vector_clear(&node->children);
}