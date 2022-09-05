/**
 * @file main.c
 * Ficheiro main do programa
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "operations.h"
#include "logica.h"
#include "conversions.h"
#include "logger.h"
#include "operations_storage.h"
#include "parser.h"
#include "variable_operations.h"

/** Tamanho do buffer de input */
#define INPUT_BUFFER_SIZE 10001
/** Capacidade inicial da stack main */
#define INITIAL_STACK_CAPACITY 10

/**
 * @brief A função main, a função que conecta tudo na stack e a faz funcionar.
 */
int main() {
    char input[INPUT_BUFFER_SIZE];

    if (fgets(input, sizeof input, stdin) != input) {
        return EXIT_FAILURE;
    }

    Stack *stack = create_stack(INITIAL_STACK_CAPACITY);
    StackElement *variables = create_variable_array();

    tokenize_and_parse(stack, variables, input);

    dump_stack(stack);
    printf("\n");

    free_stack(stack);
    free(variables);

    return 0;
}
