#ifndef CIDADES_H
#define CIDADES_H

typedef struct Cidade {
    char nome[50];
    double distancia;
    struct Cidade *prox;
} Cidade;

void inserirCidade(Cidade **lista, const char *nome, double distancia);
double calcularMenorVizinhanca(const char *nomeArquivo, double comprimentoEstrada);
char *cidadeMenorVizinhanca(const char *nomeArquivo, double comprimentoEstrada);

#endif