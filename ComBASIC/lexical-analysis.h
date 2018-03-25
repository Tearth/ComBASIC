#pragma once
#define MAX_KEYWORDS_TOKENS_COUNT 64

#include <ctype.h>
#include <string.h>
#include "vector.h"
#include "string.h"

typedef enum token_type
{
	KEYWORD,
	IDENTIFIER,
	NUMBER,
	STRING,
	OPERATOR,
	END_OF_INSTRUCTION
} token_type;

typedef struct token
{
	token_type token_type;
	string value;
} token;

vector* lexical_gettokens(const char* source);
token* lexical_readword(const char* source, int* length);
token* lexical_readnumber(const char* source, int* length);
token* lexical_readoperator(const char* source, int* length);

void lexical_checklasttoken(vector* tokens_vector);
void lexical_mergeoperators(vector* tokens_vector);