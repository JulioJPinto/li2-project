/**
 * @file array_operations.h
 * @brief Header de operações para arrays
 */

#pragma once

#include "stack.h"

/**
* @brief Dá parse a um array e da push a este para a stack
* @param stack target
*/
int parse_array(Stack *stack, StackElement *variables, char *word);

/**
* @brief Devolve o tamanho de um array/string ou então devolve um array com o range até este valor caso seja long
* @param stack target
*/
void size_range_operation(Stack *stack);

/**
* @brief Copia uma string e da push a esta para a stack
* @param stack target
*/
void repeat_string_operation(Stack *stack);

/**
* @brief Copia um array e da push a estes para a stack
* @param stack target
*/
void repeat_array_operation(Stack *stack);

/**
* @brief Dá push a todos os elemenentos de array para a stack
* @param stack target
*/
void push_all_elements_from_array_operation(Stack *stack);

/**
* @brief Executa a operação de separar a string @param{string_element} em substrings @param{substring_element}
* @param stack target
*/
void separate_string_by_substring_operation(Stack *stack);

/**
* @brief Executa a operação de separar as substrings @param{substring_element} por linhas
* @param stack target
*/
void separate_string_by_new_line_operation(Stack *stack);

/**
* @brief Executa a operação de separar as substrings @param{substring_element} por espaços brancos
* @param stack target
*/
void separate_string_by_whitespace_operation(Stack *stack);

/**
* @brief Executa a operação de devolver os primeiros n elementos do array num novo array
* @param stack target
*/
void take_first_n_elements_from_array_operation(Stack *stack);

/**
* @brief Executa a operação de devolver os primeiros n caracteres da string numa nova string
* @param stack target
*/
void take_first_n_elements_from_string_operation(Stack *stack);

/**
* @brief Executa a operação de devolver os últimos n elementos do array num novo array
* @param stack target
*/
void take_last_n_elements_from_array_operation(Stack *stack);

/**
* @brief Executa a operação de devolver os últimos n caracteres da string numa nova string
* @param stack target
*/
void take_last_n_elements_from_string_operation(Stack *stack);

/**
* @brief Executa a operação de devolver o elemento na posição x do array
* @param stack target
*/
void get_element_from_index_array_operation(Stack *stack);

/**
* @brief Executa a operação de devolver o caractere na posição x da string
* @param stack target
*/
void get_element_from_index_string_operation(Stack *stack);

/**
* @brief Executa a operação de remover o primeiro elemento do array
* @param stack target
*/
void remove_first_element_from_array_operation(Stack *stack);

/**
* @brief Executa a operação de remover o primeiro caractere da string
* @param stack target
*/
void remove_first_element_from_string_operation(Stack *stack);

/**
* @brief Executa a operação de remover o último elemento do array
* @param stack target
*/
void remove_last_element_from_array_operation(Stack *stack);

/**
* @brief Executa a operação de remover o último caractere da string
* @param stack target
*/
void remove_last_element_from_string_operation(Stack *stack);

/**
* @brief Executa a operação de procurar a substring na string
* @param stack target
*/
void search_substring_in_string_operation(Stack *stack);
