/**
 * @file stack.h
 * @brief Funções sobre stacks
 */

#pragma once

/**
 * @brief Enum dos tipos de elementos existentes
 */
typedef enum {
    /** Tipo double */
    DOUBLE_TYPE,
    /** Tipo inteiro */
    LONG_TYPE,
    /** Tipo caractere */
    CHAR_TYPE,
    /** Tipo string */
    STRING_TYPE,
    /** Tipo array */
    ARRAY_TYPE,
    /** Tipo bloco */
    BLOCK_TYPE
} ElementType;

/**
 * Struct da stack
 */
typedef struct stack Stack;

/**
 * Struct de um elemento da stack
 */
typedef struct {
    /** Tipo do elemento */
    ElementType type;
    /** Union do conteudo do elemento */
    union {
        /** Valor double */
        double double_value;
        /** Valor inteiro */
        long long_value;
        /** Valor caractere */
        char char_value;
        /** Valor string */
        char *string_value;
        /** Valor array */
        Stack *array_value;
        /** Valor bloco */
        char *block_value;
    } content;
} StackElement;

/**
 * Definição do struct da stack com implementação de array dinâmica
 */
typedef struct stack {
    /** Capacidade atual da stack */
    int capacity;
    /** Indice do último elemento adicionado (Começa em -1) */
    int current_index;
    /** Array dos elementos */
    StackElement *array;
} Stack;

/**
 * Cria e aloca uma stack na memória
 * @param initial_capacity capacidade incial
 * @return Um pointer para a stack
 */
Stack *create_stack(int initial_capacity);

/**
 * Libera a memória ocupada pela stack
 * @param stack
 */
void free_stack(Stack *stack);

/**
 * Faz print de todos os elementos da stack
 * @param stack target
 */
void dump_stack(Stack *stack);

/**
 * Faz print de um elemento
 * @param element target
 */
void dump_element(StackElement *element);

/**
 * Calcula o tamanho do stack
 * @param stack target
 * @return tamanho
 */
int length(Stack *stack);

/**
 * Remove e retorna o último elemento adicionado à stack
 * @param stack target
 * @return O elemento da stack
 */
StackElement pop(Stack *stack);

/**
 * Faz pop da stack e converte o valor para long
 * @param stack target
 * @return O valor do long
 */
long pop_long(Stack *stack);

/**
 * Faz push a um StackElement para a @param{stack}
 * @param stack target
 * @param x StackElement para adicionar
 */
void push(Stack *stack, StackElement x);

/**
 * Faz push de todos os elementos (faz uma cópia deles) de uma stack para a @param{stack}
 * @param stack target
 * @param elements elementos para adicionar
 */
void push_all(Stack *stack, Stack *elements);

/**
 * Faz push de um double para a @param{stack}
 * @param stack target
 * @param value valor double
 */
void push_double(Stack *stack, double value);

/**
 * Faz push de um long para a @param{stack}
 * @param stack target
 * @param value valor long
 */
void push_long(Stack *stack, long value);

/**
 * Faz push de um char para a @param{stack}
 * @param stack target
 * @param value valor char
 */
void push_char(Stack *stack, char value);

/**
 * Faz push de uma string para a @param{stack}
 * @param stack target
 * @param value valor string
 */
void push_string(Stack *stack, char *value);

/**
 * Faz push de uma array para a @param{stack}
 * @param stack target
 * @param value valor array
 */
void push_array(Stack *stack, Stack *value);

/**
 * Faz push de um bloco para a @param{stack}
 * @param stack target
 * @param value valor bloco
 */
void push_block(Stack *stack, char *value);

/**
 * @param stack target
 * @return O ultimo elemento adicionado à stack sem o remover
 */
StackElement peek(Stack *stack);

/**
 * Retorna o elemento da stack que está no indice @param{index}
 * O indice 0 é o ultimo elemento adicionado.
 * @param stack target
 * @param index indice
 * @return O elemento do indice
 */
StackElement get(Stack *stack, long index);

/**
 * Cria um elemento do tipo double.
 * @param value double
 * @return O elemento criado
 */
StackElement create_double_element(double value);

/**
 * Cria um elemento do tipo long.
 * @param value long
 * @return O elemento criado
 */
StackElement create_long_element(long value);

/**
 * Cria um elemento do tipo char.
 * @param value char
 * @return O elemento criado
 */
StackElement create_char_element(char value);

/**
 * Cria um elemento do tipo string.
 * É feito uma copia do @param{value}.
 * @param value string
 * @return O elemento criado
 */
StackElement create_string_element(char *value);

/**
 * Cria um elemento do tipo array.
 * @param value array
 * @return O elemento criado
 */
StackElement create_array_element(Stack *value);

/**
 * Cria um elemento do tipo bloco.
 * É feito uma copia do @param{value}.
 * @param value bloco
 * @return O elemento criado
 */
StackElement create_block_element(char *value);

/**
 * Verifica o valor booleano de um elemento
 * @param a o elemento
 * @return O valor booleano
 */
int is_truthy(StackElement *a);

/**
 * Liberta a memória de um elemento
 * @param element elemento para dar free
 */
void free_element(StackElement element);

/**
 * Deep copy de um elemento
 * @param element elemento a ser copiado
 * @return O elemento deep copied
 */
StackElement duplicate_element(StackElement element);

/**
 * Deep copy de arrays
 * @param element elemento array a ser copiado
 * @return A array deep copied
 */
StackElement duplicate_array(StackElement element);
