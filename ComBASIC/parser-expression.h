/**
* @file parser-expression.h
* @brief Expression parser based on Reverse Polish Notation (RPN).
*
* Each expression in ComBASIC is evaluated on rules based on RPN and the following algorithm:\n
*  - if the next token is a number of function identifier, move it to the output\n
*  - if the next token is an operator:\n
*      - if stack is empty or last token on it has less priority, move it here\n
*      - if stack is not empty and the last token has greater priority, then pop all operators until the stack is
*		 not empty or the operator priority is greater than current token\n
*  - if the next token is a left parenthesis, move it to the stack\n
*  - if the next token is a right parenthesis or comma, pop all operators from stack until the left parenthesis. Note that
*		comma don't pops the left parenthesis.\n
*
*
* Following this algorithm, the expression 1 + (2 + 3) * sin(10) will be translated to the following AST:\n
* @code
* [root]
*   -> [+]
*       -> [*]
*           -> [+]
*               -> [2]
*               -> [3]
*           -> [sin]
*               -> 10
*       -> [1]
* @endcode
*/

#pragma once
#include "ast-node.h"
#include "lexical-analysis.h"
#include "symbol-table.h"
#include "symbol-node.h"
#include "parser-utils.h"

/**
* @brief Builds an AST (Abstract Syntax Tree) for the expression.
* @param tokens The vector of tokens to parse.
* @param index Current token index.
* @param line_number Current line number to display in error messages.
* @param symbol_table Symbol table.
* @return The pointer to the ast root node of the parsed expression.
*/
ast_node* parser_expression_build(vector* tokens, int* index, lexical_token* line_number, vector* symbol_table);

/**
* @brief Converts an vector of tokens to the RPN output vector.
* @param tokens The vector of tokens to parse.
* @param index Current token index.
* @param line_number Current line number to display in error messages.
* @param symbol_table Symbol table.
* @return The vector with valid RPN expression.
*/
vector* parser_expression_buildrpn(vector* tokens, int* index, lexical_token* line_number, vector* symbol_table);

/**
* @brief Converts an output RPN vector to the vector of AST nodes (but still not tree).
* @param rpn The output RPN vector.
* @param symbol_table Symbol table.
* @return The vector of RPN expression nodes.
*/
vector* parser_expression_buildrpnnodes(vector* rpn, vector* symbol_table);

/**
* @brief Converts an vector of RPN nodes to the tree.
* @param rpn_nodes The vector of RPN nodes.
* @param expression_root The expression root node.
* @param line_number Current line number to display in error messages.
*/
void parser_expression_buildrpntree(vector* rpn_nodes, ast_node* expression_root, lexical_token* line_number);

/**
* @brief Checks if the specified token is a part of the expression.
* @param token The token to check.
* @return True if the specified token is a part of an expression, otherwise false.
*/
bool parser_expression_istokenvalid(lexical_token* token);

/**
* @brief Checks if the specified token is a parenthesis.
* @param token The token to check.
* @return True if the specified token is a parenthesis, otherwise false.
*/
bool parser_expression_isparenthesis(lexical_token* token);

/**
* @brief Returns the priority of the specified operator (greater number = more important).
* @param token The token to check.
* @return The operator priority.
*/
int parser_expression_getpriority(lexical_token* token);

/**
* @brief Returns the arguments count of the specified operator.
* @param node_type The token to check.
* @return The operator arguemnts count.
*/
int parser_expression_getargumentscount(ast_node_type node_type);