#include "lexical-analysis.h"

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
			token = lexical_readidentifier(source, &length);
		}
		else if (isdigit(*source))
		{
			token = lexical_readnumber(source, &length);
		}
		else if(*source != ' ')
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

	return tokens_vector;
}

token* lexical_readidentifier(const char* source, int* length)
{
	bool firstLetter = true;

	token* read_token = (token*)malloc(sizeof(token));
	read_token->token_type = IDENTIFIER;
	string_init(&read_token->value);

	while (isalpha(*source) != 0 || (!firstLetter && isdigit(*source)) != 0)
	{
		string_append_c(&read_token->value, *source);

		firstLetter = false;
		(*length)++;
		source++;
	}

	return read_token;
}

token* lexical_readnumber(const char* source, int* length)
{
	token* read_token = (token*)malloc(sizeof(token));
	read_token->token_type = NUMBER;
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
	read_token->token_type = OPERATOR;
	string_init(&read_token->value);

	string_append_c(&read_token->value, *source);
	(*length) = 1;
	source++;

	return read_token;
}