#include "lexical-analysis.h"

const char* keywords[MAX_KEYWORDS_TOKENS_COUNT] = { "CLS", "LET", "PRINT", "REM" };
const char* operators[MAX_KEYWORDS_TOKENS_COUNT] = { "=", "+", "-", "*", "/", ">=", "<=" };

vector* lexical_gettokens(const char* source)
{
	vector* tokens_vector = (vector*)malloc(sizeof(vector));
	vector_init(tokens_vector);

	while (*source != '\0')
	{
		token* token = NULL;
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

		if (token != NULL)
		{
			vector_add(tokens_vector, token);
			source += length;
		}
	}

	lexical_checklasttoken(tokens_vector);
	lexical_mergeoperators(tokens_vector);

	return tokens_vector;
}

token* lexical_readword(const char* source, int* length)
{
	bool firstLetter = true;

	token* read_token = (token*)malloc(sizeof(token));
	read_token->token_type = T_IDENTIFIER;
	string_init(&read_token->value);

	while (isalpha(*source) != 0 || (!firstLetter && isdigit(*source)) != 0)
	{
		string_append_c(&read_token->value, *source);

		firstLetter = false;
		(*length)++;
		source++;
	}

	for (int i = 0; i < MAX_KEYWORDS_TOKENS_COUNT; i++)
	{
		if (keywords[i] != NULL && strcmp(string_get(&read_token->value), keywords[i]) == 0)
		{
			read_token->token_type = T_KEYWORD;
			break;
		}
	}

	return read_token;
}

token* lexical_readnumber(const char* source, int* length)
{
	token* read_token = (token*)malloc(sizeof(token));
	read_token->token_type = T_NUMBER;
	string_init(&read_token->value);

	while (isdigit(*source) != 0)
	{
		string_append_c(&read_token->value, *source);
		(*length)++;
		source++;
	}

	return read_token;
}

token* lexical_readoperator(const char* source, int* length)
{
	token* read_token = (token*)malloc(sizeof(token));
	read_token->token_type = T_OPERATOR;
	string_init(&read_token->value);

	string_append_c(&read_token->value, *source);
	(*length) = 1;
	source++;

	if (strcmp(string_get(&read_token->value), "\n") == 0)
	{
		read_token->token_type = T_END_OF_INSTRUCTION;
	}
	else if(strcmp(string_get(&read_token->value), "\"") == 0)
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

	return read_token;
}

void lexical_checklasttoken(vector* tokens_vector)
{
	token* last_token = vector_get(tokens_vector, vector_count(tokens_vector) - 1);
	if (last_token->token_type != T_END_OF_INSTRUCTION)
	{
		token* end_of_instruction_token = (token*)malloc(sizeof(token));
		string_init(&end_of_instruction_token->value);

		end_of_instruction_token->token_type = T_END_OF_INSTRUCTION;
		string_append_c(&end_of_instruction_token->value, '\n');

		vector_add(tokens_vector, end_of_instruction_token);
	}
}

void lexical_mergeoperators(vector* tokens_vector)
{
	for (int i = 0; i < vector_count(tokens_vector) - 1; i++)
	{
		token* first = vector_get(tokens_vector, i);
		token* second = vector_get(tokens_vector, i + 1);

		if (first->token_type == T_OPERATOR && second->token_type == T_OPERATOR)
		{
			string* merged_operator = (string*)malloc(sizeof(string));
			string_init(merged_operator);

			string_append_s(merged_operator, string_get(&first->value));
			string_append_s(merged_operator, string_get(&second->value));

			for (int op = 0; op < MAX_KEYWORDS_TOKENS_COUNT; op++)
			{
				if (operators[op] != NULL && strcmp(string_get(merged_operator), operators[op]) == 0)
				{
					string_free(&first->value);
					string_free(&second->value);

					first->value = *merged_operator;
					vector_remove(tokens_vector, i + 1);

					break;
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
		token* r = tokens->data[i];

		if (r->token_type == T_END_OF_INSTRUCTION)
		{
			printf("[%d END]\n", (int)r->token_type);
		}
		else
		{
			printf("[%d %s] ", (int)r->token_type, string_get(&r->value));
		}
	}
	printf("End of tokens list\n");
}