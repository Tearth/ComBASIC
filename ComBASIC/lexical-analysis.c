#include "lexical-analysis.h"

vector* lexical_gettokens(const char* source)
{
	vector* tokens_vector = (vector*)malloc(sizeof(vector));
	vector_init(tokens_vector);

	while (*source != '\0')
	{
		string* token = NULL;
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

string* lexical_readidentifier(const char* source, int* length)
{
	bool firstLetter = true;

	string* token = (string*)malloc(sizeof(string));
	string_init(token);

	while (isalpha(*source) != 0 || (!firstLetter && isdigit(*source)) != 0)
	{
		string_append_c(token, *source);

		firstLetter = false;
		(*length)++;
		source++;
	}

	return token;
}

string* lexical_readnumber(const char* source, int* length)
{
	string* token = (string*)malloc(sizeof(string));
	string_init(token);

	while (isdigit(*source) != 0)
	{
		string_append_c(token, *source);
		(*length)++;
		source++;
	}

	return token;
}

string* lexical_readoperator(const char* source, int* length)
{
	string* token = (string*)malloc(sizeof(string));
	string_init(token);

	string_append_c(token, *source);
	(*length) = 1;
	source++;

	return token;
}