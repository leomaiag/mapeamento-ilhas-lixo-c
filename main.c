#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_MAX 100

int matriz_lixo[TAMANHO_MAX][TAMANHO_MAX];
int visitado[TAMANHO_MAX][TAMANHO_MAX];

int linhas, colunas;

int explora_e_soma_ilha(int i, int j){
    if (i < 0 || i >= linhas || j < 0 || j >= colunas)
        return 0;
    if (visitado[i][j] == 1 || matriz_lixo[i][j] == 0)
        return 0;

    visitado[i][j] = 1;
    int soma = matriz_lixo[i][j];

    soma += explora_e_soma_ilha(i + 1, j);
    soma += explora_e_soma_ilha(i - 1, j);
    soma += explora_e_soma_ilha(i, j + 1);
    soma += explora_e_soma_ilha(i, j - 1);

    return soma;
}

int acha_combinacao(int alvo, int *profundidades, int num_profundidades, int *solucao, int *tam_solucao, int indice_atual){
    if (alvo == 0)
        return 1;
    if (alvo < 0 || indice_atual >= num_profundidades)
        return 0;

    solucao[*tam_solucao] = profundidades[indice_atual];
    (*tam_solucao)++;
    if (acha_combinacao(alvo - profundidades[indice_atual], profundidades, num_profundidades, solucao, tam_solucao, indice_atual + 1))
        return 1;

    (*tam_solucao)--;

    if (acha_combinacao(alvo, profundidades, num_profundidades, solucao, tam_solucao, indice_atual + 1))
        return 1;

    return 0;
}

int comparar_desc(const void *a, const void *b){
    return (*(int*)b - *(int*)a);
}

int main(int argc, char *argv[]){
    if (argc != 5) {
        printf("Uso: ./EP1 <profundidade_container> <linhas> <colunas> <arquivo.txt>\n");
        return 1;
    }

    int prof_container = atoi(argv[1]);
    linhas = atoi(argv[2]);
    colunas = atoi(argv[3]);
    char *nome_arquivo = argv[4];

    if (linhas > TAMANHO_MAX || colunas > TAMANHO_MAX){
        printf("Erro: A matriz e muito grande. Maximo: %dx%d\n", TAMANHO_MAX, TAMANHO_MAX);
        return 1;
    }

    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro: Nao foi possivel abrir o arquivo %s\n", nome_arquivo);
        return 1;
    }

    for (int i = 0; i < linhas; i++){
        for (int j = 0; j < colunas; j++){
            if (fscanf(arquivo, "%d", &matriz_lixo[i][j]) != 1){
                printf("Erro de formatacao no arquivo.\n");
                fclose(arquivo);
                return 1;
            }
        }
    }
    fclose(arquivo);

    int profundidades_ilhas[TAMANHO_MAX];
    int num_ilhas = 0;

    for (int i = 0; i < linhas; i++){
        for (int j = 0; j < colunas; j++){
            if (matriz_lixo[i][j] > 0 && visitado[i][j] == 0){
                int soma = explora_e_soma_ilha(i, j);
                int profundidade = soma / 6;
                if (soma > 0 && profundidade == 0)
                    profundidade = 1;
                profundidades_ilhas[num_ilhas++] = profundidade;
            }
        }
    }

    //imprimir num de ilha
    printf("%d\n", num_ilhas);

    //imprime as profundidades
    for (int i = 0; i < num_ilhas; i++)
        printf("%d%s", profundidades_ilhas[i], (i == num_ilhas - 1) ? "" : "");
    printf("\n");

    //exemplo 1 tinha dado ao contrario
    qsort(profundidades_ilhas, num_ilhas, sizeof(int), comparar_desc);

    int solucao[TAMANHO_MAX];
    int tam_solucao = 0;

    if (acha_combinacao(prof_container, profundidades_ilhas, num_ilhas, solucao, &tam_solucao, 0)){
        for (int i = 0; i < tam_solucao; i++)
            printf("%d%s", solucao[i], (i == tam_solucao - 1) ? "" : "");
        printf("\n");
    } else {
        printf("Nao ha resposta valida!\n");
    }

    return 0;
}
