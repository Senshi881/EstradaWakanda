/*
    gcc -o cidades main.c cidades.c
    ./cidades
*/
#include <stdio.h>
#include <stdlib.h>
#include "cidades.h"

int main() {
    char nomeArquivo[100];

    printf("Digite o nome do arquivo de entrada: ");
    scanf("%s", nomeArquivo);

    double menorVizinhanca = calcularMenorVizinhanca(nomeArquivo);
    if (menorVizinhanca >= 0) {
        printf("\nMenor vizinhanca: %.2f", menorVizinhanca);
    } else {
        printf("\n*ERRO AO CALCULAR MENOR VIZINHANCA*");
    }

    char *cidade = cidadeMenorVizinhanca(nomeArquivo);
    if (cidade != NULL) {
        printf("\nCidade com a menor vizinhanca: %s", cidade);
        free(cidade);
    } else {
        printf("\n*ERRO AO ENCONTRAR A CIDADE COM A MENOR VIZINHANCA*");
    }

    return 0;
}
