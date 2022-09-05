/**
 * @file polymorphic_operations.h
 * @brief Ficheiro para controlar operações com o mesmo operador
 * @brief Executa a operação pretendida conforme os tipos presentes na stack
 */
#pragma once

#include "stack.h"

/**
 * @brief Executa a operação que tem simbolo '*' associado ao tipo correspondente
 * @param stack target
 * @param variables
 */
void asterisk_operation(Stack *stack, StackElement *variables);

/**
 * @brief Executa a operação que tem simbolo '~' associado ao tipo correspondente
 * @param stack target
 * @param variables
 */
void tilde_operation(Stack *stack, StackElement *variables);

/**
 * @brief Executa a operação que tem simbolo '<' associado ao tipo correspondente
 * @param stack target
 */
void lesser_than_symbol_operation(Stack *stack);

/**
 * @brief Executa a operação que tem simbolo '>' associado ao tipo correspondente
 * @param stack target
 */
void bigger_than_symbol_operation(Stack *stack);

/**
 * @brief Executa a operação que tem simbolo '(' associado ao tipo correspondente
 * @param stack target
 */
void open_parentheses_operation(Stack *stack);

/**
 * @brief Executa a operação que tem simbolo ')' associado ao tipo correspondente
 * @param stack target
 */
void close_parentheses_operation(Stack *stack);

/**
 * @brief Executa a operação que tem simbolo '=' associado ao tipo correspondente
 * @param stack target
 */
void equal_symbol_operation(Stack *stack);

/**
 * @brief Executa a operação que tem simbolo '/' associado ao tipo correspondente
 * @param stack target
 */
void slash_symbol_operation(Stack *stack);

/**
 * @brief Executa a operação que tem simbolo '#' associado ao tipo correspondente
 * @param stack target
 */
void hashtag_symbol_operation(Stack *stack);

/**
 * @brief Executa a operação que tem simbolo '%' associado ao tipo correspondente
 * @param stack target
 * @param variables
 */
void parentheses_symbol_operation(Stack *stack, StackElement *variables);

/**
 * @brief Executa a operação que tem simbolo ',' associado ao tipo correspondente
 * @param stack target
 * @param variables
 */
void comma_symbol_operation(Stack *stack, StackElement *variables);

/**
 * @brief Executa a operação que tem simbolo '$' associado ao tipo correspondente
 * @param stack target
 * @param variables
 */
void dollar_symbol_operation(Stack *stack, StackElement *variables);
