#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestaoTestagem.h"
#include "gestaoConfinamentos.h"

/*
 * Função:  adicionaMembro
 * --------------------
 * Adiciona um membro da comunidade académica ao vetor
 *
 *  vetorMembros: vetor com os membros da comunidade academica
 *  totalMembros: ponteiro com o total (contagem) de membros
 *  returns: void
 */
void adicionaMembro(tipo_membro_comunidade_academica vetorMembros[], int *totalMembros, tipo_confinamento *vetorConfinamento, int *totalConfinamentos)
{
    int n_membros, cont, flag, numero_utente;
    char buffer[120];
    int qtdTipoMembro;
    int qtdDosesVacina;
    int qtdTipoConfinamento;

    // Validação dos tipos existentes
    qtdTipoMembro = 3;
    qtdDosesVacina = 4;
    qtdTipoConfinamento = 3;

    int vetorTipoMembro[] = {ESTUDANTE, DOCENTE, TECNICO};
    int vetorDosesVacina[] = {NAO_VACINADO, VACINA_DOSE1, VACINA_DOSE2, VACINA_DOSE3};
    int vetorTipoConfinamento[] = {NAO_CONFINADO, QUARENTENA, ISOLAMENTO_PROFILATICO};

    limpaEcraInicial();
    if (*totalMembros == MAX_MEMBROS)
    {
        printf("\t| O total maximo dos membros da comunidade academica já foi atingido.\n\t| Nao e possivel adicionar mais membros\n");
    }
    else
    {

        do
        {
            n_membros = lerInteiro(MIN_MEMBROS, MAX_MEMBROS, "Quantos membros quer adiconar a comunidade academica?");
            if (*totalMembros + n_membros >= MAX_MEMBROS)
            {
                printf("\t| Nao pode adicionar mais membro que do que o maximo(%d)\n", MAX_MEMBROS);
            }
        } while (*totalMembros + n_membros >= MAX_MEMBROS);

        for (cont = 0; cont < n_membros; cont++)
        {
            do
            {

                numero_utente = lerInteiro(MIN_UTENTE, MAX_UTENTE, "Insira o numero de utente");
                if (procuraMembro(vetorMembros, *totalMembros, numero_utente) == -1)
                {
                    flag = 0;
                }
                else
                {
                    flag = 1;
                    printf("\t\t-> Utente ja existente!\n");
                }
            } while (flag);
            vetorMembros[*totalMembros].num_utente = numero_utente;
            lerSring(vetorMembros[*totalMembros].nome, MAX_NOME, "Insira o nome do utente");
            sprintf(buffer, "Insira o tipo de membro (%d - Estudante; %d - Docente; %d - Tecnico)", ESTUDANTE, DOCENTE, TECNICO);
            do
            {
                vetorMembros[*totalMembros].tipo_membro = lerInteiro(minimoEmVetor(vetorTipoMembro, qtdTipoMembro), maximoEmVetor(vetorTipoMembro, qtdTipoMembro), buffer);
                if (procuraEmVetor(vetorTipoMembro, qtdTipoMembro, vetorMembros[*totalMembros].tipo_membro) == -1) // Verifica se o tipo de membro é valido
                {
                    flag = 1;
                    printf("\t\t-> Tipo Inválido!\n");
                }
                else
                {
                    flag = 0;
                }

            } while (flag);

            vetorMembros[*totalMembros].ano_nascimento = lerInteiro(MIN_ANO, MAX_ANO, "Insira o ano de nascimento");

            sprintf(buffer, "Insira o estado de vacincao (%d - Nao Vacinado; %d - 1 Dose; %d - 2 Doses; %d - 3 Doses)", NAO_VACINADO, VACINA_DOSE1, VACINA_DOSE2, VACINA_DOSE3);
            do
            {
                vetorMembros[*totalMembros].estado_vacinacao = lerInteiro(minimoEmVetor(vetorDosesVacina, qtdDosesVacina), maximoEmVetor(vetorDosesVacina, qtdDosesVacina), buffer);

                if (procuraEmVetor(vetorTipoMembro, qtdDosesVacina, vetorMembros[*totalMembros].estado_vacinacao) == -1)
                {
                    flag = 1;
                    printf("\t\t-> Tipo Inválido!\n");
                }
                else
                {
                    flag = 0;
                }
            } while (flag);

            if (vetorMembros[*totalMembros].estado_vacinacao != NAO_VACINADO)
            {

                vetorMembros[*totalMembros].data_ult_vacina = lerData("Insira a data da ultima vacina");
            }

            sprintf(buffer, "Insira o estado de confinamento (%d - Nao confinado; %d - Quarentena; %d - Isolametno Profilatico)", NAO_CONFINADO, QUARENTENA, ISOLAMENTO_PROFILATICO);

            do
            {
                vetorMembros[*totalMembros].estadoConfinamento = lerInteiro(minimoEmVetor(vetorTipoConfinamento, qtdTipoConfinamento), maximoEmVetor(vetorDosesVacina, qtdDosesVacina), buffer);

                if (procuraEmVetor(vetorTipoMembro, qtdTipoConfinamento, vetorMembros[*totalMembros].estadoConfinamento) == -1)
                {
                    flag = 1;
                    printf("\t\t-> Tipo Inválido!\n");
                }
                else
                {
                    flag = 0;
                }
            } while (flag);

            if (vetorMembros[*totalMembros].estadoConfinamento != NAO_CONFINADO)
            {
                vetorConfinamento = confinaMembro(vetorConfinamento, totalConfinamentos, vetorMembros, (*totalMembros + 1), vetorMembros[*totalMembros].num_utente, vetorMembros[*totalMembros].estadoConfinamento, dataNula());
            }
            *totalMembros = (*totalMembros) + 1;
        }
    }
    printf("\n\n");
}

/*
 * Função:  alteraEstadoDeVacinacao
 * --------------------
 * Altera o estado de vacinacao de um membro da comunidade académica
 *
 *  vetorMembros: vetor com os membros da comunidade academica
 *  totalMembros: ponteiro com o total (contagem) de membros
 *  returns: void
 */
void alteraEstadoDeVacinacao(tipo_membro_comunidade_academica vetorMembros[], int *totalMembros)
{
    int numeroMembro;
    int posicao;
    int opcao;
    tipoData data;
    char bufferString[150];
    
    limpaEcraInicial();

    numeroMembro = lerInteiro(MIN_UTENTE, MAX_UTENTE, "Introduza o numero do utente de saude para alterar o estado de vacinacao");
    posicao = procuraMembro(vetorMembros, *totalMembros, numeroMembro);
    
    if (posicao == -1)
    {
        printf("\t| O membro que selecionou nao esta insirido na comunidade, adicione o membro a comunidade para agendar um teste\n");
    }
    else
    {
        if (vetorMembros[posicao].estado_vacinacao == NAO_VACINADO)
        {
            sprintf(bufferString, "Insira a quantidade de doses de Vacina (0 - sair; %d - 1 Dose; %d - 2 Dose; %d - 3 Dose)", VACINA_DOSE1, VACINA_DOSE2, VACINA_DOSE3);
            opcao = lerInteiro(0, VACINA_DOSE3, bufferString);
            if (opcao != 0)
            {

                vetorMembros[posicao].data_ult_vacina = lerData("Insira a data da ultima vacina");
                vetorMembros[posicao].estado_vacinacao = opcao;
            }
            else
            {
                printf("\t\t-> Operacao Cancelada\n");
            }
        }
        else if (vetorMembros[posicao].estado_vacinacao == VACINA_DOSE1)
        {
            sprintf(bufferString, "Insira a quantidade de doses de Vacina (%d - sair; %d - 2 Dose; %d - 3 Dose)", VACINA_DOSE1, VACINA_DOSE2, VACINA_DOSE3);
            opcao = lerInteiro(VACINA_DOSE1, VACINA_DOSE3, bufferString);
            if (opcao != VACINA_DOSE1)
            {
                data = lerData("Insira a data da ultima vacina");
                while (diferencaEntreDatas(vetorMembros[posicao].data_ult_vacina, data) < 0)
                {
                    data = lerData("A data de vacinao nao pode ser anterior a data da dose anteiror");
                }
                vetorMembros[posicao].estado_vacinacao = opcao;
                vetorMembros[posicao].data_ult_vacina = data;
            }
            else
            {
                printf("\t\t-> Operacao Cancelada\n");
            }
        }
        else if (vetorMembros[posicao].estado_vacinacao == VACINA_DOSE2)
        {
            sprintf(bufferString, "Insira a quantidade de doses de Vacina (%d - sair; %d - 3 Dose)", VACINA_DOSE2, VACINA_DOSE3);
            opcao = lerInteiro(VACINA_DOSE2, VACINA_DOSE3, bufferString);
            if (opcao != VACINA_DOSE2)
            {
                data = lerData("Insira a data da ultima vacina");
                while (diferencaEntreDatas(vetorMembros[posicao].data_ult_vacina, data) < 0)
                {
                    data = lerData("A data de vacinao nao pode ser anterior a data da dose anteiror");
                }
                vetorMembros[posicao].estado_vacinacao = opcao;
                vetorMembros[posicao].data_ult_vacina = data;
            }
            else
            {
                printf("\t\t-> Operacao Cancelada\n");
            }
        }
        else
        {
            printf("\t\t-> O membro ja tem a vacinacao completa\n");
        }
    }
    printf("\n\n");
}

/*
 * Função:  listaMembros
 * --------------------
 *  Lista todos os membros da comunidade academica
 *
 *  vetorMembros: vetor com os membros da comunidade academica
 *  totalMembros: total (contagem) de membros
 *  returns: void
 */
void listaMembros(tipo_membro_comunidade_academica vetorMembros[], tipo_teste_diagnostico vetorTestes[], int totalMembros, int totalTestes)
{
    limpaEcraInicial();
    int nr_testes;

    if (totalMembros == 0)
    {
        printf("\t| Adicione Membros a comunidade para os poder listar");
    }
    else
    {
        printf("\t|\n");
        printf("\t| Membros da Comunidade\n");
        printf("\t|-----------------------------\n");
        for (int i = 0; i < totalMembros; i++)
        {

            printf("\t|\n");

            printf("\t| Numero de Utente: %d\n", vetorMembros[i].num_utente);
            printf("\t| Nome: %s\n", vetorMembros[i].nome);

            printf("\t| Tipo de Membro: ");
            switch (vetorMembros[i].tipo_membro)
            {
            case DOCENTE:
                printf("Docente");
                break;
            case ESTUDANTE:
                printf("Estudante");
                break;
            case TECNICO:
                printf("Tecnico");
                break;
            }
            printf("\n");

            printf("\t| Ano de nascimento: %d\n", vetorMembros[i].ano_nascimento);
            printf("\t| Estado de Confinamento: ");
            switch (vetorMembros[i].estadoConfinamento) {
                case NAO_CONFINADO:
                  printf("Nenhum");
                break;

                case QUARENTENA:
                  printf("Quarentena");
                break;

                case ISOLAMENTO_PROFILATICO:
                  printf("Isolamento Profilatico");
                break;
            }
            printf("\n");

            printf("\t| Estado de vacinacao: ");
            switch (vetorMembros[i].estado_vacinacao)
            {
            case NAO_VACINADO:
                printf("Nao Vacinado");
                break;
            case VACINA_DOSE1:
                printf("Vacina 1 Dose");
                break;
            case VACINA_DOSE2:
                printf("Vacina 2 Dose");
                break;
            case VACINA_DOSE3:
                printf("Vacina 3 Dose");
                break;
            }

            printf("\n");
            nr_testes = nr_testes_utente_realizados(vetorTestes, totalTestes, vetorMembros[i].num_utente);
            printf("\t| Numero de testes realizados: %d\n", nr_testes);
            nr_testes = nr_testes_utente(vetorTestes, totalTestes, vetorMembros[i].num_utente);
            if (nr_testes == 0)
            {
                printf("\t| Sem testes Agendados\n");
            }
            else
            {
                printf("\t|--------------------------------------\n");
                printf("\t| Informacoes dos Testes Agendados\n");
                informa_testes_membros(vetorTestes, totalTestes, vetorMembros[i].num_utente);
            }
            printf("\t|\n");
        }
    }
    printf("\n\n");
}

/*
 * Função:  listaMembro
 * --------------------
 *  Lista um membro da comunidade academica
 *
 *  vetorMembros: vetor com os membros da comunidade academica
 *  totalMembros: total (contagem) de membros
 *  returns: void
 */
void listaMembro(tipo_membro_comunidade_academica vetorMembros[], tipo_teste_diagnostico vetorTestes[], int totalMembros, int totalTestes)
{
    limpaEcraInicial();
    int nr_testes;
    int posicaoMembro = -1;
    int numeroMembro = -1;

    if (totalMembros == 0)
    {
        printf("\t| Adicione Membros a comunidade para os poder listar um\n\n");
        return;
    }
    
    numeroMembro = lerInteiro(MIN_UTENTE, MAX_UTENTE, "Introduza o numero do utente de saude");
    posicaoMembro = procuraMembro(vetorMembros, totalMembros, numeroMembro);
    if (posicaoMembro == -1)
    {
        printf("\t\t-> Membro nao encontrado!\n\n");
        return;
    }
    
    printf("\t|\n\t|\n");
    printf("\t| Informacao relativa ao utente com numero: %.9d\n",vetorMembros[posicaoMembro].num_utente);
    printf("\t|-----------------------------------------------\n");
    printf("\t|\n");
    printf("\t| Numero de Utente: %d\n", vetorMembros[posicaoMembro].num_utente);
    printf("\t| Nome: %s\n", vetorMembros[posicaoMembro].nome);

    printf("\t| Tipo de Membro: ");
    switch (vetorMembros[posicaoMembro].tipo_membro)
    {
    case DOCENTE:
        printf("Docente");
        break;
    case ESTUDANTE:
        printf("Estudante");
        break;
    case TECNICO:
        printf("Tecnico");
        break;
    }
    printf("\n");

    printf("\t| Ano de nascimento: %d\n", vetorMembros[posicaoMembro].ano_nascimento);
    printf("\t| Estado de Confinamento: ");
    switch (vetorMembros[posicaoMembro].estadoConfinamento) {
        case NAO_CONFINADO:
          printf("Nenhum");
        break;

        case QUARENTENA:
          printf("Quarentena");
        break;

        case ISOLAMENTO_PROFILATICO:
          printf("Isolamento Profilatico");
        break;
    }
    printf("\n");

    printf("\t| Estado de vacinacao: ");
    switch (vetorMembros[posicaoMembro].estado_vacinacao)
    {
    case NAO_VACINADO:
        printf("Nao Vacinado");
        break;
    case VACINA_DOSE1:
        printf("Vacina 1 Dose");
        break;
    case VACINA_DOSE2:
        printf("Vacina 2 Dose");
        break;
    case VACINA_DOSE3:
        printf("Vacina 3 Dose");
        break;
    }

    printf("\n");
    nr_testes = nr_testes_utente_realizados(vetorTestes, totalTestes, vetorMembros[posicaoMembro].num_utente);
    printf("\t| Numero de testes realizados: %d\n", nr_testes);
    nr_testes = nr_testes_utente(vetorTestes, totalTestes, vetorMembros[posicaoMembro].num_utente);
    if (nr_testes == 0)
    {
        printf("\t| Sem testes Agendados\n");
    }
    else
    {
        printf("\t|--------------------------------------\n");
        printf("\t| Informacoes dos Testes Agendados\n");
        informa_testes_membros(vetorTestes, totalTestes, vetorMembros[posicaoMembro].num_utente);
    }
    printf("\t|\n");
}

void informa_testes_membros(tipo_teste_diagnostico vetorTestes[], int totalTestes, int n_utente)
{
    for (int i = 0; i < totalTestes; i++)
    {
        if (vetorTestes[i].utente == n_utente && vetorTestes[i].resultado == -1)
        {
            if (vetorTestes[i].tipo == TESTE_PCR)
            {
                printf("\t| PCR -> %02d-%02d-%d\n", vetorTestes[i].dataRealizacao.dia, vetorTestes[i].dataRealizacao.mes, vetorTestes[i].dataRealizacao.ano);
            }
            else
            {
                printf("\t| Antigenio -> %02d-%02d-%d\n", vetorTestes[i].dataRealizacao.dia, vetorTestes[i].dataRealizacao.mes, vetorTestes[i].dataRealizacao.ano);
            }
        }
    }
}
/*
 * Função:  procuraMembro
 * --------------------
 *  Retorna o index do membro a procurar, retorna -1 caso não exista
 *
 *  vetorMembros: vetor com os membros da comunidade academica
 *  totalMembros: total (contagem) de membros
 *  numeroDeUtente: número de utente a procurar
 *  returns: int
 */
int procuraMembro(tipo_membro_comunidade_academica vetorMembros[], int totalMembros, int numeroDeUtente)
{
    int buffer = -1;

    for (int i = 0; i < totalMembros; i++)
    {
        if (vetorMembros[i].num_utente == numeroDeUtente)
        {
            buffer = i;
        }
    }

    return buffer;
}

/*
 * Função:  procuraTeste
 * --------------------
 *  Retorna o index do teste a procurar, retorna -1 caso não exista
 *
 *  vetorTestes: vetor com os testes
 *  totalTestes: total (contagem) de testes
 *  caracterizacao: número de utente a procurar
 *  returns: int
 */
int procuraTeste(tipo_teste_diagnostico vetorTestes[], int totalTestes, char caracterizacao[])
{
    int buffer = -1;

    for (int i = 0; i < totalTestes; i++)
    {
        if (strcmp(caracterizacao, vetorTestes[i].caracterizacao) == 0)
        {
            buffer = i;
        }
    }

    return buffer;
}

int procuraTeste_utente(tipo_teste_diagnostico *vetorTestes, int totalTestes, int n_utente)
{
    int buffer = -1;

    for (int i = 0; i < totalTestes; i++)
    {
        if (vetorTestes[i].utente == n_utente)
        {
            buffer = i;
        }
    }

    return buffer;
}

int nr_testes_utente(tipo_teste_diagnostico *vetorTestes, int totalTestes, int n_utente)
{
    int contador = 0;

    for (int i = 0; i < totalTestes; i++)
    {
        if (vetorTestes[i].utente == n_utente && vetorTestes[i].resultado == -1)
        {
            contador++;
        }
    }

    return contador;
}

int nr_testes_utente_realizados(tipo_teste_diagnostico *vetorTestes, int totalTestes, int n_utente)
{
    int contador = 0;

    for (int i = 0; i < totalTestes; i++)
    {
        if (vetorTestes[i].utente == n_utente && vetorTestes[i].resultado != -1)
        {
            contador++;
        }
    }

    return contador;
}

/*
 * Função:  verifica_data
 * --------------------
 *  Verifica de determinado utente tem naquela data um teste e retorna -1 caso contrario retorna 0
 *
 *  vetorTestes: vetor com os testes
 *  testes_agendados: testes que já estão agendados
 *  n_utente: número de utente a procurar
 *  data: data a procurar
 *  returns: int
 */
int verifica_data(tipo_teste_diagnostico *vetorTestes, int testes_agendados, int n_utente, tipoData data)
{
    int buffer = 0;
    for (int cont = 0; cont < testes_agendados; cont++)
    {
        if (vetorTestes[cont].utente == n_utente && vetorTestes[cont].dataRealizacao.dia == data.dia && vetorTestes[cont].dataRealizacao.mes == data.mes && vetorTestes[cont].dataRealizacao.ano == data.ano)
        {
            buffer = -1;
        }
    }
    return buffer;
}

int verifica_data_ano(tipo_membro_comunidade_academica *vetorMembros, int totalMembros, int n_utente, tipoData data)
{
    int buffer = 0;
    for (int i = 0; i < totalMembros; i++)
    {
        if (vetorMembros[i].num_utente == n_utente)
        {
            if (vetorMembros[i].ano_nascimento > data.ano)
            {
                buffer = -1;
            }
        }
    }
    return buffer;
}

/*
 * Função:  procuraTeste_caracterizacao
 * --------------------
 *  Procura a caracterizao de um teste, retorna -1 caso não exista
 *
 *  vetorTestes: vetor com os testes
 *  totalTestes: total (contagem) de testes
 *  caracterizacao: caracterizacao a procurar
 *  returns: int
 */
int procuraTeste_caracterizacao(tipo_teste_diagnostico *vetorTestes, int totalTestes, char caracterizacao[], int *posVetor, int *nr_utente)
{
    int buffer = -1;
    int valor;

    for (int i = 0; i < totalTestes; i++)
    {
        valor = strcmp(caracterizacao, vetorTestes[i].caracterizacao);
        if (valor == 0)
        {
            buffer = 0;
            *posVetor = i;
            *nr_utente = vetorTestes[i].utente;
        }
    }

    return buffer;
}

/*
 * Função:  nr_testes_positivos
 * --------------------
 *  Conta o numero de testes positivos de um determinado utente, retorna 0 se não houver testes positivos
 *
 *  vetorTestes: vetor com os testes
 *  totalTestes: total (contagem) de testes
 *  nr_utente: numero de utente a procurar
 *  returns: int
 */
int nr_testes_positivos(tipo_teste_diagnostico *vetorTestes, int totalTestes, int nr_utente)
{
    int totalTestesPos = 0;
    for (int i = 0; i < totalTestes; i++)
    {
        if (vetorTestes[i].utente == nr_utente && vetorTestes[i].resultado == POSITIVO)
        {
            totalTestesPos++;
        }
    }

    return totalTestesPos;
}

/*
 * Função:  testesRealizados_recentemente
 * --------------------
 *  Verifica a data ou as datas do(s) testes realizados mais recentemente
 *
 *  vetorTestes: vetor com os testes
 *  testes_agendados: total (contagem) de testes
 *  returns: void
 */
void testesRealizados_recentemente(tipo_teste_diagnostico vetorTestes[], int testes_agendados)
{
    int i;
    tipoData data;
    data.ano = 1;
    data.mes = 1;
    data.dia = 1;
    for (i = 0; i < testes_agendados; i++)
    {
        if (data.ano < vetorTestes[i].dataRealizacao.ano && vetorTestes[i].resultado != -1)
        {
            data = vetorTestes[i].dataRealizacao;
        }
        else
        {
            if (data.ano == vetorTestes[i].dataRealizacao.ano && vetorTestes[i].resultado != -1)
            {
                if (data.mes < vetorTestes[i].dataRealizacao.mes && vetorTestes[i].resultado != -1)
                {
                    data = vetorTestes[i].dataRealizacao;
                }
                else
                {
                    if (data.mes == vetorTestes[i].dataRealizacao.mes && vetorTestes[i].resultado != -1)
                    {
                        if (data.dia < vetorTestes[i].dataRealizacao.dia && vetorTestes[i].resultado != -1)
                        {
                            data = vetorTestes[i].dataRealizacao;
                        }
                    }
                }
            }
        }
    }

    printf("\t\t|\n");
    printf("\t\t| Data do teste realizado mais recente\n\t");
    escreverData(data);
    printf("\t\t|\n");
    printf("\t\t| Teste(s) com a data\n");
    for (i = 0; i < testes_agendados; i++)
    {
        if (vetorTestes[i].resultado != -1 && vetorTestes[i].dataRealizacao.ano == data.ano && vetorTestes[i].dataRealizacao.mes == data.mes && vetorTestes[i].dataRealizacao.dia == data.dia)
        {
            printf("\t\t| %s\n", vetorTestes[i].caracterizacao);
        }
    }
}

int dataRecente(tipoData dataTeste, tipoData data)
{
    int buffer = 0;

    if (dataTeste.ano < data.ano)
    {
        buffer = 1;
    }
    else
    {
        if (dataTeste.ano == data.ano)
        {
            if (dataTeste.mes < data.mes)
            {
                buffer = 1;
            }
            else
            {
                if (dataTeste.mes == data.mes)
                {
                    if (dataTeste.dia < data.dia)
                    {
                        buffer = 1;
                    }
                    else
                    {
                        if (dataTeste.dia == data.dia)
                        {
                            buffer = 2;
                        }
                    }
                }
            }
        }
    }
    return buffer;
}

/*
 * Função:  menorQuantidade_testes
 * --------------------
 *  Verifica o(s) membro(s) que têm menos testes
 *
 *  vetorMembros: vetor com os membros
 *  vetorTestes: vetor com os testes
 *  totalMembros: numero total dos membros
 *  totalTestes: total (contagem) de testes
 *  returns: void
 */
void menorQuantidade_testes(tipo_membro_comunidade_academica vetorMembros[], tipo_teste_diagnostico vetorTestes[], int totalMembros, int totalTestes)
{
    int i, i2, nr_testes;
    int vetor[MAX_MEMBROS], vetor2[MAX_MEMBROS], menorTestes, posVetor;
    for (i = 0; i < totalMembros; i++)
    {
        nr_testes = 0;
        for (i2 = 0; i2 < totalTestes; i2++)
        {
            if (vetorTestes[i2].utente == vetorMembros[i].num_utente && vetorTestes[i2].resultado != -1)
            {
                nr_testes++;
            }
        }
        vetor[i] = nr_testes;
    }
    i2 = 1;
    vetor2[0] = 0;
    menorTestes = vetor[0];
    for (i = 1; i < totalMembros; i++)
    {
        if (vetor[i] < menorTestes)
        {
            menorTestes = vetor[i];
            posVetor = i;
            i2 = 0;
        }
        if (vetor[i] == menorTestes)
        {
            vetor2[i2] = i;
            i2++;
        }
    }

    if (i2 == 0)
    {
        printf("\t\t|\n");
        printf("\t\t| O membro com menos teste e %s -> %d\n", vetorMembros[posVetor].nome, menorTestes);
    }
    else
    {
        printf("\t\t|\n");
        printf("\t\t|-------------------------------------\n");
        printf("\t\t|\n");
        printf("\t\t| Os Membros com Menos Testes\n");
        printf("\t\t|\n");
        for (i = 0; i < i2; i++)
        {
            printf("\t\t| %s -> %d\n", vetorMembros[vetor2[i]].nome, menorTestes);
        }
        printf("\t\t|\n");
    }
}

/*
 * Função:  agenda_realizacao_teste
 * ------------------------------
 * Agenda a realização de um teste para um membro da comunidade, e guarda os valores na estrutura dos testes.
 *
 * vetorMembros: vetor com os membros da comunidade academica
 * vetorTestes: vetor com os testes
 * totalMembros: total (contagem) de membros
 * testes_agendados: testes que já estão agendados
 * returns: vetor dos testes
 */
tipo_teste_diagnostico *agenda_realizacao_teste(tipo_membro_comunidade_academica vetorMembros[], tipo_teste_diagnostico vetorTestes[], int totalMembros, int *testes_agendados)
{
    int cont;
    tipo_teste_diagnostico *backup;
    backup = vetorTestes;
    char bufferDesignacao[MAX_NOME + 1];
    vetorTestes = realloc(vetorTestes, (*testes_agendados + 1) * sizeof(tipo_teste_diagnostico));
    limpaEcraInicial();
    if (vetorTestes == NULL)
    {
        printf("\t\t-> Erro em alocar a memoria\n");
        vetorTestes = backup;
    }
    else
    {
        int agenda_utente, verifica, escolha;
        int max_pcr = 0;
        tipoData data;
        agenda_utente = lerInteiro(MIN_UTENTE, MAX_UTENTE, "Introduza o numero do utente de saude para agendar o teste");
        verifica = procuraMembro(vetorMembros, totalMembros, agenda_utente);
        if (verifica == -1)
        {
            printf("\t\t-> O membro que selecionou nao esta insirido na comunidade, adicione o membro a comunidade para agendar um teste\n");
        }
        else
        {
            data = lerData("Introduza a data para agendar o teste");
            verifica = verifica_data_ano(vetorMembros, totalMembros, agenda_utente, data);
            if (verifica == -1)
            {
                printf("\t\t-> Nao pode agendar um teste antes da data de nascimento do utente");
            }
            else
            {
                if (*testes_agendados != 0)
                {
                    verifica = verifica_data(vetorTestes, *testes_agendados, agenda_utente, data);
                }
                if (verifica == -1)
                {
                    printf("\t\t-> O utente ja tem um teste agendado nesse dia\n");
                }
                else
                {
                    printf("\t| 1 -> PCR\n");
                    printf("\t| 2 -> Antigenio\n");
                    escolha = lerInteiro(1, 2, "Que tipo de teste pretende agendar");
                    switch (escolha)
                    {
                    case 1:
                        if ((*testes_agendados) != 0)
                        {
                            for (cont = 0; cont < (*testes_agendados); cont++)
                            {
                                if (vetorTestes[cont].tipo == TESTE_PCR && vetorTestes[cont].dataRealizacao.dia == data.dia && vetorTestes[cont].dataRealizacao.mes == data.mes && vetorTestes[cont].dataRealizacao.ano == data.ano)
                                {
                                    if (vetorTestes[cont].tipo == 0)
                                    {
                                        max_pcr++;
                                    }
                                }
                            }
                            if (max_pcr == MAX_PCR_POR_DIA)
                            {
                                printf("\t\t-> Nao pode agendar mais testes nesse dia\n");
                            }
                            else
                            {
                                sprintf(bufferDesignacao, "PCR-%010d", *testes_agendados);
                                strcpy(vetorTestes[*testes_agendados].caracterizacao, bufferDesignacao);
                                vetorTestes[*testes_agendados].tipo = TESTE_PCR;
                                vetorTestes[*testes_agendados].utente = agenda_utente;
                                vetorTestes[*testes_agendados].dataRealizacao = data;
                                vetorTestes[*testes_agendados].resultado = -1;
                                (*testes_agendados) = (*testes_agendados) + 1;

                                printf("\t| O Teste PCR foi Agendado\n");
                            }
                        }
                        else
                        {
                            sprintf(bufferDesignacao, "PCR-%010d", *testes_agendados);
                            strcpy(vetorTestes[*testes_agendados].caracterizacao, bufferDesignacao);
                            vetorTestes[*testes_agendados].tipo = TESTE_PCR;
                            vetorTestes[*testes_agendados].utente = agenda_utente;
                            vetorTestes[*testes_agendados].dataRealizacao = data;
                            vetorTestes[*testes_agendados].resultado = -1;
                            (*testes_agendados) = (*testes_agendados) + 1;

                            printf("\t| O Teste PCR foi Agendado\n");
                        }
                        break;

                    case 2:
                        sprintf(bufferDesignacao, "Antigenio-%010d", *testes_agendados);
                        strcpy(vetorTestes[*testes_agendados].caracterizacao, bufferDesignacao);
                        vetorTestes[*testes_agendados].tipo = TESTE_ANTIGENIO;
                        vetorTestes[*testes_agendados].utente = agenda_utente;
                        vetorTestes[*testes_agendados].dataRealizacao = data;
                        vetorTestes[*testes_agendados].resultado = -1;
                        (*testes_agendados) = (*testes_agendados) + 1;
                        printf("\t| O Teste Antigenio foi Agendado\n");
                        break;
                    }
                }
            }
        }
    }
    printf("\n\n\n");
    return vetorTestes;
}

/*
 * Função:  agenda_PCR
 * ------------------------------
 * Agenda um teste do tipo PCR
 *
 * vetorTestes: vetor com os testes
 * testes_agendados: testes que já estão agendados
 * nr_utente: numero de utente que vai realizar o teste
 * completa: variavel para verificar vetor foi incementado com os seus dados
 * dataTeste: data do teste Precendente ao PCR
 * returns: tipo_teste_diagnostico (vetor dos testes)
 */
tipo_teste_diagnostico *agenda_PCR(tipo_teste_diagnostico vetorTestes[], int *testes_agendados, int nr_utente, int *completa, tipoData dataTeste)
{
    tipo_teste_diagnostico *backup;
    backup = vetorTestes;
    vetorTestes = realloc(vetorTestes, (*testes_agendados + 1) * sizeof(tipo_teste_diagnostico));
    printf("\t|\n");
    if (vetorTestes == NULL)
    {
        printf("\t\t-> Erro em alocar a memoria\n");
        vetorTestes = backup;
    }
    else
    {
        int verifica, cont, max_pcr = 0;
        tipoData data;
        char bufferDesignacao[MAX_NOME];
        do
        {

            data = lerData("Introduza a data para agendar o teste PCR");
            verifica = dataRecente(dataTeste, data);
            if (verifica == 0)
            {
                printf("\t\t-> ERRO: O teste PCR nao pode ser marcado em uma data anterior a do teste original!\n");
            }
            if (verifica == 2)
            {
                printf("\t\t-> Nao pode agendar para o mesmo dia em que fez o teste\n");
            }
        } while (verifica == 0 || verifica == 2);

        for (cont = 0; cont < (*testes_agendados); cont++)
        {
            if (vetorTestes[cont].tipo == TESTE_PCR && vetorTestes[cont].dataRealizacao.dia == data.dia && vetorTestes[cont].dataRealizacao.mes == data.mes && vetorTestes[cont].dataRealizacao.ano == data.ano)
            {
                if (vetorTestes[cont].tipo == 0)
                {
                    max_pcr++;
                }
            }
        }
        if (max_pcr == MAX_PCR_POR_DIA)
        {
            printf("\t\t-> Nao pode agendar mais testes nesse dia\n");
        }
        else
        {
            sprintf(bufferDesignacao, "PCR-%010d", *testes_agendados);
            strcpy(vetorTestes[*testes_agendados].caracterizacao, bufferDesignacao);
            vetorTestes[*testes_agendados].tipo = TESTE_PCR;
            vetorTestes[*testes_agendados].utente = nr_utente;
            vetorTestes[*testes_agendados].dataRealizacao = data;
            vetorTestes[*testes_agendados].resultado = -1;
            (*testes_agendados)++;
            *completa = 1;
            printf("\t| O Teste PCR foi Agendado\n");
        }
    }

    printf("\t|\n");
    return vetorTestes;
}

/*
 * Função:  altera_realizacao_teste
 * ------------------------------
 * Altera a data de realização de um teste de um membro da comunidade, e guarda os valores na estrutura dos testes.
 *
 * vetorTestes: vetor com os testes
 * testes_agendados: testes que já estão agendados
 * returns: void
 */
void altera_realizacao_teste(tipo_teste_diagnostico vetorTestes[], int testes_agendados, tipo_membro_comunidade_academica vetorMembros[], int totalMembros)
{
    limpaEcraInicial();
    int procura_teste, procura_teste2;
    tipoData data, data2;
    int verifica = 0, verifica2 = 0;
    procura_teste = lerInteiro(MIN_UTENTE, MAX_UTENTE, "Introduza o numero do utente de saude para alterar a data do teste");
    procura_teste2 = nr_testes_utente(vetorTestes, testes_agendados, procura_teste);
    // Procura o teste do utente e verifica se é um agendamento sem resultado
    if (procura_teste2 == 0)
    {
        printf("\t| O utente nao tem agendado nenhum teste\n");
    }
    else
    {
        printf("\t| Escolha a data a alterar\n");
        printf("\t|-----------------------------\n\t|\n");

        for (int i = 0; i < testes_agendados; i++)
        {
            if (vetorTestes[i].utente == procura_teste && vetorTestes[i].resultado == -1)
            {
                if (vetorTestes[i].tipo == TESTE_PCR)
                {
                    printf("\t| Teste PCR\n");
                }
                else
                {
                    printf("\t| Teste Antigenio\n");
                }
                escreverData(vetorTestes[i].dataRealizacao);
                printf("\t|\n");
            }
        }
        data = lerData("Introduza a data que quer alterar");
        verifica = verifica_data(vetorTestes, testes_agendados, procura_teste, data);

        if (verifica == -1)
        {
            data2 = lerData("Introduza a nova data");
            verifica2 = verifica_data_ano(vetorMembros, totalMembros, procura_teste, data2);
            if (verifica2 == -1)
            {
                printf("\t| Nao pode agendar para uma data antes do nascimento do utente");
            }
            else
            {
                verifica = verifica_data(vetorTestes, testes_agendados, procura_teste, data2);
                if (verifica == -1)
                {
                    printf("\t| A data que pretende inserir ja esta agendada para esse utente\n");
                }
                else
                {
                    for (int i = 0; i < testes_agendados; i++)
                    {
                        if (vetorTestes[i].dataRealizacao.ano == data.ano && vetorTestes[i].dataRealizacao.mes == data.mes && vetorTestes[i].dataRealizacao.dia == data.dia)
                        {
                            vetorTestes[i].dataRealizacao = data2;
                        }
                    }
                    printf("\t| A data foi alterada\n");
                }
            }
        }
        else
        {
            printf("\t| A data que introduziu nao e uma das escolhas apresentadas\n");
        }
    }
}

/*
 * Função:  listaTestes
 * ------------------------------
 * Lista todos os testes agendados
 *
 * vetorTestes: vetor com os testes
 * testes_agendados: testes que já estão agendados
 * returns: void
 */

void listaTestes(tipo_teste_diagnostico *vetorTestes, int testes_agendados)
{
    limpaEcraInicial();
    if (testes_agendados == 0)
    {
        printf("\t| Nao existem testes agendados\n");
    }
    else
    {
        printf("\t\t|\n");
        printf("\t\t| Testes Agendados\n");
        printf("\t\t|-----------------------------\n");
        for (int i = 0; i < testes_agendados; i++)
        {
            printf("\t\t|\n");

            if (vetorTestes[i].tipo == 0)
            {
                printf("\t\t| %s\n", vetorTestes[i].caracterizacao);
                printf("\t\t| tipo - PCR\n");
            }
            else
            {
                printf("\t\t| %s\n", vetorTestes[i].caracterizacao);
                printf("\t\t| tipo - Antigenio\n");
            }
            printf("\t\t| numero utente - %d\n\t", vetorTestes[i].utente);
            escreverData(vetorTestes[i].dataRealizacao);
            if (vetorTestes[i].resultado == -1)
            {
                printf("\t\t| resultado - sem resultado\n");
            }
            else
            {
                switch (vetorTestes[i].resultado)
                {
                case 0:
                    printf("\t\t| resultado - positivo\n");
                    break;
                case 1:
                    printf("\t\t| resultado - negativo\n");
                    break;
                case 2:
                    printf("\t\t| resultado - inconclusivo\n");
                    break;
                }
                printf("\t");
                escreveHora(vetorTestes[i].horaColheita);
                printf("\t\t| duracao - %d\n", vetorTestes[i].duracao);
            }
            printf("\t\t|\n");
        }
    }
}

/*
 * Função:  resultado_teste
 * ------------------------------
 * Registar resultado de um determinado teste
 *
 * vetorMembros: vetor com os membros
 * vetorTestes: vetor com os testes
 * totalMembros: total dos membros da comunidade
 * testes_agendados: testes que já estão agendados
 * quantTestesRealizados: quantidade dos testes realizados
 *
 * returns: tipo_teste_diagnostico (vetor dos testes)
 */
tipo_teste_diagnostico *resultado_teste(tipo_membro_comunidade_academica vetorMembros[], tipo_teste_diagnostico vetorTestes[], int totalMembros, int *testes_agendados, int *quantTestesRealizados, tipo_teste_diagnostico *dadosTeste)
{
    int nr_utente, verifica, duracao, resultado;
    int posTestes_utente; // verifica a posicao do vetor onde esta aquele teste de um determinado utente
    int completa = 0;
    tipoHora hora;
    char teste[MAX_NOME];
    int testes_empty = 0;

    limpaEcraInicial();

    // Verifica se existem teste sem resultado para efetuar o seu registado
    for (int i = 0; i < *testes_agendados; i++)
    {
        if(vetorTestes[i].resultado == -1){
            testes_empty += 1;
        }
    }

    if (testes_empty == 0) {
      printf("\t| Nao existem testes agendados sem resultado\n\n\n");
      return vetorTestes;
    }
    
    // Mostra os testes existentes sem resultado
    printf("\t|\n");
    printf("\t| Testes Agendados Sem Resultado\n");
    printf("\t|-----------------------------\n");
    for (int i = 0; i < *testes_agendados; i++)
    {
        if(vetorTestes[i].resultado == -1){
            printf("\t| %s\n", vetorTestes[i].caracterizacao);
        }
    }
    printf("\t|\n\t|\n");

    lerSring(teste, MAX_NOME, "Introduza a caracterizacao do teste");
    verifica = procuraTeste_caracterizacao(vetorTestes, *testes_agendados, teste, &posTestes_utente, &nr_utente);
    if (verifica == -1)
    {
        printf("\t\t-> Caracterizacao do teste invalido\n");
    }
    else
    {
        if (vetorTestes[posTestes_utente].resultado != -1)
        {
            printf("\t| O resultado do teste que selecionou ja foi registado");
        }
        else
        {
            printf("\t|\n");
            printf("\t| %d -> Positivo\n", POSITIVO);
            printf("\t| %d -> Negativo\n", NEGATIVO);
            printf("\t| %d -> Incoclusivo\n", INCONCLUSIIVO);

            resultado = lerInteiro(0, 2, "Selecione o resultado obtido no teste");

            switch (resultado)
            {
            case POSITIVO:
                if (vetorTestes[posTestes_utente].tipo == TESTE_ANTIGENIO)
                {
                    do
                    {
                        //=============Quando o teste dá antigenio positivo tenho de agendar pcr e a data tem de ser mais recente que a do teste realizado aqui
                        vetorTestes = agenda_PCR(vetorTestes, testes_agendados, nr_utente, &completa, vetorTestes[posTestes_utente].dataRealizacao);
                    } while (completa != 1);
                }
                // por em isolamento profilático
                break;
            case INCONCLUSIIVO:
                do
                {
                    //=============Quando o teste dá antigenio positivo tenho de agendar pcr e a data tem de ser mais recente que a do teste realizado aqui
                    vetorTestes = agenda_PCR(vetorTestes, testes_agendados, nr_utente, &completa, vetorTestes[posTestes_utente].dataRealizacao);
                } while (completa != 1);
                // por em Quarentena

                break;
            default:
                break;
            }
            vetorTestes[posTestes_utente].resultado = resultado;

            // hora colheita
            hora = lerHora("Insira a hora em que foi realizado o teste");
            vetorTestes[posTestes_utente].horaColheita = hora;

            // Duração
            duracao = lerInteiro(1, 60, "Introduza a duracao do teste");
            vetorTestes[posTestes_utente].duracao = duracao;

            gravaResultadoTeste_texto(vetorMembros, vetorTestes, nr_utente, posTestes_utente, totalMembros);
            *dadosTeste = vetorTestes[posTestes_utente];

            (*quantTestesRealizados)++;
        }
    }
    printf("\n\n\n");
    return vetorTestes;
}

/*
 * Função:  informacaoTeste
 * ------------------------------
 * Registar resultado de um determinado teste
 *
 * vetorMembros: vetor com os membros
 * vetorTestes: vetor com os testes
 * totalMembros: total dos membros da comunidade
 * totalTestes: total dos testes agendados
 * returns: void
 */
void informacaoTeste(tipo_membro_comunidade_academica vetorMembros[], tipo_teste_diagnostico vetorTestes[], int totalMembros, int totalTestes)
{
    limpaEcraInicial();

    int verifica;
    char teste[MAX_NOME];
    int posTestes_utente, posMembros_utente, nr_utente;
    int quantPositivos;

    if (totalTestes <= 0) {
        printf("\t| Sem testes disponiveis\n");
        return;
    }

    printf("\t|\n");
    printf("\t| Testes Registados\n");
    printf("\t|-----------------------------\n");
    for (int i = 0; i < totalTestes; i++)
    {
        printf("\t| %s\n", vetorTestes[i].caracterizacao);
    }
    printf("\t|\n\t|\n");
    lerSring(teste, MAX_NOME, "Qual teste pretende visualizar");
    verifica = procuraTeste_caracterizacao(vetorTestes, totalTestes, teste, &posTestes_utente, &nr_utente);
    if (verifica == -1)
    {
        printf("\t| Nao selecionou um teste apresentado\n");
        return;
    }
    
    posMembros_utente = procuraMembro(vetorMembros, totalMembros, nr_utente);
    printf("\t|\n");
    printf("\t|---------------------------------\n");
    printf("\t| Membro da comunidade -> %s\n", vetorMembros[posMembros_utente].nome);
    switch (vetorMembros[posMembros_utente].tipo_membro)
    {
    case ESTUDANTE:
        printf("\t| Tipo Membro -> Estudante\n");
        break;
    case DOCENTE:
        printf("\t| Tipo Membro -> Docente\n");
        break;
    case TECNICO:
        printf("\t| Tipo Membro -> Tecnico\n");
        break;
    }
    quantPositivos = nr_testes_positivos(vetorTestes, totalTestes, nr_utente);
    printf("\t| Numero de Testes Positivos -> %d\n", quantPositivos);

    printf("\t|\n");
    printf("\t|-------------- Dados do Teste Selecionado ------------------\n");
    printf("\t| %s\n", vetorTestes[posTestes_utente].caracterizacao);
    if (vetorTestes[posTestes_utente].tipo == 0)
    {
        printf("\t| tipo - PCR\n");
    }
    else
    {
        printf("\t| tipo - Antigenio\n");
    }
    printf("\t| numero utente - %d\n", vetorTestes[posTestes_utente].utente);
    printf("\t|\n");
    printf("\t| Data da realizacao\n");
    escreverData(vetorTestes[posTestes_utente].dataRealizacao);
    printf("\t|\n");
    if (vetorTestes[posTestes_utente].resultado == -1)
    {
        printf("\t| resultado - sem resultado\n");
    }
    else
    {
        switch (vetorTestes[posTestes_utente].resultado)
        {
        case 0:
            printf("\t| resultado - positivo\n");
            break;
        case 1:
            printf("\t| resultado - negativo\n");
            break;
        case 2:
            printf("\t| resultado - inconclusivo\n");
            break;
        }
        printf("\t|\n");
        printf("\t| Hora da realizacao\n");
        escreveHora(vetorTestes[posTestes_utente].horaColheita);
        printf("\t|\n");
        printf("\t| duracao - %d minutos\n", vetorTestes[posTestes_utente].duracao);
    }
    printf("\t|\n");
}

/*
 * Função:  dadosEstatisticos
 * ------------------------------
 * Apresenta dados estatísticos dos membros e dos testes realizados
 *
 * vetorMembros: vetor com os membros
 * vetorTestes: vetor com os testes
 * totalMembros: total dos membros da comunidade
 * totalTestes: total dos testes agendados
 * testesRealizados: numero de testes realizados
 * returns: void
 */
void dadosEstatisticos(tipo_membro_comunidade_academica vetorMembros[], tipo_teste_diagnostico vetorTestes[], int totalMembros, int totalTestes, int testesRealizados)
{
    limpaEcraInicial();
    if (totalMembros == 0)
    {
        printf("\t| Adicione Membros para apresentar dados estatisticos\n");
        return;
    }
    if (testesRealizados == 0)
    {
        printf("\t| Registe o resutado de testes agendados\n");
        return;
    }
    
    int membros_estudante = 0, membros_docente = 0, membros_tecnico = 0;
    int i, soma = 0, nr_testes = 0;
    float resultado, percentagem_inconclusivos = 0;

    for (i = 0; i < totalMembros; i++)
    {
        switch (vetorMembros[i].tipo_membro)
        {
        case ESTUDANTE:
            membros_estudante++;
            break;
        case DOCENTE:
            membros_docente++;
            break;
        case TECNICO:
            membros_tecnico++;
            break;
        }
    }

    for (i = 0; i < totalTestes; i++)
    {
        if (vetorTestes[i].resultado != -1)
        {
            soma += vetorTestes[i].duracao;
            nr_testes++;
        }
    }
    resultado = (float)soma / nr_testes;

    nr_testes = 0;
    for (i = 0; i < totalTestes; i++)
    {
        if (vetorTestes[i].resultado == INCONCLUSIIVO)
        {
            percentagem_inconclusivos++;
        }
        nr_testes++;
    }
    percentagem_inconclusivos = ((float)percentagem_inconclusivos / nr_testes) * 100;

    printf("\t\t|\n");
    printf("\t\t| Dados Estatisticos\n");
    printf("\t\t|------------------------------------------------\n");
    printf("\t\t|\n");
    printf("\t\t| Tipos de membros da comunidade academica\n");
    printf("\t\t|\n");
    printf("\t\t| Estudantes -> %d\n", membros_estudante);
    printf("\t\t|\n");
    printf("\t\t| Docentes -> %d\n", membros_docente);
    printf("\t\t|\n");
    printf("\t\t| Tecnicos -> %d\n", membros_tecnico);
    printf("\t\t|\n");
    printf("\t\t|------------------------------------\n");
    printf("\t\t|\n");
    printf("\t\t| Tempo Medio de Duracao de cada Teste Realizado -> %.2f minutos\n", resultado);
    printf("\t\t|\n");
    printf("\t\t| Percentagem de Testes Inconclusivos -> %.2f%%\n", percentagem_inconclusivos);

    menorQuantidade_testes(vetorMembros, vetorTestes, totalMembros, totalTestes);
    printf("\t\t|--------------------------------\n");
    testesRealizados_recentemente(vetorTestes, totalTestes);
    printf("\t\t|\n\n");

}
/*
 * Função:  gravaFicheiroBinarioMembros
 * ------------------------------
 * Guarda os membros em um ficheiro binário
 *
 * vetorMembros: vetor com os membros
 * totalMembros: contagem dos membros existentes
 * returns: void
 */
void gravaFicheiroBinarioMembros(tipo_membro_comunidade_academica vetorMembros[], int totalMembros)
{
    FILE *ficheiro;
    int nElementosEscritos = 0;

    // Guarda Membros
    ficheiro = fopen("dadosMembros.bin", "wb");

    if (ficheiro == NULL)
    {
        printf("\n Membros da Comunidade (ERRO): falha na abertura do ficheiro\n");
    }
    else
    {
        nElementosEscritos = fwrite(&totalMembros, sizeof(int), 1, ficheiro);
        if (nElementosEscritos != 1)
        {
            printf("\n Membros da Comunidade (ERRO): Falha na gravacao dos dados\n");
        }
        else
        {
            nElementosEscritos = fwrite(vetorMembros, sizeof(tipo_membro_comunidade_academica), totalMembros, ficheiro);
            if (nElementosEscritos != totalMembros)
            {
                printf("\n Membros da Comunidade (ERRO): Falha na gravacao dos dados\n");
            }
            else
            {
                printf("\n Membros da Comunidade: Gravacao efetuada com sucesso\n");
            }
        }
        fclose(ficheiro);
    }
}

/*
 * Função:  gravaFicheiroBinarioTestes
 * ------------------------------
 * Guarda os testes em um ficheiro binário
 *
 * vetorTestes: vetor com os testes
 * testes_agendados: contagem dos testes existentes
 * returns: void
 */
void gravaFicheiroBinarioTestes(tipo_teste_diagnostico vetorTestes[], int testes_agendados)
{
    // Guarda Testes
    FILE *ficheiro;
    int nElementosEscritos = 0;

    ficheiro = fopen("dadosTestes.bin", "wb");

    if (ficheiro == NULL)
    {
        printf("\n Testes Agendados (ERRO): falha na abertura do ficheiro\n");
    }
    else
    {
        nElementosEscritos = fwrite(&testes_agendados, sizeof(int), 1, ficheiro);
        if (nElementosEscritos != 1)
        {
            printf("\n Testes Agendados (ERRO): Falha na gravacao dos dados\n");
        }
        else
        {
            nElementosEscritos = fwrite(vetorTestes, sizeof(tipo_teste_diagnostico), testes_agendados, ficheiro);

            if (nElementosEscritos != testes_agendados)
            {
                printf("\n Testes Agendados (ERRO): Falha na gravacao dos dados\n");
            }
            else
            {
                printf("\n Testes Agendados: Gravacao efetuada com sucesso\n");
            }
        }
        fclose(ficheiro);
    }
}

/*
 * Função:  gravaFicheiroBinario_testesRealizados
 * ------------------------------
 * Guarda os testes realizados em um ficheiro binário
 *
 * testesRealizados: numero de testes realizados
 * returns: void
 */
void gravaFicheiroBinario_testesRealizados(int testesRealizados)
{
    // Guarda Testes
    FILE *ficheiro;
    int nElementosEscritos = 0;

    ficheiro = fopen("testesRealizados.bin", "wb");

    if (ficheiro == NULL)
    {
        printf("\n Testes Realizados (ERRO): falha na abertura do ficheiro\n");
    }
    else
    {
        nElementosEscritos = fwrite(&testesRealizados, sizeof(int), 1, ficheiro);
        if (nElementosEscritos != 1)
        {
            printf("\n Testes Realizados (ERRO): Falha na gravacao dos dados\n");
        }
        else
        {
            printf("\n Testes Realizados: Gravacao efetuada com sucesso\n");
        }
        fclose(ficheiro);
    }
}

/*
 * Função:  lerFicheiroBinario_testesRealizados
 * ------------------------------
 * Lê os testes realizados em um ficheiro binário
 *
 * testesRealizados: numero de testes realizados
 * returns: void
 */
void lerFicheiroBinario_testesRealizados(int *testesRealizados)
{
    // Guarda Testes
    FILE *ficheiro;
    int nElementosLidos = 0;

    ficheiro = fopen("testesRealizados.bin", "rb");

    if (ficheiro == NULL)
    {
        printf("\n Testes Realizados: Sem Dados Encontrados\n");
    }
    else
    {
        nElementosLidos = fread(testesRealizados, sizeof(int), 1, ficheiro);

        if (nElementosLidos != 1)
        {
            *testesRealizados = 0;
            printf("\n Testes Realizados (ERRO): Falha na leitura dos dados\n");
        }
        else
        {
            printf("\n Testes Realizados: Carregamento efetuado com sucesso\n");
        }
        fclose(ficheiro);
    }
}
/*
 * Função:  lerFicheiroBinarioMembros
 * ------------------------------
 * Lê os membros a partir de um ficheiro
 *
 * vetorMembros: vetor com os mebros existentes
 * totalMembros: contagem dos membros existentes
 * returns: void
 */
void lerFicheiroBinarioMembros(tipo_membro_comunidade_academica vetorMembros[], int *totalMembros)
{
    FILE *ficheiro;
    int nElementosLidos = 0;

    ficheiro = fopen("dadosMembros.bin", "rb");

    if (ficheiro == NULL)
    {
        printf("\n Membros da Comunidade: Sem Dados Encontrados\n");
    }
    else
    {
        // nElementosEscritos = fread(&*totalMembros, sizeof(int), 1, ficheiro);
        nElementosLidos = fread(totalMembros, sizeof(int), 1, ficheiro);

        if (nElementosLidos != 1)
        {
            *totalMembros = 0;
            printf("\n Membros da Comunidade (ERRO): Falha na leitura dos dados\n");
        }
        else
        {
            nElementosLidos = fread(vetorMembros, sizeof(tipo_membro_comunidade_academica), *totalMembros, ficheiro);
            if (nElementosLidos != *totalMembros)
            {
                printf("\n Membros da Comunidade (ERRO): Falha na leitura dos dados\n");
            }
            else
            {
                printf("\n Membros da Comunidade: Carregamento efetuado com sucesso\n");
            }
        }
        fclose(ficheiro);
    }
}

/*
 * Função:  lerFicheiroBinarioTestes
 * ------------------------------
 * Lê os membros a partir de um ficheiro
 *
 * vetorTestes: vetor com os com os testes existentes
 * testes_agendados: contagem dos testes existentes
 * returns: tipo_teste_diagnostico
 */
tipo_teste_diagnostico *lerFicheiroBinarioTestes(tipo_teste_diagnostico *vetorTestes, int *testes_agendados)
{
    FILE *ficheiro;
    int nElementosLidos = 0;

    ficheiro = fopen("dadosTestes.bin", "rb");

    if (ficheiro == NULL)
    {
        printf("\n Testes Agendados: Sem Dados Encontrados\n");
    }
    else
    {
        // nElementosEscritos = fread(&*totalMembros, sizeof(int), 1, ficheiro);
        nElementosLidos = fread(testes_agendados, sizeof(int), 1, ficheiro);

        if (nElementosLidos != 1)
        {
            *testes_agendados = 0;
            printf("\n Testes Agendados (ERRO): Falha na leitura dos dados\n");
        }
        else
        {

            vetorTestes = realloc(vetorTestes, (*testes_agendados) * sizeof(tipo_teste_diagnostico));
            if (vetorTestes == NULL)
            {
                printf("\n Testes Agendados (ERRO): Erro em alocar a memoria\n");
            }
            else
            {
                nElementosLidos = fread(vetorTestes, sizeof(tipo_teste_diagnostico), (*testes_agendados), ficheiro);

                if (nElementosLidos != *testes_agendados)
                {
                    printf("\n Testes Agendados (ERRO): Falha na leitura dos dados\n");
                }
                else
                {
                    printf("\n Testes Agendados: Carregamento efetuado com sucesso\n");
                }
            }
        }
        fclose(ficheiro);
    }
    return vetorTestes;
}

void gravaResultadoTeste_texto(tipo_membro_comunidade_academica vetorMembros[], tipo_teste_diagnostico vetorTestes[], int nr_utente, int pos_utente_testes, int totalMembros)
{
    FILE *ficheiro;
    int nr_utente_vetor;
    ficheiro = fopen("logResultadoTestes.txt", "a");
    if (ficheiro == NULL)
    {
        printf("\nERRO: falha na abertura do ficheiro\n");
    }
    else
    {
        nr_utente_vetor = procuraMembro(vetorMembros, totalMembros, nr_utente);
        fprintf(ficheiro, "\n\n----------- Listagem do Resultado do Teste do Aluno: %s ------------\n", vetorMembros[nr_utente_vetor].nome);
        switch (vetorMembros[nr_utente_vetor].estado_vacinacao)
        {
        case NAO_VACINADO:
            fprintf(ficheiro, "Estado da Vacinacao -> Nao Vacinado\n");
            break;

        case VACINA_DOSE1:
            fprintf(ficheiro, "Estado da Vacinacao -> Vacina com 1 dose\n");
            break;

        case VACINA_DOSE2:
            fprintf(ficheiro, "Estado da Vacinacao -> Vacina com 2 doses\n");
            break;

        case VACINA_DOSE3:
            fprintf(ficheiro, "Estado da Vacinacao -> Vacina com 3 doses\n");
            break;
        }
        fprintf(ficheiro, "Caracterizacao -> %s\n", vetorTestes[pos_utente_testes].caracterizacao);
        switch (vetorTestes[pos_utente_testes].tipo)
        {
        case TESTE_PCR:
            fprintf(ficheiro, "Tipo -> PCR\n");
            break;

        case TESTE_ANTIGENIO:
            fprintf(ficheiro, "Tipo -> Antigenio\n");
            break;
        }
        fprintf(ficheiro, "Data da Realizacao -> %02d-%02d-%d\n", vetorTestes[pos_utente_testes].dataRealizacao.dia, vetorTestes[pos_utente_testes].dataRealizacao.mes, vetorTestes[pos_utente_testes].dataRealizacao.ano);
        switch (vetorTestes[pos_utente_testes].resultado)
        {
        case POSITIVO:
            fprintf(ficheiro, "Resultado --> Positivo\n");
            break;
        case NEGATIVO:
            fprintf(ficheiro, "Resultado --> Negativo\n");
            break;
        case INCONCLUSIIVO:
            fprintf(ficheiro, "Resultado --> Inconclusivo\n");
            break;
        }
        fprintf(ficheiro, "Hora da Realizacao -> %02d:%02d:%02d\n", vetorTestes[pos_utente_testes].horaColheita.hora, vetorTestes[pos_utente_testes].horaColheita.minuto, vetorTestes[pos_utente_testes].horaColheita.segundo);
        fprintf(ficheiro, "Duracao -> %d minutos", vetorTestes[pos_utente_testes].duracao);
    }
}
int membrosVacinados(tipo_membro_comunidade_academica vetorMembros[], int totalMembros)
{
    int contador = 0;
    for (int i = 0; i < totalMembros; i++)
    {
        if (vetorMembros[i].estado_vacinacao != NAO_VACINADO)
        {
            contador++;
        }
    }
    return contador;
}
