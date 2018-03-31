#include "parser-expression.h"

ast_node* parser_expression_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table)
{
	ast_node* expression_node = (ast_node*)malloc(sizeof(ast_node));
	astnode_init(expression_node);
	expression_node->type = N_EXPRESSION;

	vector* rpn = parser_expression_buildrpn(tokens, keyword, index, symbol_table);

	return expression_node;
}

vector* parser_expression_buildrpn(vector* tokens, ast_node* keyword, int* index, vector* symbol_table)
{
	vector* rpn = (vector*)malloc(sizeof(vector));
	vector_init(rpn);

	vector* stack = (vector*)malloc(sizeof(vector));
	vector_init(stack);

	token* current_token = tokens->data[*index];
	while (parser_expression_istokenvalid(current_token))
	{
		if (current_token->token_type == T_NUMBER || current_token->token_type == T_IDENTIFIER)
		{
			vector_add(rpn, current_token);
		}
		else
		{
			if (strcmp("(", current_token->value.data) == 0) vector_add(stack, current_token);
			else if (strcmp(")", current_token->value.data) == 0)
			{
				token* last_operator_on_stack = stack->data[stack->count - 1];
				while (stack->count > 0 && strcmp("(", last_operator_on_stack->value.data) != 0)
				{
					vector_add(rpn, last_operator_on_stack);
					vector_remove(stack, stack->count - 1);

					last_operator_on_stack = stack->data[stack->count - 1];
				}

				if (stack->count == 0)
				{
					printf("ERROR: Invalid expression (right parenthesis).\n");
					exit(-1);
				}

				vector_remove(stack, stack->count - 1);
			}
			else
			{
				if (stack->count == 0) vector_add(stack, current_token);
				else
				{
					token* last_operator_on_stack = stack->data[stack->count - 1];
					int current_token_priority = parser_expression_getpriority(current_token);

					while (current_token_priority <= parser_expression_getpriority(last_operator_on_stack))
					{
						vector_add(rpn, last_operator_on_stack);
						vector_remove(stack, stack->count - 1);

						last_operator_on_stack = stack->data[stack->count - 1];
					}

					vector_add(stack, current_token);
				}
			}
		}

		(*index)++;
		current_token = tokens->data[*index];
	}

	token* last_operator_on_stack = stack->data[stack->count - 1];
	while (stack->count > 0 && !parser_expression_isparenthesis(last_operator_on_stack))
	{
		vector_add(rpn, last_operator_on_stack);
		vector_remove(stack, stack->count - 1);

		last_operator_on_stack = stack->data[stack->count - 1];
	}

	if (stack->count > 0)
	{
		printf("ERROR: Invalid expression (redundant parenthesis).\n");
		exit(-1);
	}

	vector_clean(stack);
	free(stack);

	printf("\n");
	for (int i = 0; i < rpn->count; i++)
	{
		printf("%s ", ((token*)rpn->data[i])->value);
	}
	printf("\n");
	printf("\n");

	return rpn;
}

bool parser_expression_istokenvalid(token* token)
{
	return token->token_type == T_NUMBER || token->token_type == T_IDENTIFIER || token->token_type == T_OPERATOR;
}

bool parser_expression_isparenthesis(token* token)
{
	return strcmp("(", token->value.data) == 0 || strcmp(")", token->value.data) == 0;
}

int parser_expression_getpriority(token* token)
{
	if (strcmp("(", token->value.data) == 0)	return 0;
	if (strcmp(")", token->value.data) == 0)	return 0;
	if (strcmp("+", token->value.data) == 0)	return 1;
	if (strcmp("-", token->value.data) == 0)	return 1;
	if (strcmp("*", token->value.data) == 0)	return 2;
	if (strcmp("/", token->value.data) == 0)	return 2;

	printf("ERROR: Unrecognised symbol: %s", token->value.data);
	exit(-1);
}