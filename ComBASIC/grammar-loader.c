#include "grammar-loader.h"

vector* grammar_load(const char* filename)
{
	const char* grammar = file_load(filename);
	const char* grammar_ptr = grammar;

	vector* grammar_tokens = (vector*)malloc(sizeof(vector));
	vector_init(grammar_tokens);

	while (*grammar_ptr != 0)
	{
		if (*grammar_ptr == '[')
		{
			grammar_token* token = grammar_readtoken(grammar_ptr);
			vector_add(grammar_tokens, token);
		}

		grammar_ptr++;
	}

	free((char*)grammar);

	return grammar_tokens;
}

void grammar_inittoken(grammar_token *token)
{
	token->grammar_token_type = 0;
	string_init(&token->value);
}

grammar_token* grammar_readtoken(const char* grammar)
{
	string token;
	string_init(&token);

	grammar++;

	while (*grammar != ']' && *grammar != ' ')
	{
		string_append_c(&token, *grammar);
		grammar++;
	}

	grammar_token* read_token = (grammar_token*)malloc(sizeof(grammar_token));
	grammar_inittoken(read_token);
	
	if (strcmp(token.data, "KEYWORD") == 0)
	{
		grammar_readargument(grammar, &read_token->value);
		read_token->grammar_token_type = GT_KEYWORD;
	}
	else if (strcmp(token.data, "OPERATOR") == 0)
	{
		grammar_readargument(grammar, &read_token->value);
		read_token->grammar_token_type = GT_OPERATOR;
	}
	else if (strcmp(token.data, "*") == 0)
	{
		read_token->grammar_token_type = GT_ANY;
	}
	else if (strcmp(token.data, "END_OF_INSTRUCTION") == 0)
	{
		read_token->grammar_token_type = GT_END_OF_INSTRUCTION;
	}
	else if (strcmp(token.data, "IDENTIFIER") == 0)
	{
		read_token->grammar_token_type = GT_IDENTIFIER;
	}
	else if (strcmp(token.data, "STRING") == 0)
	{
		read_token->grammar_token_type = GT_STRING;
	}
	else if (strcmp(token.data, "EXPRESSION") == 0)
	{
		read_token->grammar_token_type = GT_EXPRESSION;
	}
	else if (strcmp(token.data, "LINE_NUMBER") == 0)
	{
		read_token->grammar_token_type = GT_LINE_NUMBER;
	}

	string_clean(&token);
	return read_token;
}

void grammar_readargument(const char* grammar, string* str)
{
	grammar++;
	while (*grammar != ']')
	{
		string_append_c(str, *grammar);
		grammar++;
	}
}

void grammar_dump(vector* grammar_tokens)
{
	printf("List of loaded grammar tokens:\n");
	for (int i = 0; i < grammar_tokens->count; i++)
	{
		grammar_token* r = grammar_tokens->data[i];

		if (r->grammar_token_type == GT_END_OF_INSTRUCTION)
		{
			printf("[%d END_OF_INSTRUCTION]\n", (int)r->grammar_token_type);
		}
		else
		{
			if (r->value.count > 0)
			{
				printf("[%d %s] ", (int)r->grammar_token_type, r->value.data);
			}
			else
			{
				printf("[%d] ", (int)r->grammar_token_type);
			}
		}
	}
	printf("End of grammar tokens list\n");
}

void grammar_clean(vector* grammar_tokens)
{
	while(grammar_tokens->count > 0)
	{
		grammar_token* token = grammar_tokens->data[0];

		string_clean(&token->value);
		free(token);

		vector_remove(grammar_tokens, 0);
	}

	vector_clean(grammar_tokens);
}