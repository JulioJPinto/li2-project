/**
 * @file polymorphic_operations.c
 * @brief Implementação das operações polimorfas
 */

#include "polymorphic_operations.h"
#include "operations.h"
#include "logica.h"
#include "array_operations.h"
#include "block_operations.h"

void asterisk_operation(Stack *stack, StackElement *variables) {
    ElementType left_element_type = get(stack, 1).type;

    if (peek(stack).type == BLOCK_TYPE) {
        fold_operation(stack, variables);
    } else if (left_element_type == ARRAY_TYPE) {
        repeat_array_operation(stack);
    } else if (left_element_type == STRING_TYPE) {
        repeat_string_operation(stack);
    } else {
        mult_operation(stack);
    }
}

void tilde_operation(Stack *stack, StackElement *variables) {
    StackElement element = peek(stack);
    ElementType element_type = element.type;

    if (element_type == ARRAY_TYPE) {
        push_all_elements_from_array_operation(stack);
    } else if (element_type == BLOCK_TYPE) {
        execute_block_operation(stack, variables);
    } else {
        not_bitwise_operation(stack);
    }
}

void lesser_than_symbol_operation(Stack *stack) {
    ElementType left_element_type = get(stack, 1).type;
    ElementType right_element_type = peek(stack).type;

    if (left_element_type == ARRAY_TYPE && right_element_type == LONG_TYPE) {
        take_first_n_elements_from_array_operation(stack);
    } else if (left_element_type == STRING_TYPE && right_element_type == LONG_TYPE) {
        take_first_n_elements_from_string_operation(stack);
    } else {
        lesser_than_operation(stack);
    }
}

void bigger_than_symbol_operation(Stack *stack) {
    ElementType left_element_type = get(stack, 1).type;
    ElementType right_element_type = peek(stack).type;

    if (left_element_type == ARRAY_TYPE && right_element_type == LONG_TYPE) {
        take_last_n_elements_from_array_operation(stack);
    } else if (left_element_type == STRING_TYPE && right_element_type == LONG_TYPE) {
        take_last_n_elements_from_string_operation(stack);
    } else {
        bigger_than_operation(stack);
    }
}

void open_parentheses_operation(Stack *stack) {
    ElementType element_type = peek(stack).type;

    if (element_type == ARRAY_TYPE) {
        remove_first_element_from_array_operation(stack);
    } else if (element_type == STRING_TYPE) {
        remove_first_element_from_string_operation(stack);
    } else {
        decrement_operation(stack);
    }
}

void close_parentheses_operation(Stack *stack) {
    ElementType element_type = peek(stack).type;

    if (element_type == ARRAY_TYPE) {
        remove_last_element_from_array_operation(stack);
    } else if (element_type == STRING_TYPE) {
        remove_last_element_from_string_operation(stack);
    } else {
        increment_operation(stack);
    }
}

void equal_symbol_operation(Stack *stack) {
    ElementType left_element_type = get(stack, 1).type;
    ElementType right_element_type = peek(stack).type;

    if (left_element_type == ARRAY_TYPE && right_element_type == LONG_TYPE) {
        get_element_from_index_array_operation(stack);
    } else if (left_element_type == STRING_TYPE && right_element_type == LONG_TYPE) {
        get_element_from_index_string_operation(stack);
    } else {
        is_equal_operation(stack);
    }
}

void slash_symbol_operation(Stack *stack) {
    ElementType left_element_type = get(stack, 1).type;

    if (left_element_type == STRING_TYPE) {
        separate_string_by_substring_operation(stack);
    } else {
        div_operation(stack);
    }
}

void hashtag_symbol_operation(Stack *stack) {
    ElementType left_element_type = get(stack, 1).type;
    ElementType right_element_type = peek(stack).type;

    if (left_element_type == STRING_TYPE && (right_element_type == STRING_TYPE || right_element_type == CHAR_TYPE)) {
        search_substring_in_string_operation(stack);
    } else {
        exponential_operation(stack);
    }
}

void parentheses_symbol_operation(Stack *stack, StackElement *variables) {
    ElementType left_element_type = get(stack, 1).type;
    ElementType right_element_type = peek(stack).type;

    if (left_element_type == ARRAY_TYPE && right_element_type == BLOCK_TYPE) {
        map_block_array_operation(stack, variables);
    } else if (left_element_type == STRING_TYPE && right_element_type == BLOCK_TYPE) {
        map_block_string_operation(stack, variables);
    } else {
        modulo_operation(stack);
    }
}

void comma_symbol_operation(Stack *stack, StackElement *variables) {
    ElementType left_element_type = get(stack, 1).type;
    ElementType right_element_type = peek(stack).type;

    if (left_element_type == ARRAY_TYPE && right_element_type == BLOCK_TYPE) {
        filter_block_array_operation(stack, variables);
    } else if (left_element_type == STRING_TYPE && right_element_type == BLOCK_TYPE) {
        filter_block_string_operation(stack, variables);
    } else {
        size_range_operation(stack);
    }
}

void dollar_symbol_operation(Stack *stack, StackElement *variables) {
    ElementType right_element_type = peek(stack).type;

    if (right_element_type == BLOCK_TYPE) {
        sort_block_array_operation(stack, variables);
    } else {
        copy_nth_element_operation(stack);
    }
}
