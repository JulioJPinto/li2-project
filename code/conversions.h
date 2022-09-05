/**
 * @file conversions.h
 * @brief Headers das conversões de tipo
 */

#include "stack.h"

/** Número de bytes alocados para conversão de tipos para string */
#define MAX_CONVERT_TO_STRING_SIZE 100

/**
 * @brief Dá parse a @param{word} para um long
 * @param word target
 * @param to result
 * @return int 
 */
int parse_long(char word[], long *to);

/**
 * @brief Dá parse a @param{word} para um double
 * @param word target
 * @param to result
 * @return double 
 */
int parse_double(char word[], double *to);

/**
* @brief Converte o topo da stack para caractere
* @param stack target
*/
void convert_last_element_to_char(Stack *stack);

/**
* @brief Converte o topo da stack num double
* @param stack target
*/
void convert_last_element_to_double(Stack *stack);

/**
* @brief Converte o topo da stack num inteiro
* @param stack target
*/
void convert_last_element_to_long(Stack *stack);

/**
* @brief Executa a conversão do topo da stack para string
* @param stack target
*/
void convert_last_element_to_string(Stack *stack);

/**
* @brief Converte um elemento da stack numa string
* @param stack target
*/
void convert_element_to_string(StackElement *stack_element, char *dest);

/**
 * @brief Converte um elemento da stack no tipo char.
 * @param stack_element target
 */
char convert_element_to_char(StackElement *stack_element);
