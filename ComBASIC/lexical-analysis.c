#include "lexical-analysis.h"

const char* keywords[MAX_KEYWORDS_TOKENS_COUNT] = { "CLS", "LET", "PRINT", "REM" };
const char* operators[MAX_KEYWORDS_TOKENS_COUNT] = { "=", "+", "-", "*", "/", "(", ")", "%" };

vector* lexical_gettokens(const char* source)
{
	vector* tokens_vector = (vector*)malloc(sizeof(vector));
	vector_init(tokens_vector);

	while (*source != 0)
	{
		lexical_token* token = NULL;
		int length = 0;

		if (isalpha(*source))
		{
			token = lexical_readword(source, &length);
		}
		else if (isdigit(*source))
		{
			token = lexical_readnumber(source, &length);
		}
		else if (*source != ' ')
		{
			token = lexical_readoperator(source, &length);
		}
		else
		{
			source++;
		}

		if (token)
		{
			vector_add(tokens_vector, token);
			source += length;
		}
	}

	lexical_checklasttoken(tokens_vector);
	lexical_mergeoperators(tokens_vector);
	lexical_fixunaryoperators(tokens_vector);

	return tokens_vector;
}

lexical_token* lexical_readword(const char* source, int* length)
{
	bool firstLetter = true;

	lexical_token* read_token = (lexical_token*)malloc(sizeof(lexical_token));
	lexicaltoken_init(read_token, T_IDENTIFIER, "");

	while (isalpha(*source) != 0 || (!firstLetter && isdigit(*source)) != 0)
	{
		string_append_c(&read_token->value, *source);

		firstLetter = false;
		(*length)++;
		source++;
	}

	for (int i = 0; i < MAX_KEYWORDS_TOKENS_COUNT; i++)
	{
		if (keywords[i] && strcmp(read_token->value.data, keywords[i]) == 0)
		{
			read_token->token_type = T_KEYWORD;
			break;
		}
	}

	return read_token;
}

lexical_token* lexical_readnumber(const char* source, int* length)
{
	lexical_token* read_token = (lexical_token*)malloc(sizeof(lexical_token));
	lexicaltoken_init(read_token, T_NUMBER, "");

	while (isdigit(*source) != 0)
	{
		string_append_c(&read_token->value, *source);
		(*length)++;
		source++;
	}

	return read_token;
}

lexical_token* lexical_readoperator(const char* source, int* length)
{
	lexical_token* read_token = (lexical_token*)malloc(sizeof(lexical_token));
	lexicaltoken_init(read_token, T_OPERATOR, "");
	string_append_c(&read_token->value, *source);

	(*length) = 1;
	source++;

	if (strcmp(read_token->value.data, "\n") == 0)
	{
		read_token->token_type = T_END_OF_INSTRUCTION;
	}
	else if (strcmp(read_token->value.data, ";") == 0)
	{
		read_token->token_type = T_NO_NEWLINE;
	}
	else if(strcmp(read_token->value.data, "\"") == 0)
	{
		string_removelast(&read_token->value);

		while (*source != '"')
		{
			string_append_c(&read_token->value, *source);
			(*length)++;
			source++;
		}

		(*length)++;
		read_token->token_type = T_STRING;
	}
	else
	{
		if (!lexical_operatorexists(read_token->value.data))
		{
			printf("ERROR: unknown operator %s\n", read_token->value.data);
			exit(-1);
		}
	}

	return read_token;
}

void lexical_checklasttoken(vector* tokens_vector)
{
	lexical_token* last_token = tokens_vector->data[tokens_vector->count - 1];
	if (last_token->token_type != T_END_OF_INSTRUCTION)
	{
		lexical_token* end_of_instruction_token = (lexical_token*)malloc(sizeof(lexical_token));
		lexicaltoken_init(end_of_instruction_token, T_END_OF_INSTRUCTION, "\n");

		vector_add(tokens_vector, end_of_instruction_token);
	}
}

bool lexical_operatorexists(const char* operator)
{
	for (int op = 0; op < MAX_KEYWORDS_TOKENS_COUNT; op++)
	{
		if (operators[op] && strcmp(operator, operators[op]) == 0)
		{
			return true;
		}
	}

	return false;
}

void lexical_mergeoperators(vector* tokens_vector)
{
	for (int i = 0; i < tokens_vector->count - 1; i++)
	{
		lexical_token* first = tokens_vector->data[i];
		lexical_token* second = tokens_vector->data[i + 1];

		if (first->token_type == T_OPERATOR && second->token_type == T_OPERATOR)
		{
			string merged_operator;
			string_init(&merged_operator);

			string_append_s(&merged_operator, first->value.data);
			string_append_s(&merged_operator, second->value.data);

			if (lexical_operatorexists(merged_operator.data))
			{
				string_clean(&first->value);
				string_clean(&second->value);

				string_append_s(&first->value, merged_operator.data);

				vector_remove(tokens_vector, i + 1);
				free(second);
			}

			string_clean(&merged_operator);
		}
	}
}

void lexical_fixunaryoperators(vector* tokens_vector)
{
	for (int i = 1; i < tokens_vector->count - 1; i++)
	{
		lexical_token* current_token = tokens_vector->data[i];
		if (current_token->token_type == T_OPERATOR && strcmp("-", current_token->value.data) == 0)
		{
			lexical_token* left_token = tokens_vector->data[i - 1];
			lexical_token* right_token = tokens_vector->data[i + 1];

			if (left_token->token_type == T_OPERATOR && strcmp(")", left_token->value.data) != 0)
			{
				lexical_token* left_parenthesis_token = (lexical_token*)malloc(sizeof(lexical_token));
				lexicaltoken_init(left_parenthesis_token, T_OPERATOR, "(");

				lexical_token* zero_token = (lexical_token*)malloc(sizeof(lexical_token));
				lexicaltoken_init(zero_token, T_NUMBER, "0");

				lexical_token* right_parenthesis_token = (lexical_token*)malloc(sizeof(lexical_token));
				lexicaltoken_init(right_parenthesis_token, T_OPERATOR, ")");

				vector_insert(tokens_vector, left_parenthesis_token, i++);
				vector_insert(tokens_vector, zero_token, i++);

				if (right_token->token_type == T_NUMBER)
				{
					vector_insert(tokens_vector, right_parenthesis_token, i + 2);
				}
				else if (right_token->token_type == T_OPERATOR && strcmp("(", right_token->value.data) == 0)
				{
					int parenthesis_balance = 1;
					int current_search_index = i + 2;

					while (parenthesis_balance > 0)
					{
						lexical_token* current_search_token = tokens_vector->data[current_search_index];
						if (current_search_token->token_type == T_END_OF_INSTRUCTION)
						{
							printf("ERROR: invalid parenthesis");
							exit(-1);
						}

						if (current_search_token->token_type == T_OPERATOR)
						{
							if (strcmp("(", current_search_token->value.data) == 0) parenthesis_balance++;
							if (strcmp(")", current_search_token->value.data) == 0) parenthesis_balance--;
						}

						current_search_index++;
					}

					vector_insert(tokens_vector, right_parenthesis_token, current_search_index);
				}
			}
		}
	}
}

void lexical_dump(vector* tokens)
{
	printf("List of generated tokens:\n");
	for (int i = 0; i < tokens->count; i++)
	{
		lexical_token* r = tokens->data[i];

		if (r->token_type == T_END_OF_INSTRUCTION)
		{
			printf("[%d END_OF_INSTRUCTION]\n", (int)r->token_type);
		}
		else
		{
			printf("[%d %s] ", (int)r->token_type, r->value.data);
		}
	}
	printf("End of tokens list\n");
}

void lexical_clean(vector* tokens)
{
	while (tokens->count > 0)
	{
		lexical_token* token = tokens->data[0];
		lexicaltoken_clean(token);

		free(token);
		vector_remove(tokens, 0);
	}

	vector_clean(tokens);
}