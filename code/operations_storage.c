/**
 * @file operations_storage.c
 * @brief Ficheiro de implementação do @file{operations_storage.h}
 */

#include "operations_storage.h"
#include "operations.h"
#include "conversions.h"
#include "array_operations.h"
#include "logica.h"
#include "block_operations.h"

#include "polymorphic_operations.h"
#include "logger.h"
#include <string.h>

/**
 * @brief Macro para criar uma operação simples (que recebe apenas a stack como parametro)
 */
#define SIMPLE_OPERATION(simple_operation_function) {SIMPLE_OPERATION, {.operation_function = simple_operation_function}}

/**
 * @brief Macro para criar uma operação com variáveis globais
 */
#define VARIABLES_OPERATION(variables_operation_function) {VARIABLES_OPERATION, {.variables_operation = variables_operation_function}}

StackOperation get_operation(char op[]) {
    static const StackOperationTableEntry entries[] = {
            {"+",  SIMPLE_OPERATION(add_operation)},
            {"-",  SIMPLE_OPERATION(minus_operation)},
            {"*",  VARIABLES_OPERATION(asterisk_operation)},
            {"/",  SIMPLE_OPERATION(slash_symbol_operation)},
            {"%",  VARIABLES_OPERATION(parentheses_symbol_operation)},
            {"(",  SIMPLE_OPERATION(open_parentheses_operation)},
            {")",  SIMPLE_OPERATION(close_parentheses_operation)},
            {"#",  SIMPLE_OPERATION(hashtag_symbol_operation)},
            {"&",  SIMPLE_OPERATION(and_bitwise_operation)},
            {"|",  SIMPLE_OPERATION(or_bitwise_operation)},
            {"^",  SIMPLE_OPERATION(xor_bitwise_operation)},
            {"~",  VARIABLES_OPERATION(tilde_operation)},
            {"_",  SIMPLE_OPERATION(duplicate_operation)},
            {";",  SIMPLE_OPERATION(pop_operation)},
            {"\\", SIMPLE_OPERATION(swap_last_two_operation)},
            {"@",  SIMPLE_OPERATION(rotate_last_three_operation)},
            {"$",  VARIABLES_OPERATION(dollar_symbol_operation)},
            {"c",  SIMPLE_OPERATION(convert_last_element_to_char)},
            {"i",  SIMPLE_OPERATION(convert_last_element_to_long)},
            {"f",  SIMPLE_OPERATION(convert_last_element_to_double)},
            {"l",  SIMPLE_OPERATION(read_input_from_console_operation)},
            {"t",  SIMPLE_OPERATION(read_all_input_from_console_operation)},
            {"s",  SIMPLE_OPERATION(convert_last_element_to_string)},
            {">",  SIMPLE_OPERATION(bigger_than_symbol_operation)},
            {"<",  SIMPLE_OPERATION(lesser_than_symbol_operation)},
            {"=",  SIMPLE_OPERATION(equal_symbol_operation)},
            {"e&", SIMPLE_OPERATION(and_operation)},
            {"e|", SIMPLE_OPERATION(or_operation)},
            {"e>", SIMPLE_OPERATION(lesser_value_operation)},
            {"e<", SIMPLE_OPERATION(bigger_value_operation)},
            {"?",  SIMPLE_OPERATION(if_then_else_operation)},
            {"!",  SIMPLE_OPERATION(not_operation)},
            {",",  VARIABLES_OPERATION(comma_symbol_operation)},
            {"S/", SIMPLE_OPERATION(separate_string_by_whitespace_operation)},
            {"N/", SIMPLE_OPERATION(separate_string_by_new_line_operation)},
            {"w",  VARIABLES_OPERATION(while_top_truthy_operation)},
            {"p",  SIMPLE_OPERATION(print_stack_top_operation)}
    };

    size_t size = sizeof(entries) / sizeof(StackOperationTableEntry);

    for (size_t i = 0; i < size; i++) {
        if (strcmp(entries[i].operator, op) == 0) {
            return entries[i].operation;
        }
    }

    PANIC("Couldn't find operation_function '%s'", op)
}

void execute_operation(StackOperation operation, Stack *stack, StackElement *variables) {
    switch (operation.type) {
        case SIMPLE_OPERATION:
            operation.operation_function(stack);
            return;
        case VARIABLES_OPERATION:
            operation.variables_operation(stack, variables);
            return;
        default:
            return;
    }
}
