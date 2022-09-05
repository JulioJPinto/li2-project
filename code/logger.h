/**
 * @file logger.h
 * @brief Ficheiro utilitário para logs
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Se DEBUG_MODE for passado como parametro ao compilar, faz com que PRINT_DEBUG tenha significado
 */
#ifdef DEBUG_MODE
/**
 * Macro para printf, que só executa quando DEBUG_MODE foi passado como parametro
 */
#define PRINT_DEBUG(...) printf(__VA_ARGS__);
#else
#define PRINT_DEBUG(...)
#endif

/**
 * Macro para abortar o programa quando está num estado não suportado
 */
#define PANIC(...) { fprintf(stderr, "PANIC: "); fprintf(stderr, __VA_ARGS__); exit(EXIT_FAILURE); }
