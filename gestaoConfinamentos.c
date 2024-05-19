#include <stdio.h>
#include <stdlib.h>
#include "funcoesGenericas.h"
#include "gestaoConfinamentos.h"
#include "gestaoTestagem.h"

/*
 * Função:  confinaMembro
 * --------------------
 *  Confina um membro da comunidade academica, extendendo tambem o vetor dinamico
 *
 *  vetorConfinamento: vetor com os confinamentos da comunidade academica
 *  totalConfinamentos: ponteiro com o total (contagem) de confinamentos
 *  vetorMembros: vetor com os membros da comunidade academica
 *  totalMembros: ponteiro com o total (contagem) de membros
 *  numeroMembro: numero de utente do membro a confinar
 *  tipoConfinamento: tipo de confinamento a colocar o membro
 *  data: pode ser usada para marcar o inicio de confinamento ou para fim, se o ano for -1 pede ao utilizador uma data
 *  returns: tipo_confinamento (vetor dinamico)
 */
tipo_confinamento *confinaMembro(tipo_confinamento *vetorConfinamento, int *totalConfinamentos, tipo_membro_comunidade_academica vetorMembros[], int totalMembros, int numeroMembro, int tipoConfinamento, tipoData data)
{
	int posicaoMembro;
	int posicaoConfinamento;
	int flag = 0;
	float diasEntreDatas;
	tipo_confinamento *vetorBackup = vetorConfinamento;
	tipoData dataInserida;
	if (numeroMembro != -1)
	{
		posicaoMembro = procuraMembro(vetorMembros, totalMembros, numeroMembro);
		if (posicaoMembro == -1)
		{
			printf("\n\t\t-> ERRO! Membro nao existente\n");
      return vetorConfinamento;
		}
		
    vetorConfinamento = realloc(vetorConfinamento, (*totalConfinamentos + 1) * sizeof(tipo_confinamento));
    if (vetorConfinamento == NULL && *totalConfinamentos != 0)
    {
      printf("\n\t\t-> ERRO na alocacao de memoria! Os dados anteriores foram restaurados\n");
      vetorConfinamento = vetorBackup;
      return vetorConfinamento;
    }
    
    if (vetorMembros[posicaoMembro].estadoConfinamento != tipoConfinamento)
    {

      if (tipoConfinamento != NAO_CONFINADO)
      {
        // Confina o membro

        vetorConfinamento[*totalConfinamentos].n_utente = numeroMembro;
        vetorConfinamento[*totalConfinamentos].tipo_confinamento = tipoConfinamento;
        if (data.ano == -1)
        {
          vetorConfinamento[*totalConfinamentos].dataConfinamento = lerData("Insira a data de inicio do confinamento");
        }
        else
        {
          vetorConfinamento[*totalConfinamentos].dataConfinamento = data;
        }

        vetorConfinamento[*totalConfinamentos].duracao = -1;
        vetorMembros[posicaoMembro].estadoConfinamento = tipoConfinamento;

        (*totalConfinamentos)++;
      }
      else
      {
        // Desconfinar o membro
        posicaoConfinamento = procuraUltimoConfinamento(vetorConfinamento, *totalConfinamentos, numeroMembro);
        vetorMembros[posicaoMembro].estadoConfinamento = NAO_CONFINADO;
        if (data.ano == -1)
        {
          do
          {
            dataInserida = lerData("Insira a data de fim do confinamento");
            diasEntreDatas = diferencaEntreDatas(vetorConfinamento[posicaoConfinamento].dataConfinamento, dataInserida);

            if (diasEntreDatas < 0)
            {
              printf("\t\t-> ERRO: data inserida nao pode ser anterior a data do confinamento!\n");
              flag = 1;
            }
            else
            {
              flag = 0;
              vetorConfinamento[posicaoConfinamento].duracao = diasEntreDatas;
            }
          } while (flag);
        }
        else
        {
          vetorConfinamento[posicaoConfinamento].duracao = diferencaEntreDatas(vetorConfinamento[posicaoConfinamento].dataConfinamento, data);
        }
      }
    }
    
	}
	return vetorConfinamento;
}

/*
 * Função:  gestaoConfinamentos
 * --------------------
 *  Pede ao utilizador um numero de utente, valida-o e pede confirmacao de alteracao de estado.
 *  Faz também decisões sobre o tipo de confinamento a colocar
 *
 *  vetorConfinamento: vetor com os confinamentos da comunidade academica
 *  totalConfinamentos: ponteiro com o total (contagem) de confinamentos
 *  vetorMembros: vetor com os membros da comunidade academica
 *  totalMembros: ponteiro com o total (contagem) de membros
 *  returns: tipo_confinamento (vetor dinamico)
 */
tipo_confinamento *gestaoConfinamentos(tipo_confinamento *vetorConfinamento, int *totalConfinamentos, tipo_membro_comunidade_academica vetorMembros[], int totalMembros)
{
	int numUtente, posicaoMembro;
	char bufferMensagem[150];

  limpaEcra();
	numUtente = lerInteiro(MIN_UTENTE, MAX_UTENTE, "Insira o numero de utente");

	posicaoMembro = procuraMembro(vetorMembros, totalMembros, numUtente);
	if (posicaoMembro == -1)
	{
		printf("\t\t-> Membro nao encontrado!\n\n\n");
    return vetorConfinamento;
	}

  sprintf(bufferMensagem, "Pretende mesmo alterar o estado de confinamento do membro %s (%d)", vetorMembros[posicaoMembro].nome, vetorMembros[posicaoMembro].num_utente);
  if (pedeConfirmacao(bufferMensagem))
  {
    // Atualizar estado de confinamento do membro
    int estado;
    switch (vetorMembros[posicaoMembro].estadoConfinamento) {
        case NAO_CONFINADO:
          if (!pedeConfirmacao("Pretende colocar o membro em isolamento?")){
            printf("\t| Operacao Cancelada!\n\n\n");
            return vetorConfinamento;
          }
          estado = ISOLAMENTO_PROFILATICO;
      break;
        default:
          if (!pedeConfirmacao("Pretende tirar o membro de confinamento?")){
            printf("\t| Operacao Cancelada!\n\n\n");
            return vetorConfinamento;
          }
          estado = NAO_CONFINADO;
      break;
    }

    vetorConfinamento = confinaMembro(vetorConfinamento, totalConfinamentos, vetorMembros, totalMembros, numUtente, estado, dataNula());
    
  }
  else
  {
    printf("\t| Operacao Cancelada!\n");
  }

  printf("\n\n");
	
	return vetorConfinamento;
}

void listarConfinamentosPorMembro(tipo_confinamento *vetorConfinamento, int totalConfinamentos, tipo_membro_comunidade_academica vetorMembros[], int totalMembros)
{
  limpaEcraInicial();

	int posicaoMembro;
  int numeroMembro;
  int confinamentosPorMembro = 0;

	if (totalConfinamentos == 0)
	{
		printf("\t| Nao existem confinamentos\n");
    return;
	}

  numeroMembro = lerInteiro(MIN_UTENTE, MAX_UTENTE, "Introduza o numero do utente de saude");
  posicaoMembro = procuraMembro(vetorMembros, totalMembros, numeroMembro);

  if (posicaoMembro == -1) {
    printf("\t\t-> Utente nao encontrado!\n\n");
    return;
  }

  for (int i = 0; i < totalConfinamentos; i++){
    if(vetorConfinamento[i].n_utente == numeroMembro){
        confinamentosPorMembro += 1;
    }
  }

  if (confinamentosPorMembro == 0) {
    printf("\t| Nao existem confinamentos associado ao utente %d \n",numeroMembro);
    return;
  }
	
  printf("\t|\n");
  printf("\t|\n");
  printf("\t| Informacoes Gerais do Utente\n");
  printf("\t|-----------------------------\n");
  printf("\t| Numero de Utente: %d\n", numeroMembro);
  printf("\t| Nome: %s\n", vetorMembros[posicaoMembro].nome);
  printf("\t|\n");
  printf("\t|\n");
  printf("\t| Confinamentos do Utente\n");
  printf("\t|-----------------------------\n");
  for (int i = 0; i < totalConfinamentos; i++)
  {

    if (vetorConfinamento[i].n_utente != numeroMembro) {
      continue;
    }

    printf("\t|\n");
    printf("\t| Data de inicio: %d-%d-%d \n", vetorConfinamento[i].dataConfinamento.dia, vetorConfinamento[i].dataConfinamento.mes, vetorConfinamento[i].dataConfinamento.ano);
    printf("\t| Estado de confinamento: ");

    switch (vetorConfinamento[i].tipo_confinamento)
    {
    case NAO_CONFINADO:
      printf("Nao Confinado");
      break;
    case ISOLAMENTO_PROFILATICO:
      printf("Isolamento Profilatico");
      break;
    case QUARENTENA:
      printf("Quarentena");
      break;
    }

    if (vetorConfinamento[i].duracao == -1)
    {
      // Codigo a exectar caso ainda esteja em confinamento
      printf(" (Em curso)");

      printf("\n");
      printf("\t| Duracao: ");
      printf("Ainda em confinamento");
    }
    else
    {
      // Codigo a exectar caso o confinamento tenha acabado
      printf(" (Terminado)");
      printf("\n");
      printf("\t| Duracao: ");
      printf("%d Dias", vetorConfinamento[i].duracao);
    }
    printf("\n");
    printf("\t|\n");
  }
}

void listarConfinamentos(tipo_confinamento *vetorConfinamento, int totalConfinamentos, tipo_membro_comunidade_academica vetorMembros[], int totalMembros)
{
	limpaEcraInicial();

	int posicaoMembro;
	if (totalConfinamentos == 0)
	{
		printf("\t| Nao existem confinamentos\n");
    return;
	}
	
  printf("\t|\n");
  printf("\t| Confinamentos\n");
  printf("\t|-----------------------------\n");
  for (int i = 0; i < totalConfinamentos; i++)
  {
    posicaoMembro = procuraMembro(vetorMembros, totalMembros, vetorConfinamento[i].n_utente);
    printf("\t|\n");

    printf("\t| Numero de Utente: %d\n", vetorMembros[posicaoMembro].num_utente);
    printf("\t| Nome: %s\n", vetorMembros[posicaoMembro].nome);
    printf("\t| Data de inicio: %d-%d-%d \n", vetorConfinamento[i].dataConfinamento.dia, vetorConfinamento[i].dataConfinamento.mes, vetorConfinamento[i].dataConfinamento.ano);
    printf("\t| Estado de confinamento: ");

    switch (vetorConfinamento[i].tipo_confinamento)
    {
    case NAO_CONFINADO:
      printf("Nao Confinado");
      break;
    case ISOLAMENTO_PROFILATICO:
      printf("Isolamento Profilatico");
      break;
    case QUARENTENA:
      printf("Quarentena");
      break;
    }

    if (vetorConfinamento[i].duracao == -1)
    {
      // Codigo a exectar caso ainda esteja em confinamento
      printf(" (Em curso)");

      printf("\n");
      printf("\t| Duracao: ");
      printf("Ainda em confinamento");
    }
    else
    {
      // Codigo a exectar caso o confinamento tenha acabado
      printf(" (Terminado)");
      printf("\n");
      printf("\t| Duracao: ");
      printf("%d Dias", vetorConfinamento[i].duracao);
    }
    printf("\n");
    printf("\t|\n");
  }
}

/*
 * Função:  procuraUltimoConfinamento
 * --------------------
 *  Procura o confinamento mais recente de um certo membro da comunidade
 *
 *  vetorConfinamento: vetor com os confinamentos da comunidade academica
 *  totalConfinamentos: ponteiro com o total (contagem) de confinamentos
 *  numeroMembro: numero de utente do membro a procurar
 *  returns: posicao no vetor confinamento
 */
int procuraUltimoConfinamento(tipo_confinamento *vetorConfinamento, int totalConfinamentos, int numeroUtente)
{
	int posicao = -1;
	for (int i = totalConfinamentos; i >= 0; i--)
	{
		if (vetorConfinamento[i].n_utente == numeroUtente)
		{
			posicao = i;
			i = 0;
		}
	}
	return posicao;
}

/*
 * Função:  lerFicheiroBinarioConfinamentos
 * ------------------------------
 * Lê os confinamentos a partir de um ficheiro
 *
 * vetorConfinamento: vetor com os confinamentos existentes
 * totalConfinamentos: contagem dos confinamentos existentes
 * returns: tipo_confinamento
 */
tipo_confinamento *lerFicheiroBinarioConfinamentos(tipo_confinamento *vetorConfinamento, int *totalConfinamentos)
{
	FILE *ficheiro;
	int nElementosLidos = 0;

	ficheiro = fopen("dadosConfinamentos.bin", "rb");

	if (ficheiro == NULL)
	{
		printf("\n Registo Confinamentos: Sem Dados Encontrados\n");
	}
	else
	{
		// nElementosEscritos = fread(&*totalMembros, sizeof(int), 1, ficheiro);
		nElementosLidos = fread(totalConfinamentos, sizeof(int), 1, ficheiro);

		if (nElementosLidos != 1)
		{
			*totalConfinamentos = 0;
			printf("\n Registo Confinamentos (ERRO): Falha na leitura dos dados\n");
		}
		else
		{

			vetorConfinamento = realloc(vetorConfinamento, (*totalConfinamentos) * sizeof(tipo_confinamento));
			if (vetorConfinamento == NULL)
			{
				printf("Registo Confinamentos (ERRO): Erro em alocar a memoria");
			}
			else
			{
				nElementosLidos = fread(vetorConfinamento, sizeof(tipo_confinamento), (*totalConfinamentos), ficheiro);

				if (nElementosLidos != *totalConfinamentos)
				{
					printf("\n Registo Confinamentos (ERRO): Falha na leitura dos dados\n");
				}
				else
				{
					printf("\n Registo Confinamentos: Carregamento efetuado com sucesso\n");
				}
			}
		}
		fclose(ficheiro);
	}
	return vetorConfinamento;
}

/*
 * Função:  gravaFicheiroBinarioConfinamentos
 * ------------------------------
 * Guarda os confinamentos em um ficheiro binário
 *
 * vetorConfinamento: vetor com os confinamentos existentes
 * totalConfinamentos: contagem dos confinamentos existentes
 * returns: void
 */
void gravaFicheiroBinarioConfinamentos(tipo_confinamento *vetorConfinamento, int totalConfinamentos)
{
	// Guarda Testes
	FILE *ficheiro;
	int nElementosEscritos = 0;

	ficheiro = fopen("dadosConfinamentos.bin", "wb");

	if (ficheiro == NULL)
	{
		printf("\n Registo Confinamentos (ERRO): falha na abertura do ficheiro\n");
	}
	else
	{
		nElementosEscritos = fwrite(&totalConfinamentos, sizeof(int), 1, ficheiro);
		if (nElementosEscritos != 1)
		{
			printf("\n Registo Confinamentos (ERRO): Falha na gravacao dos dados\n");
		}
		else
		{
			nElementosEscritos = fwrite(vetorConfinamento, sizeof(tipo_confinamento), totalConfinamentos, ficheiro);

			if (nElementosEscritos != totalConfinamentos)
			{
				printf("\n Registo Confinamentos (ERRO): Falha na gravacao dos dados\n");
			}
			else
			{
				printf("\n Registo Confinamentos: Gravacao efetuada com sucesso\n");
			}
		}
		fclose(ficheiro);
	}
}

/*
 * Função:  dataNula
 * ------------------------------
 * Retorna uma data com ano,dia e mes tudo a -1.
 *
 * returns: data
 */
tipoData dataNula()
{
	tipoData data;
	data.ano = -1;
	data.dia = -1;
	data.mes = -1;

	return data;
}
