#include "ast-builder.h"

ast_node* ast_build(vector* tokens, vector* symbol_table)
{
	ast_node* root = (ast_node*)malloc(sizeof(ast_node));
	astnode_init(root, N_ROOT, "");
	
	for (int i = 0; i < tokens->count; i++)
	{
		ast_node* line_number = parser_linenumber_build(tokens, &i);
		if (line_number == NULL)
		{
			lexical_token* current_token = tokens->data[i];

			printf("ERROR: Line number not found: %s\n", current_token->value.data);
			exit(-1);
		}

		ast_node* keyword = parser_keyword_build(tokens, &i);
		if (keyword == NULL)
		{
			lexical_token* current_token = tokens->data[i];

			printf("ERROR: Keyword not found: %s\n", current_token->value.data);
			exit(-1);
		}
		
		if (!ast_parsearguments(tokens, keyword, &i, symbol_table))
		{
			lexical_token* current_token = tokens->data[i];

			printf("ERROR: Invalid argument: %s\n", current_token->value.data);
			exit(-1);
		}

		vector_add(&root->children, line_number);
		vector_add(&line_number->children, keyword);
	}

	return root;
}

bool ast_parsearguments(vector* tokens, ast_node* keyword, int* index, vector* symbol_table)
{
	bool result = true;
	switch (keyword->type)
	{
		case N_CLS:		{ result = parser_cls_build(tokens, keyword, index, symbol_table); break; }
		case N_REM:		{ result = parser_rem_build(tokens, keyword, index, symbol_table); break; }
		case N_PRINT:	{ result = parser_print_build(tokens, keyword, index, symbol_table); break; }
		case N_LET:		{ result = parser_let_build(tokens, keyword, index, symbol_table); break; }
	}

	return result;
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