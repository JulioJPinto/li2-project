/**
 * @file logica.h
 * @brief Header das operações de lógica
 */

#include "stack.h"

/**
 * @brief Função que vê se o último valor da stack é menor do que o penúltimo e devolve 1 ou 0.
 * A Função vê se o último valor da stack é menor que o penúltimo e devolve 1 ou 0 caso este seja verdadeiro ou falso.
 * @param stack
 */
void lesser_than_operation(Stack *stack);

/**
 * @brief Função que vê se o último valor da stack é maior do que o penúltimo e devolve 1 ou 0
 * A Função vê se o último valor da stack é maior que o penúltimo e devolve 1 ou 0 caso este seja verdadeiro ou falso.
 * @param stack
 */
void bigger_than_operation(Stack *stack);

/**
 * @brief Função que vê se o último valor da stack é igual ao penúltimo e devolve 1 ou 0.
 * A Função vê se o último valor da stack é igual ao penúltimo e devolve 1 ou 0 caso este seja verdadeiro ou falso.
 * @param stack
 */
void is_equal_operation(Stack *stack);

/**
 * @brief Função que vê a interseção dos últimos dois valores da stack e devolve 1 ou 0
 * A Função que vê se ambos os valores não são do tipo falsy caso nenhum seja devolve o último valor que testa,
 * caso um destes seja devolve o valor falsy.
 * @param stack
 */
void and_operation(Stack *stack);

/**
 * @brief Função que vê a união dos últimos dois valores da stack
 * A Função que vê se existe pelo menos um valor do tipo truthy, caso exista devolve o primeiro que se encontra nesse tipo,
 * caso nao exista devolve o valor falsy
 * @param stack
 */
void or_operation(Stack *stack);

/**
 * @brief Função que transforma um valor na sua negação.
 * A Função que caso o valor seja truthy devove um falsy, caso este seja falsy devolve um valor qualquer do tipo truthy.
 * @param stack
 */
void not_operation(Stack *stack);

/**
 * @brief Esta função realiza o mesmo que a função lesser_then_operation porém devolve o maior valor.
 * A Função compara os últimos dois elementos que se encontram na stack e devolve o maior deste dois.
 * @param stack
 */
void lesser_value_operation(Stack *stack);

/**
 * @brief Esta função realiza o mesmo que a função bigger_then_operation porém devolve o maior valor.
 * A Função compara os últimos dois elementos que se encontram na stack e devolve o menor deste dois.
 * @param stack
 */
void bigger_value_operation(Stack *stack);

/**
 * @brief Esta função dependendo no antepenúltimo elemento da stack ser truthy ou falsy devolve o penúltimo ou último elemento desta.
 * A Função vê se o antepenúltimo elemenento da stack é truthy ou falsy, caso este seja falsy esta vai retornar o último valor da stack,
 * caso este seja truthy esta vai devolver o penúltimo valor da stack.
 * @param stack
 */
void if_then_else_operation(Stack *stack);
