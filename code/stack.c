/**
 * @file stack.c
 * @brief Implementação da stack com array dinâmica
 */

#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logger.h"
#include "conversions.h"
#include <ctype.h>

Stack *create_stack(int initial_capacity) {
    Stack *stack = malloc(sizeof(Stack));

    stack->capacity = initial_capacity;
    stack->current_index = -1;
    stack->array = calloc((unsigned long) initial_capacity, sizeof(StackElement));

    return stack;
}

void free_stack(Stack *stack) {
    for (int i = 0; i < length(stack); ++i) {
        free_element(stack->array[i]);
    }

    free(stack->array);
    free(stack);
}

void dump_element(StackElement *element) {
    switch ((*element).type) {
        case LONG_TYPE:
            printf("%ld", element->content.long_value);
            return;
        case CHAR_TYPE:
            printf("%c", element->content.char_value);
            return;
        case DOUBLE_TYPE:
            printf("%g", element->content.double_value);
            return;
        case STRING_TYPE:
            printf("%s", element->content.string_value);
            return;
        case ARRAY_TYPE:
            dump_stack(element->content.array_value);
            return;
        case BLOCK_TYPE:
            printf("{%s}", element->content.block_value);
            return;
        default: PANIC("Couldn't match type for %d when dumping\n", (*element).content.char_value)
    }
}

void dump_stack(Stack *stack) {
    for (int i = 0; i < length(stack); ++i) {
        dump_element(&stack->array[i]);
    }
}

int length(Stack *stack) {
    return stack->current_index + 1;
}

StackElement pop(Stack *stack) {
    if (length(stack) <= 0) PANIC("Trying to pop from empty stack")

    StackElement result = stack->array[stack->current_index];
    stack->current_index--;

    return result;
}

long pop_long(Stack *stack) {
    StackElement element = pop(stack);
    long value = element.content.long_value;

    free_element(element);
    return value;
}

void push(Stack *stack, StackElement x) {
    if (length(stack) >= stack->capacity) {
        stack->capacity *= 2;
        stack->array = realloc(stack->array, (unsigned long) stack->capacity * sizeof(StackElement));
        PRINT_DEBUG("REALLOCATED STACK (new capacity = %d)\n", stack->capacity)
    }

    stack->array[++(stack->current_index)] = x;
}

void push_all(Stack *stack, Stack *elements) {
    int elements_length = length(elements);
    for (int i = 0; i < elements_length; ++i) {
        push(stack, duplicate_element(elements->array[i]));
    }
}

void push_double(Stack *stack, double value) {
    push(stack, create_double_element(value));
}

void push_long(Stack *stack, long value) {
    push(stack, create_long_element(value));
}

void push_char(Stack *stack, char value) {
    push(stack, create_char_element(value));
}

void push_string(Stack *stack, char *value) {
    push(stack, create_string_element(value));
}

void push_array(Stack *stack, Stack *value) {
    push(stack, create_array_element(value));
}

void push_block(Stack *stack, char *value) {
    push(stack, create_block_element(value));
}

StackElement create_double_element(double value) {
    StackElement element;
    element.type = DOUBLE_TYPE;
    element.content.double_value = value;

    return element;
}

StackElement create_long_element(long value) {
    StackElement element;
    element.type = LONG_TYPE;
    element.content.long_value = value;

    return element;
}

StackElement create_char_element(char value) {
    StackElement element;
    element.type = CHAR_TYPE;
    element.content.char_value = value;

    return element;
}

StackElement create_string_element(char *value) {
    StackElement element;
    element.type = STRING_TYPE;

    size_t length = strlen(value) + 1;
    char *copied_string = calloc(length, sizeof(char));
    strcpy(copied_string, value);

    element.content.string_value = copied_string;

    return element;
}

StackElement create_array_element(Stack *value) {
    StackElement element;
    element.type = ARRAY_TYPE;
    element.content.array_value = value;

    return element;
}

StackElement create_block_element(char *value) {
    StackElement element;
    element.type = BLOCK_TYPE;

    size_t length = strlen(value) + 1;
    char *copied_string = calloc(length, sizeof(char));
    strcpy(copied_string, value);

    element.content.block_value = copied_string;

    return element;
}

StackElement peek(Stack *stack) {
    return stack->array[stack->current_index];
}

StackElement get(Stack *stack, long index) {
    return stack->array[stack->current_index - index];
}

/**
 * Retorna 1 se a string conter apenas whitespaces, 0 caso contrário
 * @param s string para testar
 * @return Valor booleano
 */
static int string_only_contains_whitespaces(const char *s) {
    while (*s != '\0') {
        if (!isspace(*s)) return 0;
        s++;
    }
    return 1;
}

int is_truthy(StackElement *a) {
    switch (a->type) {
        case LONG_TYPE:
            return a->content.long_value != 0;
        case CHAR_TYPE:
            return a->content.char_value != '\0';
        case STRING_TYPE:
            return strlen(a->content.string_value) != 0;
        case DOUBLE_TYPE:
            return a->content.double_value != .0;
        case ARRAY_TYPE:
            return length(a->content.array_value) != 0;
        case BLOCK_TYPE:
            return string_only_contains_whitespaces(a->content.block_value);
        default: PANIC("Couldn't retrieve truthy value from type %d\n", a->type)
    }
}

void free_element(StackElement element) {
    switch (element.type) {
        case STRING_TYPE:
            free(element.content.string_value);
            return;
        case ARRAY_TYPE:
            free_stack(element.content.array_value);
            return;
        case BLOCK_TYPE:
            free(element.content.block_value);
            return;
        case LONG_TYPE:
        case CHAR_TYPE:
        case DOUBLE_TYPE:
        default:
            return;
    }
}

StackElement duplicate_array(StackElement element) {
    Stack *old_array = element.content.array_value;
    Stack *new_array = create_stack(old_array->capacity);
    for (int i = 0; i < length(old_array); i++) {
        push(new_array, duplicate_element(old_array->array[i]));
    }
    return create_array_element(new_array);
}

StackElement duplicate_element(StackElement element) {
    switch (element.type) {
        case STRING_TYPE:
            return create_string_element(element.content.string_value);
        case ARRAY_TYPE:
            return duplicate_array(element);
        case BLOCK_TYPE:
            return create_block_element(element.content.block_value);
        case LONG_TYPE:
        case CHAR_TYPE:
        case DOUBLE_TYPE:
        default:
            return element;
    }
}
