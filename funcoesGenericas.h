#ifndef FUNCOESGENERICAS_H_INCLUDED
#define FUNCOESGENERICAS_H_INCLUDED

#define MAX_STRING 50

#define MIN_ANO 1900
#define MAX_ANO 2030

#define MAX_HORA 24
#define MIN_HORA 1

#define MAX_MINUTOS_SEGUNDOS 59
#define MIN_MINUTOS_SEGUNDOS 0

typedef struct
{
    int dia, mes, ano;
} tipoData;

typedef struct
{
    int hora, minuto, segundo;
} tipoHora;

float lerFloat(float limMin, float limMax, char msg[]);
int lerInteiro(int limMin, int limMax, char msg[]);
tipoData lerData(char msg[]);
tipoHora lerHora(char msg[]);
void escreverData(tipoData data);
void lerSring(char texto[], int tamanho, char msg[]);
void limpaBuffer(void);
int maximoEmVetor(int vetor[], int tamVetor);
int minimoEmVetor(int vetor[], int tamVetor);
int procuraEmVetor(int vetor[], int tamVetor, int valor);
void escreveHora(tipoHora hora);
void limpaEcra(void);
void limpaEcraInicial(void);
int pedeConfirmacao(char msg[]);
float diferencaEntreDatas(tipoData data1, tipoData data2);

#endif // FUNCOESGENERICAS_H_INCLUDED
