#ifndef MATRIZ_ESPARSA_H
#define MATRIZ_ESPARSA_H
#include "tipos.h"
#include "lista.h"

typedef struct matrizEsparsaLC_s{
    void * head;
    uint32_t linhas, colunas;
} matrizEsparsaLC_t;

matrizEsparsaLC_t * matrizEsparsaLC_cria(uint32_t linhas, uint32_t colunas);
void leMatriz(matrizEsparsaLC_t * matriz);
bool_t matrizEsparsaLC_adicionarElemento(matrizEsparsaLC_t * matriz, uint32_t linha, uint32_t coluna, dadosItem info);
void matrizEsparsaLC_destroi(matrizEsparsaLC_t * matriz);
void matrizEsparsaLC_imprime(matrizEsparsaLC_t * matriz);
void matrizEsparsaLC_imprimeLinha(matrizEsparsaLC_t * matriz, uint32_t linha);
void matrizEsparsaLC_imprimeColuna(matrizEsparsaLC_t * matriz, uint32_t coluna);
bool_t matrizEsparsaLC_somaMatriz(matrizEsparsaLC_t * matrizA, matrizEsparsaLC_t * matrizB, matrizEsparsaLC_t ** matrizC);
bool_t matrizEsparsaLC_multiplicaMatriz(matrizEsparsaLC_t * matrizA, matrizEsparsaLC_t * matrizB, matrizEsparsaLC_t ** matrizC);

#endif