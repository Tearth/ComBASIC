#include "lexical-analysis.h"

const char* keywords[MAX_KEYWORDS_TOKENS_COUNT] = { "CLS", "LET", "PRINT", "REM" };
const char* operators[MAX_KEYWORDS_TOKENS_COUNT] = { "=", "+", "-", "*", "/", ">=", "<=" };

vector* lexical_gettokens(const char* source)
{
	vector* tokens_vector = (vector*)malloc(sizeof(vector));
	vector_init(tokens_vector);

	while (*source != 0)
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

		if (token)
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
		if (keywords[i] && strcmp(read_token->value.data, keywords[i]) == 0)
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

	return read_token;
}

void lexical_checklasttoken(vector* tokens_vector)
{
	token* last_token = tokens_vector->data[tokens_vector->count - 1];
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
	for (int i = 0; i < tokens_vector->count - 1; i++)
	{
		token* first = tokens_vector->data[i];
		token* second = tokens_vector->data[i + 1];

		if (first->token_type == T_OPERATOR && second->token_type == T_OPERATOR)
		{
			string* merged_operator = (string*)malloc(sizeof(string));
			string_init(merged_operator);

			string_append_s(merged_operator, first->value.data);
			string_append_s(merged_operator, second->value.data);

			for (int op = 0; op < MAX_KEYWORDS_TOKENS_COUNT; op++)
			{
				if (operators[op] && strcmp(merged_operator->data, operators[op]) == 0)
				{
					string_clean(&first->value);
					string_clean(&second->value);

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
		token* token = tokens->data[0];

		string_clean(&token->value);
		free(token);

		vector_remove(tokens, 0);
	}

	vector_clean(tokens);
}