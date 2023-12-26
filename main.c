#include "matrizEsparsa.h"
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char ** argv){
    matrizEsparsaLC_t *A, *B, *C;
    FILE * arquivo;

    arquivo = fopen("./matrizes-teste/matriz1.txt", "r");
    matrizEsparsaLC_leMatrizTxt(&A, arquivo);
    // Imprime a matriz
    printf("Matriz A:\n");
    matrizEsparsaLC_imprime(A);
    fclose(arquivo);

   arquivo = fopen("./matrizes-teste/matriz2.txt", "r");
    matrizEsparsaLC_leMatrizTxt(&B, arquivo);
    // Imprime a matriz
    printf("Matriz B:\n");
    matrizEsparsaLC_imprime(B);
    fclose(arquivo);
    
    printf("Somando a matriz A e B e guardando em C:\n");
    matrizEsparsaLC_somaMatriz(A, B, &C);
    printf("Resultado da soma:\n");
    matrizEsparsaLC_imprime(C);

    matrizEsparsaLC_destroi(A);
    matrizEsparsaLC_destroi(B);
    matrizEsparsaLC_destroi(C);

   arquivo = fopen("./matrizes-teste/matriz3.txt", "r");
    matrizEsparsaLC_leMatrizTxt(&A, arquivo);
    // Imprime a matriz
    printf("Matriz A:\n");
    matrizEsparsaLC_imprime(A);
    fclose(arquivo);

   arquivo = fopen("./matrizes-teste/matriz4.txt", "r");
    matrizEsparsaLC_leMatrizTxt(&B, arquivo);
    // Imprime a matriz
    printf("Matriz B:\n");
    matrizEsparsaLC_imprime(B);
    fclose(arquivo);

    printf("Multiplicando a matriz A e B e guardando em C:\n");
    matrizEsparsaLC_multiplicaMatriz(A, B, &C);
    printf("Resultado da multiplicação:\n");
    matrizEsparsaLC_imprime(C);

    matrizEsparsaLC_destroi(A);
    matrizEsparsaLC_destroi(B);
    matrizEsparsaLC_destroi(C);

    return SUCESSO;
}