/**
 * @file parser.h
 * @brief Responsável de converter o input para objetos do programa
 */

#pragma once

#include "stack.h"

/**
 * @brief Separa a string de input em espaços, strings, arrays e blocos e executa função parse_word nessa word separada
 * @param stack target
 * @param variables variáveis
 * @param input input bruto
 */
void tokenize_and_parse(Stack *stack, StackElement *variables, char *input);

/**
 * @brief Dá parse_word a uma word.
 * @brief Transforma a word no seu devido valor e coloca-o na stack, ou executa-o se for uma operação.
 * @param stack target
 * @param variables variáveis
 * @param word word para transformar
 */
void parse_word(Stack *stack, StackElement *variables, char word[]);
