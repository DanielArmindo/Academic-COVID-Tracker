#ifndef GESTAO_TESTES_H_INCLUDED
#define GESTAO_TESTES_H_INCLUDED

// #include "gestaoConfinamentos.h"

#include "funcoesGenericas.h"

#define MAX_VACINAS 1000

#define MIN_MEMBROS 1
#define MAX_MEMBROS 200

// Tipos de membro
#define ESTUDANTE 0
#define DOCENTE 1
#define TECNICO 2

// Estados de vacinação
#define NAO_VACINADO 0
#define VACINA_DOSE1 1
#define VACINA_DOSE2 2
#define VACINA_DOSE3 3

// Estados de confinamento
#define NAO_CONFINADO 0
#define QUARENTENA 1
#define ISOLAMENTO_PROFILATICO 2

// Tipos de testes
#define TESTE_PCR 0
#define TESTE_ANTIGENIO 1
#define PCR "PCR-"
#define ANTIGENIO "ANTIGENIO-"

// Resultados Testes
#define POSITIVO 0
#define NEGATIVO 1
#define INCONCLUSIIVO 2

// Limites de Valores
#define MAX_STRING 50
#define MAX_NOME 50
#define MAX_PCR_POR_DIA 15

// Limites nº utente de saude
#define MAX_UTENTE 999999999
#define MIN_UTENTE 0

typedef struct
{
    int num_utente;
    char nome[MAX_NOME];
    int tipo_membro;
    int ano_nascimento;
    int estado_vacinacao;
    int estadoConfinamento;
    tipoData data_ult_vacina;

} tipo_membro_comunidade_academica;

typedef struct
{
    char caracterizacao[MAX_NOME + 1];
    int tipo;
    int utente;
    tipoData dataRealizacao;
    int resultado;
    tipoHora horaColheita;
    int duracao;
} tipo_teste_diagnostico;

void listaMembros(tipo_membro_comunidade_academica vetorMembros[],tipo_teste_diagnostico vetorTestes[], int totalMembros,int totalTestes);
void listaMembro(tipo_membro_comunidade_academica vetorMembros[],tipo_teste_diagnostico vetorTestes[], int totalMembros,int totalTestes);
int procuraMembro(tipo_membro_comunidade_academica vetorMembros[], int totalMembros, int numeroDeUtente);
void alteraEstadoDeVacinacao(tipo_membro_comunidade_academica vetorMembros[], int *totalMembros);

int procuraTeste(tipo_teste_diagnostico vetorTestes[], int totalTestes, char caracterizacao[]);
int procuraTeste_utente(tipo_teste_diagnostico *vetorTestes, int totalTestes, int n_utente);
int nr_testes_utente(tipo_teste_diagnostico *vetorTestes, int totalTestes, int n_utente);
int nr_testes_utente_realizados(tipo_teste_diagnostico *vetorTestes, int totalTestes, int n_utente);
int verifica_data(tipo_teste_diagnostico *vetorTestes, int testes_agendados, int n_utente, tipoData data);
int verifica_data_ano(tipo_membro_comunidade_academica *vetorMembros, int totalMembros, int n_utente, tipoData data);
int procuraTeste_caracterizacao(tipo_teste_diagnostico *vetorTestes, int totalTestes, char caracterizacao[], int *posVetor, int *nr_utente);
int nr_testes_positivos(tipo_teste_diagnostico *vetorTestes, int totalTestes, int nr_utente);
void menorQuantidade_testes(tipo_membro_comunidade_academica vetorMembros[], tipo_teste_diagnostico vetorTestes[], int totalMembros, int totalTestes);
void informa_testes_membros(tipo_teste_diagnostico vetorTestes[], int totalTestes, int n_utente);
void testesRealizados_recentemente(tipo_teste_diagnostico vetorTestes[], int testes_agendados);
int dataRecente(tipoData dataTeste,tipoData data);

tipo_teste_diagnostico *agenda_realizacao_teste(tipo_membro_comunidade_academica vetorMembros[], tipo_teste_diagnostico vetorTestes[], int totalMembros, int *testes_agendados);
tipo_teste_diagnostico *agenda_PCR(tipo_teste_diagnostico vetorTestes[], int *testes_agendados, int nr_utente, int *completa, tipoData dataTeste);
void altera_realizacao_teste(tipo_teste_diagnostico vetorTestes[], int testes_agendados,tipo_membro_comunidade_academica vetorMembros[],int totalMembros);
void listaTestes(tipo_teste_diagnostico *vetorTestes, int testes_agendados);
void informacaoTeste(tipo_membro_comunidade_academica vetorMembros[], tipo_teste_diagnostico vetorTestes[], int totalMembros, int totalTestes);
void dadosEstatisticos(tipo_membro_comunidade_academica vetorMembros[], tipo_teste_diagnostico vetorTestes[], int totalMembros, int totalTestes, int testesRealizados);

void gravaFicheiroBinarioMembros(tipo_membro_comunidade_academica vetorMembros[], int totalMembros);
void gravaFicheiroBinarioTestes(tipo_teste_diagnostico vetorTestes[], int testes_agendados);
void gravaResultadoTeste_texto(tipo_membro_comunidade_academica vetorMembros[], tipo_teste_diagnostico vetorTestes[], int nr_utente, int pos_utente_testes, int totalMembros);
void gravaFicheiroBinario_testesRealizados(int testesRealizados);

void lerFicheiroBinarioMembros(tipo_membro_comunidade_academica vetorMembros[], int *totalMembros);
tipo_teste_diagnostico *lerFicheiroBinarioTestes(tipo_teste_diagnostico *vetorTestes, int *testes_agendados);
void lerFicheiroBinario_testesRealizados(int *testesRealizados);

int membrosVacinados(tipo_membro_comunidade_academica vetorMembros[], int totalMembros);

char Menu_Principal(int quantMembros, int testesAgendados, int quantVacinados, int quantTestesRealizados);
char Menu_Membros(void);
char Menu_Testes(void);
char Menu_Confinamentos(void);

#endif // GESTAO_TESTES_H_INCLUDED
