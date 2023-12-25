/** 
 * @file lista.h
 * @brief Arquivo com as definições comuns a todos os tipos de lista
 * @author Bernardo Venancio 
 * @date 2023-12-25
*/

#ifndef LISTA_H
#define LISTA_H

/* Inclusões */

/* Constantes */

/// Número máximo de erros de lista permitidos
#define LISTA_ERROS_MAXIMO (16)
///Valor inicial a partir dos quais os erros de lista aparecem
#define LISTA_ERROS_OFFSET (16) // [0x10:0x1F] / [16-31]

/* Erros */
#define ERRO_LISTA_POSICAO_INVALIDA (LISTA_ERROS_OFFSET + 0)

/// Tipo que representa os dados armazenados no item da lista
typedef double dadosItem;

#endif