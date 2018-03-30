#pragma once
#define MAX_KEYWORDS_TOKENS_COUNT 64

#include <ctype.h>
#include <string.h>
#include "vector.h"
#include "string.h"

typedef enum token_type
{
	T_KEYWORD,
	T_IDENTIFIER,
	T_NUMBER,
	T_STRING,
	T_NO_NEWLINE,
	T_OPERATOR,
	T_END_OF_INSTRUCTION
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
void lexical_dump(vector* tokens);
void lexical_clean(vector* tokens);