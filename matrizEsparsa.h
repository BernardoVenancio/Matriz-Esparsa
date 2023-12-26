/**
 * @file matrizEsparsa.h
 * @brief Arquivo com a definição dos tipos e funções relacionadas a matrizes esparsas
 *        representados com Listas Encadeadas
 * @author Bernardo Venancio
 * @date 2023-12-25
*/

#ifndef MATRIZ_ESPARSA_H
#define MATRIZ_ESPARSA_H

/* Inclusões */
#include <stdio.h>
#include "tipos.h"
#include "lista.h"
#include "erros.h"

/* Tipos */
/// Estrutura com as informações de uma matriz
typedef struct matrizEsparsaLC_s{
    void * head;
    uint32_t linhas, colunas;
} matrizEsparsaLC_t;

/* Constantes */
/// Número máximo de erros de matriz esparsa permitidos
#define MATRIZ_ERROS_MAXIMO (16)
/// Valor inicial a partir dos quais os erros de matriz aparecem
#define MATRIZ_ERROS_OFFSET (32) // [0x20:0x2F] / [32-47]

/* Erros */
#define ERRO_MATRIZ_SOMA_INCOMPATIVEL (MATRIZ_ERROS_OFFSET + 0)
#define ERRO_MATRIZ_MULTIPLICACAO_INCOMPATIVEL (MATRIZ_ERROS_OFFSET + 1)


/* Funções Exportadas */
matrizEsparsaLC_t * matrizEsparsaLC_cria(uint32_t linhas, uint32_t colunas);
void matrizEsparsaLC_leMatriz(matrizEsparsaLC_t * matriz);
void matrizEsparsaLC_leMatrizTxt(matrizEsparsaLC_t ** matriz, FILE * arquivo);
erro_t matrizEsparsaLC_adicionarElemento(matrizEsparsaLC_t * matriz, uint32_t linha, uint32_t coluna, dadosItem info);
void matrizEsparsaLC_destroi(matrizEsparsaLC_t * matriz);
void matrizEsparsaLC_imprime(matrizEsparsaLC_t * matriz);
erro_t matrizEsparsaLC_imprimeLinha(matrizEsparsaLC_t * matriz, uint32_t linha);
erro_t matrizEsparsaLC_imprimeColuna(matrizEsparsaLC_t * matriz, uint32_t coluna);
erro_t matrizEsparsaLC_somaMatriz(matrizEsparsaLC_t * matrizA, matrizEsparsaLC_t * matrizB, matrizEsparsaLC_t ** matrizC);
erro_t matrizEsparsaLC_multiplicaMatriz(matrizEsparsaLC_t * matrizA, matrizEsparsaLC_t * matrizB, matrizEsparsaLC_t ** matrizC);

#endif