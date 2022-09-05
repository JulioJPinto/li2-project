/**
 * @file operations.c
 * @brief Implementação das operações matemáticas
 */

#include "logger.h"
#include "operations.h"
#include "conversions.h"
#include <math.h>
#include <string.h>

/** Tamanho em bytes do buffer das operações de ler input do terminal */
#define READ_INPUT_FROM_CONSOLE_MAX_LENGTH 10001

double get_element_as_double(StackElement *element) {
    ElementType type = element->type;
    if (type == DOUBLE_TYPE) {
        return element->content.double_value;
    } else if (type == LONG_TYPE) {
        return (double) element->content.long_value;
    } else if (type == CHAR_TYPE) {
        return (double) element->content.char_value;
    } else {
        PANIC("Trying to get double value from non-number element (type: %d)", type)
    }
}

long get_element_as_long(StackElement *element) {
    ElementType type = element->type;
    if (type == DOUBLE_TYPE) {
        return (long) element->content.double_value;
    } else if (type == LONG_TYPE) {
        return element->content.long_value;
    } else if (type == CHAR_TYPE) {
        return (long) element->content.char_value;
    } else {
        PANIC("Trying to get long value from non-number element (type: %d)", type)
    }
}

/**
 * @brief Converte um elemento para um array.
 * Caso o elemento seja um array, retorna simplesmente o seu conteudo, caso contrário cria um array apenas com o elemento inserido.
 * @param element O elemento para converter
 * @return A array do elemento
 */
static Stack *get_element_as_array(StackElement *element) {
    ElementType type = element->type;
    if (type == ARRAY_TYPE) {
        return element->content.array_value;
    }

    Stack *new_array = create_stack(1);
    push(new_array, *element);

    return new_array;
}

/**
 * @brief Função que recebe a stack e dois apontadores para as funções do tipo númericas dos operadores.
 * @param stack A stack que contem os elementos.
 * @param double_operation_function_pointer Apontador para a função do tipo double.
 * @param long_operation_function_pointer Apontador para a função do tipo long.
 */
void operate_promoting_number_type(Stack *stack,
                                   void (*double_operation_function_pointer)(Stack *, double, double),
                                   void (*long_operation_function_pointer)(Stack *, long, long)) {
    StackElement y = pop(stack);
    StackElement x = pop(stack);

    ElementType x_type = x.type;
    ElementType y_type = y.type;

    if (x_type == DOUBLE_TYPE || y_type == DOUBLE_TYPE) {
        double_operation_function_pointer(stack, get_element_as_double(&x), get_element_as_double(&y));
    } else if (x_type == LONG_TYPE || y_type == LONG_TYPE) {
        long_operation_function_pointer(stack, get_element_as_long(&x), get_element_as_long(&y));
    } else {
        PANIC("Trying to operate non number elements. (x_type: %d, y_type: %d)", x_type, y_type)
    }

    free_element(y);
    free_element(x);
}

/**
 * @brief Operação de adicionar dois arrays/elementos num array
 * @param stack Stack para adicionar o novo array
 * @param a Primeiro elemento/array
 * @param b Segundo elemento/array
 */
void add_array_operation(Stack *stack, StackElement *a, StackElement *b) {
    Stack *a_array = get_element_as_array(a);
    Stack *b_array = get_element_as_array(b);

    for (int i = 0; i < length(b_array); ++i) {
        push(a_array, duplicate_element(b_array->array[i]));
    }

    push_array(stack, a_array);

    free_element(*b);
}

/**
 * @brief Retorna o número de bytes necessários para converter o elemento para string.
 * Caso o elemento seja string, retorna o tamanho da string + 1, caso contrário retorna MAX_CONVERT_TO_STRING_SIZE
 * @param element elemento para calcular
 * @return O número de bytes
 */
static long get_max_string_size(StackElement *element) {
    if (element->type == STRING_TYPE) return (long) strlen(element->content.string_value) + 1;
    return MAX_CONVERT_TO_STRING_SIZE;
}

/**
 * @brief Operação de concatenar duas strings/elementos convertidos para string
 * @param stack Stack para colocar a string concatenada
 * @param a O primeiro elemento/string
 * @param b O segundo elemento/string
 */
void add_string_operation(Stack *stack, StackElement *a, StackElement *b) {
    long max_a_size = get_max_string_size(a);
    char a_string[max_a_size];
    long max_b_size = get_max_string_size(b);
    char b_string[max_b_size];

    convert_element_to_string(a, a_string);
    convert_element_to_string(b, b_string);

    size_t a_length = strlen(a_string);
    size_t b_length = strlen(b_string);

    char *concat = calloc(a_length + b_length + 1, sizeof(char));

    memcpy(concat, a_string, a_length);
    memcpy(concat + a_length, b_string, b_length + 1);

    push_string(stack, concat);

    free(concat);
    free_element(*a);
    free_element(*b);
}

/**
 * @brief Operação de adicionar dois doubles
 * @param stack Stack colocar o resultado
 * @param a Primeiro double
 * @param b Segundo double
 */
void add_double_operation(Stack *stack, double a, double b) {
    push_double(stack, a + b);
}

/**
 * @brief Operação de adicionar dois inteiros
 * @param stack Stack colocar o resultado
 * @param a Primeiro long
 * @param b Segundo long
 */
void add_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a + b);
}

/**
 * @brief Operação de adicionar dois caracteres
 * @param stack Stack colocar o resultado
 * @param a Primeiro char
 * @param b Segundo char
 */
void add_char_operation(Stack *stack, char a, char b) {
    push_long(stack, a + b);
}

/**
 * Retorna 1 se @param{a} ou @param{b} é do tipo @param{type}, 0 caso os dois diferentes de @param{type}
 * @param type O tipo para corresponder
 * @param a O primeiro elemento
 * @param b O segundo elemento
 * @return 1 se algum dos dois é do tal tipo, 0 caso contrário
 */
int any_element_is_type(ElementType type, StackElement a, StackElement b) {
    return a.type == type || b.type == type;
}

void add_operation(Stack *stack) {
    StackElement x = pop(stack);
    StackElement y = pop(stack);

    if (any_element_is_type(ARRAY_TYPE, x, y)) {
        add_array_operation(stack, &y, &x);
    } else if (any_element_is_type(STRING_TYPE, x, y)) {
        add_string_operation(stack, &y, &x);
    } else if (any_element_is_type(DOUBLE_TYPE, x, y)) {
        add_double_operation(stack, get_element_as_double(&y), get_element_as_double(&x));
    } else if (any_element_is_type(LONG_TYPE, x, y)) {
        add_long_operation(stack, get_element_as_long(&y), get_element_as_long(&x));
    } else if (any_element_is_type(CHAR_TYPE, x, y)) {
        add_char_operation(stack, convert_element_to_char(&y), convert_element_to_char(&x));
    } else {
        PANIC("Couldn't find add operation for types x=%d, y=%d", x.type, y.type)
    }
}

/**
 * \brief Nesta função fazemos a diferença dos dois ultimos números na stack do tipo double.
 */
void minus_double_operation(Stack *stack, double a, double b) {
    push_double(stack, a - b);
}

/**
 * \brief Nesta função fazemos a diferença dos dois ultimos números na stack do tipo long.
 */
void minus_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a - b);
}

/**
 * \brief Nesta função fazemos a diferença dos dois ultimos números na stack.
 */
void minus_operation(Stack *stack) {
    operate_promoting_number_type(stack, minus_double_operation, minus_long_operation);
}

/**
 * \brief Nesta função fazemos o produto dos dois ultimos números na stack do tipo double.
 */
void mult_double_operation(Stack *stack, double a, double b) {
    push_double(stack, a * b);
}

/**
 * \brief Nesta função fazemos o produto dos dois ultimos números na stack do tipo long.
 */
void mult_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a * b);
}

/**
 * \brief Nesta função fazemos o produto dos dois ultimos números na stack.
 */
void mult_operation(Stack *stack) {
    operate_promoting_number_type(stack, mult_double_operation, mult_long_operation);
}

/**
 * \brief Nesta função fazemos a divisão do número último número da stack pelo penúltimo número da stack do long.
 */
void div_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a / b);
}

/**
 * \brief Nesta função fazemos a divisão do número último número da stack pelo penúltimo número da stack do double.
 */
void div_double_operation(Stack *stack, double a, double b) {
    push_double(stack, a / b);
}

/**
 * \brief Nesta função fazemos a divisão do número último número da stack pelo penúltimo número da stack.
 */
void div_operation(Stack *stack) {
    operate_promoting_number_type(stack, div_double_operation, div_long_operation);
}

/**
 * \brief Nesta função retiramos ao ultimo número da stack um.
 */
void decrement_operation(Stack *stack) {
    StackElement element = pop(stack);

    if (element.type == DOUBLE_TYPE) {
        push_double(stack, element.content.double_value - 1);
    } else if (element.type == LONG_TYPE) {
        push_long(stack, element.content.long_value - 1);
    } else if (element.type == CHAR_TYPE) {
        push_char(stack, (char) (element.content.char_value - 1));
    } else {
        PANIC("Trying to decrement non number element. (type: %d)", element.type)
    }

    free_element(element);
}

/**
 * \brief Nesta função adicionamos ao ultimo número da stack um.
 */
void increment_operation(Stack *stack) {
    StackElement element = pop(stack);

    if (element.type == DOUBLE_TYPE) {
        push_double(stack, element.content.double_value + 1);
    } else if (element.type == LONG_TYPE) {
        push_long(stack, element.content.long_value + 1);
    } else if (element.type == CHAR_TYPE) {
        push_char(stack, (char) (element.content.char_value + 1));
    } else {
        PANIC("Trying to increment non number element. (type: %d)", element.type)
    }

    free_element(element);
}

/**
 * \brief Nesta função retornamos o módulo do ultimo número da stack.
 */
void modulo_operation(Stack *stack) {
    long x = pop_long(stack);
    long y = pop_long(stack);

    push_long(stack, y % x);
}

/**
 * \brief Nesta função retornamos o expoente do número no topo da stack um do tipo double.
 */
void exponential_double_operation(Stack *stack, double a, double b) {
    push_double(stack, pow(a, b));
}

/**
 * \brief Nesta função retornamos o módulo do número no topo da stack um do tipo long.
 */
void exponential_long_operation(Stack *stack, long a, long b) {
    push_long(stack, (long) pow((double) a, (double) b));
}

/**
 * \brief Nesta função retornamos o módulo do número no topo da stack um.
 */
void exponential_operation(Stack *stack) {
    operate_promoting_number_type(stack, exponential_double_operation, exponential_long_operation);
}

/**
 * \brief Nesta função devolvemos a disjunção dos dois últimos números da stack.
 */
void and_bitwise_operation(Stack *stack) {
    long x = pop_long(stack);
    long y = pop_long(stack);

    push_long(stack, x & y);
}

/**
 * \brief Nesta função devolvemos a conjunção dos dois últimos números da stack.
 */
void or_bitwise_operation(Stack *stack) {
    long x = pop_long(stack);
    long y = pop_long(stack);

    push_long(stack, x | y);
}

/**
 * \brief Nesta função devolvemos a realizamos o xor dos dois últimos números da stack.
 */
void xor_bitwise_operation(Stack *stack) {
    long x = pop_long(stack);
    long y = pop_long(stack);

    push_long(stack, x ^ y);
}

/**
 * \brief Nesta função devolvemos a negação do número no topo da stack.
 */
void not_bitwise_operation(Stack *stack) {
    long x = pop_long(stack);

    push_long(stack, ~x);
}

/**
 * \brief Nesta função duplicamos o que se encontra na stack.
 */
void duplicate_operation(Stack *stack) {
    push(stack, duplicate_element(peek(stack)));
}

/**
 * \brief Nesta função retiramos o valor que se encontra no topo da stack da mesma.
 */
void pop_operation(Stack *stack) {
    free_element(pop(stack));
}

/**
 * \brief Nesta função trocamos a ordem dos ultimos dois elementos da stack.
 */
void swap_last_two_operation(Stack *stack) {
    StackElement x1 = pop(stack);
    StackElement x2 = pop(stack);

    push(stack, x1);
    push(stack, x2);
}

/**
 * \brief Nesta função trocamos a ordem dos ultimos três elementos da stack.
 */
void rotate_last_three_operation(Stack *stack) {
    StackElement x1 = pop(stack);
    StackElement x2 = pop(stack);
    StackElement x3 = pop(stack);

    push(stack, x2);
    push(stack, x1);
    push(stack, x3);
}

/**
 * \brief Nesta função copiamos o valor da posição n para o topo da stack.
 */
void copy_nth_element_operation(Stack *stack) {
    long index = pop_long(stack);

    push(stack, get(stack, index));
}

/**
 * \brief Nesta função lemos o input inserido na consola
 */
void read_input_from_console_operation(Stack *stack) {
    char input[READ_INPUT_FROM_CONSOLE_MAX_LENGTH];
    if (fgets(input, READ_INPUT_FROM_CONSOLE_MAX_LENGTH, stdin) == NULL) {
        PANIC("Couldn't read input operation from console: fgets returned null pointer\n")
    }

    // fgets returns string ending in \n\0
    // temos que filtrar o \n
    size_t length = strlen(input);
    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';
    }
    push_string(stack, input);
}

void read_all_input_from_console_operation(Stack *stack) {
    char *input = calloc(READ_INPUT_FROM_CONSOLE_MAX_LENGTH, sizeof(char));
    char *current_line = calloc(READ_INPUT_FROM_CONSOLE_MAX_LENGTH, sizeof(char));

    while (fgets(current_line, READ_INPUT_FROM_CONSOLE_MAX_LENGTH, stdin) != NULL && strlen(current_line) > 1) {
        strcat(input, current_line);
    }

    push_string(stack, input);

    free(input);
    free(current_line);
}

void print_stack_top_operation(Stack *stack) {
    StackElement element = peek(stack);
    dump_element(&element);
    printf("\n");
}
