#ifndef CIDADES_HTEST 
#define CIDADESTEST_H 

typedef struct { 
char Nome[256];     
int Posicao;        
} Cidade; 

typedef struct { 
int N;              
int T;              
Cidade *C;          
} Estrada; 
// Nome do cidade 
// Posição da cidade 
// Número de cidades 
// Comprimento da estrada 
// Vetor de cidades 

Estrada *getEstrada(const char *nomeArquivo);               
double calcularMenorVizinhanca(const char *nomeArquivo);    
// Inicializa cidades no TAD indicado acima. 
// Retorna a menor vizinhança. 
char *cidadeMenorVizinhanca(const char *nomeArquivo);   // Retorna a cidade que tem menor vizinhança. 
#endif 