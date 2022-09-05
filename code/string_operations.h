/**
 * @file string_operations.h
 * @brief Operações das strings
 */

#pragma once

#include "stack.h"

/**
 * Tenta dar parse a uma string. Caso @param{string} começe e acabe com aspas, adiciona o conteudo interior das aspas como string à stack
 * @param stack A stack para adicionar a string
 * @param string A string input
 * @return 1 caso tenha conseguido parsear a string, 0 caso contrário
 */
int parse_string(Stack *stack, char *string);

/**
 * @brief Função que compara se duas strings são iguais, caso sejam devolve 1, caso não devolve 0
 * @param stack A Stack onde vamos buscar os elementos para comparar
 */
void string_compare_equal_operation(Stack *stack);

/**
 * @brief Função que compara se a string a esquerda é menor (a nível lexicográfico) que a string a direita, caso seja devolve 1, caso não devolve 0
 * @param stack A Stack onde vamos buscar os elementos para comparar
 */
void string_compare_smaller_operation(Stack *stack);

/**
 * @brief Função que compara se a string a esquerda é maior (a nível lexicográfico) que a string a direita, caso seja devolve 1, caso não devolve 0
 * @param stack A Stack onde vamos buscar os elementos para comparar
 */
void string_compare_bigger_operation(Stack *stack);

/**
 * @brief Função que compara se a string a esquerda é menor (a nível lexicográfico) que a string a direita e devolve a menor das duas
 * @param stack A Stack onde vamos buscar os elementos para comparar
 */
void string_compare_smaller_value_operation(Stack *stack);

/**
 * @brief Função que compara se a string a esquerda é maior (a nível lexicográfico) que a string a direita e devolve a maior das duas
 * @param stack A Stack onde vamos buscar os elementos para comparar
 */
void string_compare_bigger_value_operation(Stack *stack);

/**
 * @brief Operação de procurar indice de susbtring em string
 * @param stack A stack para dar push ao indice resultado
 */
void search_substring_in_string_operation(Stack *stack);
