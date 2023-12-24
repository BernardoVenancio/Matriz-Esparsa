#include "matrizEsparsa.h"
#include <stdlib.h>
#include <stdio.h>

#define SUCESSO 0

int main(int argc, char ** argv){
    uint32_t nLinhas = 3, nColunas = 3;

    matrizEsparsaLC_t * A = matrizEsparsaLC_cria(nLinhas, nColunas);
    matrizEsparsaLC_t * B = matrizEsparsaLC_cria(nLinhas, nColunas);
    matrizEsparsaLC_t * C;

    matrizEsparsaLC_adicionarElemento(A, 1, 2, 13);
    matrizEsparsaLC_adicionarElemento(A, 2, 1, 7);
    matrizEsparsaLC_adicionarElemento(A, 2, 2, 20);
    matrizEsparsaLC_adicionarElemento(A, 2, 2, 0);

    matrizEsparsaLC_adicionarElemento(B, 1, 2, 2);
    matrizEsparsaLC_adicionarElemento(B, 3, 1, 69);
    matrizEsparsaLC_adicionarElemento(B, 2, 2, 3);

    printf("Impressão matriz A:\n");
    matrizEsparsaLC_imprime(A);

    printf("Impressão matriz B:\n");
    matrizEsparsaLC_imprime(B);

    printf("Somando A e B e armazenando em C:\n");
    matrizEsparsaLC_somaMatriz(A, B, &C);
    printf("Impressão do resultado(C):\n");
    matrizEsparsaLC_imprime(C);

    matrizEsparsaLC_destroi(C);

    printf("Multiplicando A e B e armazenando em C:\n");
    matrizEsparsaLC_multiplicaMatriz(A, B, &C);
    printf("Impressão do resultado(C):\n");
    matrizEsparsaLC_imprime(C);

    matrizEsparsaLC_destroi(A);
    matrizEsparsaLC_destroi(B);
    matrizEsparsaLC_destroi(C);
    
    return SUCESSO;
}