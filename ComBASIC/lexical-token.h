#pragma once
#include "string.h"

typedef enum lexical_token_type
{
	T_KEYWORD,
	T_FUNCTION,
	T_IDENTIFIER,
	T_NUMBER,
	T_STRING,
	T_SEMICOLON,
	T_OPERATOR,
	T_COMMA,
	T_END_OF_INSTRUCTION
} lexical_token_type;

typedef struct lexical_token
{
	lexical_token_type token_type;
	string value;
} lexical_token;

void lexicaltoken_init(lexical_token* token, lexical_token_type type, const char* value);
void lexicaltoken_clear(lexical_token* token);