/**
 * @file logica.c
 * @brief Implementação das operações de lógica
 */

#include "logger.h"
#include "operations.h"
#include "conversions.h"
#include "stack.h"
#include "logica.h"
#include "string_operations.h"

/**
 * @brief Função lesser_than_operation para longs
 * @param stack target
 * @param a último valor da stack
 * @param b penúltimo valor da stack
 */
void bigger_than_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a > b);
}
/**
 * @brief Função lesser_than_operation para doubles.
  * @param stack target
 * @param a último valor da stack
 * @param b penúltimo valor da stack
 */
void bigger_than_double_operation(Stack *stack, double a, double b) {
    push_long(stack, a > b);
}

void bigger_than_operation(Stack *stack) {
    ElementType left_element_type = get(stack, 1).type;
    ElementType element_type = peek(stack).type;

    if (element_type == STRING_TYPE && left_element_type == STRING_TYPE) {
        string_compare_bigger_operation(stack);
    } else {
        operate_promoting_number_type(stack, bigger_than_double_operation, bigger_than_long_operation);
    }
}
/**
 * @brief Função bigger_than_operation para doubles.
  * @param stack target
 * @param a último valor da stack
 * @param b penúltimo valor da stack
 */
void lesser_than_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a < b);
}
/**
 * @brief Função bigger_than_operation para doubles.
 * @param stack target
 * @param a último valor da stack
 * @param b penúltimo valor da stack
 */
void lesser_than_double_operation(Stack *stack, double a, double b) {
    push_long(stack, a < b);
}

void lesser_than_operation(Stack *stack) {
    ElementType left_element_type = get(stack, 1).type;
    ElementType element_type = peek(stack).type;
    
    if (element_type == STRING_TYPE && left_element_type == STRING_TYPE) {
        string_compare_smaller_operation(stack);
    } else {
        operate_promoting_number_type(stack, lesser_than_double_operation, lesser_than_long_operation);
    }
}
/**
 * @brief Função is_equal_operation para longs.
 * @param stack target
 * @param a último valor da stack
 * @param b penúltimo valor da stack
 */
void is_equal_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a == b);
}
/**
 * @brief Função is_equal_operation para doubles.
 * @param stack target
 * @param a último valor da stack
 * @param b penúltimo valor da stack
 */
void is_equal_double_operation(Stack *stack, double a, double b) {
    push_long(stack, a == b);
}

void is_equal_operation(Stack *stack) {
    ElementType left_element_type = get(stack, 1).type;
    ElementType element_type = peek(stack).type;
    
    if (element_type == STRING_TYPE && left_element_type == STRING_TYPE) {
        string_compare_equal_operation(stack);
    } else {
        operate_promoting_number_type(stack, is_equal_double_operation, is_equal_long_operation);
    }
    
}
/**
 * @brief Função and_operation para longs.
 * @param stack target
 * @param a último valor da stack
 * @param b penúltimo valor da stack
 */
void and_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a && b ? b : 0);
}
/**
 * @brief Função and_operation para doubles.
 * @param stack target
 * @param a último valor da stack
 * @param b penúltimo valor da stack
 */
void and_double_operation(Stack *stack, double a, double b) {
    push_double(stack, a != 0 && b != 0 ? b : 0);
}

void and_operation(Stack *stack) {
    operate_promoting_number_type(stack, and_double_operation, and_long_operation);
}
/**
 * @brief Função or_operation para longs.
 * @param stack target
 * @param a último valor da stack
 * @param b penúltimo valor da stack
 */
void or_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a ? a : b);
}
/**
 * @brief Função or_operation para doubles.
 * @param stack target
 * @param a último valor da stack
 * @param b penúltimo valor da stack
 */
void or_double_operation(Stack *stack, double a, double b) {
    push_double(stack, a != 0 ? a : b);
}

void or_operation(Stack *stack) {
    operate_promoting_number_type(stack, or_double_operation, or_long_operation);
}

void not_operation(Stack *stack) {
    StackElement element = pop(stack);

    int truthy = is_truthy(&element);
    free_element(element);
    push_long(stack, !truthy);
}
/**
 * @brief Função lesser_value_operation para longs.
 * @param stack target
 * @param a último valor da stack
 * @param b penúltimo valor da stack
 */
void lesser_value_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a < b ? b : a);
}
/**
 * @brief Função lesser_value_operation para doubles.
 * @param stack target
 * @param a último valor da stack
 * @param b penúltimo valor da stack
 */
void lesser_value_double_operation(Stack *stack, double a, double b) {
    push_double(stack, a < b ? b : a);
}

void lesser_value_operation(Stack *stack) {
    ElementType left_element_type = get(stack, 1).type;
    ElementType element_type = peek(stack).type;
    
    if (element_type == STRING_TYPE && left_element_type == STRING_TYPE) {
        string_compare_smaller_value_operation(stack);
    } else {
        operate_promoting_number_type(stack, lesser_value_double_operation, lesser_value_long_operation);
    }
}
/**
 * @brief Função bigger_value_operation para longs.
 * @param stack target
 * @param a último valor da stack
 * @param b penúltimo valor da stack
 */
void bigger_value_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a > b ? b : a);
}
/**
 * @brief Função bigger_value_operation para doubles.
 * @param stack target
 * @param a último valor da stack
 * @param b penúltimo valor da stack
 */
void bigger_value_double_operation(Stack *stack, double a, double b) {
    push_double(stack, a > b ? b : a);
}

void bigger_value_operation(Stack *stack) {
    ElementType left_element_type = get(stack, 1).type;
    ElementType element_type = peek(stack).type;
    
    if (element_type == STRING_TYPE && left_element_type == STRING_TYPE) {
        string_compare_bigger_value_operation(stack);
    } else {
        operate_promoting_number_type(stack, bigger_value_double_operation, bigger_value_long_operation);
    }
}

void if_then_else_operation(Stack *stack) {
    StackElement c = pop(stack);
    StackElement b = pop(stack);
    StackElement a = pop(stack);

    int cond = is_truthy(&a);
    push(stack, cond ? b : c);

    free_element(a);
    free_element(!cond ? b : c);
}
