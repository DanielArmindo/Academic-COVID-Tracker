#include <stdio.h>
#include <stdlib.h>
#include "funcoesGenericas.h"
#include "gestaoTestagem.h"
#include "gestaoConfinamentos.h"

#include "args.h"

int main(int argc, char *argv[])
{
    struct gengetopt_args_info valores;

    if (cmdline_parser(argc,argv,&valores))
    {
      exit(1);
    }
    
    (void)argc; (void)argv;

    printf("\n");

    tipo_membro_comunidade_academica vetorMembros[MAX_MEMBROS];
    tipo_teste_diagnostico *vetorTeste;
    tipo_confinamento *vetorConfinamento;
    tipo_teste_diagnostico testeBuffer;
    vetorTeste = NULL;
    vetorConfinamento = NULL;

    int totalMembros = 0;
    int totalConfinamentos = 0;
    char escolha, escolha_membros, escolha_testes, escolha_confinamentos;

    int quantTestesRealizados = 0;
    int testesAgendados = 0;
    int quantVacinados = 0;

    //Caregamento de dados dos ficheiros
    lerFicheiroBinarioMembros(vetorMembros, &totalMembros);
    vetorTeste = lerFicheiroBinarioTestes(vetorTeste, &testesAgendados);
    lerFicheiroBinario_testesRealizados(&quantTestesRealizados);
    vetorConfinamento = lerFicheiroBinarioConfinamentos(vetorConfinamento, &totalConfinamentos);

    quantVacinados = membrosVacinados(vetorMembros, totalMembros);
    do
    {
        escolha = Menu_Principal(totalMembros, testesAgendados, quantVacinados, quantTestesRealizados);
        switch (escolha)
        {
        case 'M':
            do
            {
                limpaEcraInicial();
                escolha_membros = Menu_Membros();
                switch (escolha_membros)
                {
                case 'I':
                    adicionaMembro(vetorMembros, &totalMembros, vetorConfinamento, &totalConfinamentos);
                    gravaFicheiroBinarioConfinamentos(vetorConfinamento, totalConfinamentos);
                    gravaFicheiroBinarioMembros(vetorMembros, totalMembros);
                    quantVacinados = membrosVacinados(vetorMembros, totalMembros);
                    break;

                case 'U':
                    listaMembro(vetorMembros, vetorTeste, totalMembros, testesAgendados);
                    break;
                case 'L':
                    listaMembros(vetorMembros, vetorTeste, totalMembros, testesAgendados);
                    break;

                case 'R':
                    // Registar/Atualizar Estado de Vacinacao de 1 Membro da Comunidade
                    alteraEstadoDeVacinacao(vetorMembros, &totalMembros);
                    gravaFicheiroBinarioMembros(vetorMembros, totalMembros);
                    quantVacinados = membrosVacinados(vetorMembros, totalMembros);
                    break;

                default:
                    break;
                }

            } while (escolha_membros != 'V');
            printf("\n\n");
            break;

        case 'T':
            do
            {
                limpaEcraInicial();
                escolha_testes = Menu_Testes();
                switch (escolha_testes)
                {
                case 'L':
                    listaTestes(vetorTeste, testesAgendados);
                    break;

                case 'A':
                    vetorTeste = agenda_realizacao_teste(vetorMembros, vetorTeste, totalMembros, &testesAgendados);
                    gravaFicheiroBinarioTestes(vetorTeste, testesAgendados);
                    break;

                case 'D':
                    altera_realizacao_teste(vetorTeste, testesAgendados, vetorMembros, totalMembros);
                    break;

                case 'R':
                    vetorTeste = resultado_teste(vetorMembros, vetorTeste, totalMembros, &testesAgendados, &quantTestesRealizados, &testeBuffer);
                    gravaFicheiroBinarioTestes(vetorTeste, testesAgendados);
                    gravaFicheiroBinario_testesRealizados(quantTestesRealizados);

                    switch (testeBuffer.resultado)
                    {
                    case POSITIVO:
                        // por em isolamento profilático
                        vetorConfinamento = confinaMembro(vetorConfinamento, &totalConfinamentos, vetorMembros, totalMembros, testeBuffer.utente, ISOLAMENTO_PROFILATICO, testeBuffer.dataRealizacao);
                        break;
                    case INCONCLUSIIVO:

                        // por em Quarentena
                        vetorConfinamento = confinaMembro(vetorConfinamento, &totalConfinamentos, vetorMembros, totalMembros, testeBuffer.utente, QUARENTENA, testeBuffer.dataRealizacao);

                        break;
                    default:
                        break;
                    }
                    gravaFicheiroBinarioConfinamentos(vetorConfinamento, totalConfinamentos);
                    gravaFicheiroBinarioMembros(vetorMembros, totalMembros);

                    break;

                case 'I':
                    informacaoTeste(vetorMembros, vetorTeste, totalMembros, testesAgendados);
                    break;

                default:
                    break;
                }

            } while (escolha_testes != 'V');
            printf("\n\n");
            break;

        case 'C':
            do
            {
                limpaEcraInicial();
                escolha_confinamentos = Menu_Confinamentos();
                switch (escolha_confinamentos)
                {

                case 'A':
                case 'R':
                    vetorConfinamento = gestaoConfinamentos(vetorConfinamento, &totalConfinamentos, vetorMembros, totalMembros);
                    gravaFicheiroBinarioConfinamentos(vetorConfinamento, totalConfinamentos);
                    gravaFicheiroBinarioMembros(vetorMembros, totalMembros);
                    break;

                case 'U':
                    listarConfinamentosPorMembro(vetorConfinamento, totalConfinamentos, vetorMembros, totalMembros);
                    break;

                case 'L':
                    listarConfinamentos(vetorConfinamento, totalConfinamentos, vetorMembros, totalMembros);
                    break;

                default:
                    break;
                }
            } while (escolha_confinamentos != 'V');
            break;

        case 'D':
            dadosEstatisticos(vetorMembros, vetorTeste, totalMembros, testesAgendados, quantTestesRealizados);
            break;
        case 'S':
            break;
        default:
            printf("\t| Escolha Invalida\n");
            limpaEcra();
            break;
        }
    } while (escolha != 'S');

    free(vetorTeste);
    free(vetorConfinamento);

    return 0;
}
