/**
 * @file variable_operations.h
 * @brief Responsável por controlar as variáveis globais
 */

#pragma once

#include "stack.h"

/**
 * Cria uma array de variáveis com as variáveis inicializadas e setadas para o seu valor default
 * @return A array de variáveis criada
 */
StackElement *create_variable_array();

/**
 * Tenta executar a operação de fazer push de uma variável global
 * @param stack A stack onde irá fazer push da variável global
 * @param variables A array de variáveis globais
 * @param input O input onde irá buscar a varíavel pretendida
 * @return 1 se conseguiu executar a operação, 0 caso contrário
 */
int parse_push_variable(Stack *stack, StackElement *variables, const char *input);

/**
 * Tenta executar a operação de alterar o valor de uma variável global
 * @param stack A stack onde irá fazer push da variável global
 * @param variables A array de variáveis globais
 * @param input O input onde irá buscar a varíavel pretendida
 * @return 1 se conseguiu executar a operação, 0 caso contrário
 */
int parse_set_variable(Stack *stack, StackElement *variables, const char *input);
