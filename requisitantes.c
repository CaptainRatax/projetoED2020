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
#include "requisitantes.h"
#include "auxiliares.c"
#include "auxiliares.h"
#include "freguesias.h"
#include "freguesias.c"
#include "requisicoes.h"

REQUISITANTE *criarRequisitante() //criar requisitante vazio (alocar espaco)
{
    REQUISITANTE *requisitante = (REQUISITANTE *)malloc(sizeof(REQUISITANTE)); //alocar espaco
    requisitante->n_requisicoes=0; //inicializar o n_requisicoes a 0
    return requisitante; //retorna o requisitante
}

NO_REQUISITANTE *criarNodoRequisitante() //criar o no da requisicao vazio(aloca espaco)
{
    NO_REQUISITANTE *noReq = (NO_REQUISITANTE *)malloc(sizeof(NO_REQUISITANTE)); //alocar espaco
    noReq->seg = NULL; //coloca o ponteiro para o no seguinte a NULL
    return noReq; //retorna o no da requisicao
}

LISTA_REQUISITANTES *criarListaRequisitante() //criar a lista de requisitantes vazia (aloca espaco)
{
    LISTA_REQUISITANTES *listaReq = (LISTA_REQUISITANTES *)malloc(sizeof(LISTA_REQUISITANTES)); //alocar espaco
    listaReq->nel = 0; //inicializa o numero de elementos a 0
    listaReq->ultimoIdRequisitante = 0; //inicializa o ultimo id do requisitante a 0
    listaReq->inicio = NULL;
    return  listaReq; //retorna a lista
}

void inserirRequisitanteNaLista(LISTA_REQUISITANTES *listaReq, NO_REQUISITANTE *noReq)
{
    if (!listaReq) //verifica a listaReq
    {
		printf("\nNao existe lista!");
		return;//sai
	}
	if (!noReq) //verifica o noReq
	{
		printf("\nNao existe no do requisitante!");
		return;//sai
	}

	//insere no inicio da lista
    noReq->seg = listaReq->inicio;
    listaReq->inicio = noReq;
    listaReq->nel++;
}

int preencherRequisitante(REQUISITANTE *req, int ultimoId) //cria um pequeno form para o utilizador preencher o requisitante com os dados que desejar
{
    int i=0;
    do
    {
        ultimoId++;
        i = validarIdRequisitante(ultimoId);

    }while(!(i%10==0)); //enquanto o resultado da funcao validarIdRequisitante for multiplo de 10
    sprintf(req->id_requisitante, "%d", ultimoId); //coloca o id do requisitante calculado automaticamente
    printf("\nInsira os detalhes do novo requisitante \nNome: ");
    //prencher o nome
    char temp;
    scanf("%c",&temp);
    scanf("%[^\n]", req->nome);
    //prencher a data de nascimento
    printf("\nAno de nascimento: ");
    scanf("%d", &req->ano); //colocar o ano
    printf("\nMes de nascimento: ");
    scanf("%d", &req->mes);//colocar o mes
    printf("\nDia de nascimento: ");
    scanf("%d", &req->dia);//colocar o dia
    //preencher o id da freguesia
    printf("\nID da freguesia: ");
    scanf("%s", req->id_freguesia);

    req->n_requisicoes = 0; //colocar o n_requisicoes a 0
    printf("\nRequesitante inserido com sucesso!\n");

    return ultimoId; //retornar o id do requisitante para o guardar como ultimo
}

int validarIdRequisitante(num) //valida o id do requisitante
{
    int i, soma = 0;

    for(i = 0; i < 9; i++)
    {
      soma +=  num % 10;
      num = num / 10;
    }
    return soma;
}

void apresentarDetalhesRequisitante(REQUISITANTE *req) //retorna os detalhes do requisitante
{
    printf("\nOs detalhes do requisitante sao: ");
    printf("\nID: %s", req->id_requisitante);
    printf("\nNome: %s", req->nome);
    printf("\nData de Nascimento: %d/%d/%d", req->dia,req->mes,req->ano);
    printf("\nId da frequesia: %s", req->id_freguesia);
    return;
}

void lerFicheiroRequisitantes(LISTA_REQUISITANTES* listaReq, LISTA_FREGUESIAS* listaFreg) //le o ficheiro txt dos requisitantes
{
    FILE *fic;
    char nomeFic[10];
    strcpy(nomeFic, "requisitantes.txt");
    char linha[200];
    char linhaInteira[200];
    int ultimoId=0;
    fic = fopen(nomeFic, "r"); //abre o ficheiro
    char *dados[4]; // 0 - id_requisitante | 1 - nome | 2 - data de nascimento | 3 - id freguesia
    if(!fic) //verifica o ficheiro
    {
        printf("\nNao foi possivel abrir o ficheiro %s\n", nomeFic);
        return;//sai
    }
    while(!feof(fic))
    {
        if(fgets(linha, 200, fic) != NULL) //verifica se a linha foi bem lida
        {
            char dataAntiga[100];
            int pos = 0;
            strcpy(linhaInteira, linha);
            char *elemento = strtok(linha, "\t");
            while (elemento != NULL) //guarda todos os dados da linha no array
            {
                dados[pos] = (char *)malloc((strlen(elemento) + 1) * sizeof(char)); //aloca espaco para a posicao do array
                strcpy(dados[pos], elemento);
                if(pos==2) //se estiver na segunda posicao (a ler a data)
                {
                    strcpy(dataAntiga,elemento); //guarda a data numa variavel auxiliar
                }
                pos++;
                elemento = strtok(NULL, "\t");
            }
            //validar o id do requisitante
            int validadeID = validarIdRequisitante(atoi(dados[0]));
            if(!(validadeID%10 == 0)) //se o id for valido
            {
                char mensagem[300];
                strcpy(mensagem, "O ID ");
                strcat(mensagem, dados[0]);
                strcat(mensagem, " e invalido!");
                logs(linhaInteira, mensagem); //escreve o erro no ficheiro logs
            }else
            {
                //validar a data de nascimento
                DATA *validadeData = criarData();
                char dataAux[100];
                strcpy(dataAux, dados[2]);
                validadeData = validarData(dataAux); //valida a data
                if(validadeData->valid == 1 || validadeData->valid == 2) // se a data for valida ou composta || 0 - Data Inválida | 1 - Data Correta | 2 - Data Composta
                {
                    if(validadeData->valid == 2)//se a data for composta || 0 - Data Inválida | 1 - Data Correta | 2 - Data Composta
                    {
                        //escreve no ficheiro logs que a data foi composta
                        char mensagem[300], dataChar[100];
                        sprintf(dados[2], "%02d-%02d-%04d", validadeData->dia, validadeData->mes, validadeData->ano);
                        strcpy(mensagem, "A data do requisitante com ID ");
                        strcat(mensagem, dados[0]); //escreve a data anterior
                        strcat(mensagem, " era ");
                        strcat(mensagem, dataAntiga);
                        strcat(mensagem, " e foi convertida para ");
                        strcat(mensagem, dados[2]); //escreve a data composta
                        logs(linhaInteira, mensagem); //escreve o warning no ficheiro logs
                    }
                    //validar o id da freguesia
                    int tam = strlen(dados[3]);
                    dados[3][tam-1] = '\0';
                    int validadeIdFreg = validarIdFreguesia(listaFreg, dados[3]);

                    if(validadeIdFreg == 0)
                    {
                        char mensagem[300];
                        strcpy(mensagem, "O ID da freguesia pretencente ao requesitante com ID ");
                        strcat(mensagem, dados[0]);
                        strcat(mensagem, " e invalido. Valor do ID da Freguesia: ");
                        strcat(mensagem, dados[3]);
                        logs(linhaInteira, mensagem); //escreve o erro no ficheiro logs
                    }else
                    {
                        //cria o requisitante
                        NO_REQUISITANTE *noReq = criarNodoRequisitante(); // cria o noReq vazio (aloca espaco)
                        noReq->requisitante = criarRequisitante(); //cria o requisitante vazio (aloca espaco) e aponta o noReq para ele
                        REQUISITANTE *req = noReq->requisitante;

                        int tamID = strlen(dados[0]);
                        dados[0][tamID] = '\0';
                        strcpy(req->id_requisitante, dados[0]); //coloca o id do requisitante

                        strcpy(req->id_freguesia, dados[3]); //coloca o id da freguesia

                        strcpy(req->nome, dados[1]); //coloca o nome do requisitante

                        int dia, mes, ano;
                        int validadeFormato = sscanf(dados[2], "%02d-%02d-%04d", &dia, &mes, &ano);
                        req->dia = dia; //coloca o dia na data de nascimento
                        req->mes = mes; //coloca o mes na data de nascimento
                        req->ano = ano; //coloca o ano na data de nascimento
                        ultimoId = atoi(dados[0]); //coloca o ultimo id requisitante
                        inserirRequisitanteNaLista(listaReq, noReq); //insere o requisitante na lista
                    }

                }else
                {
                    if(validadeData->valid == 0)//se a data for valida || 0 - Data Inválida | 1 - Data Correta | 2 - Data Composta
                    {
                        char mensagem[300];
                        strcpy(mensagem, "A data do requisitante com ID ");
                        strcat(mensagem, dados[0]);
                        strcat(mensagem, " e invalida! Valor da data: ");
                        strcat(mensagem, dataAntiga);
                        logs(linhaInteira, mensagem); //escrever o erro no ficheiro logs
                    }
                }
            }

            //libertar o espaco ocupado pelo array
            free(dados[0]);
            free(dados[2]);
            free(dados[3]);
        }
    }
    listaReq->ultimoIdRequisitante = ultimoId; //guarda o ultimo id do requisitante
    fclose(fic); //fecha o ficheiro
}

REQUISITANTE* pesquisarRequisitantePorNome(LISTA_REQUISITANTES* listaReq, char nome[50]) //devolve o requisitante com um certo nome
{
    NO_REQUISITANTE *noReq = listaReq->inicio;
    while(noReq)//percoore todos os requisitantes
    {
        if(strcmp(noReq->requisitante->nome, nome) == 0) //se o nome do requisitante for igual ao recebido
        {
            return noReq->requisitante; //retorna o requisitante
        }
        noReq = noReq->seg;//passo seguinte
    }
    return NULL; //retorna null (nao encontrou nenhum requisitante com esse nome)
}

void determinarIdadeMaximaRequisitantes(LISTA_REQUISITANTES* listaReq)
{
    //vai buscar a data atual
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char anoAtual[4], mesAtual[3], diaAtual[3], dataAtualChar[10], ano[4], mes[3], dia[3], dataChar[10], nome[50];
    int dataAtual, data, dataMenor=99999999, idade;
    sprintf(anoAtual, "%d", (tm.tm_year + 1900)); //guarda o ano atual
    sprintf(mesAtual, "%02d", (tm.tm_mon + 1)); //guarda o mes atual
    sprintf(diaAtual, "%02d", tm.tm_mday); //guarda o dia atual
    strcpy(dataAtualChar, anoAtual); //coloca o ano na data em char
    strcat(dataAtualChar, mesAtual); //coloca o mes na data em char
    dataAtual = atoi(strcat(dataAtualChar, diaAtual)); //coloca o dia na data char e converte-a para int ficando AAAAmmdd (tudo junto)
    NO_REQUISITANTE *noReq = listaReq->inicio;
    while(noReq) //percorre todos os requisitantes
    {
        sprintf(ano, "%d", noReq->requisitante->ano); //guarda o ano de nasicmento do requisitante
        sprintf(mes, "%02d", noReq->requisitante->mes); //guarda o mes de nasicmento do requisitante
        sprintf(dia, "%02d", noReq->requisitante->dia); //guarda o dia de nasicmento do requisitante
        strcpy(dataChar, ano); //coloca o ano na data em char
        strcat(dataChar, mes); //coloca o mes na data em char
        data = atoi(strcat(dataChar, dia));  //coloca o dia na data en char e converte-a para int ficando AAAAmmdd (tudo junto)
        if(data<dataMenor) //se a data for menor que a menor data guardada anteriormente
        {
            dataMenor = data; //entao a data de nascimento do requisitante atual e a menor
            strcpy(nome, noReq->requisitante->nome); //guarda o nome do requisitante com a menor data
        }
        noReq = noReq->seg; //passa para o seguinte
    }
    idade=dataAtual-dataMenor; //subtrai a data menor pela data atual para ter uma idade
    sprintf(dataChar, "%d", idade); //coloca a idade na string dataChar
    //apresenta a idade e o nome dessa idade
    printf("\nA idade maxima de todos os requisitantes e %c%c e pertence ao %s.\n", dataChar[0], dataChar[1], nome);
}

void determinarIdadeMediaRequisitantes(LISTA_REQUISITANTES* listaReq)
{
    //vai buscar a data atual
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char anoAtual[4], mesAtual[3], diaAtual[3], dataAtualChar[10], ano[4], mes[3], dia[3], dataChar[10];
    int dataAtual, data, idade, soma=0, n=0;
    float media;
    sprintf(anoAtual, "%d", (tm.tm_year + 1900));
    sprintf(mesAtual, "%02d", (tm.tm_mon + 1));
    sprintf(diaAtual, "%02d", tm.tm_mday);
    strcpy(dataAtualChar, anoAtual);
    strcat(dataAtualChar, mesAtual);
    dataAtual = atoi(strcat(dataAtualChar, diaAtual));
    NO_REQUISITANTE *noReq = listaReq->inicio;
    while(noReq)//percorre todos os requisitantes
    {
        sprintf(ano, "%d", noReq->requisitante->ano);
        sprintf(mes, "%02d", noReq->requisitante->mes);
        sprintf(dia, "%02d", noReq->requisitante->dia);
        strcpy(dataChar, ano);
        strcat(dataChar, mes);
        data = atoi(strcat(dataChar, dia));
        idade = dataAtual-data;
        idade = getFirst2Digits((long)idade); //vai buscar apenas os primeiros 2 digitos do numero
        soma += idade; //soma todas as idades
        n++;//conta o numero de idades
        noReq = noReq->seg;//passa para o seguinte
    }
    media = soma/n;//faz a media de todas as idades
    //apresenta media das idades
    printf("\nA idade media de todos os requisitantes e de %0.0f.\n", round(media));
}

void determinarNumeroRequisitantesAcimaDeX(LISTA_REQUISITANTES* listaReq, int x) //determina o numero de requisitantes acima/abaixo e com a mesma idade de uma inserida pelo utilizador
{
    //vai buscar a data atual
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char anoAtual[4], mesAtual[3], diaAtual[3], dataAtualChar[10], ano[4], mes[3], dia[3], dataChar[10];
    int dataAtual, data, idade, n=0, y=0, z=0;
    float media;
    sprintf(anoAtual, "%d", (tm.tm_year + 1900));
    sprintf(mesAtual, "%02d", (tm.tm_mon + 1));
    sprintf(diaAtual, "%02d", tm.tm_mday);
    strcpy(dataAtualChar, anoAtual);
    strcat(dataAtualChar, mesAtual);
    dataAtual = atoi(strcat(dataAtualChar, diaAtual));
    NO_REQUISITANTE *noReq = listaReq->inicio;
    while(noReq)//percorre todos os requisitantes
    {
        sprintf(ano, "%d", noReq->requisitante->ano);
        sprintf(mes, "%02d", noReq->requisitante->mes);
        sprintf(dia, "%02d", noReq->requisitante->dia);
        strcpy(dataChar, ano);
        strcat(dataChar, mes);
        data = atoi(strcat(dataChar, dia));
        idade= dataAtual-data;
        idade = getFirst2Digits((long)idade);
        if (idade>x)//se a idade for menor
        {
            n++; //incrementar o n || n - numero de idades acima | y - numero de idades iguais | z - numero de idades abaixo
        }else if (idade==x)
        {
            y++; //incrementar o y || n - numero de idades acima | y - numero de idades iguais | z - numero de idades abaixo
        }else if (idade<x)
        {
            z++; //incrementar o z || n - numero de idades acima | y - numero de idades iguais | z - numero de idades abaixo
        }
        noReq = noReq->seg;//passa para o seguinte
    }
    //apresenta os numeros das idades
    printf("\nExistem %d requisitantes acima de %d anos, %d da mesma idade e %d menores.\n", n, x, y, z);
}

void gravarRequisitantes(LISTA_REQUISITANTES* listaReq) //grava os requisitantes no ficheiro txt
{
    if(!listaReq || !listaReq->inicio)//verifica a lista
    {
        return;//sai
    }
    FILE *ficheiro;
    ficheiro = fopen("requisitantes.txt", "w"); //abre o fiicheiro
    if(!ficheiro)//verifica o ficheiro
    {
        printf("\nNao foi possivel abrir o ficheiro %s\n", "requisitantes.txt");
        return;//sai
    }
    NO_REQUISITANTE *noReq = listaReq->inicio;
    while(noReq)//percorre todos os requisitantes
    {
        //grava os dados desse requisitante numa linha no ficheiro
        fprintf(ficheiro,"%s\t%s\t%02d-%02d-%04d\t%s\n", noReq->requisitante->id_requisitante, noReq->requisitante->nome, noReq->requisitante->dia, noReq->requisitante->mes, noReq->requisitante->ano, noReq->requisitante->id_freguesia);
        noReq=noReq->seg;//passa para o seguinte requisitante
    }
    fclose(ficheiro);//fecha o ficheiro
}
void verRequistantes(LISTA_REQUISITANTES* listaReq) //apresenta todos os requisitantes existentes
{
    if(!listaReq || !listaReq->inicio)//verifica a lista
    {
        return;//sai
    }
    NO_REQUISITANTE *noReq = listaReq->inicio;
    while(noReq)//percorre todos os requisitantes
    {
        //apresenta os detalhes do requisitante
        printf("\n");
        apresentarDetalhesRequisitante(noReq->requisitante);
        noReq = noReq->seg;//passa para o seguinte requisiante
    }
}

void inserirRequisitanteListaPorOrdemAlfabetica(LISTA_REQUISITANTES* listaReq, REQUISITANTE* requisitante)
{
	if (!listaReq) //verifica a lista de requisitantes
    {
        return; //sai
    }
	if (!requisitante)//verifica o requisitante
    {
        return; //sai
    }

	NO_REQUISITANTE* noReq = criarNodoRequisitante(); //cria um no do requisitante vazio (aloca espaco)
	noReq->requisitante = requisitante;

	if (!listaReq->inicio) //se a lista ainda nao continha nenhum elemento
    {
		listaReq->inicio = noReq; //coloca o no no inicio da lista
	}
	else //se a lista ja tinha requisitantes
	{
		NO_REQUISITANTE* aux = listaReq->inicio; //criar auxiliar para guardar o primeiro
		int i = 1;
		while (i) //enquanto o i for 1
		{
			if (strcmp(noReq->requisitante->nome, aux->requisitante->nome) >= 0) //se o nome do requisitante recebido for maior (na cadeia ASCII) ou igual ao do requisitante atual
			{
				if (aux->seg)//se nao for o ultimo requisitante
				{
					if (strcmp(noReq->requisitante->nome, aux->seg->requisitante->nome) <= 0) //se o nome do requisitante recebido for menor (na cadeia ASCII) ou igual ao do requisitante atual
					{
						//insere no meio
						noReq->seg = aux->seg;
						noReq->ant = aux;
						aux->seg->ant = noReq;
						aux->seg = noReq;
						i = 0;
					}
				}
				else //se for o ultimo
				{
					//insere no fim
					aux->seg = noReq;
					noReq->ant = aux;
					i = 0;
				}
			}
			else //se for menor (na cadeia ASCII)
			{
				//insere no inicio
				noReq->seg = aux;
				aux->ant = noReq;
				listaReq->inicio = noReq;
				i = 0;
			}

			aux = aux->seg;//passa para o seguinte
		}
	}

	listaReq->nel++; //incrementa o numero de elementos da lista
}

void mostrarPorOrdemAlfabetica(LISTA_REQUISITANTES* listaReq) //mostra todos os requisitantes por ordem alfabetica
{
    if(!listaReq || !listaReq->inicio)//verifica a lista
    {
        return;//sai
    }
    NO_REQUISITANTE *noReq = listaReq->inicio;

    LISTA_REQUISITANTES* listaAux = criarListaRequisitante(); //cria uma lista auxiliar que vai guardar todos os requistantes por ordem alfabetica
    while(noReq)//percorre todos os requisitantes
    {
        inserirRequisitanteListaPorOrdemAlfabetica(listaAux,noReq->requisitante); //insere o requisitante na lista auxiliar por ordem alfabetica
        noReq=noReq->seg; //passa para o seguinte
    }
    verRequistantes(listaAux); //apresenta todos os requisitantes da lista por ordem alfabetica
    free(listaAux); //liberta o espaco ocupado pela lista auxiliar

}

void inserirRequisitanteListaPorOrdemIdFreguesia(LISTA_REQUISITANTES* listaReq, REQUISITANTE* requisitante) //insere os requisitantes na lista por ordem do id freguesia
{
	if (!listaReq) //verifica a lista dos requisitantes
    {
        return; //sai
    }
	if (!requisitante)//verifica o requisitante
    {
        return; //sai
    }

	NO_REQUISITANTE* noReq = criarNodoRequisitante();
	noReq->requisitante = requisitante;
	if (!listaReq->inicio) //se ainda nao houver nenhum requisitante
    {
		listaReq->inicio = noReq; //inserir requisitante no inicio
	}
	else //se ja houver requisitantes na lista
	{

		NO_REQUISITANTE* aux = listaReq->inicio; //criar auxiliar para guardar o primeiro
		int i = 1;
		while (i) //enquanto o i for 1
		{
			if (strcmp(noReq->requisitante->id_freguesia, aux->requisitante->id_freguesia) >= 0) //se o id da freguesia do requisitante recebido for maior ou igual ao do requisitante atual
			{
				if (aux->seg) //se nao for o ultimo
				{
					if (strcmp(noReq->requisitante->id_freguesia, aux->seg->requisitante->id_freguesia) <= 0) //se o id da freguesia do requisitante recebido for menor ou igual ao do requisitante atual
					{
						//insere no meio
						noReq->seg = aux->seg;
						noReq->ant = aux;
						aux->seg->ant = noReq;
						aux->seg = noReq;
						i = 0;
					}
				}
				else //se for o ultimo
				{
					//insere no fim
					aux->seg = noReq;
					noReq->ant = aux;
					i = 0;
				}
			}
			else //se o id da freguesia do requisitante recebido for menor ao do requisitante atual
			{
				//insere no inicio
				noReq->seg = aux;
				aux->ant = noReq;
				listaReq->inicio = noReq;
				i = 0;
			}

			aux = aux->seg;//passa para o seguinte
		}
	}

	listaReq->nel++; //incrementa o numero de elementos da lista
}

void mostrarPorOrdemIdFreguesia(LISTA_REQUISITANTES* listaReq) //mostra todos os requisitantes por ordem do id freguesia
{
    if(!listaReq || !listaReq->inicio) //verifica a lista dos requisitantes
    {
        return;//sai
    }
    NO_REQUISITANTE *noReq = listaReq->inicio;

    LISTA_REQUISITANTES* listaAux = criarListaRequisitante(); //cria uma lista auxiliar que vai guardar todos os requistantes por ordem do id_freguesia
    {
        inserirRequisitanteListaPorOrdemIdFreguesia(listaAux,noReq->requisitante); //insere o requistiante na lista por ordem do id freguesia
        noReq=noReq->seg;//passa para o seguinte
    }

    verRequistantes(listaAux);//apresenta todos os requisitantes da lista auxiliar
    free(listaAux);//liberta o espaco ocupado pela lista auxiliar
}

void inserirRequisitanteListaPorOrdemAlfabeticaApelido(LISTA_REQUISITANTES* listaReq, REQUISITANTE* requisitante)
{
	if (!listaReq) //verificar a lista dos requisitantes
    {
        return; //sai
    }
	if (!requisitante) //verifica o requisitante
    {
        return; //sai
    }

	NO_REQUISITANTE* noReq = criarNodoRequisitante();
	noReq->requisitante = requisitante;

	if (!listaReq->inicio) //se ainda nao houver nenhum requisitante
    {
		listaReq->inicio = noReq; // o noReq passa a ser o primeiro
	}
	else //se ja houver algum requisitante na lista
    {

		NO_REQUISITANTE* aux = listaReq->inicio; //criar auxiliar para guardar o primeiro
		int i = 1;
		while (i) //enquanto o i for 1
		{
		    //guarda o apelido
		    char aux1[100];
            strcpy(aux1, noReq->requisitante->nome);
            char* p = strrchr(aux1, ' ') + 1;
            char aux2[100];
            //guarda o apelido
            strcpy(aux2, aux->requisitante->nome);
            char* p2 = strrchr(aux2, ' ') + 1;
			if (strcmp(p, p2) >= 0) //se o apelido do requisitante recebido for maior (na cadeia ASCII) ou igual ao do requisitante atual
			{
				if (aux->seg) //se nao for o ultimo
				{
				    //guarda o apelido
				    char aux3[100];
                    strcpy(aux3, aux->seg->requisitante->nome);
                    char* p3 = strrchr(aux3, ' ') + 1;
					if (strcmp(p, p3) <= 0) //se o apelido do requisitante recebido for menor (na cadeia ASCII) ou igual ao do requisitante atual
					{
						//insere no meio
						noReq->seg = aux->seg;
						noReq->ant = aux;
						aux->seg->ant = noReq;
						aux->seg = noReq;
						i = 0;
					}
				}
				else //se for o ultimo
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

			aux = aux->seg; //passa para o requisitante seguinte
		}
	}

	listaReq->nel++; //incrementa o numero de elementos
}

void mostrarPorOrdemAlfabeticaApelido(LISTA_REQUISITANTES* listaReq) //mostra todos os requisitantes por ordem alfabetica do apelido
{
    if(!listaReq || !listaReq->inicio) //verifica a lista
    {
        return;//sai
    }
    NO_REQUISITANTE *noReq = listaReq->inicio;

    LISTA_REQUISITANTES* listaAux = criarListaRequisitante(); //cria uma lista auxiliar que vai guardar todos os requistantes por ordem do apelido
    while(noReq)//percorre todos os requisitantes
    {
        inserirRequisitanteListaPorOrdemAlfabeticaApelido(listaAux,noReq->requisitante); //insere o requisitante atual na lista auxiliar por ordem alfabetica do apelido
        noReq=noReq->seg; //passa apra o seguinte
    }

    verRequistantes(listaAux);//apresenta todos os requisitantes
    free(listaAux);//liberta o espaco ocupado pela lista auxiliar

}

void idadeComMaisRequisitantes(LISTA_REQUISITANTES* listaReq) //apresenta qual a idade com mais requisitantes
{
    //vai buscar a data atual
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char anoAtual[4], mesAtual[3], diaAtual[3], dataAtualChar[10], ano[4], mes[3], dia[3], dataChar[10];
    int dataAtual, data, idadeAtual, idades[200], idadeMaior=0, n, nAux;
    float media;
    sprintf(anoAtual, "%d", (tm.tm_year + 1900));
    sprintf(mesAtual, "%02d", (tm.tm_mon + 1));
    sprintf(diaAtual, "%02d", tm.tm_mday);
    strcpy(dataAtualChar, anoAtual);
    strcat(dataAtualChar, mesAtual);
    dataAtual = atoi(strcat(dataAtualChar, diaAtual));
    NO_REQUISITANTE *noReq = listaReq->inicio;
    for(int l=0; l<200;l++) //percorrer o array e limpá-lo
    {
        idades[l] = 0;
    }
    while(noReq) //percorre todos os requisitantes
    {
        //calcula a idade do requisitante
        sprintf(ano, "%d", noReq->requisitante->ano);
        sprintf(mes, "%02d", noReq->requisitante->mes);
        sprintf(dia, "%02d", noReq->requisitante->dia);
        strcpy(dataChar, ano);
        strcat(dataChar, mes);
        data = atoi(strcat(dataChar, dia));
        idadeAtual= dataAtual-data; //subtrai as datas para ter a idade
        idadeAtual = getFirst2Digits((long)idadeAtual);//retira apenas os primeiros dois digitos da idade

        if(idades[idadeAtual] == 0)//se nao houver ninguem com essa idade
        {
            idades[idadeAtual] = 1;//entao passa a haver 1
        }else //se ja houver alguem com essa idade
        {//incrementa o numero de pessoas no array com essa idade
            nAux = idades[idadeAtual]; // coloca o numero de pessoas com essa idade numa variavel auxiliar
            nAux++; //incrementa a variavel auxiliar
            idades[idadeAtual] = nAux; // e coloca o valor incerementado no array
            //isto tudo e feito assim, pois deu problemas quando incrementavamos o array diretamente
            //tanto com "idades[idadeAtual]++" como com "idades[idadeAtual] = idades[idadeAtual] + 1"
        }
        noReq = noReq->seg; //passa para o seguinte
    }
    for(int i=0; i<200;i++) //percorre o array todo
    {
        if(idades[i]>idadeMaior) //se a idade i for maior (tiver mais requisitantes) que a idade maior
        {
            idadeMaior = idades[i]; //a idade maior passa a ser o numero de requisitantes da diade i
            n = i; //o n passa a guardar a idade i
        }
    }
    //apresenta a idade <n> e o numero de requisitantes com essa idade <idadeMaior>
    printf("\nA idade com mais requisitantes e %d com um total de %d requisitantes.\n", n, idadeMaior);
}

void apelidoMaisUsadoPelosRequisitantes(LISTA_REQUISITANTES* listaReq) //apresenta qual o apelido mais usado pelos requisitantes
{
    char apelidoMaisUsado[100], apelidoAnterior[100];
    int n=0, x=0;
    if(!listaReq || !listaReq->inicio)//verifica a lista
    {
        return;//sai
    }
    NO_REQUISITANTE *noReq = listaReq->inicio;

    LISTA_REQUISITANTES* listaAux = criarListaRequisitante();//cria uma lista auxiliar que vai guardar todos os requisitantes por ordem do seu apelido
    while(noReq)//percorre todos os requisitantes
    {
        inserirRequisitanteListaPorOrdemAlfabeticaApelido(listaAux,noReq->requisitante); //insere os requisitantes na lista auxiliar por ordem alfabetica do apelido
        noReq=noReq->seg;//passa para o seguinte
    }

    noReq = listaAux->inicio;//volta a colocar o noReq a apontar para o inicio (para voltar a percorrer a lista depois)
    //retira o apelido do nome
    char aux2[100];
    strcpy(aux2, noReq->requisitante->nome);
    char* p2 = strrchr(aux2, ' ') + 1;
    strcpy(apelidoAnterior, p2);

    while(noReq)//percorrer todos os requisitantes
    {
        //retira o apelido do nome
        char aux1[100];
        strcpy(aux1, noReq->requisitante->nome);
        char* p = strrchr(aux1, ' ') + 1;
        if(!(strcmp(apelidoAnterior, p)==0))//se o apelido for diferente
        {//pk os requisitantes estao por ordem alfabetica dos apelidos signfica que ja nao ha mais requisitantes com o apelidoAnterior
            if(n>x)//se o n for maior que o x || n - numero de requisitantes com o mesmo apelido atual | x - numero maior de requisitantes com o mesmo apelido
            {
                x=n; // o numero maior de requisitantes com o mesmo apelido anterior passa a ser igual ao do atual
                strcpy(apelidoMaisUsado, p); //o apelidoMaisUsado passa a ser o atual
                n=1; //o n passa a 1
            }
        }else //senao ainda e o mesmo apelido
        {
            n++;//incrementa o numero de requisitantes com o mesmo apelido atual
        }
        noReq=noReq->seg;//passa para o seguinte
    }
    //apresenta o apleido mais usado e o numero de requisitantes que o usa
    printf("\nO apelido mais usado é %s com um total de %d requisitantes com o mesmo.", apelidoMaisUsado, x);
    free(listaAux);//liberta o espaco ocupado pela lista auxiliar
}

REQUISITANTE* pesquisarRequisitantePorID(LISTA_REQUISITANTES* listaReq, char id_requisitante[9]) //retorna o requisitante com um certo id
{
    NO_REQUISITANTE *noReq = listaReq->inicio;
    while(noReq)//percorre todos os requisitantes
    {
        if(strcmp(noReq->requisitante->id_requisitante, id_requisitante) == 0) //se o id do requisitante for igual
        {
            return noReq->requisitante; //retorna o requisitante
        }
        noReq = noReq->seg;//passa apra o seguinte
    }
    return NULL;//retorna null se nao encontrar ninguem
}

void libertarMemoriaListaRequisitantes(LISTA_REQUISITANTES* listaReq)//nao esta a funcionar
{
    if(!listaReq || !listaReq->inicio)
    {
        return;
    }
    NO_REQUISITANTE* noReq = listaReq->inicio, *noReqAux = NULL;
    while(noReq)
    {
        noReqAux = noReq->seg;
        free(noReq->requisitante);
        free(noReq);
        noReq = noReqAux;
    }
    free(listaReq);
}

#endif
