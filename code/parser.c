/**
 * @file parser.c
 * @brief Implemetação do parser
 */

#include <ctype.h>
#include <string.h>
#include "parser.h"
#include "logger.h"
#include "conversions.h"
#include "variable_operations.h"
#include "operations_storage.h"
#include "string_operations.h"
#include "array_operations.h"
#include "block_operations.h"

/**
 * @brief O parse state atual (O que é que está a dar parse)
 */
enum parseState {
    /** @brief A parsear elementos normais */
    PARSING_NORMAL_TEXT,
    /** @brief A parsear dentro de aspas */
    PARSING_INSIDE_QUOTE,
    /** @brief A parsear dentro de parentesis retos */
    PARSING_INSIDE_BRACKETS,
    /** @brief A parsear dentro de parentesis curvos */
    PARSING_INSIDE_CURLY_BRACKETS
};

void parse_word(Stack *stack, StackElement *variables, char word[]) {
    PRINT_DEBUG("Parsing: '%s'\n", word)

    long l;
    double d;

    if (parse_long(word, &l)) {
        PRINT_DEBUG("Pushing long: %ld\n", l)
        push_long(stack, l);
        return;
    }

    if (parse_double(word, &d)) {
        PRINT_DEBUG("Pushing double: %g\n", d)
        push_double(stack, d);
        return;
    }

    if (parse_push_variable(stack, variables, word)) {
        PRINT_DEBUG("Pushing variable '%s'\n", word)
        return;
    }

    if (parse_set_variable(stack, variables, word)) {
        PRINT_DEBUG("Setting variable '%s'\n", word)
        return;
    }

    if (parse_string(stack, word)) {
        PRINT_DEBUG("Pushing string '%s'\n", word + 1)
        return;
    }

    if (parse_array(stack, variables, word)) {
        PRINT_DEBUG("Pushing array '%s'\n", word + 1)
        return;
    }

    if (try_to_parse_block(stack, word)) {
        PRINT_DEBUG("Pushing block '{%s}'\n", word + 1)
        return;
    }

    PRINT_DEBUG("Parsed symbol: %s\n", word)

    StackOperation operation = get_operation(word);

    execute_operation(operation, stack, variables);
}

/**
 * @brief Retorna o novo state do parser conforme um caractere
 * @param c o caractere
 * @param target o pointer para onde o novo state irá ficar
 * @return 1 se o tal caractere é um caractere de começar um novo state, 0 caso contrário
 */
int was_success_set_state_from_open_char(char c, enum parseState *target) {
    if (c == '[') {
        *target = PARSING_INSIDE_BRACKETS;
        return 1;
    }
    if (c == '{') {
        *target = PARSING_INSIDE_CURLY_BRACKETS;
        return 1;
    }
    if (c == '"') {
        *target = PARSING_INSIDE_QUOTE;
        return 1;
    }
    return 0;
}

/**
 * @brief Retorna o char correspondente ao caractere de começar o state
 * @param state state
 * @return o caractere de começar o state
 */
char get_open_char(enum parseState state) {
    if (state == PARSING_INSIDE_BRACKETS) return '[';
    if (state == PARSING_INSIDE_CURLY_BRACKETS) return '{';
    if (state == PARSING_INSIDE_QUOTE) return '"';
    return -1;
}

/**
 * @brief Retorna o char correspondente ao caractere de fechar o state
 * @param state state
 * @return o caractere de fechar o state
 */
char get_close_char(enum parseState state) {
    if (state == PARSING_INSIDE_BRACKETS) return ']';
    if (state == PARSING_INSIDE_CURLY_BRACKETS) return '}';
    if (state == PARSING_INSIDE_QUOTE) return '"';
    return -1;
}

/**
 * @brief Calcula o novo número de brackets conforme um char
 * @param bracket_count O número de brackets atuais
 * @param current_char O caractere para calcular o novo número
 * @param open_bracket O caractere de abrir bracket
 * @param close_bracket O caractere de fechar bracket
 * @return O novo número de brackets
 */
int get_new_bracket_count(int bracket_count, char current_char, char open_bracket, char close_bracket) {
    if (current_char == close_bracket) {
        bracket_count--;
    } else if (current_char == open_bracket) {
        bracket_count++;
    }
    return bracket_count;
}

void tokenize_and_parse(Stack *stack, StackElement *variables, char *input) {
    enum parseState state = PARSING_NORMAL_TEXT;

    size_t input_length = strlen(input);

    char word[input_length];

    int current_word_index = 0;

    int bracket_count = 0;

    for (size_t i = 0; i < input_length + 1; ++i) {
        char current_char = input[i];

        word[current_word_index++] = current_char;

        if (state == PARSING_NORMAL_TEXT) {
            if (isspace(current_char) || current_char == '\0') {
                word[current_word_index - 1] = '\0';
                current_word_index = 0;

                if (*word) {
                    parse_word(stack, variables, word);
                }
            } else if (was_success_set_state_from_open_char(current_char, &state)) {
                bracket_count++;
            }
        } else {
            bracket_count = get_new_bracket_count(bracket_count, current_char,
                                                  get_open_char(state),
                                                  get_close_char(state));

            if (bracket_count <= 0) {
                state = PARSING_NORMAL_TEXT;
            }
        }
    }
}
