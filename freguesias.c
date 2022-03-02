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
#include "requisicoes.h"

FREGUESIA *criarFreguesia() //cria uma freguesia vazia (aloca espaco)
{
    FREGUESIA *freguesia = (FREGUESIA *)malloc(sizeof(FREGUESIA)); //aloca espaco para a freguesia
    return freguesia; //retorna a freguesia
}


NO_FREGUESIA *criarNodaFreguesia() // cria um no_freguesia vazio (aloca espaco)
{
    NO_FREGUESIA *no_freguesia = (NO_FREGUESIA *)malloc(sizeof(NO_FREGUESIA)); //aloca espaco para o no da freguesia
    no_freguesia->seg = NULL; //coloca o ponteiro para o no seguinte a NULL
    return no_freguesia; // retorna o no da freguesia
}

LISTA_FREGUESIAS *criarListaFreguesias() //cria a lista de freguesias vazias (aloca espaco)
{
    LISTA_FREGUESIAS *listaFreg = (LISTA_FREGUESIAS *)malloc(sizeof(LISTA_FREGUESIAS)); //aloca espaco para a lista de freguesias
    listaFreg->nel = 0; // inicializa o numero de elementos a 0
    return  listaFreg; // retorna a lista de freguesias
}

void inserirFreguesiaNaLista(LISTA_FREGUESIAS* listaFreg, NO_FREGUESIA* noFreg)
{
    if (!listaFreg) //verifica a lista de freguesias
    {
		printf("\nNao existe lista!");
		return;//sai
	}
	if (!noFreg) //verifica o no da freguesia
    {
		printf("\nNao existe no da freguesia!");
		return;//sai
	}
	//insere na lista
    noFreg->seg = listaFreg->inicio;
    listaFreg->inicio = noFreg;
    listaFreg->nel++;
}

void lerFicheiroFreguesias(LISTA_FREGUESIAS* listaFreg)
{
    FILE *fic;
    char nomeFic[10];
    strcpy(nomeFic, "freguesias.txt");
    char linha[120];
    char linhaInteira[120];

    fic = fopen(nomeFic, "r");//abrir ficheiro

    char *dados[2]; //0 - id_freguesia | 1 -  nome

    if(!fic)//verificar ficheiro
    {
        printf("\nNao foi possivel abrir o ficheiro %s\n", nomeFic);
        return;//sai
    }

    while(!feof(fic))
    {

        if(fgets(linha, 120, fic) != NULL) //verifica se a linha foi bem lida
        {
            int pos = 0;
            strcpy(linhaInteira, linha);
            char *elemento = strtok(linha, "\t");

            while (elemento != NULL) //guarda todos os dados da linha do array dados
            {
                dados[pos] = (char *)malloc((strlen(elemento) + 1) * sizeof(char));//aloca espaco para a posicao do array
                strcpy(dados[pos], elemento);
                pos++;
                elemento = strtok(NULL, "\t");
            }

            NO_FREGUESIA *noFreg = criarNodaFreguesia(); //cria um no da freguesia vazio (aloca espaco)
            noFreg->freguesia = criarFreguesia(); //cria uma freguesia vazia (aloca espaco)
            FREGUESIA *freg = noFreg->freguesia; //coloca o no a apontar para a freguesia

            int tamID = strlen(dados[0]);
            dados[0][tamID] = '\0';
            strcpy(freg->id_freguesia, dados[0]); //coloca o id da freguesia no array

            strcpy(freg->nome, dados[1]); //coloca o nome da freguesia no array

            inserirFreguesiaNaLista(listaFreg, noFreg);//insere a freguesia na lista

            //libertar o espaco ocupado no array
            free(dados[0]);
            free(dados[1]);
        }
    }
    fclose(fic);//fechar o ficheiro
}

FREGUESIA* listarTodasAsFreguesias(LISTA_FREGUESIAS* listaFreg)
{
    NO_FREGUESIA *noFreg = listaFreg->inicio;
    while(noFreg)//enquanto nao for null
    {
        //lista os detalhes da freguesia
        printf("\nOs detalhes da freguesia sao: ");
        printf("\nID: %s", noFreg->freguesia->id_freguesia);
        printf("\nNome: %s", noFreg->freguesia->nome);
        noFreg = noFreg->seg;
    }
}

int validarIdFreguesia(LISTA_FREGUESIAS* listaFreg, char id_freguesia[6]) //retorna 0 - invalido | 1 - valido
{
    NO_FREGUESIA *noFreg = listaFreg->inicio;
    while(noFreg)//percorre as freguesias todas e ve se o id recebido existe na lista
    {
        if(strcmp(noFreg->freguesia->id_freguesia, id_freguesia)==0)//se o id da freguesia existir
        {
            return 1;//retorna 1 - valido
        }
        noFreg=noFreg->seg;//passa para o seguinte
    }
    return 0;//retorna 0 - invalido
}

void libertarMemoriaListaFreguesias(LISTA_FREGUESIAS* listaFreg)//nao esta a funcionar
{
    if(!listaFreg || !listaFreg->inicio)
    {
        return;
    }
    NO_FREGUESIA* noFreg = listaFreg->inicio, *noFregAux = NULL;
    while(noFreg)
    {
        noFregAux = noFreg->seg;
        free(noFreg->freguesia);
        free(noFreg);
        noFreg = noFregAux;
    }
    free(listaFreg);
}

#endif
