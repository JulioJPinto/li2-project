/**
 * @file operations_storage.h
 * @brief Responsável por guardar as operações possíveis na stack
 */

#include "stack.h"

/**
 * @brief Operação de quando apenas precisa de receber stack como parametro
 */
typedef void (*StackOperationFunction)(Stack *);

/**
 * @brief Operação de quando precisa de receber a stack e as variáveis globais como parametro
 */
typedef void (*StackOperationVariablesFunction)(Stack *, StackElement *);

/**
 * @brief Tipos de operações possíveis (Operação recebe variaveis globais ou não)
 */
typedef enum {
    /** @brief Recebe apenas a stack como parametro */
    SIMPLE_OPERATION,
    /** @brief Recebe a stack e as variáveis globais como parametro */
    VARIABLES_OPERATION
} OperationType;

/**
 * @brief Struct para guardar informação sobre a função da operação
 */
typedef struct {
    /** @brief Tipo da operação */
    OperationType type;
    /** @brief Union dos possíveis tipos de operaçã */
    union {
        /** @brief Pointer para função que recebe apenas stack como parametro */
        StackOperationFunction operation_function;
        /** @brief Pointer para função que recebe stack e variáveis globais como parametro */
        StackOperationVariablesFunction variables_operation;
    };
} StackOperation;

/**
 * @brief Struct para juntar o operador e a operação num só
 */
typedef struct {
    /** @brief Operador string */
    char operator[5];
    /** @brief Operação */
    StackOperation operation;
} StackOperationTableEntry;

/**
 * @brief Procura a correspondente operação StackOperation do @param{op} operador.
 * @brief Caso o operador não tenha correspondente operação o programa irá abortar.
 */
StackOperation get_operation(char op[]);

/**
 * @brief Executa a operação pretendida na stack
 * @param operation A operação
 * @param stack A stack target
 * @param variables Variáveis globais (usadas apenas se necessárias)
 */
void execute_operation(StackOperation operation, Stack *stack, StackElement *variables);
