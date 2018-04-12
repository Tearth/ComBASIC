#include "lexical-token.h"

void lexicaltoken_init(lexical_token* token, lexical_token_type type, const char* value)
{
	string_init(&token->value);

	token->token_type = type;
	string_append_s(&token->value, value);
}

void lexicaltoken_clear(lexical_token* token)
{
	string_clear(&token->value);
}