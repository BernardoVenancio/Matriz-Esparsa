/**
 * @file tipos.h
 * @brief Arquivo com a definição de tipos globais
 * @author Bernardo Venancio
 * @date 2023-12-25
*/

#ifndef TIPOS_H
#define TIPOS_H

/* Inclusões */
#include <stdint.h>

/// Definição de verdadeiro e falso
#define TRUE (1 == 1)
#define FALSE !TRUE

/// Representação de um tipo booleano
typedef uint8_t bool_t;

/// Representação de um tipo que armazena um código de erro
typedef uint8_t erro_t;

#endif