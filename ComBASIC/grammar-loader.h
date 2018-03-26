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
grammar_token* grammar_readtoken(const char* grammar);
string* grammar_readargument(const char* grammar);