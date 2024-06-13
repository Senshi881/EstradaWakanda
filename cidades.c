#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"

void inserirCidade(Cidade **lista, const char *nome, int posicao) {
    Cidade *novaCidade = (Cidade *)malloc(sizeof(Cidade));
    if (!novaCidade) {
        perror("\n*ERRO EM ALOCAR MEMORIA*");
        return;
    }
    strcpy(novaCidade->Nome, nome);
    novaCidade->Posicao = posicao;
    novaCidade->prox = *lista;
    *lista = novaCidade;
}

Estrada *getEstrada(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        perror("\n*ERRO EM ABRIR ARQUIVO*");
        return NULL;
    }

    Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
    if (!estrada) {
        perror("\n*ERRO EM ALOCAR MEMORIA*");
        fclose(arquivo);
        return NULL;
    }

    fscanf(arquivo, "%d %d", &estrada->N, &estrada->T);

    estrada->C = (Cidade *)malloc(estrada->N * sizeof(Cidade));
    if (!estrada->C) {
        perror("\n*ERRO EM ALOCAR MEMORIA*");
        fclose(arquivo);
        free(estrada);
        return NULL;
    }

    for (int i = 0; i < estrada->N; i++) {
        fscanf(arquivo, "%s %d", estrada->C[i].Nome, &estrada->C[i].Posicao);
    }

    fclose(arquivo);
    return estrada;
}

double calcularMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (estrada == NULL) {
        return -1.0;
    }

    double menorVizinhanca = estrada->T;

    for (int i = 0; i < estrada->N - 1; i++) {
        double vizinhanca = (estrada->C[i + 1].Posicao - estrada->C[i].Posicao) / 2.0;
        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
        }
    }

    free(estrada->C);
    free(estrada);

    return menorVizinhanca;
}

char *cidadeMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (estrada == NULL) {
        return NULL;
    }

    int indiceMenorVizinhanca = 0;
    double menorVizinhanca = estrada->T;

    for (int i = 0; i < estrada->N - 1; i++) {
        double vizinhanca = (estrada->C[i + 1].Posicao - estrada->C[i].Posicao) / 2.0;
        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
            indiceMenorVizinhanca = i;
        }
    }

    char *nomeCidade = strdup(estrada->C[indiceMenorVizinhanca].Nome);

    free(estrada->C);
    free(estrada);

    return nomeCidade;
}
