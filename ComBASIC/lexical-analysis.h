#pragma once
#define MAX_KEYWORDS_TOKENS_COUNT 64

#include <ctype.h>
#include "vector.h"
#include "string.h"

typedef enum token_type
{
	IDENTIFIER,
	NUMBER,
	OPERATOR
} token_type;

typedef struct token
{
	token_type token_type;
	string value;
} token;

vector* lexical_gettokens(const char* source);
token* lexical_readidentifier(const char* source, int* length);
token* lexical_readnumber(const char* source, int* length);
token* lexical_readoperator(const char* source, int* length);