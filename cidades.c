#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cidades.h"

void inserirCidade(Cidade **lista, const char *nome, double distancia){
    Cidade *novaCidade = (Cidade *)malloc(sizeof(Cidade));
    if(!novaCidade){
        perror("\n*ERRO EM ALOCAR MEMORIA*");
        return;
    }
    strcpy(novaCidade->nome, nome);
    novaCidade->distancia = distancia;
    novaCidade->prox = *lista;
    *lista = novaCidade;
}

Cidade *carregarCidades(const char *nomeArquivo, double *comprimentoEstrada){
    FILE *arquivo = fopen(nomeArquivo, "r");
    if(arquivo == NULL){
        perror("\n*ERRO EM ABRIR ARQUIVO*");
        return NULL;
    }

    int numCidades;
    fscanf(arquivo, "%lf %d", comprimentoEstrada, &numCidades);

    Cidade *lista = NULL;
    char nome[50];
    double distancia;
    for(int i = 0; i < numCidades; i++){
        fscanf(arquivo, "%lf", &distancia);
        fgetc(arquivo);
        fgets(nome, sizeof(nome), arquivo);
        nome[strcspn(nome, "\n")] = '\0';
        inserirCidade(&lista, nome, distancia);
    }

    fclose(arquivo);
    return lista;
}

double calcularMenorVizinhanca(const char *nomeArquivo, double comprimentoEstrada){
    Cidade *cidades = carregarCidades(nomeArquivo, &comprimentoEstrada);
    if(cidades == NULL){
        return -1.0;
    }

    Cidade *atual = cidades;
    double menorVizinhanca = comprimentoEstrada;

    while(atual){
        Cidade *proxima = atual->prox;
        double vizinhanca;
        if (proxima){
            vizinhanca = (proxima->distancia - atual->distancia) / 2.0;
        } else{
            vizinhanca = comprimentoEstrada - atual->distancia;
        }
        if(vizinhanca < menorVizinhanca){
            menorVizinhanca = vizinhanca;
        }
        atual = atual->prox;
    }

    while(cidades){
        Cidade *tmp = cidades;
        cidades = cidades->prox;
        free(tmp);
    }

    return menorVizinhanca;
}

char *cidadeMenorVizinhanca(const char *nomeArquivo, double comprimentoEstrada){
    Cidade *cidades = carregarCidades(nomeArquivo, &comprimentoEstrada);
    if(cidades == NULL){
        return NULL;
    }

    Cidade *atual = cidades;
    Cidade *cidadeMenor = NULL;
    double menorVizinhanca = comprimentoEstrada;

    while(atual){
        Cidade *proxima = atual->prox;
        double vizinhanca;
        if(proxima){
            vizinhanca = (proxima->distancia - atual->distancia) / 2.0;
        }else{
            vizinhanca = comprimentoEstrada - atual->distancia;
        }
        if(vizinhanca < menorVizinhanca){
            menorVizinhanca = vizinhanca;
            cidadeMenor = atual;
        }
        atual = atual->prox;
    }

    char *nomeCidade = NULL;
    if(cidadeMenor){
        nomeCidade = strdup(cidadeMenor->nome);
    }
    while(cidades){
        Cidade *tmp = cidades;
        cidades = cidades->prox;
        free(tmp);
    }

    return nomeCidade;
}