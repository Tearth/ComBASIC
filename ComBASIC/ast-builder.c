#include "ast-builder.h"

ast_node* ast_build(vector* tokens, vector* symbol_table)
{
	ast_node* root = (ast_node*)malloc(sizeof(ast_node));
	astnode_init(root, N_ROOT, "");
	
	parser_block_build(tokens, root, symbol_table);

	return root;
}

void ast_dump(ast_node* node)
{
	printf("Generated abstract syntax tree:\n");
	ast_dump_r(node, 0);
	printf("End of abstract syntax tree\n");
}

void ast_dump_r(ast_node* node, int level)
{
	for (int i = 0; i < level; i++) printf("   ");
	printf("%d %s\n", node->type, node->value.data);

	for (int i = 0; i < node->children.count; i++)
	{
		ast_dump_r(node->children.data[i], level + 1);
	}
}

void ast_clean(ast_node* root)
{
	while (root->children.count > 0)
	{
		ast_node* child = root->children.data[0];
		ast_clean(child);

		vector_remove(&root->children, 0);
		free(child);
	}

	astnode_clean(root);
}