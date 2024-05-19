#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "funcoesGenericas.h"

float lerFloat(float limMin, float limMax, char msg[])
{
    float num;
    int controlo;

    do
    {
        printf("\t\t| %s [%.2f, %.2f]: ", msg, limMin, limMax);
        controlo = scanf("%f", &num);
        limpaBuffer();

        if (controlo != 1)
        {
            printf("\t\t| ERRO: o valor inserido nao foi um numero\n");
        }
        else if (num < limMin || num > limMax)
        {
            printf("\t\t| ERRO: valor invalido");
        }
    } while (controlo != 1 || num < limMin || num > limMax);

    return num;
}

void lerSring(char texto[], int tamanho, char msg[])
{
    int tamStr;

    do
    {
        printf("\t| %s: ", msg);
        fgets(texto, tamanho, stdin);

        tamStr = strlen(texto);
        if (tamStr == 1) // apenas inseriu o \n
        {
            printf("\t\t-> ERRO: campo obrigatorio. Tem que inserir valor\n");
        }
    } while (tamStr == 1);

    if (texto[tamStr - 1] != '\n')
    {
        limpaBuffer();
    }
    else
    {
        texto[tamStr - 1] = '\0';
    }
}

void escreverData(tipoData data)
{
    printf("\t| %02d-%02d-%d\n", data.dia, data.mes, data.ano);
}

void escreveHora(tipoHora hora)
{
    printf("\t| %02d:%02d:%d\n", hora.hora, hora.minuto, hora.segundo);
}

tipoData lerData(char msg[])
{
    tipoData data;
    int controlo, diaMax = -1, falha = 0;

    do
    {
        falha = 0;
        do
        {
            printf("\t| %s(dd-mm-aaaa): ", msg);
            controlo = scanf("%d-%d-%d", &data.dia, &data.mes, &data.ano);
            limpaBuffer();

            if (controlo != 3)
            {
                printf("\t\t-> ERRO: Valores invalidos\n");
            }
        } while (controlo != 3);

        if (data.ano < MIN_ANO || data.ano > MAX_ANO)
        {
            printf("\t\t-> ERRO: ano invalido\n");
            falha = 1;
        }
        else
        {
            switch (data.mes)
            {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                diaMax = 31;
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                diaMax = 30;
                break;
            case 2:
                if (data.ano % 400 == 0 ||
                    (data.ano % 4 == 0 && data.ano % 100 != 0))
                {
                    diaMax = 29;
                }
                else
                {
                    diaMax = 28;
                }
                break;
            default:
                printf("\t\t-> ERRO: mes invalido\n");
                falha = 1;
            }
            if (data.dia < 1 || data.dia > diaMax)
            {
                printf("\t\t-> ERRO: dia invalido\n");
                falha = 1;
            }
        }
    } while (falha);

    return data;
}

tipoHora lerHora(char msg[])
{
    tipoHora hora;
    int controlo, falha = 0;
    do
    {
        falha = 0;
        do
        {
            printf("\t| %s (hora:minutos:segundos): ", msg);
            controlo = scanf("%d:%d:%d", &hora.hora, &hora.minuto, &hora.segundo);
            limpaBuffer();

            if (controlo != 3)
            {
                printf("\t\t-> ERRO: Valores invalidos\n");
            }
        } while (controlo != 3);

        if (hora.hora < MIN_HORA || hora.hora > MAX_HORA)
        {
            printf("\t\t-> ERRO: hora invalida\n");
            falha = 1;
        }
        if (hora.minuto < MIN_MINUTOS_SEGUNDOS || hora.minuto > MAX_MINUTOS_SEGUNDOS)
        {
            printf("\t\t-> ERRO: minutos invalido\n");
            falha = 1;
        }
        if (hora.segundo < MIN_MINUTOS_SEGUNDOS || hora.segundo > MAX_MINUTOS_SEGUNDOS)
        {
            printf("\t\t-> ERRO: segundos invalido\n");
            falha = 1;
        }
    } while (falha);
    return hora;
}

/*
 * Função:  lerInteiro
 * --------------------
 *  Lê e valida um valor do tipo inteiro
 *
 *  limMin: Limite Mínimo
 *  limMax: Limite Máximo
 *  msg: Mensagem a mostar
 *
 *  returns: número lido e validado
 */
int lerInteiro(int limMin, int limMax, char msg[])
{
    int num, controlo;
    do
    {
        printf("\t| %s [%d, %d]: ", msg, limMin, limMax);
        controlo = scanf("%d", &num);
        limpaBuffer();

        if (controlo != 1)
        {
            printf("\t\t-> ERRO: o valor inserido nao foi um numero\n");
        }
        else if (num < limMin || num > limMax)
        {
            printf("\t\t-> ERRO: valor invalido\n");
        }
    } while (controlo != 1 || num < limMin || num > limMax);

    return num;
}

void limpaBuffer(void)
{
    char chr;
    do
    {
        chr = getchar();
    } while (chr != '\n' && chr != EOF);
}

/*
 * Função:  maximoEmVetor
 * --------------------
 *  procura o valor minimo em um vetor
 *
 *  vetor: vetor a verificar
 *  tamVetor: tamanho do vetor
 *
 *  returns: maior numero no vetor
 */
int maximoEmVetor(int vetor[], int tamVetor)
{
    int buffer = -2147483647;
    for (int i = 0; i < tamVetor; i++)
    {
        /* code here */
        if (buffer < vetor[i])
        {
            buffer = vetor[i];
        }
    }
    return buffer;
}

/*
 * Função:  minimoEmVetor
 * --------------------
 *  procura o valor maximo em um vetor
 *
 *  vetor: vetor a verificar
 *  tamVetor: tamanho do vetor
 *
 *  returns: maior numero no vetor
 */
int minimoEmVetor(int vetor[], int tamVetor)
{
    int buffer = 2147483647;

    for (int i = 0; i < tamVetor; i++)
    {
        /* code here */
        if (buffer > vetor[i])
        {
            buffer = vetor[i];
        }
    }
    return buffer;
}

/*
 * Função:  procuraEmVetor
 * --------------------
 *  procura um valor em um vetor, retorna -1 caso valor não se encontre no vetor
 *
 *  vetor: vetor a verificar
 *  tamVetor: tamanho do vetor
 *  valor: valor a procurar
 *
 *  returns: maior numero no vetor
 */
int procuraEmVetor(int vetor[], int tamVetor, int valor)
{
    int buffer = -1;
    for (int i = 0; i < tamVetor; i++)
    {
        /* code here */
        if (valor == vetor[i])
        {
            buffer = i;
        }
    }
    return buffer;
}

void limpaEcra(void)
{
    printf("\n\n\n");
}
void limpaEcraInicial(void)
{
    printf("\n\n\n");
}

/*
 * Função:  pedeConfirmacao
 * --------------------
 *  pede um confirmacao (sim ou nao) ao utilizador
 *
 *  msg: mensagem a aparecer antes da verificacao
 *
 *  returns: 0 caso a resposta seja nao e 1 caso a resposta seja sim
 */
int pedeConfirmacao(char msg[])
{
    char opcao;
    int resultado;
    printf("\t| %s\n", msg);
    printf("\t| (S)im ou (N)ao?\n");
    do
    {
        printf("\t| Resposta: ");
        scanf("%c", &opcao);
        limpaBuffer();

        opcao = toupper(opcao);
    } while (opcao != 'S' && opcao != 'N');

    resultado = (opcao == 'S');

    return resultado;
}

/*
 * Função:  diferencaEntreDatas
 * --------------------
 *  Calcula a diferenca entre duas datas
 *  Se o valor for positivo data1 < data2, caso seja negativo data1>data2
 *
 *  data1: tipoData
 *  data2: tipoData
 *
 *
 *  returns: 0 caso a resposta seja nao e 1 caso a resposta seja sim
 */
float diferencaEntreDatas(tipoData data1, tipoData data2)
{
    struct tm data1_obj, data2_obj, *tptr;
    time_t tempo1, tempo2;

    // Inicializa "objetos" da time.h
    time(&tempo1);
    time(&tempo2);
    tptr = localtime(&tempo1);
    data1_obj = *tptr;
    tptr = localtime(&tempo2);
    data2_obj = *tptr;

    // Copia datas do nosso tipo de dados para o tipo de dados da time.h
    data1_obj.tm_year = data1.ano - 1900;
    data1_obj.tm_mon = data1.mes - 1;
    data1_obj.tm_mday = data1.dia;

    data2_obj.tm_year = data2.ano - 1900;
    data2_obj.tm_mon = data2.mes - 1;
    data2_obj.tm_mday = data2.dia;

    tempo1 = mktime(&data1_obj);
    tempo2 = mktime(&data2_obj);

    return (difftime(tempo2, tempo1) / 86400);
}
