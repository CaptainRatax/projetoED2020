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
#include "auxiliares.h"
#include "freguesias.h"
#include "freguesias.c"
#include "requisicoes.h"

DATA *criarData() //cria uma data vazia (aloca espaco)
{
    DATA *data = (DATA *)malloc(sizeof(DATA)); //aloca espaco para a data
    data->dia=0; //inicializa o dia em 0
    data->mes=0; //inicializa o mes em 0
    data->ano=0; //inicializa o ano em 0
    data->valid=0; //inicializa a variael valid em 0
    return data; //retorna a data
}

DATA* validarData(char data[100])
{
    int pos = 0;
    char dataInteira[100];
    char *dados[3];
    strcpy(dataInteira, data);
    char *elemento = strtok(data, "-");//a data tem que ser separada por "-" senao sera invalida

    while (elemento != NULL) //guarda todos os dados da data separados no array dados
    {
        dados[pos] = (char *)malloc((strlen(elemento) + 1) * sizeof(char));//aloca espaco para a posicao do array
        strcpy(dados[pos], elemento);
        pos++;
        elemento = strtok(NULL, "-");
    }
    if(strlen(dados[0])==2) // se no primeiro espaco tiver dois digitos(se for um dia)
    {
        if(strlen(dados[1])==2) //se no segundo espaco tiver dois digitos(se for um mes)
        {
            if(strlen(dados[2])==4) // se no terceiro espaco tiver quatro digitos(se for um ano)
            {//entao a data esta correta
                //devolve a mesma data que recebeu
                DATA* data = criarData();//cria uma data vazia (aloca espaco)
                data->dia = atoi(dados[0]);//coloca o dia
                data->mes = atoi(dados[1]);//coloca o mes
                data->ano = atoi(dados[2]);//coloca o ano
                data->valid = 1;//coloca a data valida || 0 - Data Invalida | 1 - Data Correta | 2 - Data Composta
                return data;//retorna a data
            }else if (strlen(dados[0])==4 && strlen(dados[2])==2) // se o primeiro espaco tiver 4 digitos(ano) e o terceiro tiver 2 digitos(dia)
            {//entao a data esta em formato americano
                //devolve a data no formato europeu
                DATA* dataComposta = criarData();//cria uma data vazia (aloca espaco)
                dataComposta->dia = atoi(dados[2]);//coloca o dia
                dataComposta->mes = atoi(dados[1]);//coloca o mes
                dataComposta->ano = atoi(dados[0]);//coloca o ano
                dataComposta->valid = 2;//coloca a data como composta || 0 - Data Invalida | 1 - Data Correta | 2 - Data Composta
                return dataComposta;//retorna a data
            }else//a data e invalida
            {
                DATA* dataErrada = criarData();//cria uma estrutura de dados vazia (aloca espaco)
                dataErrada->valid = 0;//coloca a data como invalida || 0 - Data Invalida | 1 - Data Correta | 2 - Data Composta
                return dataErrada;//retorna a estrutura data vazia apenas com o valid a 0
            }
        }else //a data e invalida
        {
            DATA* dataErrada = criarData();//cria uma estrutura de dados vazia (aloca espaco)
            dataErrada->valid = 0;//coloca a data como invalida || 0 - Data Invalida | 1 - Data Correta | 2 - Data Composta
            return dataErrada;//retorna a estrutura data vazia apenas com o valid a 0
        }
    }else if (strlen(dados[0])==4 && strlen(dados[2])==2) // se o primeiro espaco tiver 4 digitos(ano) e o terceiro tiver 2 digitos(dia)
    {//entao a data esta em formato americano
        //devolve a data no formato europeu
        DATA* dataComposta = criarData();//cria uma data vazia (aloca espaco)
        dataComposta->dia = atoi(dados[2]);//coloca o dia
        dataComposta->mes = atoi(dados[1]);//coloca o mes
        dataComposta->ano = atoi(dados[0]);//coloca o ano
        dataComposta->valid = 2;//coloca a data como composta || 0 - Data Invalida | 1 - Data Correta | 2 - Data Composta
        return dataComposta;//retorna a data
    }
    //a data e invalida
    DATA* dataErrada = criarData();//cria uma estrutura de dados vazia (aloca espaco)
    dataErrada->valid = 0;//coloca a data como invalida || 0 - Data Invalida | 1 - Data Correta | 2 - Data Composta
    return dataErrada;//retorna a estrutura data vazia apenas com o valid a 0
}

void logs(char linhaInteira[200], char mensagem[300])//escreve algum tipo de erro no ficheiro logs.txt
{
    FILE *fic;
    fic = fopen("logs.txt", "a");//abrir o fichero
    //vai buscar a data autal
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    //escreve no ficheiro logs a data e o tempo em que o erro decooreu, a linha e a mensagem
    fprintf(fic, "%02d-%02d-%d %02d:%02d:%02d -> Linha: %s -> %s\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec, linhaInteira, mensagem);
    fclose(fic);//fecha o ficheiro
}

int getFirst2Digits(long input) // retorna os dosi primeiros digitos de um numero
{
    long local = input;

    while (local >= 100)
    {
        local /= 10;
    }

    return local;
}

int mensagemConfirmacao(char mensagem[1000]) //escreve uma mensagem de confirmacao para o utilizador confirmar algo e retorna a resposta do mesmo
{
    char confirmacao[10];
    printf("\n%s\nSe sim escreva 'sim':", mensagem);
    char temp;
    scanf("%c",&temp);
    scanf("%[^\n]", confirmacao);
    if(strcmp(confirmacao, "sim")==0||strcmp(confirmacao, "Sim")==0||strcmp(confirmacao, "sIm")==0||strcmp(confirmacao, "siM")==0||strcmp(confirmacao, "SIm")==0||strcmp(confirmacao, "sIM")==0||strcmp(confirmacao, "SIM")==0)
    {//se ele escrever sim
        return 1; // 0 - nao confirmou || 1 - confirmou
    }
    //se ele escrever qualquer outra coisa
    return 0; // 0 - nao confirmou || 1 - confirmou
}

void gravarFicheiroXML(HASHING_LIVRO* hashingLiv, LISTA_REQUISITANTES* listaReq, HASHING_REQUISICOES* hashingReq, LISTA_NUM_REQUISICOES* listaNumRequisicoes, char nomeFicheiro[100])
{
    if(!hashingLiv || !hashingLiv->inicio)//verifica o hashing
    {
        return;//sai
    }
    if(!listaReq || !listaReq->inicio)//verifica a lista
    {
        return;//sai
    }
    if(!hashingReq || !hashingReq->inicio) //verifica o hashing
    {
        return;//sai
    }
    if(!listaNumRequisicoes || !listaNumRequisicoes->inicio) //verifica a lista
    {
        return; //sai
    }

    strcat(nomeFicheiro, ".xml");

    FILE *ficheiro;
    ficheiro = fopen(nomeFicheiro, "w");//abre o ficheiro
    if(!ficheiro)//verifica o ficheiro
    {
        printf("\nNao foi possivel abrir o ficheiro %s\n", "requisitantes.txt");
        return;//sai
    }
    printf("\nA criar o ficheiro xml...\n");

    //escrita do ficheiro xml
    fprintf (ficheiro,"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");//cabecalho
    fprintf(ficheiro, "<biblioteca>\n");

        //escreve todos os livros no ficheiro xml
        fprintf(ficheiro, "\t<livros>\n");
        NO_HASHING_LIVRO* noHashLivro = hashingLiv->inicio;
        while(noHashLivro)//percore o hashing todo
        {
            NO_LIVRO *noLiv = noHashLivro->listaLiv->inicio;
            while(noLiv)//percorre todos os livros
            {
                //escreve no ficheiro todos os dados do livro
                fprintf(ficheiro, "\t\t<livro>\n");
                    fprintf(ficheiro,"\t\t\t<ISBN>%d</ISBN>\n\t\t\t<area>%s</area>\n\t\t\t<n_requisicoes_area>%d</n_requisicoes_area>\n\t\t\t<titulo>%s</titulo>\n\t\t\t<fornecedor>%s</fornecedor>\n\t\t\t<ano>%d</ano>\n\t\t\t<estado>%d</estado>\n\t\t\t<n_requisicoes_livro>%d</n_requisicoes_livro>\n", noLiv->livro->ISBN, noLiv->livro->area, noHashLivro->n_requisicoes, noLiv->livro->titulo, noLiv->livro->fornecedor, noLiv->livro->ano, noLiv->livro->estado, noLiv->livro->n_requisicoes);
                fprintf(ficheiro, "\t\t</livro>\n");
                noLiv=noLiv->seg;//passa para o seguinte
            }
            noHashLivro = noHashLivro->seg;//passa apra o seguinte
        }
        fprintf(ficheiro, "\t</livros>\n");

        //escreve todos os requisitantes no ficheiro xml
        fprintf(ficheiro, "\t<requisitantes>\n");
        NO_REQUISITANTE *noReq = listaReq->inicio;
        while(noReq)//percorre todos os requisitantes
        {
            //grava os dados desse requisitante numa linha no ficheiro
            fprintf(ficheiro, "\t\t<requisitante>\n");
            fprintf(ficheiro,"\t\t\t<id>%s</id>\n\t\t\t<nome>%s</nome>\n\t\t\t<data_nascimento>%04d-%02d-%02d</data_nascimento>\n\t\t\t<id_freguesia>%s</id_freguesia>\n", noReq->requisitante->id_requisitante, noReq->requisitante->nome, noReq->requisitante->ano, noReq->requisitante->mes, noReq->requisitante->dia, noReq->requisitante->id_freguesia);
            fprintf(ficheiro, "\t\t</requisitante>\n");
            noReq=noReq->seg;//passa para o seguinte requisitante
        }
        fprintf(ficheiro, "\t</requisitantes>\n");

        //escreve todas as requisicoes no ficheiro xml
        fprintf(ficheiro, "\t<requisicoes>\n");
        NO_HASHING_REQUISICAO* noHashReq = hashingReq->inicio;
        while(noHashReq) //enquanto o noHash nao for null
        {
            NO_REQUISICAO *noReq = noHashReq->listaReq->inicio;
            while(noReq) //enquanto o noReq nao for null
            {
                //escreve no ficheiro os dados
                fprintf(ficheiro, "\t\t<requisicao>\n");
                fprintf(ficheiro,"\t\t\t<id_requisitante>%s</id_requisitante>\n\t\t\t<ISBN>%d</ISBN>\n\t\t\t<dataInicio>%04d-%02d-%02d</dataInicio>\n\t\t\t<dataFim>%04d-%02d-%02d</dataFim>\n\t\t\t<estado>%d</estado>\n", noReq->requisicao->requisitante->id_requisitante, noReq->requisicao->livro->ISBN, noReq->requisicao->dataInicio->ano, noReq->requisicao->dataInicio->mes, noReq->requisicao->dataInicio->dia, noReq->requisicao->dataFim->ano, noReq->requisicao->dataFim->mes, noReq->requisicao->dataFim->dia, noReq->requisicao->estado);
                fprintf(ficheiro, "\t\t</requisicao>\n");
                noReq=noReq->seg; //passa para o no seguinte
            }
            noHashReq = noHashReq->seg; //passa para o no seguinte
        }
        fprintf(ficheiro, "\t</requisicoes>\n");

        //escreve todas os numRequisicoes no ficheiro xml
        fprintf(ficheiro, "\t<numRequisicoes>\n");
        NO_NUM_REQUISICOES *noNumReq = listaNumRequisicoes->inicio;
        while(noNumReq) //enquanto o noNumReq nao e NULL
        {
            fprintf(ficheiro, "\t\t<numRequisicao>\n");
            fprintf(ficheiro,"\t\t\t<id_requisitante>%s</id_requisitante>\n\t\t\t<num>%d</num>\n", noNumReq->num_requisicoes->requisitante->id_requisitante, noNumReq->num_requisicoes->num); //escreve no ficheiro os dados
            fprintf(ficheiro, "\t\t</numRequisicao>\n");
            noNumReq=noNumReq->seg; // passa para o no seguinte
        }
        fprintf(ficheiro, "\t</numRequisicoes>\n");
    fprintf(ficheiro, "</biblioteca>");
    fclose(ficheiro);//fecha o ficheiro
    printf("\nFicheiro criado com sucesso!");
}

#endif
