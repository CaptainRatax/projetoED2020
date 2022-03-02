#ifndef HEADERFILE_H
#define HEADERFILE_H
#include <stdio.h> // main
#include <stdlib.h> // main
#include <string.h> // strings
#include <locale.h> //acentos
#include <time.h> //data atual
#include <stdbool.h>//booleans
#include "livros.h"
#include "livros.c"
#include "requisitantes.c"
#include "requisitantes.h"
#include "auxiliares.c"
#include "auxiliares.h"
#include "freguesias.h"
#include "freguesias.c"
#include "requisicoes.h"

HASHING_REQUISICOES *criarHashingRequisicoes() //cria um hashing requisicoes vazio (aloca espaco)
{
    HASHING_REQUISICOES* hashingReq = (HASHING_REQUISICOES *)malloc(sizeof(HASHING_REQUISICOES)); //aloca memoria para o hashing
    hashingReq->inicio = NULL; //coloca o ponteiro para o inicio a NULL
    hashingReq->nel = 0; //inicializa o numero de elementos em 0
    return hashingReq; //retorna a estrutura que acabou de criar
}

NO_HASHING_REQUISICAO* criarNodoHashingRequisicao() //cria um no_hashing_livros vazio (aloca espaco)
{
	NO_HASHING_REQUISICAO* noHashReq = (NO_HASHING_REQUISICAO *)malloc(sizeof(NO_HASHING_REQUISICAO)); //aloca memoria para o no
	noHashReq->ant = NULL; // coloca o ponteiro para o no seguinte a NULL
	noHashReq->seg = NULL; // coloca o ponteiro para o no anterior a NULL
	return noHashReq; //retorna a estrutura que acabou de criar
}

LISTA_REQUISICOES *criarListaRequisicoes() //cria uma lista de requisicoes (aloca espaco)
{
    LISTA_REQUISICOES *listaReq = (LISTA_REQUISICOES *)malloc(sizeof(LISTA_REQUISICOES));  //aloca memoria para a lista
    listaReq->inicio = NULL; //coloca o ponteiro para o inicio a NULL
    listaReq->nel = 0; //inicializa o numero de elementos em 0
    return listaReq; //retorna a estrutura
}

NO_REQUISICAO *criarNodaRequisicao() //cria um no da requisicao (aloca espaco)
{
    NO_REQUISICAO *noReq = (NO_REQUISICAO *)malloc(sizeof(NO_REQUISICAO)); //aloca memoria para o no da requisicao
    noReq->seg = NULL; //coloca o ponteiro para o no seguinte a NULL
    noReq->ant = NULL; //coloca o ponteiro para o no seguinte a NULL
    noReq->requisicao = NULL; //coloca o ponteiro para a requisicao a NULL
    return noReq; //retorna a estrutura
}

REQUISICAO *criarRequisicao() //cria a requisicao vazia (aloca o espaco)
{
    REQUISICAO *req = (REQUISICAO *)malloc(sizeof(REQUISICAO)); //aloca o espaco para o requisitante
    req->dataInicio = criarData(); //aponta a dataInicio para uma estrutura de data vazia
    req->dataFim = criarData(); //aponta a dataFim para uma estrutura de data vazia
    //inicializa todos os valores das datas e o estado em 0
    req->dataInicio->dia = 0;
    req->dataInicio->mes = 0;
    req->dataInicio->ano = 0;
    req->dataFim->dia = 0;
    req->dataFim->mes = 0;
    req->dataFim->ano = 0;
    req->estado = 0;
    return req; //retorna a estrutura
}

NUM_REQUISICOES *criarNumRequisicoes() //cria a estrutura numRequisicoes vazia (aloca espaco)
{
    NUM_REQUISICOES *numReq = (NUM_REQUISICOES *)malloc(sizeof(NUM_REQUISICOES)); //aloca espaco
    numReq->requisitante = NULL; //coloca o ponteiro para o requisitante a NULL
    numReq->num=0; //inicializa a variavel que guarda o numero de requisicoes
    return numReq; //retorna a estrutura
}

NO_NUM_REQUISICOES *criarNoNumRequisicoes() //cria o noNumRequisicoes (aloca espaco)
{
    NO_NUM_REQUISICOES *noNumReq = (NO_NUM_REQUISICOES *)malloc(sizeof(NO_NUM_REQUISICOES)); //aloca espaco
    noNumReq->seg = NULL; //coloca o poteiro para o no seguinte a NULL
    noNumReq->num_requisicoes = criarNumRequisicoes(); //aponta o num_requisicoes para uma estrutura vazia, mas com o espaco já alocado
    return noNumReq; //retorna a estrutura
}

LISTA_NUM_REQUISICOES *criarListaNumRequisicoes() //cria a listaNumRequisicoes (aloca espaco)
{
    LISTA_NUM_REQUISICOES *listaNumReq = (LISTA_NUM_REQUISICOES *)malloc(sizeof(LISTA_NUM_REQUISICOES)); //aloca espaco
    listaNumReq->inicio = NULL; //coloca o ponteiro para o inicio a NULL
    listaNumReq->nel=0; // inicializa o numero de elementos em 0
    return listaNumReq; //retorna a estrutura
}

void inserirNumRequisicoesNaLista(LISTA_NUM_REQUISICOES* listaNumRequisicoes, NO_NUM_REQUISICOES* noNumRequisicoes)
{
    if (!listaNumRequisicoes) { //verifica a lista recebida
		printf("\nNao existe lista!");
		return; //sai do metodo
	}
	NO_NUM_REQUISICOES* aux = listaNumRequisicoes->inicio; //cria uma variavel auxiliar para percorer o hashing
	while(aux) //enquanto o aux não for NULL (precorre a lista toda)
    {
        if(strcmp(aux->num_requisicoes->requisitante->id_requisitante, noNumRequisicoes->num_requisicoes->requisitante->id_requisitante)==0) //se o id do requisitante do aux for igual ao do no recebido
        {
            aux->num_requisicoes->num++; //incrementa o numero de requisicoes do requisitante
            return; //sai
        }
        aux = aux->seg; //passa para o no seguinte
    }
    //coloca o primeiro em segundo e acrescenta o no que recebeu em primeiro lugar na lista
    noNumRequisicoes->seg = listaNumRequisicoes->inicio; //o seguinte passa a apontar para o primeiro elemento da lista
    listaNumRequisicoes->inicio = noNumRequisicoes; // o inicio da lista passa a ser o novo no que foi recebido
    listaNumRequisicoes->nel++; //incrementa o numero de elementos
}

void lerNumRequisicoes(LISTA_NUM_REQUISICOES* listaNumRequisicoes, LISTA_REQUISITANTES* listaReq) //le o ficheiro txt que guarda todos os numeros de requisicoes dos requisitantes
{
    FILE *ficheiro;
    char nomeficheiro[10];
    strcpy(nomeficheiro, "numRequisicoes.txt"); //nome do ficheiro
    char linha[120];
    char linhaInteira[120];

    ficheiro = fopen(nomeficheiro, "r"); //abre o ficheiro

    char *dados[2]; // 0 - id_requisitante | 1 -  num_requisicoes




    if(!ficheiro)//verifica o ficheiro
    {
        printf("\nNao foi possivel abrir o ficheiro %s\n", nomeficheiro);
        return 0;
    }



    while(!feof(ficheiro))
    {

        if(fgets(linha, 120, ficheiro) != NULL) //verifica se leu bem a linha
        {
            int pos = 0;
            strcpy(linhaInteira, linha);
            char *elemento = strtok(linha, "\t"); //separa a linha por elementos

            while (elemento != NULL) //guarda todos os dados da linha no array dados
            {
                dados[pos] = (char *)malloc((strlen(elemento) + 1) * sizeof(char)); //aloca espaco
                strcpy(dados[pos], elemento);
                pos++;
                elemento = strtok(NULL, "\t");
            }

            NO_NUM_REQUISICOES *noNumRequisicoes = criarNoNumRequisicoes();

            int tamID = strlen(dados[0]);
            dados[0][tamID] = '\0';
            REQUISITANTE* requisitante = pesquisarRequisitantePorID(listaReq ,dados[0]); //pesquisa o requisitante pelo id
            if(!requisitante) //verifica o requisitante
            {
                char mensagem[300];
                strcpy(mensagem, "Nao exite nenhum requisitante com o ID ");
                strcat(mensagem, dados[0]);
                logs(linhaInteira, mensagem); //escreve no ficheiro logs o erro
            }else
            {
                noNumRequisicoes->num_requisicoes->requisitante = requisitante; //guarda o requisitante
                noNumRequisicoes->num_requisicoes->num = atoi(dados[1]); //guarda o numero de requisicoes desse requisitante
                inserirNumRequisicoesNaLista(listaNumRequisicoes, noNumRequisicoes); //isere a estrutura na lista
            }

            //libeta o espaco ocupado do array
            free(dados[0]);
            free(dados[1]);
        }
    }
    fclose(ficheiro); //fecha o ficheiro
}

void gravarNumRequisicoes(LISTA_NUM_REQUISICOES* listaNumRequisicoes) //grava todos os numeros de requisicoes dos requisitantes no ficheiro txt
{
    if(!listaNumRequisicoes || !listaNumRequisicoes->inicio) //verifica a lista e se contem algo
    {
        return; //sai
    }
    FILE *ficheiro;
    ficheiro = fopen("numRequisicoes.txt", "w"); //abre o ficheiro (em escrita(w))
    if(!ficheiro) //verifica o ficheiro
    {
        printf("\nNao foi possivel abrir o ficheiro %s\n", "numRequisicoes.txt");
        return; //sai
    }
    NO_NUM_REQUISICOES *noNumReq = listaNumRequisicoes->inicio;
    while(noNumReq) //enquanto o noNumReq nao e NULL
    {
        fprintf(ficheiro,"%s\t%d\n", noNumReq->num_requisicoes->requisitante->id_requisitante, noNumReq->num_requisicoes->num); //escreve no ficheiro os dados
        noNumReq=noNumReq->seg; // passa para o no seguinte
    }
    fclose(ficheiro); //fecha o ficheiro
}

void apresentarNumRequisicoesRequisitante(LISTA_NUM_REQUISICOES* listaNumRequisicoes, REQUISITANTE* requisitante)
{
    if (!listaNumRequisicoes) //verifica a lista
    {
        printf("\nNao existe lista!");
        return;//sai
    }
	if (!requisitante) //verifica o requisitante
	{
		printf("\nNao existe requisitante!");
		return;//sai
	}
	NO_NUM_REQUISICOES* aux = listaNumRequisicoes->inicio;
	while(aux)//enquanto o aux não é NULL
    {
        if(strcmp(aux->num_requisicoes->requisitante->id_requisitante, requisitante->id_requisitante)==0) //se o id do requisitante e igual ao do requisitante recebido
        {
            if(aux->num_requisicoes->num == 0) //se o numero de requisicoes e 0
            {
                printf("\nEsse requisitante nao tem nenhuma requisicao feita.");
                return;//sai
            }
            printf("\nO requisitante %s tem %d requisicoes feitas.", aux->num_requisicoes->requisitante->nome, aux->num_requisicoes->num);
            return;//sai
        }
        aux = aux->seg; //passa para o no seguinte
    }
    printf("\nEsse requisitante nao tem nenhuma requisicao feita.");
}

void lerFicheiroRequisicoes(HASHING_LIVRO* hashingLiv, HASHING_REQUISICOES* hashingReq, LISTA_REQUISITANTES* listaReq) //le o ficheiro txt que guarda as requisicoes
{
    FILE *ficheiro;
    char nomeficheiro[10];
    strcpy(nomeficheiro, "requisicoes.txt");
    char linha[200];
    char linhaInteira[200];
    ficheiro = fopen(nomeficheiro, "r"); //abre o ficheiro

    char *dados[5]; // 0 - id_requisitante | 1 - ISBN | 2 - Data Inicio | 3 - Data Fim | 4 - estado


    if(!ficheiro) //verifica o ficheiro
    {
        printf("\nNao foi possivel abrir o ficheiro %s\n", nomeficheiro);
        return 0;
    }

    while(!feof(ficheiro))
    {

        if(fgets(linha, 200, ficheiro) != NULL) //verifica se a linha foi bem lida
        {
            char dataAntiga[100], dataAntiga2[100];
            int pos = 0;
            strcpy(linhaInteira, linha);
            char *elemento = strtok(linha, "\t");

            while (elemento != NULL) //guarda todos os dados da linha no array dados
            {
                dados[pos] = (char *)malloc((strlen(elemento) + 1) * sizeof(char)); //alocar espaco
                strcpy(dados[pos], elemento);
                if(pos==2)
                {
                    strcpy(dataAntiga,elemento);
                }else if (pos==3)
                {
                    strcpy(dataAntiga2,elemento);
                }
                pos++;
                elemento = strtok(NULL, "\t");
            }
            //validar o requisitante
            int validadeID = validarIdRequisitante(atoi(dados[0]));
            if(!(validadeID%10 == 0))//valida o id do requisitante
            {
                char mensagem[300];
                strcpy(mensagem, "O ID ");
                strcat(mensagem, dados[0]);
                strcat(mensagem, " e invalido!");
                logs(linhaInteira, mensagem); //escreve no ficheiro logs o erro
            }else
            {
                char id_requisitante[9];
                strcpy(id_requisitante, dados[0]);
                REQUISITANTE* requisitante = pesquisarRequisitantePorID(listaReq, id_requisitante); //pesquisa o requisitante pelo id
                if(!requisitante) //verifica o requisitante
                {
                    char mensagem[300];
                    strcpy(mensagem, "O ID do requisitante ");
                    strcat(mensagem, dados[0]);
                    strcat(mensagem, " e invalido!");
                    logs(linhaInteira, mensagem); //escreve no ficheiro logs o erro
                }else
                {
                    //validar o livro
                    int ISBN = atoi(dados[1]);
                    LIVRO* livro = pesquisarLivroPorISBN(hashingLiv, ISBN); //pesquisa o livro pelo ISBN
                    if(!livro) //verifica o livro
                    {
                        char mensagem[300];
                        strcpy(mensagem, "O ID do livro ");
                        strcat(mensagem, dados[1]);
                        strcat(mensagem, " e invalido!");
                        logs(linhaInteira, mensagem); //escreve no ficheiro logs o erro
                    }else
                    {
                        //validar as datas
                        char dataAux[100];
                        strcpy(dataAux, dados[2]);
                        DATA* validadeData = validarData(dataAux);
                        if(validadeData->valid == 0 ) //0 - Data Inválida | 1 - Data Correta | 2 - Data Composta
                        {
                            char mensagem[300];
                            strcpy(mensagem, "A data de inicio da requisicao do requisitante com ID ");
                            strcat(mensagem, dados[0]);
                            strcat(mensagem, " e invalida! Valor da data: ");
                            strcat(mensagem, dataAntiga);
                            logs(linhaInteira, mensagem); //escreve no ficheiro logs o erro
                        }else
                        {
                            char dataAux2[100];
                            strcpy(dataAux2, dados[3]);
                            DATA* validadeData2 = validarData(dataAux2);
                            if(validadeData2->valid == 0 ) //0 - Data Inválida; 1 - Data Correta; 2 - Data Composta
                            {
                                char mensagem[300];
                                strcpy(mensagem, "A data de fim da requisicao do requisitante com ID ");
                                strcat(mensagem, dados[0]);
                                strcat(mensagem, " e invalida! Valor da data: ");
                                strcat(mensagem, dataAntiga2);
                                logs(linhaInteira, mensagem); //escreve no ficheiro logs o erro
                            }else
                            {
                                if(validadeData->valid == 2)//0 - Data Inválida; 1 - Data Correta; 2 - Data Composta
                                {
                                    char mensagem[300];
                                    sprintf(dados[2], "%02d-%02d-%04d", validadeData->dia, validadeData->mes, validadeData->ano);
                                    strcpy(mensagem, "A data de inicio da requisicao do requisitante com ID ");
                                    strcat(mensagem, dados[0]);
                                    strcat(mensagem, " era ");
                                    strcat(mensagem, dataAntiga);
                                    strcat(mensagem, " e foi convertida para ");
                                    strcat(mensagem, dados[2]);
                                    logs(linhaInteira, mensagem); //escreve no ficheiro logs o erro
                                }
                                if(validadeData2->valid == 2)//0 - Data Inválida; 1 - Data Correta; 2 - Data Composta
                                {
                                    char mensagem[300];
                                    sprintf(dados[3], "%02d-%02d-%04d", validadeData2->dia, validadeData2->mes, validadeData2->ano);
                                    strcpy(mensagem, "A data de fim da requisicao do requisitante com ID ");
                                    strcat(mensagem, dados[0]);
                                    strcat(mensagem, " era ");
                                    strcat(mensagem, dataAntiga2);
                                    strcat(mensagem, " e foi convertida para ");
                                    strcat(mensagem, dados[3]);
                                    logs(linhaInteira, mensagem); //escreve no ficheiro logs o erro
                                }
                                int naux = atoi(dados[4]);
                                if(naux != 0 && naux != 1)
                                {
                                    char mensagem[300];
                                    strcpy(mensagem, "O estado da requisicao do requesitante com ID ");
                                    strcat(mensagem, dados[0]);
                                    strcat(mensagem, " e invalido! O valor só pode variar entre 0 e 1. Valor do estado: ");
                                    strcat(mensagem, dados[4]);
                                    logs(linhaInteira, mensagem); //escreve no ficheiro logs o erro
                                }else
                                {
                                    REQUISICAO *requisicao = criarRequisicao();
                                    int tamID = strlen(dados[0]);
                                    dados[0][tamID] = '\0';
                                    requisicao->requisitante = requisitante; //coloca o requisitante da requisicao

                                    requisicao->livro = livro; //coloca o livro na requisicao

                                    int dia, mes, ano;
                                    sscanf(dados[2], "%02d-%02d-%04d", &dia, &mes, &ano); //separa a data por dia, mes e ano
                                    requisicao->dataInicio->dia = dia; //insere o dia
                                    requisicao->dataInicio->mes = mes; //insere o mes
                                    requisicao->dataInicio->ano = ano; //insere o ano
                                    dia = 0; //reseta a variavel dia
                                    mes = 0; //reseta a variavel mes
                                    ano = 0; //reseta a variavel ano
                                    sscanf(dados[3], "%02d-%02d-%04d", &dia, &mes, &ano); //separa a data por dia, mes e ano
                                    requisicao->dataFim->dia = dia; //insere o dia
                                    requisicao->dataFim->mes = mes; //insere o mes
                                    requisicao->dataFim->ano = ano; //insere o ano
                                    requisicao->estado = atoi(dados[4]); //coloca o estado na requisicao
                                    adicionarRequisicaoHashing(hashingReq, requisicao); //adiciona a requisicao ao hashing
                                    if(strcmp(dados[4], "1") == 0) //requisicao está ativa
                                    {
                                        colocarLivroRequisitado(hashingLiv, livro); //altera o estado do livro para requisitado
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

    }
    memset(dados,0,sizeof(dados)); //limpa o array dados
    fclose(ficheiro); //fecha o ficheiro
}

void gravarRequisicoes(HASHING_REQUISICOES* hashingReq) //grava as requisicoes no ficheiro txt
{
    if(!hashingReq || !hashingReq->inicio) //verifica o hashing
    {
        return;//sai
    }
    FILE *ficheiro;
    ficheiro = fopen("requisicoes.txt", "w"); //abre o ficheiro (em escrita(w))
    if(!ficheiro) //verifica o ficheiro
    {
        printf("\nNao foi possivel abrir o ficheiro %s\n", "requisicoes.txt");
        return;
    }
    NO_HASHING_REQUISICAO* noHash = hashingReq->inicio;
    while(noHash) //enquanto o noHash nao for null
    {
        NO_REQUISICAO *noReq = noHash->listaReq->inicio;
        while(noReq) //enquanto o noReq nao for null
        {
            //escreve no ficheiro os dados
            fprintf(ficheiro,"%s\t%d\t%02d-%02d-%04d\t%02d-%02d-%04d\t%d\n", noReq->requisicao->requisitante->id_requisitante, noReq->requisicao->livro->ISBN, noReq->requisicao->dataInicio->dia, noReq->requisicao->dataInicio->mes, noReq->requisicao->dataInicio->ano, noReq->requisicao->dataFim->dia, noReq->requisicao->dataFim->mes, noReq->requisicao->dataFim->ano, noReq->requisicao->estado);
            noReq=noReq->seg; //passa para o no seguinte
        }
        noHash = noHash->seg; //passa para o no seguinte
    }
    fclose(ficheiro); //fecha o ficheiro
}

void apresentarRequisicoesPorData(HASHING_REQUISICOES* hashingReq)
{
    if(!hashingReq || !hashingReq->inicio){
        printf("\nSem requisicoes!");
        return;
    }

    NO_HASHING_REQUISICAO *noHashing = hashingReq->inicio;
    while(noHashing)
    {
        printf("\n-----------------------> Data: %02d-%02d-%04d <-----------------------\n", noHashing->data->dia, noHashing->data->mes, noHashing->data->ano);
        NO_REQUISICAO *noReq = noHashing->listaReq->inicio;
        while(noReq)
        {
            printf("\n");
            apresentarDetalhesRequisicao(noReq->requisicao);

            noReq = noReq->seg;
        }
        noHashing = noHashing->seg;
    }
}

REQUISICAO* criarRequisicaoPreenchida(HASHING_REQUISICOES* requisicoes, REQUISITANTE* requisitante, LIVRO* livro, DATA* dataInicio, DATA* dataFim, int estado)
{
	REQUISICAO* req = criarRequisicao();
	if (!requisitante) //verificar requisitante
    {
		return NULL; //sair
	}
	else
    {
		req->requisitante = requisitante; //colocar requesitante na requisicao
	}

	if (!livro) //verificar livro
    {
		return NULL; //sair
	}
	else
	{
		req->livro = livro; //colocar livro na requisicao
	}

	if (!dataInicio) //verificar dataInicio
    {
		return NULL; //sair
	}
	else
	{
		req->dataInicio = dataInicio; //colocar dataInicio na requisicao
	}
	if (!dataFim) //verificar dataFim
	{
		return NULL; //sair
	}
	else
	{
		req->dataFim = dataFim; //colocar dataFim na requisicao
	}
	req->estado = estado; //colocar estado na requisicao
	return req; //retorna a requisicao preenchida
}

NO_HASHING_REQUISICAO* verificarData(HASHING_REQUISICOES* hashingReq, DATA* data) //verifica se uma data data existe no hashing requisicoes
{

	if (!hashingReq) //verificar hashing
	{
	    return NULL; //sair
	}
	if (!data) //verificar data
    {
        return NULL; //sair
    }
	char dataChar[11], dataChar2[11];
	sprintf(dataChar, "%04d%02d%02d", data->ano, data->mes, data->dia); //juntar a data numa string
	NO_HASHING_REQUISICAO* aux = hashingReq->inicio;
	while (aux)//enquanto aux nao for null
	{
	    sprintf(dataChar2, "%04d%02d%02d", aux->data->ano, aux->data->mes, aux->data->dia); //juntar a data numa string
		if (strcmp(dataChar2, dataChar) == 0) //se data recebida for igual à data que esa no aux
        {
			return aux; //retorna a data do aux
		}
		aux = aux->seg; //passa para o seguinte
	}
	return NULL; //sair
}

void apresentarDetalhesRequisicao(REQUISICAO* requisicao)
{
    printf("\nDados da requisicao:");
    printf("\nRequisitante: %s", requisicao->requisitante->nome);
    printf("\nLivro: %s", requisicao->livro->titulo);
    printf("\nDataInicio: %02d-%02d-%04d", requisicao->dataInicio->dia, requisicao->dataInicio->mes, requisicao->dataInicio->ano);
    printf("\nDataFim: %02d-%02d-%04d", requisicao->dataFim->dia, requisicao->dataFim->mes, requisicao->dataFim->ano);
    if(requisicao->estado == 0) //se o estado for 0 (invalida)
    {
        printf("\nEstado: Entregue");
    }else if(requisicao->estado == 1) //se o estado for 1 (valida)
    {
        printf("\nEstado: Por entregar");
    }
}

void inserirRequisicaoListaPorOrdemAlfabeticaRequisitante(LISTA_REQUISICOES* listaReq, REQUISICAO* requisicao) //insere uma requisicao na lista por ordem alfabetica
{
	if (!listaReq)//verificar listaReq
    {
        return;//sair
    }
	if (!requisicao)//verifica requisicao
    {
        return;//sair
    }
	NO_REQUISICAO* noReq = criarNodaRequisicao();
	noReq->requisicao = requisicao;

	if (!listaReq->inicio) //se a lista estiver vazia
    {
		listaReq->inicio = noReq; //insere em primeiro lugar
	}
	else {
		NO_REQUISICAO* aux = listaReq->inicio; //criar auxiliar para guardar o primeiro no_requisicao da lista
		int i = 1;
		while (i) //enquanto o i for 1
		{
			if (strcmp(noReq->requisicao->requisitante->nome, aux->requisicao->requisitante->nome) >= 0) // se o nome do requisitante recebido for igual ou superior na cadeia ASCII
			{
				if (aux->seg) //se nao for o ultimo
				{
					if (strcmp(noReq->requisicao->requisitante->nome, aux->seg->requisicao->requisitante->nome) <= 0) // se o nome do requisitante recebido for igual ou inferior na cadeia ASCII
					{
						//insere no meio
						noReq->seg = aux->seg;
						noReq->ant = aux;
						aux->seg->ant = noReq;
						aux->seg = noReq;
						i = 0;
					}
				}
				else
				{
					//insere no fim
					aux->seg = noReq;
					noReq->ant = aux;
					i = 0;
				}
			}
			else
			{
				//insere no inicio
				noReq->seg = aux;
				aux->ant = noReq;
				listaReq->inicio = noReq;
				i = 0;
			}

			aux = aux->seg; //passa para o seguinte
		}
	}
	listaReq->nel++; //incrementa o numero de elementos da lista
}

void adicionarRequisicaoHashing(HASHING_REQUISICOES* hashingReq, REQUISICAO* requisicao) //adiciona uma requisicao ao hashing
{
	if (!hashingReq) //verifica o hashing
    {
        return;//sair
    }
	if (!requisicao)//verifica a requisicao
    {
        return;//sair
    }
	NO_HASHING_REQUISICAO* noReq = verificarData(hashingReq, requisicao->dataInicio); //verifica se a data ja existe no hashing
	char dataChar[11], dataChar2[11], dataChar3[11];
	if (!noReq) //se o noReq for null (se a data ainda nao existe no hashing)
    {
		noReq = criarNodoHashingRequisicao(); //cria o noReq vazio (aloca espaco)

		noReq->listaReq = criarListaRequisicoes();
		noReq->data = requisicao->dataInicio;

		if (!hashingReq->inicio) //se o hashing estiver vazio
        {
			hashingReq->inicio = noReq; //inserir o noReq em primeiro
		}
		else
		{
			NO_HASHING_REQUISICAO* aux = hashingReq->inicio; //criar auxiliar para guardar o primeiro
			int i = 1;
			while (i) //enquanto o i for 1
			{
			    sprintf(dataChar, "%04d%02d%02d", noReq->data->ano, noReq->data->mes, noReq->data->dia); //coverter a data para string
			    sprintf(dataChar2, "%04d%02d%02d", aux->data->ano, aux->data->mes, aux->data->dia); //converter a data para string
				if (strcmp(dataChar, dataChar2) >= 0) //se a data for maior ou igual
				{
					if (aux->seg) // se nao for o ultimo
					{
					    sprintf(dataChar3, "%04d%02d%02d", aux->seg->data->ano, aux->seg->data->mes, aux->seg->data->dia); //converter a data para string
						if (strcmp(dataChar, dataChar3) <= 0) //se a data for menor ou igual
						{
							//insere no meio
							noReq->seg = aux->seg;
							noReq->ant = aux;
							aux->seg->ant = noReq;
							aux->seg = noReq;
							i = 0;
						}
					}
					else
					{
						//insere no fim
						aux->seg = noReq;
						noReq->ant = aux;
						i = 0;
					}
				}
				else
				{
					//insere no inicio
					noReq->seg = aux;
					aux->ant = noReq;
					hashingReq->inicio = noReq;
					i = 0;
				}
				aux = aux->seg; //passa para o seguinte
			}
		}
		hashingReq->nel++; //incrementa o numero de elementos do hashing
	}
    inserirRequisicaoListaPorOrdemAlfabeticaRequisitante(noReq->listaReq, requisicao); //insere a requisicao na lista por ordem alfabetica
}

void efetuarRequisicao(HASHING_LIVRO* hashingLiv, LISTA_REQUISITANTES* listaRequisitantes, HASHING_REQUISICOES* hashingReq, LISTA_NUM_REQUISICOES* listaNumRequisicoes)
{
    if(!hashingLiv || !hashingLiv->inicio)//verificar hashingLiv
    {
        printf("Hashing livros invalido!");
        return;//sair
    }
    if(!listaRequisitantes || !listaRequisitantes->inicio)//verificar listaRequisitantes
    {
        printf("Lista de requisitantes invalida!");
        return;//sair
    }
    if(!hashingReq)//verificar hashingReq
    {
        printf("Lista de Requisicoes invalida!");
        return;//sair
    }

    //o utilizador escolhe qual o requisitante que vai requisitar
    char idRequisitante[9];
    printf("\nQual o ID do requisitante que deseja requisitar um livro?\n");
    char temp;
    scanf("%c",&temp);
    scanf("%[^\n]", idRequisitante);
    REQUISITANTE* requisitante = pesquisarRequisitantePorID(listaRequisitantes, idRequisitante); //pesquisa o requisitante pelo Id que o utilizador inseriu (retorna NULL se nao existir)
    if(!requisitante)//verifica o requisitante
    {
        printf("\nNao existe nenhum requisitante com o ID %s !", idRequisitante);
        return;//sair
    }
    apresentarDetalhesRequisitante(requisitante);//apresenta os detalhes para o utilizador confirmar
    if(mensagemConfirmacao("E este o requisitante que deseja fazer a requisicao?")==0) //se o utilizador nao confirmar || 0 - nao confirmou | 1 - confirmou
    {
        printf("\nOperacao cancelada\n");
        return;//sair
    }

    //o utilizador escolhe qual o livro a requisitar
    int ISBN;
    printf("\nQual o ISBN do livro?\n");
    scanf("%d",&ISBN);
    LIVRO* livro = pesquisarLivroPorISBN(hashingLiv, ISBN); //pesquisa o livro pelo ISBN que o utilizador inseriu (retorna null se nao existir)
    if(!livro) //verifica o livro
    {
        printf("\nNao exsite nenhum livro com o ISBN %d !", ISBN);
        return;//sair
    }
    if(livro->estado == 1) //se o livro ja estiver requisitado || 0 - livre | 1 - requisitado
    {
        printf("Esse livro ja foi requisitado por outro utilizador!");
        return;//sair
    }
    apresentarLivro(livro); //apresenta os detalhes para o utiliazador confirmar
    if(mensagemConfirmacao("E este o livro que deseja requisitar?")==0) //se o utilizador confirmar || 0 - nao confirmou | 1 - confirmou
    {
        printf("\nOperacao cancelada\n");
        return;//sair
    }
    //vai buscar a data atual
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    DATA* dataInicio = criarData(); //cria uma estrutura data vazia (aloca espaco)
    dataInicio->dia = tm.tm_mday; //coloca o dia atual
    dataInicio->mes = tm.tm_mon + 1; //coloca o mes atual
    dataInicio->ano = tm.tm_year + 1900; //coloca o ano atual

    struct tm* dataFimAux; //estrutura de data atual auxiliar
    time(&t);
    dataFimAux = localtime(&t);

    dataFimAux->tm_mday = dataInicio->dia + 15; //incrementa mais 15 dias a data auxiliar
    mktime(dataFimAux); //converte a data auxiliar para uma data valida (por exemplo se for 32/12/2019 passa a ser 01/01/2020)
    DATA* dataFim = criarData(); //criar uma estrutura data vazia (aloca espaco)
    dataFim->dia = dataFimAux->tm_mday; //coloca o dia incrementado
    dataFim->mes = dataFimAux->tm_mon + 1; //coloca o mes incrementado
    dataFim->ano = dataFimAux->tm_year + 1900; //coloca o ano incrementado
    REQUISICAO* requisicao =  criarRequisicaoPreenchida(hashingReq, requisitante, livro, dataInicio, dataFim, 1); //criar uma requisicao preenchida com os dados obtidos antes
    if(!requisicao)//verifica a requisicao
    {
        return;//sair
    }
    adicionarRequisicaoHashing(hashingReq, requisicao);//adiciona a requisicao ao hashing
    //incrementar o numero de requisicoes de um requisitante
    NO_NUM_REQUISICOES* noNumRequisicoes = criarNoNumRequisicoes(); //cria um noNumRequisicoes vazio (aloca espaco)
    noNumRequisicoes->num_requisicoes->requisitante = requisitante; //adiciona o requisitante ao noNumRequisicoes
    noNumRequisicoes->num_requisicoes->num = 1; //coloca o numero de requisicoes como pre definicao
    inserirNumRequisicoesNaLista(listaNumRequisicoes, noNumRequisicoes); //insere o noNumRequisicoes na lista

    incrementarNumRequisicoesLivro(hashingLiv, livro); //incrementa o numero de requisicoes do livro e da area do livro
    colocarLivroRequisitado(hashingLiv, livro); // coloca o estado do livro como requisitado
    apresentarDetalhesRequisicao(requisicao); //apresenta os detalhes da requisicao para o utilizador confirmar
}

void apresentarRequisicoesDeUmRequisitante(HASHING_REQUISICOES* hashingReq, LISTA_REQUISITANTES* listaReq)
{
    if(!listaReq || !listaReq->inicio)//verificar listaReq
    {
        printf("Sem requisitantes!");
        return;//sair
    }
    if(!hashingReq || !hashingReq->inicio)//verificar hashingReq
    {
        printf("Sem requisicoes!");
        return;//sair
    }
    //pedir o requisitante ao utilizador
    char idRequisitante[9];
    printf("\nQual o ID do requisitante que deseja ver as requisicoes?\n");
    char temp;
    scanf("%c",&temp);
    scanf("%[^\n]", idRequisitante);
    REQUISITANTE* requisitante = pesquisarRequisitantePorID(listaReq, idRequisitante); //pesquisar requisitante pelo Id que o utilziador inseriu (se nao encontrar retorna null)
    if(!requisitante)//verficar requisitante
    {
        printf("\nNao existe nenhum requisitante com o ID %s !", idRequisitante);
        return;//sair
    }
    apresentarDetalhesRequisitante(requisitante);//apresenta os detalhes do requisitante para o utilizador confirmar
    if(mensagemConfirmacao("E este o requisitante que deseja ver as requisicoes?")==0)//se o utilizador nao confirmar || 0 - nao confirmou | 1 - confirmou
    {
        printf("\nOperacao cancelada\n");
        return;//sair
    }

    if(mensagemConfirmacao("A proxima funcao podera apresentar uma lista com grandes dados dependendo do numero de livros que o requisitante ja requisitou anteriormente, fazendo com que demorara algum tempo a ser executada. Tem a certeza que deseja continuar?")==0)
    {//se o utilizador nao confirmar || 0 - nao confirmou | 1 - confirmou
        printf("\nOperacao cancelada\n");
        return;//sair
    }
    NO_HASHING_REQUISICAO *noHashing = hashingReq->inicio;
    while(noHashing)//enquanto nao for null
    {
        NO_REQUISICAO *noReq = noHashing->listaReq->inicio;
        while(noReq)//enquanto nao for null
        {
            if(strcmp(noReq->requisicao->requisitante->id_requisitante, requisitante->id_requisitante) == 0) //se o id do requisitante for igual ao do requisitante escolhido pelo utilizador
            {
                printf("\n");
                apresentarDetalhesRequisicao(noReq->requisicao);//apresentar detalhes da requisicao para o utilizador confirmar
            }
            noReq = noReq->seg;//passar ao seguinte
        }
        noHashing = noHashing->seg;//passar aoi seguinte
    }
}

void apresentarRequisitantesComLivrosRequisitados(HASHING_REQUISICOES* hashingReq, LISTA_REQUISITANTES* listaReq)
{
    if(!hashingReq || !hashingReq->inicio)//verificar o hashingReq
    {
        printf("\nSem requisicoes!");
        return;//sair
    }
    int ids[listaReq->nel], k, y;
    for(int l=0; l<listaReq->nel;l++) //percorrer o array e limpa lo
    {
        ids[l] = 0;
    }
    NO_HASHING_REQUISICAO *noHashing = hashingReq->inicio;
    while(noHashing)//enquanto nao for null
    {
        NO_REQUISICAO *noReq = noHashing->listaReq->inicio;
        while(noReq)//enquanto nao for null
        {
            for(int i=0; i < listaReq->nel; i++)//percorrer o array
            {
                for(y=0; y < listaReq->nel; y++)//percorrer o array para ver se o id do requisitante ja la esta
                {
                    if(ids[y]==0)//se for 0 entao siginifica que ja acabaram os ids e agora ja so sao espacos em branco entao para de percorrer o array
                    {
                        break;
                    }
                    if(ids[y] == atoi(noReq->requisicao->requisitante->id_requisitante))//se for igual ao id do requisitante parar de percorrer o array
                    {
                        break;
                    }
                }
                if(ids[y] == atoi(noReq->requisicao->requisitante->id_requisitante))//se for igual ao id do requisitante e porque ele ja la esta entao para de percorrer o array
                {
                    break;
                }
                if(noReq->requisicao->estado == 1) // se estiver ativa || 0 - inativa | 1 - ativa
                {
                    for(k = 0; k<listaReq->nel; k++)//percorrer o array (percorre ate encontrar um espaco livre no array)
                    {
                        if(ids[k]==0) // se encontrar um espaco livre
                        {
                            ids[k]=atoi(noReq->requisicao->requisitante->id_requisitante); //insere o id do requisitante no espaco livre
                            break;
                        }
                    }
                }else if (noReq->requisicao->estado == 0) //se o estado for inativo para de percorrer o array|| 0 - inativa | 1 - ativa
                {
                    break;
                }
                if(ids[k] == atoi(noReq->requisicao->requisitante->id_requisitante))//se ele ja colocou o id do requisitante no array para de percorrer o array
                {
                    break;
                }
            }
            noReq = noReq->seg;//passa apra o seguinte
        }
        noHashing = noHashing->seg;//passa para o seguinte
    }
    for(int x=0; x<listaReq->nel;x++)//percorre o array ids para apresentar todos os que tem guardados
    {
        if(ids[x]==0)//se for 0 entao siginifica que ja acabaram os ids e agora ja so sao espacos em branco entao para de percorrer o array
        {
            break;
        }
        char id[9];
        sprintf(id, "%d", ids[x]);
        REQUISITANTE* requisitante = pesquisarRequisitantePorID(listaReq, id);//pesquisa o requisitante pelo id que esta no array
        if(!requisitante)//verifica o requisitante
        {
            printf("\n Id requisitante invalido!");
        }else
        {
            printf("\n");
            apresentarDetalhesRequisitante(requisitante);//apresenta o requisitante
        }
    }
}

void apresentarRequisitantesSemRequisicoes(HASHING_REQUISICOES* hashingReq, LISTA_REQUISITANTES* listaReq)
{
    if(!hashingReq || !hashingReq->inicio)//verifica o hashingReq
    {
        printf("\nSem requisicoes!");
        return;//sai
    }
    int ids[listaReq->nel], l=0;
    NO_REQUISITANTE *noRequisitante = listaReq->inicio;
    while(noRequisitante)//percorre todos os requisitantes para prencher o array com todos os ids de todos os requisitantes
    {
        ids[l] = atoi(noRequisitante->requisitante->id_requisitante); //preenche o array com o id do requisitante
        noRequisitante=noRequisitante->seg;//passa para o seguinte
        l++;
    }

    NO_HASHING_REQUISICAO *noHashing = hashingReq->inicio;
    while(noHashing)//enquanto nao for null
    {
        NO_REQUISICAO *noReq = noHashing->listaReq->inicio;
        while(noReq)//enquanto nao for null
        {
            for(int i=0; i<listaReq->nel; i++)//percorre o array ids
            {
                if(ids[i]==atoi(noReq->requisicao->requisitante->id_requisitante))//se houver uma requisicao com o id que esta no array entao o requisitante ja fez requisicoes
                {
                    ids[i] = 0;//retira o requisitante do array
                }
            }
            noReq = noReq->seg;//passa para o seguinte
        }
        noHashing = noHashing->seg;//passa para o seguinte
    }
    for(int x=0; x<listaReq->nel;x++) //percorre o array ids para apresentar todos os que tem guardados
    {
        if(ids[x]!=0)//se conter um id
        {
            char id[9];
            sprintf(id, "%d", ids[x]);
            REQUISITANTE* requisitante = pesquisarRequisitantePorID(listaReq, id);//pesquisa o requisitante pelo id
            if(!requisitante)//verifica o requisitante
            {
                printf("\n Id requisitante invalido!");
            }else
            {
                printf("\n");
                apresentarDetalhesRequisitante(requisitante);//apresenta os detalhes do requisitante
            }
        }
    }
}

void devolverUmLivro(HASHING_LIVRO* hashingLiv, HASHING_REQUISICOES* hashingReq)
{
    if(!hashingLiv || !hashingLiv->inicio)//verifica o hashingLiv
    {
        printf("Hashing livros invalido!");
        return;//sai
    }
    if(!hashingReq || !hashingReq->inicio)//verifica o hashingReq
    {
        printf("Sem requisicoes!");
        return;//sai
    }

    //pedir o livro ao tuilizador
    int ISBN;
    printf("\nQual o ISBN do livro?\n");
    scanf("%d",&ISBN);
    LIVRO* livro = pesquisarLivroPorISBN(hashingLiv, ISBN);//pesquisar o livro pelo ISBN que o utilizador inseriu
    if(!livro)//verificar livro
    {
        printf("\nNao exsite nenhum livro com o ISBN %d !", ISBN);
        return;//sai
    }
    if(livro->estado == 0)//verifica se esta requisitado || 0 - livre | 1 - requisitado
    {
        printf("Esse livro não esta requisitado!");
        return;//sai
    }
    apresentarLivro(livro);//apresenta o livro para o utilizador confirmar

    NO_HASHING_REQUISICAO *noHashing = hashingReq->inicio;
    while(noHashing)//equanto nao for null
    {
        NO_REQUISICAO *noReq = noHashing->listaReq->inicio;
        while(noReq)//enquanto nao for null
        {
            if(noReq->requisicao->estado == 1 && noReq->requisicao->livro->ISBN == livro->ISBN)//se o estadod a requisicao for ativo e o livro for o que o utilizdor inseriu
            {
                printf("\nRequisitado por:");
                apresentarDetalhesRequisitante(noReq->requisicao->requisitante);//apresentar os detalhes do requisitante para o utilizador confirmar
                if(mensagemConfirmacao("\nE este o livro que deseja devolver?")==0)//se o utilizador nao confirmar || 0 - nao confirmou | 1 - confirmou
                {
                    printf("\nOperacao cancelada\n");
                    return;//sai
                }
                colocarLivroDevolvido(hashingLiv, livro);//colocar o livro com o estado livre
                //vai buscar a data atual
                time_t t = time(NULL);
                struct tm tm = *localtime(&t);
                DATA* data = criarData();//cria a estrutura data vazia (aloca espaco)
                data->dia = tm.tm_mday;//coloca o dia atual
                data->mes = tm.tm_mon + 1;//coloca o mes atual
                data->ano = tm.tm_year + 1900;//coloca o ano atual
                noReq->requisicao->dataFim = data;//coloca a data atual na dataFim para ficar como data de devolucao
                noReq->requisicao->estado = 0;//coloca o estado da requsicao a 0 || 0 - inativa | 1 - ativa
            }
            noReq = noReq->seg;//passa para o seguinte
        }
        noHashing = noHashing->seg;//passa para o seguitne
    }
    printf("\nLivro devolvido com sucesso!");
}

void listarLivrosRequisitadosPorArea(HASHING_LIVRO* hashingLiv, HASHING_REQUISICOES* hashingReq)
{
    if(!hashingLiv || !hashingLiv->inicio)//verifica o hashing
    {
        return;//sai
    }
    if(!hashingReq || !hashingReq->inicio)//verifica o hashing
    {
        printf("Sem requisicoes!");
        return;//sai
    }
    NO_HASHING_LIVRO *noHashing = hashingLiv->inicio;
    while(noHashing)//enquanto nao for null
    {
        int n=0;
        NO_LIVRO *noLiv = noHashing->listaLiv->inicio;
        while(noLiv)//enquanto nao for null
        {
            if(noLiv->livro->estado==1)//se o estado for requisitado || 0 - livre | 1 - requisitado
            {
                if(n==0)//se for o primeiro livro da area
                {//apresenta o nome da area
                    printf("\n-----------------------> Area: %s <-----------------------\n",noHashing->area);
                }
                printf("\n");
                apresentarLivro(noLiv->livro);//apresenta os detalhes do livro
                n++;
            }
            noLiv = noLiv->seg;//passa ao seguinte
        }
        noHashing = noHashing->seg;//passa ao seguinte
    }
}

void libertarMemoriaRequisicoes(HASHING_REQUISICOES* hashingReq)//nao esta a funcionar
{
    if(!hashingReq || !hashingReq->inicio)//verifica o hashing
    {
        return;//sai
    }
    NO_HASHING_REQUISICAO* noHashingReq = hashingReq->inicio, *noHashingReqAux = NULL;
    while(noHashingReq)
    {
        noHashingReqAux = noHashingReq->seg;
        libertarMemoriaListaRequisicoes(noHashingReq->listaReq);
        free(noHashingReq);
        noHashingReq = noHashingReqAux;
    }
    free(hashingReq);
}

void libertarMemoriaListaRequisicoes(LISTA_REQUISICOES* listaReq)//nao esta a funcionar
{
    if(!listaReq || !listaReq->inicio)
    {
        return;
    }
    NO_REQUISICAO* noReq = listaReq->inicio, *noReqAux = NULL;
    while(noReq)
    {
        noReqAux = noReq->seg;
        free(noReq->requisicao->dataInicio);
        free(noReq->requisicao->dataFim);
        free(noReq->requisicao);
        free(noReq);
        noReq = noReqAux;
    }
    free(listaReq);
}

void libertarMemoriaListaNumRequisicoes(LISTA_LIVROS* listaNumReq)//nao esta a funcionar
{
    if(!listaNumReq || !listaNumReq->inicio)
    {
        return;
    }
    NO_LIVRO* noNumReq = listaNumReq->inicio, *noNumReqAux = NULL;
    while(noNumReq)
    {
        noNumReqAux = noNumReq->seg;
        free(noNumReq->livro);
        free(noNumReq);
        noNumReq = noNumReqAux;
    }
    free(listaNumReq);
}

#endif
