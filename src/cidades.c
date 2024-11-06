

//adicionando bibliotecas
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "cidades.h"

//declarações
#define MAX_LINHA 256  // Definindo um tamanho máximo para cada linha lida do arquivo
double VizinhancaReal;


Estrada *getEstrada(const char *nomeArquivo) 
{
    FILE *arq = fopen(nomeArquivo, "r");
    char linha[MAX_LINHA];
    
    if (!arq) 
    {
        printf("Erro: Não foi possível abrir o arquivo.\n");
        return NULL;
    }
    //printf("Abertura de arquivo bem sucedida.\n\n");

    Estrada *estrada = (Estrada *) malloc(sizeof(Estrada)); 
    if (!estrada) 
    {
        printf("Erro: Erro na alocação de memória.\n");
        fclose(arq);
        return NULL;
    }
    //printf("Alocação de memória para estrada bem sucedida.\n\n");

    do {
        if (!fgets(linha, MAX_LINHA, arq)) 
        {
            printf("Erro: Arquivo incompleto ou mal formatado ao ler T.\n");

            free(estrada);
            fclose(arq);
            return NULL;
        }
    } while (strlen(linha) <= 1);

    sscanf(linha, "%d", &estrada->T);
    if (estrada->T < 3 || estrada->T > 1000000) 
    { 
        printf("Erro de restrição. T inválido: %d. Deve estar entre 3 e 1000000.\n", estrada->T);

        free(estrada);
        fclose(arq);
        return NULL;
    }

    do {
        if (!fgets(linha, MAX_LINHA, arq)) 
        {
            printf("Erro: Arquivo incompleto ou mal formatado ao ler N.\n");

            free(estrada);
            fclose(arq);
            return NULL;
        }
    } while (strlen(linha) <= 1);

    sscanf(linha, "%d", &estrada->N);
    if (estrada->N < 2 || estrada->N > 10000) 
    {
        printf("Erro de restrição. N inválido: %d. Deve estar entre 2 e 10000.\n", estrada->N);

        free(estrada);
        fclose(arq);
        return NULL;
    }

    estrada->C = (Cidade *)malloc(estrada->N * sizeof(Cidade));
    if (!estrada->C) 
    {
        printf("Erro: Erro na alocação de memória para cidades.\n");

        free(estrada);
        fclose(arq);
        return NULL;
    }

    for (int i = 0; i < estrada->N; i++) {
        do {
            if (!fgets(linha, MAX_LINHA, arq)) 
            {
                printf("Erro: Arquivo incompleto ou mal formatado ao ler cidade %d.\n", i + 1);

                free(estrada->C);
                free(estrada);
                fclose(arq);
                return NULL;
            }
        } while (strlen(linha) <= 1);

        sscanf(linha, "%d %[^\n]", &estrada->C[i].Posicao, estrada->C[i].Nome);
        if (estrada->C[i].Posicao <= 0 || estrada->C[i].Posicao >= estrada->T) 
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
    double menorVizinhanca = estrada->T;
    double vizinhancaFora;

    if (!estrada) 
    {
        printf("Erro: Não foi possível armazenar a estrada.\n");

        return -1;
    }

    for (int i = 1; i < estrada->N; i++) 
    {
        double vizinhanca = (estrada->C[i].Posicao - estrada->C[i - 1].Posicao) / 2.0;
        vizinhancaFora = vizinhanca;

        if (vizinhanca < menorVizinhanca) 
        {
            menorVizinhanca = vizinhanca;
            //printf("Esse era o valor de depois do calculo: %lf.\n", menorVizinhanca);
        }
    }
    VizinhancaReal = fabs(vizinhancaFora);
    //printf("E esse é o valor que deve ser mandado: %lf\n\n", VizinhancaReal);

    free(estrada->C);
    free(estrada);

    //printf("Calculo de menor vizinhança concluído com sucesso.\n\n");

    return VizinhancaReal; //menorVizinhanca
}

char *cidadeMenorVizinhanca(const char *nomeArquivo) 
{
    Estrada *estrada = getEstrada(nomeArquivo);
    double menorVizinhanca = calcularMenorVizinhanca(nomeArquivo);
    char *menorCidade = NULL;
    double valorcerto;

    if (!estrada)
    {
        printf("Erro: Não foi possível armazenar a estrada.\n");

        return NULL;
    }

    for (int i = 1; i < estrada->N; i++) {
        double vizinhanca = (estrada->C[i].Posicao - estrada->C[i - 1].Posicao) / 2.0;
        valorcerto = fabs(vizinhanca);

        if (valorcerto == menorVizinhanca) 
        {
            menorCidade = strdup(estrada->C[i].Nome);
            break;
        }
    }
    
    free(estrada->C);
    free(estrada);

    return menorCidade;
}