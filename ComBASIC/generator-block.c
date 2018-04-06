#include "generator-block.h"

void generator_block_build(string* code, ast_node* root, vector* symbol_table)
{
	for (int i = 0; i < root->children.count; i++)
	{
		ast_node* linenumber_node = root->children.data[i];
		generator_linenumber_build(code, linenumber_node, symbol_table);

		ast_node* keyword_node = linenumber_node->children.data[0];
		switch (keyword_node->type)
		{
			case N_CLS:		{ generator_cls_build(code, keyword_node, symbol_table); break; }
			case N_PRINT:	{ generator_print_build(code, keyword_node, symbol_table); break; }
			case N_REM:		{ generator_rem_build(code, keyword_node, symbol_table); break; }
			case N_LET:		{ generator_let_build(code, keyword_node, symbol_table); break; }
			case N_END:		{ generator_end_build(code, keyword_node, symbol_table); break; }
			case N_IF:		{ generator_if_build(code, keyword_node, symbol_table); break; }
			case N_GOTO:	{ generator_goto_build(code, keyword_node, symbol_table); break; }
			case N_WHILE:	{ generator_while_build(code, keyword_node, symbol_table); break; }
			default:
			{
				printf("ERROR: Invalid keyword.\n");
				exit(-1);
			}
		}
	}
}