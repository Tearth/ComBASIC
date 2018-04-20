/**
* @file lexical-token.h
* @brief Represents an single lexical token and functions to manage it.
*/

#pragma once
#include "string.h"

/**
* @brief The list of lexical token types.
*/
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

/**
* @brief The structure which contains data about lexical token like type or value.
*/
typedef struct lexical_token
{
	/**
	* @brief The lexical token type.
	*/
	lexical_token_type token_type;

	/**
	* @brief The lexical token value.
	*/
	string value;
} lexical_token;

/**
* @brief Inits the lexical token based on the passed parameters. 
* @param token The lexical token to init.
* @param type Lexical token type.
* @param value Lexical token value.
*/
void lexicaltoken_init(lexical_token* token, lexical_token_type type, const char* value);

/**
* @brief Clears the lexical token.
* @param token Lexical token to clear.
*/
void lexicaltoken_clear(lexical_token* token);