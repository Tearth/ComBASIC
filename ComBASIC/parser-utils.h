#pragma once
#include "lexical-token.h"
#include "parser-expression.h"

bool parser_expect_operator(lexical_token* token, const char* op);
bool parser_expect_special(lexical_token* token, lexical_token_type special_type);
bool parser_expect_keyword(lexical_token* token, const char* keyword);
bool parser_expect_expression(lexical_token* token);
bool parser_expect_identifier(lexical_token* token);
bool parser_expect_number(lexical_token* token);
bool parser_expect_string(lexical_token* token);
bool parser_expect_endofinstruction(lexical_token* token);