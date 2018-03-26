#include "grammar-loader.h"

vector* grammar_load(const char* filename)
{
	const char* grammar = file_load(filename);

	vector* grammar_tokens;
	vector_init(&grammar_tokens);

	while (*grammar != '\0')
	{
		if (*grammar == '[')
		{
			grammar_token* token = grammar_readtoken(grammar);
			vector_add(&grammar_tokens, token);
		}

		grammar++;
	}

	return 0;
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
	if (strcmp(string_get(&token), "KEYWORD") == 0)
	{
		read_token->value = *grammar_readargument(grammar);
		read_token->grammar_token_type = GT_KEYWORD;
	}
	else if (strcmp(string_get(&token), "OPERATOR") == 0)
	{
		read_token->value = *grammar_readargument(grammar);
		read_token->grammar_token_type = GT_OPERATOR;
	}
	else if (strcmp(string_get(&token), "*") == 0)
	{
		read_token->grammar_token_type = GT_ANY;
	}
	else if (strcmp(string_get(&token), "END_OF_INSTRUCTION") == 0)
	{
		read_token->grammar_token_type = GT_END_OF_INSTRUCTION;
	}
	else if (strcmp(string_get(&token), "IDENTIFIER") == 0)
	{
		read_token->grammar_token_type = GT_IDENTIFIER;
	}
	else if (strcmp(string_get(&token), "STRING") == 0)
	{
		read_token->grammar_token_type = GT_STRING;
	}
	else if (strcmp(string_get(&token), "EXPRESSION") == 0)
	{
		read_token->grammar_token_type = GT_EXPRESSION;
	}
	else if (strcmp(string_get(&token), "LINE_NUMBER") == 0)
	{
		read_token->grammar_token_type = GT_LINE_NUMBER;
	}

	return read_token;
}

string* grammar_readargument(const char* grammar)
{
	string* argument = (string*)malloc(sizeof(string));
	string_init(argument);

	grammar++;
	while (*grammar != ']')
	{
		string_append_c(argument, *grammar);
		grammar++;
	}

	return argument;
}