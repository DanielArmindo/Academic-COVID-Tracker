#include <stdio.h>
#include <ctype.h>

#include "funcoesGenericas.h"
#include "gestaoTestagem.h"

char Menu_Principal(int quantMembros, int testesAgendados, int quantVacinados, int quantTestesRealizados)
{
    char escolha;
    printf("\n\n");
    printf("\t __________________________________________________      __________________________________________________\n");
    printf("\t|                                                  |    |                                                  |\n");
    printf("\t|                                                  |    |        M) Membros da Comunidade Academica        |\n");
    printf("\t|      Numero de membros da comunidade -> %3d      |    |                                                  |\n", quantMembros);
    printf("\t|                                                  |    |        T) Testes de Diagnostico da covid-19      |\n");
    printf("\t|      Testes Agendados -> %3d                     |    |                                                  |\n", testesAgendados);
    printf("\t|                                                  |    |     C) Confinamentos dos Membros da Comunidade   |\n");
    printf("\t|      Testes Realizados -> %3d                    |    |                                                  |\n", quantTestesRealizados);
    printf("\t|                                                  |    |               D) Dados Estatisticos              |\n");
    printf("\t|      Membros Vacinados -> %3d                    |    |                                                  |\n", quantVacinados);
    printf("\t|                                                  |    |                    S) Sair                       |\n");
    printf("\t|                                                  |    |                                                  |\n");
    printf("\t|__________________________________________________|    |__________________________________________________|\n");
    printf("\t|\n");
    printf("\t| Insira a escolha -> ");

    scanf("%c", &escolha);
    limpaBuffer();

    escolha = toupper(escolha);

    return escolha;
}

char Menu_Membros(void)
{
    char escolha;
    printf("\t __________________________________________________________________________\n");
    printf("\t|                                                                          |\n");
    printf("\t|                     I) Inserir Membros da Comunidade                     |\n");
    printf("\t|                                                                          |\n");
    printf("\t|                     L) Listar Membros da Comunidade                      |\n");
    printf("\t|                                                                          |\n");
    printf("\t|                    U) Listar Um Membro da Comunidade                     |\n");
    printf("\t|                                                                          |\n");
    printf("\t|    R) Registar/Atualizar Estado de Vacinacao de 1 Membro da Comunidade   |\n");
    printf("\t|                                                                          |\n");
    printf("\t|                     V) Voltar ao Menu Principal                          |\n");
    printf("\t|                                                                          |\n");
    printf("\t|__________________________________________________________________________|__\n");
    printf("\t\t\t\t\t\t\t\t\t\t   |");

    scanf("%c", &escolha);
    limpaBuffer();

    escolha = toupper(escolha);

    return escolha;
}

char Menu_Testes(void)
{
    char escolha;
    printf("\t __________________________________________________________________________\n");
    printf("\t|                                                                          |\n");
    printf("\t|                     A) Agendar Realizacao de um Teste                    |\n");
    printf("\t|                                                                          |\n");
    printf("\t|                           L) Listar Testes                               |\n");
    printf("\t|                                                                          |\n");
    printf("\t|                   D) Alterar Data de Realizacao do Teste                 |\n");
    printf("\t|                                                                          |\n");
    printf("\t|                      R) Registar Resultado do Teste                      |\n");
    printf("\t|                                                                          |\n");
    printf("\t|                  I) Informacao de um Teste de Diagnostico                |\n");
    printf("\t|                                                                          |\n");
    printf("\t|                     V) Voltar ao Menu Principal                          |\n");
    printf("\t|                                                                          |\n");
    printf("\t|__________________________________________________________________________|__\n");
    printf("\t\t\t\t\t\t\t\t\t\t   |");

    scanf("%c", &escolha);
    limpaBuffer();

    escolha = toupper(escolha);

    return escolha;
}

char Menu_Confinamentos(void)
{
    char escolha;
    printf("\t ______________________________________________________________________________________________\n");
    printf("\t|                                                                                              |\n");
    printf("\t|             R/A) Registar/Atualizar Estado de Confinamento de 1 Membro da Comunidade         |\n");
    printf("\t|                                                                                              |\n");
    printf("\t|                                 L) Listagem dos Confinamentos                                |\n");
    printf("\t|                                                                                              |\n");
    printf("\t|                        U) Listar Confinamentos relacionados a um membro                      |\n");
    printf("\t|                                                                                              |\n");
    printf("\t|                                  V) Voltar ao Menu Principal                                 |\n");
    printf("\t|                                                                                              |\n");
    printf("\t|______________________________________________________________________________________________|__\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t       |");

    scanf("%c", &escolha);
    limpaBuffer();

    escolha = toupper(escolha);

    return escolha;
}
