/**
 * @file block_operations.c
 * @brief Implementação de operações sobre blocos
 */

#include <string.h>
#include "block_operations.h"
#include "logger.h"
#include "parser.h"
#include "conversions.h"
#include "operations.h"

int try_to_parse_block(Stack *stack, char *word) {
    size_t word_length = strlen(word);

    if (*word != '{' || word[word_length - 1] != '}') {
        return 0;
    }

    // remover brackets:
    word[word_length - 1] = '\0';
    word++;

    push_block(stack, word);

    return 1;
}

/**
* @brief Executa um bloco na stack
* @param stack target
* @param block_element block to execute
* @param variables value of variables
*/
void execute_block_stack(Stack *stack, StackElement block_element, StackElement *variables) {
    if (block_element.type != BLOCK_TYPE) PANIC("Trying to execute a non-block element type (%d).", block_element.type)

    PRINT_DEBUG("Starting to execute block {%s}:\n", block_element.content.block_value)
    tokenize_and_parse(stack, variables, block_element.content.block_value);
}

Stack *execute_block(StackElement target_element, StackElement block_element, StackElement *variables) {
    Stack *result_stack = create_stack(10);
    push(result_stack, duplicate_element(target_element));

    execute_block_stack(result_stack, block_element, variables);
    return result_stack;
}

void execute_block_operation(Stack *stack, StackElement *variables) {
    StackElement block_element = pop(stack);
    StackElement target_element = pop(stack);

    Stack *result_stack = execute_block(target_element, block_element, variables);
    push_all(stack, result_stack);

    free_stack(result_stack);
}

/**
* @brief Aplica o bloco a todos os elementos deste
* @param stack target
* @param block_element block to execute
* @param variables value of variables
*/
Stack *map_blocks(Stack *array, StackElement block_element, StackElement *variables) {
    int array_target_length = length(array);
    Stack *array_result = create_stack(array_target_length);

    for (int i = 0; i < array_target_length; ++i) {
        StackElement target = duplicate_element(array->array[i]);
        Stack *result = execute_block(target, block_element, variables);

        push_all(array_result, result);

        free_stack(result);
    }

    return array_result;
}

void map_block_array_operation(Stack *stack, StackElement *variables) {
    StackElement block_element = pop(stack);
    StackElement array_element = pop(stack);

    Stack *array_target = array_element.content.array_value;

    Stack *map_result = map_blocks(array_target, block_element, variables);

    push_array(stack, map_result);

    free_element(block_element);
    free_element(array_element);
}

/**
* @brief Cria um array a partir de uma string
* @param string target
*/
Stack *create_string_array(char *string) {
    int string_length = (int) strlen(string);
    Stack *result = create_stack(string_length);

    for (int i = 0; i < string_length; ++i) {
        push_char(result, string[i]);
    }

    return result;
}

/**
* @brief Verifica se o elemento é um caractere ou uma string. Se for um caractere adiciona 1 ao resultado e se for string adiciona o comprimento da mesma ao resultado.
* @param array target
*/
int compute_string_length_from_stack_string_array(Stack *array) {
    int result = 0;
    for (int i = 0; i < length(array); ++i) {
        StackElement x = array->array[i];
        if (x.type == CHAR_TYPE) {
            result++;
        } else if (x.type == STRING_TYPE) {
            result += (int) strlen(x.content.string_value);
        }
    }
    return result;
}

/**
* @brief Converte um array para uma string
* @param array target
*/
char *convert_stack_array_to_string(Stack *array) {
    int string_length = compute_string_length_from_stack_string_array(array);
    int array_length = length(array);

    char *result = calloc((size_t) string_length + 1, sizeof(char));

    int current_index = 0;
    for (int i = 0; i < array_length; ++i) {
        StackElement current_element = array->array[i];
        if (current_element.type == CHAR_TYPE) {
            result[current_index] = current_element.content.char_value;
            current_index++;
        } else if (current_element.type == STRING_TYPE) {
            char *current_string = current_element.content.string_value;
            int current_string_length = (int) strlen(current_string);
            for (int j = 0; j < current_string_length; ++j) {
                result[current_index] = current_string[j];
                current_index++;
            }
        } else {
            PANIC("Converting string stack array back to char array contains non string/char element (type: %d).",
                  current_element.type)
        }
    }

    result[current_index] = '\0';

    return result;
}

void map_block_string_operation(Stack *stack, StackElement *variables) {
    StackElement block_element = pop(stack);
    StackElement string_element = pop(stack);

    char *string_target = string_element.content.string_value;

    Stack *string_array = create_string_array(string_target);

    Stack *map_result = map_blocks(string_array, block_element, variables);
    char *string_result = convert_stack_array_to_string(map_result);

    push_string(stack, string_result);

    free(string_result);
    free_stack(map_result);
    free_stack(string_array);
    free_element(block_element);
    free_element(string_element);
}

void filter_block_array_operation(Stack *stack, StackElement *variables) {
    StackElement block_element = pop(stack);
    StackElement array_element = pop(stack);

    Stack *target_array = array_element.content.array_value;
    int array_length = length(target_array);

    Stack *array_result = create_stack(array_length);
    for (int i = 0; i < array_length; ++i) {
        StackElement current_element = duplicate_element(target_array->array[i]);
        Stack *current_element_result = execute_block(current_element, block_element, variables);

        if (length(current_element_result) > 0) {
            StackElement first_element = pop(current_element_result);
            if (is_truthy(&first_element)) {
                push(array_result, current_element);
            }
            free_element(first_element);
        }

        free_stack(current_element_result);
    }

    push_array(stack, array_result);

    free_element(block_element);
    free_element(array_element);
}

void filter_block_string_operation(Stack *stack, StackElement *variables) {
    StackElement block_element = pop(stack);
    StackElement string_element = pop(stack);

    char *target_string = string_element.content.string_value;
    int string_length = (int) strlen(target_string);

    char *string_result = calloc((size_t) string_length + 1, sizeof(char));
    int current_string_result_index = 0;

    for (int i = 0; i < string_length; ++i) {
        char current_char = target_string[i];
        StackElement char_element = create_char_element(current_char);
        Stack *current_element_result = execute_block(char_element, block_element, variables);

        if (length(current_element_result) > 0) {
            StackElement first_element = pop(current_element_result);
            if (is_truthy(&first_element)) {
                string_result[current_string_result_index] = current_char;
                current_string_result_index++;
            }
            free_element(first_element);
        }

        free_element(char_element);
        free_stack(current_element_result);
    }

    push_string(stack, string_result);

    free(string_result);
    free_element(block_element);
    free_element(string_element);
}

/**
* @brief Compara o tipo dos elementos da stack
* @param a target
* @param b target
*/
int compare_elements(StackElement a, StackElement b) {
    if (a.type == STRING_TYPE && b.type == STRING_TYPE) {
        return strcmp(a.content.string_value, b.content.string_value);
    } else if (a.type == DOUBLE_TYPE || b.type == DOUBLE_TYPE) {
        return get_element_as_double(&a) - get_element_as_double(&b) > 0;
    } else if (a.type == LONG_TYPE || b.type == LONG_TYPE) {
        return (int) (get_element_as_long(&a) - get_element_as_long(&b));
    } else if (a.type == CHAR_TYPE || b.type == CHAR_TYPE) {
        return (int) (convert_element_to_char(&a) - convert_element_to_char(&b));
    }
    PANIC("Cannot compare elements with types x=%d, y=%d", a.type, b.type)
}

/**
* @brief Insere os elementos num array de forma ordenada
* @param array target
* @param length array length
* @param block_element block to execute
* @param variables value of variables
* @param compare_function 
*/
void insertion_sort(StackElement array[], int length, StackElement block_element, StackElement *variables,
                    int compare_function(StackElement *, StackElement, StackElement, StackElement)) {
    int j;
    StackElement key;
    for (int i = 1; i < length; i++) {
        key = array[i];
        j = i - 1;

        while (j >= 0 && compare_function(variables, block_element, array[j], key) > 0) {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
    }
}

/**
* @brief Compara dois elementos utilizando o resultado de executar um bloco
* @param variables target
* @param block_element block to execute
* @param a elemento a comparar com b
* @param b elemento a comparar com a
*/
int sort_compare_function(StackElement *variables, StackElement block_element, StackElement a, StackElement b) {
    Stack *a_block_result = execute_block(a, block_element, variables);
    Stack *b_block_result = execute_block(b, block_element, variables);

    StackElement a_compare_element = pop(a_block_result);
    StackElement b_compare_element = pop(b_block_result);

    int compare_result = compare_elements(a_compare_element, b_compare_element);

    free_element(a_compare_element);
    free_element(b_compare_element);

    free_stack(a_block_result);
    free_stack(b_block_result);

    return compare_result;
}

void sort_block_array_operation(Stack *stack, StackElement *variables) {
    StackElement block_element = pop(stack);
    StackElement array_element = pop(stack);

    Stack *array_value = array_element.content.array_value;
    StackElement *array = array_value->array;

    insertion_sort(array, length(array_value), block_element, variables, sort_compare_function);

    push(stack, array_element);
    free_element(block_element);
}

/**
* @brief Verifica se o elemento é truthy e @returns retorna o valor lógico do mesmo
* @param element target
*/
int check_truthy_and_free(StackElement element) {
    int result = is_truthy(&element);
    free_element(element);
    return result;
}

void while_top_truthy_operation(Stack *stack, StackElement *variables) {
    StackElement block_element = pop(stack);

    do {
        execute_block_stack(stack, block_element, variables);
    } while (check_truthy_and_free(pop(stack)));

    free_element(block_element);
}

void fold_operation(Stack *stack, StackElement *variables) {
    StackElement block_element = pop(stack);
    StackElement array_element = pop(stack);

    Stack *array_value = array_element.content.array_value;
    StackElement *array = array_value->array;

    int array_length = length(array_value);

    Stack *stack_result = create_stack(array_length);

    if (array_length > 0) {
        push(stack_result, duplicate_element(array[0]));
        for (int i = 1; i < array_length; ++i) {
            push(stack_result, duplicate_element(array[i]));
            execute_block_stack(stack_result, block_element, variables);
        }
    }

    push_array(stack, stack_result);

    free_element(block_element);
    free_element(array_element);
}
