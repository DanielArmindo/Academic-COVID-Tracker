#ifndef GESTAOCONFINAMENTOS_H_INCLUDED
#define GESTAOCONFINAMENTOS_H_INCLUDED

#include "funcoesGenericas.h"

#include "gestaoTestagem.h"

typedef struct
{
    int n_utente;
    int tipo_confinamento;
    tipoData dataConfinamento;
    int duracao;
} tipo_confinamento;

tipo_confinamento *confinaMembro(tipo_confinamento *vetorConfinamento, int *totalConfinamentos, tipo_membro_comunidade_academica vetorMembros[], int totalMembros, int numeroMembro, int tipoConfinamento, tipoData data);
void listarConfinamentos(tipo_confinamento *vetorConfinamento, int totalConfinamentos, tipo_membro_comunidade_academica vetorMembros[], int totalMembros);
void listarConfinamentosPorMembro(tipo_confinamento *vetorConfinamento, int totalConfinamentos, tipo_membro_comunidade_academica vetorMembros[], int totalMembros);
tipo_confinamento *gestaoConfinamentos(tipo_confinamento *vetorConfinamento, int *totalConfinamentos, tipo_membro_comunidade_academica vetorMembros[], int totalMembros);
int procuraUltimoConfinamento(tipo_confinamento *vetorConfinamento, int totalConfinamentos, int numeroUtente);
void gravaFicheiroBinarioConfinamentos(tipo_confinamento *vetorConfinamento, int totalConfinamentos);
tipo_confinamento *lerFicheiroBinarioConfinamentos(tipo_confinamento *vetorConfinamento, int *totalConfinamentos);
tipoData dataNula();

// Gestao Testagem
tipo_teste_diagnostico *resultado_teste(tipo_membro_comunidade_academica vetorMembros[], tipo_teste_diagnostico vetorTestes[], int totalMembros, int *testes_agendados, int *quantTestesRealizados, tipo_teste_diagnostico *dadosTeste);
void adicionaMembro(tipo_membro_comunidade_academica vetorMembros[], int *totalMembros, tipo_confinamento *vetorConfinamento, int *totalConfinamentos);

#endif // GESTAOCONFINAMENTOS_H_INCLUDED
