#pragma once
#include <string.h>
#include "file-loader.h"
#include "vector.h"
#include "string.h"

typedef enum grammar_token_type
{
	GT_LINE_NUMBER,
	GT_KEYWORD,
	GT_IDENTIFIER,
	GT_EXPRESSION,
	GT_STRING,
	GT_OPERATOR,
	GT_ANY,
	GT_END_OF_INSTRUCTION
} grammar_token_type;

typedef struct grammar_token
{
	grammar_token_type grammar_token_type;
	string value;
} grammar_token;

vector* grammar_load(const char* filename);
void grammar_inittoken(grammar_token *token);
grammar_token* grammar_readtoken(const char* grammar);
void grammar_readargument(const char* grammar, string* str);

void grammar_dump(vector* grammar_tokens);
void grammar_free(vector* grammar_tokens);