#include "ast-builder.h"

node* ast_build(vector* tokens)
{
	node* root = (node*)malloc(sizeof(node));
	astnode_init(root);
	root->node_type = N_ROOT;
	
	for (int i = 0; i < tokens->count; i++)
	{
		node* line_number = parser_linenumber_build(tokens, &i);
		node* keyword = parser_keyword_build(tokens, &i);

		ast_parsearguments(tokens, keyword, &i);
		vector_add(&line_number->children, keyword);
		vector_add(&root->children, line_number);
	}

	return root;
}

void ast_parsearguments(vector* tokens, node* keyword, int* index)
{
	switch (keyword->node_type)
	{
		case N_CLS: { parser_cls_build(tokens, keyword, index); break; }
		case N_REM: { parser_rem_build(tokens, keyword, index); break; }
	}
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