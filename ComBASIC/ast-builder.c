#include "ast-builder.h"

node* ast_build(vector* tokens, vector* symbol_table)
{
	node* root = (node*)malloc(sizeof(node));
	astnode_init(root);
	root->node_type = N_ROOT;
	
	for (int i = 0; i < tokens->count; i++)
	{
		node* line_number = parser_linenumber_build(tokens, &i);
		node* keyword = parser_keyword_build(tokens, &i);

		ast_parsearguments(tokens, keyword, &i, symbol_table);
		vector_add(&line_number->children, keyword);
		vector_add(&root->children, line_number);
	}

	return root;
}

void ast_parsearguments(vector* tokens, node* keyword, int* index, vector* symbol_table)
{
	bool result = true;
	switch (keyword->node_type)
	{
		case N_CLS: { result = parser_cls_build(tokens, keyword, index, symbol_table); break; }
		case N_REM: { result = parser_rem_build(tokens, keyword, index, symbol_table); break; }
		case N_PRINT: { result = parser_print_build(tokens, keyword, index, symbol_table); break; }
	}
}

void ast_dump(node* node)
{
	printf("Generated abstract syntax tree:\n");
	ast_dump_r(node, 0);
	printf("End of abstract syntax tree\n");
}

void ast_dump_r(node* node, int level)
{
	for (int i = 0; i < level; i++) printf("   ");
	printf("%d %s\n", node->node_type, node->node_value.data);

	for (int i = 0; i < node->children.count; i++)
	{
		ast_dump_r(node->children.data[i], level + 1);
	}
}

void ast_clean(node* root)
{
	while (root->children.count > 0)
	{
		node* child = root->children.data[0];
		ast_clean(child);

		string_clean(&child->node_value);
		vector_remove(&root->children.data, 0);

		free(child);
	}

	vector_clean(&root->children);
}