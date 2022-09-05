/**
 * @file block_operations.h
 * @brief Header de operações sobre blocos
 */

#pragma once

#include "stack.h"

/**
* @brief Operação de criar um bloco
* @param stack target
* @param word result
*/
int try_to_parse_block(Stack *stack, char *word);

/**
* @brief Executa um bloco com um elemento target na stack
* @param target_element target
* @param block_element block to execute
* @param variables value of variables
*/
Stack *execute_block(StackElement target_element, StackElement block_element, StackElement *variables);

/**
* @brief Operação de executar um bloco
* @param stack target
* @param variables value of variables
*/
void execute_block_operation(Stack *stack, StackElement *variables);

/**
* @brief Operação de aplicar o bloco a um array
* @param stack target
* @param variables value of variables
*/
void map_block_array_operation(Stack *stack, StackElement *variables);

/**
* @brief Operação de aplicar o bloco a uma string
* @param stack target
* @param variables value of variables
*/
void map_block_string_operation(Stack *stack, StackElement *variables);

/**
* @brief Operação de filtrar um array utilizando um bloco
* @param stack target
* @param variables value of variables
*/
void filter_block_array_operation(Stack *stack, StackElement *variables);

/**
* @brief Operação de filtrar uma string utilizando um bloco
* @param stack target
* @param variables value of variables
*/
void filter_block_string_operation(Stack *stack, StackElement *variables);

/**
* @brief Operação de ordenar um array utilizando um bloco
* @param stack target
* @param variables value of variables
*/
void sort_block_array_operation(Stack *stack, StackElement *variables);

/**
* @brief Operação de executar o bloco enquanto ele deixar um truthy no topo da stack
* @param stack target
* @param variables value of variables
*/
void while_top_truthy_operation(Stack *stack, StackElement *variables);

/**
* @brief Operação de aplicar fold sobre um array usando o bloco
* @param stack target
* @param variables value of variables
*/
void fold_operation(Stack *stack, StackElement *variables);
