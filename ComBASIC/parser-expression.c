#include "parser-expression.h"

ast_node* parser_expression_build(vector* tokens, int* index, lexical_token* line_number, vector* symbol_table)
{
	ast_node* expression_root = (ast_node*)malloc(sizeof(ast_node));
	astnode_init(expression_root, N_EXPRESSION, "");

	vector* rpn = parser_expression_buildrpn(tokens, index, line_number, symbol_table);
	vector* rpn_nodes = parser_expression_buildrpnnodes(rpn, symbol_table);
	parser_expression_buildrpntree(rpn_nodes, expression_root, line_number);

	vector_clear(rpn_nodes);
	vector_clear(rpn);

	free(rpn_nodes);
	free(rpn);

	return expression_root;
}

vector* parser_expression_buildrpn(vector* tokens, int* index, lexical_token* line_number, vector* symbol_table)
{
	vector* rpn = (vector*)malloc(sizeof(vector));
	vector_init(rpn);

	vector stack;
	vector_init(&stack);

	lexical_token* current_token = tokens->data[*index];
	while (parser_expression_istokenvalid(current_token))
	{
		if (current_token->token_type == T_NUMBER || current_token->token_type == T_IDENTIFIER)
		{
			vector_add(rpn, current_token);
		}
		else if (current_token->token_type == T_FUNCTION)
		{
			vector_add(&stack, current_token);
		}
		else if (current_token->token_type == T_COMMA)
		{
			lexical_token* last_operator_on_stack = stack.data[stack.count - 1];
			while (stack.count > 0 && strcmp("(", last_operator_on_stack->value.data) != 0)
			{
				vector_add(rpn, last_operator_on_stack);
				vector_remove(&stack, stack.count - 1);

				last_operator_on_stack = stack.data[stack.count - 1];
			}

			if (stack.count == 0)
			{
				printf("\n\nPARSER ERROR: Invalid function arguments count at line %s.\n", line_number->value.data);
				exit(-1);
			}
		}
		else if (current_token->token_type == T_OPERATOR)
		{
			if (strcmp("(", current_token->value.data) == 0)
			{
				vector_add(&stack, current_token);
			}
			else if (strcmp(")", current_token->value.data) == 0)
			{
				lexical_token* last_operator_on_stack = stack.data[stack.count - 1];
				while (stack.count > 0 && strcmp("(", last_operator_on_stack->value.data) != 0)
				{
					vector_add(rpn, last_operator_on_stack);
					vector_remove(&stack, stack.count - 1);

					last_operator_on_stack = stack.data[stack.count - 1];
				}

				if (stack.count == 0)
				{
					printf("\n\nPARSER ERROR: Invalid expression at line %s: no right parenthesis.\n", line_number->value.data);
					exit(-1);
				}

				vector_remove(&stack, stack.count - 1);
			}
			else
			{
				if (stack.count == 0)
				{
					vector_add(&stack, current_token);
				}
				else
				{
					lexical_token* last_operator_on_stack = stack.data[stack.count - 1];

					int current_token_priority = parser_expression_getpriority(current_token);
					if (current_token_priority == -1)
					{
						printf("\n\nPARSER ERROR: Unrecognised symbol at line %s: %s.\n", line_number->value.data, current_token->value.data);
						exit(-1);
					}

					int last_operator_priority = parser_expression_getpriority(last_operator_on_stack);
					if (last_operator_priority == -1)
					{
						printf("\n\nPARSER ERROR: Unrecognised symbol at line %s: %s.\n", line_number->value.data, last_operator_on_stack->value.data);
						exit(-1);
					}

					while (stack.count > 0 && current_token_priority <= last_operator_priority)
					{
						vector_add(rpn, last_operator_on_stack);
						vector_remove(&stack, stack.count - 1);

						last_operator_on_stack = stack.data[stack.count - 1];
					}

					vector_add(&stack, current_token);
				}
			}
		}

		(*index)++;
		current_token = tokens->data[*index];
	}

	if (stack.count > 0)
	{
		lexical_token* last_operator_on_stack = stack.data[stack.count - 1];
		while (stack.count > 0 && !parser_expression_isparenthesis(last_operator_on_stack))
		{
			vector_add(rpn, last_operator_on_stack);
			vector_remove(&stack, stack.count - 1);

			last_operator_on_stack = stack.data[stack.count - 1];
		}
	}

	if (stack.count > 0)
	{
		printf("\n\nPARSER ERROR: Invalid expression at line %s: redundant parenthesis.\n", line_number->value.data);
		exit(-1);
	}

	for (int i = 0; i < rpn->count; i++) printf("%s ", ((lexical_token*)rpn->data[i])->value.data);

	vector_clear(&stack);
	return rpn;
}

vector* parser_expression_buildrpnnodes(vector* rpn, vector* symbol_table)
{
	vector* rpn_nodes = (vector*)malloc(sizeof(vector));
	vector_init(rpn_nodes);

	for (int i = 0; i < rpn->count; i++)
	{
		lexical_token* current_token = rpn->data[i];

		ast_node* node = (ast_node*)malloc(sizeof(ast_node));
		astnode_init(node, -1, "");

		switch (current_token->token_type)
		{
			case T_NUMBER:
			{
				node->type = N_NUMBER;
				string_append_s(&node->value, current_token->value.data);

				break;
			}

			case T_IDENTIFIER:
			{
				symboltable_add(symbol_table, S_INTEGER, current_token->value.data, "0");

				node->type = N_VARIABLE;
				string_append_s(&node->value, current_token->value.data);

				break;
			}

			case T_OPERATOR:
			{
				if		(parser_expect_operator(current_token, "+"))		node->type = N_ADD;
				else if (parser_expect_operator(current_token, "-"))		node->type = N_SUB;
				else if (parser_expect_operator(current_token, "*"))		node->type = N_MUL;
				else if (parser_expect_operator(current_token, "/"))		node->type = N_DIV;
				else if (parser_expect_operator(current_token, "MOD"))		node->type = N_MOD;
				else if (parser_expect_operator(current_token, "="))		node->type = N_EQUAL;
				else if (parser_expect_operator(current_token, "<>"))		node->type = N_NOTEQUAL;
				else if (parser_expect_operator(current_token, ">"))		node->type = N_GREATERTHAN;
				else if (parser_expect_operator(current_token, ">="))		node->type = N_EQUAL_GREATERTHAN;
				else if (parser_expect_operator(current_token, "<"))		node->type = N_LESSTHAN;
				else if (parser_expect_operator(current_token, "<="))		node->type = N_EQUAL_LESSTHAN;
				else if (parser_expect_operator(current_token, "AND"))		node->type = N_AND;
				else if (parser_expect_operator(current_token, "OR"))		node->type = N_OR;

				break;
			}

			case T_FUNCTION:
			{
				if (strcmp("ABS", current_token->value.data) == 0)			node->type = N_ABS;
				if (strcmp("RND", current_token->value.data) == 0)			node->type = N_RND;
				if (strcmp("TIME", current_token->value.data) == 0)			node->type = N_TIME;

				break;
			}
		}

		vector_add(rpn_nodes, node);
	}

	return rpn_nodes;
}

void parser_expression_buildrpntree(vector* rpn_nodes, ast_node* expression_root, lexical_token* line_number)
{
	vector stack;
	vector_init(&stack);

	for (int i = 0; i < rpn_nodes->count; i++)
	{
		ast_node* current_node = rpn_nodes->data[i];
		if (current_node->type == N_VARIABLE || current_node->type == N_NUMBER)
		{
			vector_add(&stack, current_node);
		}
		else
		{
			int arguments_count = parser_expression_getargumentscount(current_node->type);

			for (int i = 0; i < arguments_count; i++)
			{
				ast_node* argument = stack.data[stack.count - 1];
				vector_add(&current_node->children, argument);
				vector_remove(&stack, stack.count - 1);
			}

			vector_add(&stack, current_node);
		}
	}

	if (stack.count != 1)
	{
		printf("\n\nPARSER ERROR: Invalid expression at line %s: too many numbers or operators.\n", line_number->value.data);
		exit(-1);
	}

	vector_add(&expression_root->children, stack.data[0]);
	vector_clear(&stack);
}

bool parser_expression_istokenvalid(lexical_token* token)
{
	return token->token_type == T_NUMBER || token->token_type == T_IDENTIFIER || 
		   token->token_type == T_OPERATOR || token->token_type == T_FUNCTION ||
		   token->token_type == T_COMMA;
}

bool parser_expression_isparenthesis(lexical_token* token)
{
	return parser_expect_operator(token, "(") || parser_expect_operator(token, ")");
}

int parser_expression_getpriority(lexical_token* token)
{
	if (token->token_type == T_FUNCTION)				return 99;

	if		(parser_expect_operator(token, "*"))		return 80;
	else if (parser_expect_operator(token, "/"))		return 80;
	else if (parser_expect_operator(token, "MOD"))		return 60;
	else if (parser_expect_operator(token, "+"))		return 50;
	else if (parser_expect_operator(token, "-"))		return 50;
	else if (parser_expect_operator(token, "<>"))		return 30;
	else if (parser_expect_operator(token, "<"))		return 30;
	else if (parser_expect_operator(token, "<="))		return 30;
	else if (parser_expect_operator(token, ">"))		return 30;
	else if (parser_expect_operator(token, ">="))		return 30;
	else if (parser_expect_operator(token, "="))		return 30;
	else if (parser_expect_operator(token, "AND"))		return 20;
	else if (parser_expect_operator(token, "OR"))		return 15;
	else if (parser_expect_operator(token, "("))		return 10;
	else if (parser_expect_operator(token, ")"))		return 10;

	return -1;
}

int parser_expression_getargumentscount(ast_node_type node_type)
{
	switch (node_type)
	{
		case N_ABS:		return 1;
		case N_RND:		return 1;
		case N_TIME:	return 0;
		default:		return 2;
	}
}