/**
* @file parser-utils.h
* @brief A set of helpers for statement parsers.
*/

#pragma once
#include "lexical-token.h"
#include "parser-expression.h"

/**
* @brief Check if the token is an operator and have the specified type.
* @param token The token to check.
* @param op The operator.
* @return True if the passed token is an operator specified in the op, otherwise false.
*/
bool parser_expect_operator(lexical_token* token, const char* op);

/**
* @brief Check if the token has a special type (comma, semicolon, etc.).
* @param token The token to check.
* @param special_type The token type which we are expecting.
* @return True if the passed token has the specified special type, otherwise false.
*/
bool parser_expect_special(lexical_token* token, lexical_token_type special_type);

/**
* @brief Check if the token is a keyword.
* @param token The token to check.
* @param keyword The keyword name.
* @return True if the passed token is an keyword with the specified name, otherwise false.
*/
bool parser_expect_keyword(lexical_token* token, const char* keyword);

/**
* @brief Check if the token is a part of expression.
* @param token The token to check.
* @return True if the passed token is a part of expression, otherwise false.
*/
bool parser_expect_expression(lexical_token* token);

/**
* @brief Check if the token is an identifier.
* @param token The token to check.
* @return True if the passed token is an identifier, otherwise false.
*/
bool parser_expect_identifier(lexical_token* token);

/**
* @brief Check if the token is a number.
* @param token The token to check.
* @return True if the passed token is a number, otherwise false.
*/
bool parser_expect_number(lexical_token* token);

/**
* @brief Check if the token is a string.
* @param token The token to check.
* @return True if the passed token is a string, otherwise false.
*/
bool parser_expect_string(lexical_token* token);

/**
* @brief Check if the token is an end of instruction.
* @param token The token to check.
* @return True if the passed token is an end of instruction, otherwise false.
*/
bool parser_expect_endofinstruction(lexical_token* token);