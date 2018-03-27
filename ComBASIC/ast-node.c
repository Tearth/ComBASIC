#include "ast-node.h"

void astnode_init(node* node)
{
	string_init(&node->node_value);
	vector_init(&node->children);
}