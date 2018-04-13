#include "parser-utils.h"

bool parser_expect_operator(lexical_token* token, const char* op)
{
	return token->token_type == T_OPERATOR && strcmp(op, token->value.data) == 0;
}

bool parser_expect_special(lexical_token* token, lexical_token_type special_type)
{
	return token->token_type == special_type;
}

bool parser_expect_keyword(lexical_token* token, const char* keyword)
{
	return token->token_type == T_KEYWORD && strcmp(keyword, token->value.data) == 0;
}

bool parser_expect_expression(lexical_token* token)
{
	return parser_expression_istokenvalid(token);
}

bool parser_expect_identifier(lexical_token* token)
{
	return token->token_type == T_IDENTIFIER;
}

bool parser_expect_number(lexical_token* token)
{
	return token->token_type == T_NUMBER;
}

bool parser_expect_string(lexical_token* token)
{
	return token->token_type == T_STRING;
}

bool parser_expect_endofinstruction(lexical_token* token)
{
	return token->token_type == T_END_OF_INSTRUCTION;
}