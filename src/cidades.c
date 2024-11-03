#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cidades.h"

Estrada *getEstrada(const char *nomeArquivo) 
{
    FILE *arq = fopen(nomeArquivo, "r");

    if(!arq)
    {
        printf("Erro: Não foi possível fazer a leitura do arquivo.\n");
        
        fclose(arq);
        return NULL;
    }

    Estrada *estrada = (Estrada *) malloc(sizeof(Estrada));

    if(!estrada)
    {
        printf("Erro: Erro na alocação de memória.\n");
        
        free(estrada);
        fclose(arq);
        return NULL;
    }

    fscanf(arq, "%d",&estrada->T);
    if(estrada->T < 3 || estrada->T > pow(10,6)){
        printf("Erro de restrição.\n%d não pode ser menor ou igual a 3 ou maior ou igual 1000000.\n", estrada->T);

        free(estrada);
        fclose(arq);
        return NULL;
    }

    fscanf(arq, "%d", &estrada->N);
    if(estrada->N < 2 || estrada->N > pow(10,4))
    {
        printf("Erro de restrição:\n%d não pode ser  menor ou igual a 2 ou maior ou igual a 10000.\n");
        
        fclose(arq);
        free(estrada);
        return NULL;
    }

    estrada->C = (Cidade *)malloc(estrada->N * sizeof(Cidade));
    if (!estrada->C) { // Verificação de alocação de memória
        printf("Erro: Erro na alocação de memória para cidades.\n");
        free(estrada);
        fclose(arq);
        return NULL;
    }
    
    for(int i=0;i<estrada->N;i++)
    {
        fscanf(arq, "%d %s", &estrada->C[i].Posicao, estrada->C[i].Nome);
        
        if(estrada->C[i].Posicao <= 0 || estrada->C[i].Posicao >= estrada->T)
        {
        printf("Erro de restrição: %d não pode ser menor ou igual a 0 ou maior ou igual a %d.\n", estrada->C[i].Posicao, estrada->T);

        free(estrada->C);
        free(estrada);
        fclose(arq);

        return NULL;
        }
    }
    fclose(arq);
    return estrada;
}

double calcularMenorVizinhanca(const char *nomeArquivo) 
{
    Estrada *estrada = getEstrada(nomeArquivo);
    double vizinhanca, menorVizinhanca = estrada->T;

    if(estrada == NULL)
    {
        printf("Erro: Não foi possivível armazenar a cidade.\n");
        return 1;
    }

    for(int i=1;i< estrada->N;i++)
    {
        vizinhanca = (estrada->C[i].Posicao - estrada->C[i - 1].Posicao) /2;

        if(vizinhanca < menorVizinhanca){
            menorVizinhanca = vizinhanca;
        }
    }

    free(estrada->C);
    free(estrada);

    return menorVizinhanca;
}

char *cidadeMenorVizinhanca(const char *nomeArquivo) 
{
    Estrada *estrada = getEstrada(nomeArquivo);
    double vizinhanca, menorvizinhanca = calcularMenorVizinhanca(nomeArquivo);
    char *menorCidade = NULL;

    if(estrada == NULL){
        printf("Erro: Não foi possível armazenar a estrada.\n");
        return 1;
    }

    for(int i=1;i< estrada->N;i++)
    {
        vizinhanca = (double)(estrada->C[i].Posicao - estrada->C[i - 1].Posicao) / 2.0;

        if(estrada->C[i].Posicao == menorvizinhanca)
        {
            menorCidade = strdup(estrada->C[i].Nome);
            break;
        }
    }
    
    free(estrada->C);
    free(estrada);
    return menorCidade;
}

