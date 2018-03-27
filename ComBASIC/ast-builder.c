#include "ast-builder.h"

node* ast_build(vector* tokens)
{
	node* root = (node*)malloc(sizeof(node));
	ast_initnode(root);
	root->node_type = N_ROOT;
	
	for (int i = 0; i < tokens->count; i++)
	{
		node* line_number = parser_linenumber_build(tokens, &i);
	}

	return root;
}

void ast_initnode(node* node)
{
	string_init(&node->node_value);
	vector_init(&node->children);
}

void ast_dump(node* node)
{
	ast_dump_r(node, 0);
}

void ast_dump_r(node* node, int level)
{
	for (int i = 0; i < level; i++) printf(" ");
	printf("%d %s\n", node->node_type, node->node_value.data);

	for (int i = 0; i < node->children.count; i++)
	{
		ast_dump_r(node->children.data[i], level + 1);
	}
}