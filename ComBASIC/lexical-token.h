#pragma once
#include "string.h"

typedef enum lexical_token_type
{
	T_KEYWORD,
	T_IDENTIFIER,
	T_NUMBER,
	T_STRING,
	T_NO_NEWLINE,
	T_OPERATOR,
	T_END_OF_INSTRUCTION
} lexical_token_type;

typedef struct lexical_token
{
	lexical_token_type token_type;
	string value;
} lexical_token;