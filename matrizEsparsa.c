/**
 * @file matrizEsparsa.c
 * @brief Arquivo com a implementação do TAD Matriz Esparsa utilizando Listas Encadeadas
 * @author Bernardo Venancio
 * @date 2023-12-25
*/

/* Inclusões */
#include <stdlib.h>
#include <stdio.h>
#include "matrizEsparsa.h"

/* Constantes */
#define VALOR_COMUM 0

/* Tipos */
/// Tipo "Item de Matriz", estrutura com os membros de um item de uma matriz
typedef struct itemMatrizLC_s{
    struct itemMatrizLC_s * direita, * abaixo;
    int linha, coluna;
    double info;
} itemMatrizLC_t;

/* Funções auxiliares */

/**
 * @brief Função que inicializa os itens da matriz com valores adequados
 * @param item Apontador para o item que representa um dos heads da matriz
*/
static void matrizEsparsaLC_inicializaHeads(itemMatrizLC_t * item){
    item->direita = NULL;
    item->abaixo = NULL;
    item->info = INT32_MAX;
    item->coluna = -1;
    item->linha = -1;
}

/**
 * @brief Função que verifica se as dimensões de duas matrizes são compatíveis para soma
 * @param A Apontador para a matriz à esquerda na soma
 * @param B Apontador para a matriz à direita na soma
 * @return TRUE caso seja possível somar as duas matrizes, FALSE caso contrário
*/
static bool_t matrizEsparsaLC_compatibilidadeSoma(matrizEsparsaLC_t * A, matrizEsparsaLC_t * B){
    if(A->colunas != B->colunas || A->linhas != B->linhas){
        return FALSE;  
    }
    return TRUE;
}

/**
 * @brief Função que verifica se as dimensões de duas matrizes são compatíveis para multiplicação
 * @param A Apontador para a matriz à esquerda na multiplicação
 * @param B Apontador para a matriz à direita na multiplicação
 * @return TRUE caso seja possível multiplicar as duas matrizes, FALSE caso contrário
*/
static bool_t matrizEsparsaLC_compatibilidadeMultiplicacao(matrizEsparsaLC_t * A, matrizEsparsaLC_t * B){
    //Para poder multiplicar, uma matrix MxN precisa de uma matriz NxP {colunas da primeira = linhas da segunda} 
    if(A->colunas == B->linhas){
        return TRUE;
    }
    return FALSE;
}

/* Funções exportadas */

/**
 * @brief Função que cria e inicializa uma matriz esparsa com cabeçalhos sendo listas encadeadas circulares
 * @param linhas Número de linhas que a matriz terá
 * @param colunas Número de colunas que a matriz terá
 * @return Apontador para o local onde a matriz foi criada e armazenada
*/
matrizEsparsaLC_t * matrizEsparsaLC_cria(uint32_t linhas, uint32_t colunas){
    matrizEsparsaLC_t * matriz = (matrizEsparsaLC_t *)malloc(sizeof(matrizEsparsaLC_t));

    matriz->linhas = linhas;
    matriz->colunas = colunas;

    matriz->head = (itemMatrizLC_t *)malloc(sizeof(itemMatrizLC_t));
    matrizEsparsaLC_inicializaHeads(matriz->head);

    int i;

    itemMatrizLC_t * head = (itemMatrizLC_t *)matriz->head;

    itemMatrizLC_t * atual = head;
    for(i = 1; i <= linhas; i++){
        atual->abaixo = (itemMatrizLC_t *)malloc(sizeof(itemMatrizLC_t));
        matrizEsparsaLC_inicializaHeads(atual->abaixo);
        atual = atual->abaixo;
        atual->direita = atual;
    }
    //Faço a ligação circular
    atual->abaixo = head;

    atual = head;
    for(i = 1; i <= colunas; i++){
        atual->direita = (itemMatrizLC_t *)malloc(sizeof(itemMatrizLC_t));
        matrizEsparsaLC_inicializaHeads(atual->direita);
        atual = atual->direita;
        atual->abaixo = atual;
    }
    //Faço a ligação cicular
    atual->direita = head;

    //Retorno a matriz
    return matriz;
}

/**
 * @brief Função responsável por preencher uma matriz de acordo com entradas do usuário
 * @param matriz Apontador para a lista a ser modificada
*/
void leMatriz(matrizEsparsaLC_t * matriz){
    uint32_t opcao;
    do{
        printf("1 - Adicionar mais Elementos\n");
        printf("0 - Sair\n");
        scanf("%u", &opcao);

        switch(opcao){
            case 1 :
                printf("Digite a linha, coluna e o valor que deseja adicionar:\n");
                uint32_t linha, coluna;
                double valor;
                scanf("%u %u %lf", &linha, &coluna, &valor);
                erro_t adicionou = matrizEsparsaLC_adicionarElemento(matriz, linha, coluna, valor);
                if(adicionou != SUCESSO){
                    printf("Não foi possível adicionar\n");
                }
                break;
            case 0 :
                printf("Saindo\n");
                break;
            default:
                printf("Opcao invalida\n");
        }

    } while (opcao != 0);
}

/**
 * @brief Função que adiciona um elemento na posição especificada da matriz
 * @param matriz Apontador para a matriz a ser utilizada
 * @param linha Linha que o elemento deve ser adicionado. O valor deve estar entre
 *              [0...matriz->linhas]
 * @param coluna Coluna em que o elemento deve ser adicionado. O valor deve estar
 *               entre [0...matriz->colunas]
 * @param info Informação a ser inserida na matriz
 * @return SUCESSO caso o item seja inserido corretamente na lista, ou caso contrário,
 *         o código do erro
 * 
*/
erro_t matrizEsparsaLC_adicionarElemento(matrizEsparsaLC_t * matriz, uint32_t linha, uint32_t coluna, dadosItem info){
    if(linha > matriz->linhas || coluna > matriz->colunas){
        return ERRO_LISTA_POSICAO_INVALIDA;
    }

    itemMatrizLC_t * prevLinha, *prevColuna;
    itemMatrizLC_t * atual = (itemMatrizLC_t *)matriz->head;
    itemMatrizLC_t * headLinha, * headColuna;
    uint32_t i;
    
    //Inicializo headLinha e headColuna como sendo a primeira célula
    headLinha = (itemMatrizLC_t *)matriz->head;
    headColuna = (itemMatrizLC_t *)matriz->head;

    //Caminho até a linha cabeça
    for(i = 0; i < linha; i++){
        headLinha = headLinha->abaixo;
    }
    //Caminho até a coluna cabeça
    for(i = 0; i < coluna; i++){
        headColuna = headColuna->direita;
    }
 
    //Caminho até o elemento antecessor (ou o próprio) na linha
    atual = headLinha;
    do{
        prevColuna = atual;
        atual = atual->direita;
    } while(atual->coluna != -1 && coluna > atual->coluna);

    //Caminho até o elemento antecessor (ou o próprio) na coluna
    atual = headColuna;
    do{
        prevLinha = atual;
        atual = atual->abaixo;
    } while(atual->linha != -1 && linha > atual->linha);

    //Nesse caso, o elemento já existe
    if(atual->linha == linha && atual->coluna == coluna){
        //Se o novo valor for o valor que se repete na matriz, excluo o nó dele
        if(info == VALOR_COMUM){
            prevLinha->abaixo = atual->abaixo;
            prevColuna->direita = atual->direita;
            free(atual);
        }else{
            atual->info = info;
        }
        return SUCESSO;
    }

    //Caso o elemento ainda não exista e for o valor que se repete na matriz, basta retornar e não fazer nada
    if(info == VALOR_COMUM){
        return SUCESSO;
    }

    //Se chegou até aqui, essa posição da matriz ainda não existia, então crio e faço a ligacao  
    itemMatrizLC_t * novoItem = (itemMatrizLC_t *)malloc(sizeof(itemMatrizLC_t));
    novoItem->info = info;
    novoItem->coluna = coluna;
    novoItem->linha = linha;

    novoItem->abaixo = prevLinha->abaixo;
    prevLinha->abaixo = novoItem;

    novoItem->direita = prevColuna->direita;
    prevColuna->direita = novoItem;
    
    //Se chegou até aqui, o elemento foi adicionado com sucesso
    return SUCESSO;
}

/**
 * @brief Função que destroi a matriz liberando o espaço utilizado por seus itens
 *        e por ela mesma
 * @param matriz Apontador para a matriz a ser destruiída
*/
void matrizEsparsaLC_destroi(matrizEsparsaLC_t * matriz){
    itemMatrizLC_t * itemLinha = (itemMatrizLC_t *)matriz->head;
    itemMatrizLC_t * inicioLinha, * prev;
    uint32_t i;

    for(i = 0; i <= matriz->linhas; i++){
        itemMatrizLC_t * proximaLinha = itemLinha->abaixo;
        inicioLinha = itemLinha;
        itemLinha = itemLinha->direita;
        while(itemLinha != inicioLinha){
            prev = itemLinha;
            itemLinha = itemLinha->direita;
            free(prev);
        }
        free(inicioLinha);
        itemLinha = proximaLinha;
    }
    //Libera a memória alocada para a matriz
    free(matriz);
}

/**
 * @brief Função que imprime todos os itens da matriz
 * @param matriz Apontador para a matriz a ser utilizada
*/
void matrizEsparsaLC_imprime(matrizEsparsaLC_t * matriz){
    uint32_t i, j;
    itemMatrizLC_t * atual = (itemMatrizLC_t *)matriz->head;
    //Caminho até o primeiro elemento da matriz (linha : 1 Coluna : 1)
    atual = atual->abaixo->direita;
    for(i = 0; i < matriz->linhas; i++){
        for(j = 1; j <= matriz->colunas; j++){
            if(atual->coluna == j){
                printf("%.2lf\t", atual->info);
                atual = atual->direita;
            }else{
                printf("%d\t", VALOR_COMUM);
            }
        }
        atual = atual->abaixo->direita;
        printf("\n");
    }
}

/**
 * @brief Função que imprime uma determinada linha da matriz
 * @param matriz Apontador para a matriz a ser utilizada
 * @param linha Linha da matriz a ser imprimida
 * @return SUCESSO caso a matriz tenha a linha desejada, ou caso contrário,
 *         o código do erro
*/
erro_t matrizEsparsaLC_imprimeLinha(matrizEsparsaLC_t * matriz, uint32_t linha){
    if(linha > matriz->linhas){
        return ERRO_LISTA_POSICAO_INVALIDA;
    }

    itemMatrizLC_t * atual = (itemMatrizLC_t *)matriz->head;
    uint32_t i;
    //Caminho pelas linhas
    for(i = 0; i < linha; i++){
        atual = atual->abaixo;
    }

    atual = atual->direita;
    //Ao chegar aqui, atual irá representar primeira linha da matriz, então percorro as colunas
    for(i = 1; i <= matriz->colunas; i++){
        if(atual->coluna == i){
            printf("%.2lf\t", atual->info);
            atual = atual->direita;
        }else{
            printf("%d\t", VALOR_COMUM);
        }
    }
    printf("\n");
    return SUCESSO;
}

/**
 * @brief Função que imprime uma determinada coluna da matriz
 * @param matriz Apontador para a matriz a ser utilizada
 * @param coluna Coluna da matriz a ser imprimida
 * @return SUCESSO caso a matriz tenha a coluna desejada, ou caso contrário,
 *         o código do erro
*/
erro_t matrizEsparsaLC_imprimeColuna(matrizEsparsaLC_t * matriz, uint32_t coluna){
    if(coluna > matriz->colunas){
        return ERRO_LISTA_POSICAO_INVALIDA;
    }

    itemMatrizLC_t * atual = (itemMatrizLC_t *)matriz->head;
    uint32_t i;
    //Caminho pelas colunas
    for(i = 0; i < coluna; i++){
        atual = atual->direita;
    }

    atual = atual->abaixo;
    //Ao chegar aqui, atual irá representar a primeira coluna da matriz, então percorro as linhas
    for(i = 1; i <= matriz->linhas; i++){
        if(atual->linha == i){
            printf("%.2lf\n", atual->info);
            atual = atual->abaixo;
        }else{
            printf("%d\n", VALOR_COMUM);
        }
    }
    return SUCESSO;
}

/**
 * @brief Função que soma duas matrizes
 * @param A Apontador para a matriz utilizada à esquerda na soma
 * @param B Apontador para a matriz utilizada à direita na soma
 * @param C Endereço que receberá o resultado da soma das matrizes A e B
 * @return SUCESSO caso a soma tenha sido realizada, ou caso contrário,
 *         o código do erro
*/
erro_t matrizEsparsaLC_somaMatriz(matrizEsparsaLC_t * A, matrizEsparsaLC_t * B, matrizEsparsaLC_t ** C){
    //Se as entradas da matriz não forem compatíveis, retorno falso 
    if(matrizEsparsaLC_compatibilidadeSoma(A, B) == FALSE){
        *C = NULL;
        return ERRO_MATRIZ_SOMA_INCOMPATIVEL;
    }
    erro_t erro;

    //Caso a matriz seja compatível, aloco memória para a matriz C
    //Tanto A quanto B tem o mesmo número de linhas, então nao importa qual usar
    *C = matrizEsparsaLC_cria(A->linhas, A->colunas);

    uint32_t i, j;
    itemMatrizLC_t * elementoA = (itemMatrizLC_t *)A->head;
    itemMatrizLC_t * elementoB = (itemMatrizLC_t *)B->head;

    //Caminho até o primeiro elemento de cada matriz (linha : 1 Coluna : 1)
    elementoA = elementoA->abaixo->direita;
    elementoB = elementoB->abaixo->direita;

    //Obs: operador -> tem precedência maior que *, portanto para acessar C tem que usar (*C)->

    for(i = 1; i <= (*C)->linhas; i++){
        for(j = 1; j <= (*C)->colunas; j++){
            //Nesse caso, os dois elementos existem e são somados antes de adicionar
            if(elementoA->coluna == j && elementoB->coluna == j){
                erro = matrizEsparsaLC_adicionarElemento(*C, i, j, (elementoA->info + elementoB->info));
                if(erro != SUCESSO){
                    matrizEsparsaLC_destroi(*C);
                    return erro;
                }
                elementoA = elementoA->direita;
                elementoB = elementoB->direita;
            }
            //Caso não tenha em ambos, confiro se existe um elemento em cada um deles
            else if(elementoA->coluna == j){
                erro = matrizEsparsaLC_adicionarElemento(*C, i, j, elementoA->info);
                if(erro != SUCESSO){
                    matrizEsparsaLC_destroi(*C);
                    return erro;
                }                
                elementoA = elementoA->direita;
            }
            //Não posso usar else pois há a possibilidade de não ter em nenhum, nesse caso não faço nada
            else if(elementoB->coluna == j){
                erro = matrizEsparsaLC_adicionarElemento(*C, i, j, elementoB->info);
                if(erro != SUCESSO){
                    matrizEsparsaLC_destroi(*C);
                    return erro;
                }                
                elementoB = elementoB->direita;
            }
        }
        //'Desço' para a linha seguinte em ambas as matrizes
        elementoA = elementoA->abaixo->direita;
        elementoB = elementoB->abaixo->direita;
    }    

    //Se chegou até aqui, a matriz de soma foi criada com sucesso
    return SUCESSO;
}

/**
 * @brief Função que multiplica duas matrizes
 * @param A Apontador para a matriz utilizada à esquerda na multiplicação
 * @param B Apontador para a matriz utilizada à direita na multiplicação
 * @param C Endereço que receberá o resultado da multiplicação entre as matrizes
 *          A e B
 * @return SUCESSO caso a multiplicação tenha sido realizada, ou caso contrário,
 *         o código do erro
*/
erro_t matrizEsparsaLC_multiplicaMatriz(matrizEsparsaLC_t * A, matrizEsparsaLC_t * B, matrizEsparsaLC_t ** C){
    //Se as entradas das matrizes não forem compatíveis, retorno falso
    if(matrizEsparsaLC_compatibilidadeMultiplicacao(A, B) == FALSE){
        return ERRO_MATRIZ_MULTIPLICACAO_INCOMPATIVEL;
    }

    //Caso a matriz seja compatível, aloco memória para a matriz C
    //Amxn * Bnxp = Cmxp 
    *C = matrizEsparsaLC_cria(A->linhas, B->colunas);

    uint32_t i, j, k;
    itemMatrizLC_t * elementoA = (itemMatrizLC_t *)A->head;
    itemMatrizLC_t * elementoB = (itemMatrizLC_t *)B->head;

    //Guardo o head da linha de A e da coluna de B
    itemMatrizLC_t * inicioLinha = elementoA->abaixo;
    itemMatrizLC_t * inicioColuna = elementoB->direita;


    for(i = 1; i <= A->linhas; i++){
        //Caminho entre as linhas de A
        elementoA = inicioLinha->direita;

        for(j = 1; j <= B->colunas; j++){
            //Caminho na coluna B
            elementoB = inicioColuna->abaixo;
            dadosItem resultado = 0;
            for(k = 1; k <= A->colunas; k++){
                if(elementoA->coluna == k && elementoB->linha == k && elementoB->coluna == j){
                    resultado += elementoA->info * elementoB->info;
                    elementoA = elementoA->direita;
                    elementoB = elementoB->abaixo;
                } else{
                    if(elementoA->coluna == k){
                        elementoA = elementoA->direita;
                    }
                    if(elementoB->linha == k){
                        elementoB = elementoB->abaixo;
                    }
                }
            }
            //Se o resultado tiver o mesmo valor que o que se repete na matriz, apenas ignoro
            if(resultado != VALOR_COMUM){
                matrizEsparsaLC_adicionarElemento(*C, i, j, resultado);
            }
            
            elementoA = elementoA->direita;
            //Caminho para a próxima coluna
            inicioColuna = inicioColuna->direita;
        }
        //Atualizo o inicio de acordo com o que já foi percorrido
        inicioLinha = inicioLinha->abaixo;
        //Ao chegar aqui, inicioColuna vai estar no head da matriz, tenho que movê-la para o head da coluna 
        inicioColuna = inicioColuna->direita;
    }    

    return SUCESSO;
}