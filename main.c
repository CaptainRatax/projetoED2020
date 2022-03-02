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

//MENU PARA AS FUNCIONALIDADES DOS REQUISITANTES
void requisitantes(LISTA_REQUISITANTES *listaReq, HASHING_REQUISICOES* hashingReq)
{
    int i=1;
    do
    {
        //Opcoes para o utilizador escolher
        printf("\n\nREQUISITANTES\n");
        printf("\nDigite o numero da opcao que deseja");
        printf("\n1.  Inserir requisitante");
        printf("\n2.  Procurar Requisitante pelo nome");
        printf("\n3.  Idade maxima dos requisitantes");
        printf("\n4.  Idade media dos requisitantes");
        printf("\n5.  Número de requisitantes acima, igual e abaixo de n anos");
        printf("\n6.  Mostrar lista de todos os requisitantes por ordem alfabetica");
        printf("\n7.  Mostrar lista de todos os requisitantes por ordem alfabetica do apelido");
        printf("\n8.  Mostrar lista de todos os requisitantes por ordem do id da freguesia");
        printf("\n9.  Mostrar qual a idade com mais requisitantes");
        printf("\n10. Mostrar qual o apelido mais usado pelos requistantes");
        printf("\n11. Mostrar requisicoes de um dado requisitante");
        printf("\n12. Mostrar todos os requisitantes com livros requisitados");
        printf("\n13. Mostrar todos os requisitantes que nunca requisitaram nada");
        printf("\n0. Voltar atras\n");
        scanf("%d", &i);//le a opcao que o utilizador escolheu
        switch(i)//ve qual a opcao
        {
            case 0: //se o utilizador escolheu a 0
            {
                //volta para o menu principal

                system("cls");//limpa o ecra
                break;//sai do switch
            }
            case 1: //se o utilizador escolheu a 1
            {
                //criar requisitante

                system("cls");//limpa o ecra
                REQUISITANTE* req = criarRequisitante(); //cria um requisitante vazio
                preencherRequisitante(req, listaReq->ultimoIdRequisitante); //apresenta um menu para o utilizador preencher os dados do requisitante
                NO_REQUISITANTE* noReq = criarNodoRequisitante(); //cria um noReq vazio
                noReq->requisitante = req; //aponta o noReq para o requisitante preenchido antreriormente
                inserirRequisitanteNaLista(listaReq,noReq);//insere o noReq na lista de requisitantes
                break;//sai do switch
            }
            case 2: //se o utilizador escolheu a 2
            {
                //procurar requisitante pelo nome

                //pede o nome do requisitante ao utilizador
                char nome[50];
                printf("\nInsira o nome do Requisitante que deseja encontrar: ");
                char temp;
                scanf("%c",&temp);
                scanf("%[^\n]", nome);
                REQUISITANTE* requisitante = pesquisarRequisitantePorNome(listaReq, nome); //pesquisa o requisitante pelo nome que o utilizador lhe deu
                if (!requisitante)//verificar requistiante
                {
                    printf("Nao existe nenhum requisitante com esse nome!");
                    break;//sai do switch
                }
                apresentarDetalhesRequisitante(requisitante);//apresenta os detalhes desse requisitante
                break;//sai do switch
            }
            case 3: //se o utilizador escolheu a 3
            {
                //determina a idade maxima de todos os requisitantes

                determinarIdadeMaximaRequisitantes(listaReq);
                break;//sai do switch
            }
            case 4: //se o utilizador escolheu a 4
            {
                //determina a idade media de todos os requistantes

                determinarIdadeMediaRequisitantes(listaReq);
                break;//sai do switch
            }
            case 5: //se o utilizador escolheu a 5
            {
                //determina o numero de requisitantes acima, igual e abaixo de x idade (inserida pelo utilizador)

                //pede a idade ao utilizador
                int x;
                printf("\nInsira a idade: ");
                scanf("%d", &x);
                determinarNumeroRequisitantesAcimaDeX(listaReq, x);
                break;//sai do switch
            }
            case 6: //se o utilizador escolheu a 6
            {
                //mostra todos os requisitantes por ordem alfabetica

                //faz aparecer uma mensagem de confirmacao para o utilizador confirmar se quer continuar
                char mensagem[1000];
                strcpy(mensagem, "A seguinte funcao ira mostrar uma lista com um enorme numero de dados, fazendo com que demorara algum tempo a ser executada. Tem acerteza que deseja continuar?");
                if(mensagemConfirmacao(mensagem)==1) // se confirmar || 0 - nao confirmou | 1 - confirmou
                {
                    mostrarPorOrdemAlfabetica(listaReq);
                }
                break;//sai do switch
            }
            case 7: //se o utilizador escolheu a 7
            {
                //mostra todos os requisitantes por ordem alfabetica do apelido

                //faz aparecer uma mensagem de confirmacao para o utilizador confirmar se quer continuar
                char mensagem[1000];
                strcpy(mensagem, "A seguinte funcao ira mostrar uma lista com um enorme numero de dados, fazendo com que demorara algum tempo a ser executada. Tem acerteza que deseja continuar?");
                if(mensagemConfirmacao(mensagem)==1) // se confirmar || 0 - nao confirmou | 1 - confirmou
                {
                    mostrarPorOrdemAlfabeticaApelido(listaReq);
                }
                break;//sai do switch
            }
            case 8: //se o utilizador escolheu a 8
            {
                //mostra todos os requisitantes por do id freguesia

                //faz aparecer uma mensagem de confirmacao para o utilizador confirmar se quer continuar
                char mensagem[1000];
                strcpy(mensagem, "A seguinte funcao ira mostrar uma lista com um enorme numero de dados, fazendo com que demorara algum tempo a ser executada. Tem acerteza que deseja continuar?");
                if(mensagemConfirmacao(mensagem)==1) // se confirmar || 0 - nao confirmou | 1 - confirmou
                {
                    mostrarPorOrdemIdFreguesia(listaReq);
                }
                break;//sai do switch
            }
            case 9: //se o utilizador escolheu a 9
            {
                //apresenta a idade com mais requisitantes

                idadeComMaisRequisitantes(listaReq);
                break;//sai do switch
            }
            case 10: //se o utilizador escolheu a 10
            {
                //apresenta o apelido com mais requisitantes

                apelidoMaisUsadoPelosRequisitantes(listaReq);
                break;//sai do switch
            }
            case 11: //se o utilizador escolheu a 11
            {
                //apresenta todas as requisicoes de um requisitante escolhido pelo utilizador

                apresentarRequisicoesDeUmRequisitante(hashingReq, listaReq);
                break;//sai do switch
            }
            case 12: //se o utilizador escolheu a 12
            {
                //mostra todos os requisitantes com livros requisitados

                //faz aparecer uma mensagem de confirmacao para o utilizador confirmar se quer continuar
                char mensagem[1000];
                strcpy(mensagem, "A seguinte funcao podera mostrar uma lista com um enorme numero de dados, fazendo com que demorara algum tempo a ser executada. Tem acerteza que deseja continuar?");
                if(mensagemConfirmacao(mensagem)==1) // se confirmar || 0 - nao confirmou | 1 - confirmou
                {
                    apresentarRequisitantesComLivrosRequisitados(hashingReq, listaReq);
                }
                break;//sai do switch
            }
            case 13: //se o utilizador escolheu a 13
            {
                //mostra todos os requisitantes sem requisicoes

                //faz aparecer uma mensagem de confirmacao para o utilizador confirmar se quer continuar
                char mensagem[1000];
                strcpy(mensagem, "A seguinte funcao podera mostrar uma lista com um enorme numero de dados, fazendo com que demorara algum tempo a ser executada. Tem acerteza que deseja continuar?");
                if(mensagemConfirmacao(mensagem)==1) // se confirmar || 0 - nao confirmou | 1 - confirmou
                {
                    apresentarRequisitantesSemRequisicoes(hashingReq, listaReq);
                }
                break;//sai do switch
            }
            default: //se o utilizador nao escolheu nenhuma das anteriores
            {
                printf("\nOpcao invalida!");
                break;//sai do switch
            }
        }
    }while(i!=0);//repete o menu ate o utilizador escolher a opcao 0
}

//MENU PARA AS FUNCIONALIDADES DOS LIVROS
void livros(HASHING_LIVRO *hashingLiv)
{
    int i=1;

    do
    {
        //Opcoes apra o utilizador escolher
        printf("\n\nLIVROS\n");
        printf("\nDigite o numero da opcao que deseja");
        printf("\n1. Inserir livro");
        printf("\n2. Mostrar todos os livros por area");
        printf("\n3. Pesquisar livro por ISBN");
        printf("\n4. Determinar area com mais livros");
        printf("\n5. Apresentar livros mais recentes");
        printf("\n6. Apresentar livro mais requisitado");
        printf("\n7. Apresentar a area com mais livros requisitados");
        printf("\n0. Voltar atras\n");
        scanf("%d", &i);//le a opcao que o utilizador escolheu
        switch(i) //ve qual a opcao
        {
            case 0://se o utilizador escolheu a 0
            {
                //volta para o menu principal

                system("cls");//limpa o ecra
                break;//sai do switch
            }
            case 1://se o utilizador escolheu a 1
            {
                //criar um livro

                system("cls");//limpa o ecra
                preencherLivro(hashingLiv);
                break;//sai do switch
            }
            case 2://se o utilizador escolheu a 2
            {
                //apresenta todos os livros por area

                system("cls");//limpa o ecra
                //faz aparecer uma mensagem de confirmacao para o utilizador confirmar se quer continuar
                char mensagem[1000];
                strcpy(mensagem, "A seguinte funcao ira mostrar uma lista com um enorme numero de dados, fazendo com que demorara algum tempo a ser executada. Tem acerteza que deseja continuar?");
                if(mensagemConfirmacao(mensagem)==1) // se confirmar || 0 - nao confirmou | 1 - confirmou
                {
                    apresentarLivrosPorArea(hashingLiv);
                }
                break;//sai do switch
            }
            case 3://se o utilizador escolheu a 3
            {
                //pesquisa um livro pelo ISBN

                //pede o ISBN ao utilizador
                char ISBN[10];
                printf("\nInsira o ISBN do livro que deseja encontrar: ");
                scanf("%s", ISBN);

                LIVRO *livro = pesquisarLivroPorISBN(hashingLiv, atoi(ISBN));//pesquisa o livro por ISBN
                if (!livro)//verifica o livro
                {
                    printf("Não existe nenhum livro com esse ISBN!");
                    break;//sai do switch
                }
                apresentarLivro(livro); //apresenta os detalhes do livro que encontrou
                break;//sai do switch
            }
            case 4://se o utilizador escolheu a 4
            {
                //determina a area com mais livros

                determinarAreaComMaisLivros(hashingLiv);
                break;//sai do switch
            }
            case 5://se o utilizador escolheu a 5
            {
                //apresenta os livros com o ano mais recente

                apresentarLivrosMaisRecentes(hashingLiv);
                break;//sai do switch
            }
            case 6://se o utilizador escolheu a 6
            {
                //apresenta o livro mais recente

                LIVRO* livro = livroMaisRequisitado(hashingLiv);
                if(livro->ISBN != 0)//verifica o livro que recebeu
                {//se conter algum livro
                    apresentarLivro(livro);//apresenta o livro que recebeu
                    printf("\nCom um total de %d requisicoes.", livro->n_requisicoes);
                }else//se nao retoronou nenhum livro
                {
                    printf("\nAinda nenhum livro foi requisitado");
                }
                break;//sai do switch
            }
            case 7://se o utilizador escolheu a 7
            {
                //Apresenta a area mais requisitada

                areaMaisRequisitada(hashingLiv);
                break;//sai do switch
            }
            default://se o utilizador nao escolheu nenhuma das anteriores
            {
                printf("\nOpção inválida!");
                break;//sai do switch
            }
        }
    }while(i!=0); //repete o menu ate o utilizador escolher a opcao 0
}

//MENU PARA AS FUNCIONALIDADES DAS REQUISICOES
void requisicoes(HASHING_REQUISICOES* hashingReq, HASHING_LIVRO* hashingLiv, LISTA_REQUISITANTES* listaReq, LISTA_NUM_REQUISICOES* listaNumRequisicoes)
{
    int i=1;
    do
    {
        //Opcoes apra o utilizador escolher
        printf("\n\nREQUISICOES\n");
        printf("\nDigite o número da opção que deseja");
        printf("\n1. Submeter uma requisicao");
        printf("\n2. Devolver um livro");
        printf("\n3. Apresentar todas as requisicoes por data");
        printf("\n4. Apresentar todos os livros requisitados por área");
        printf("\n0. Voltar atrás\n");
        scanf("%d", &i);//le a opcao que o utilizador escolheu
        switch(i)//ve qual a opcao
        {
            case 0://se o utilizador escolheu a 0
            {
                //volta para o menu principal

                system("cls");//limpa o ecra
                break;//sai do switch
            }
            case 1://se o utilizador escolheu a 1
            {
                //efetua uma requisicao com os dados que o utilizador escolher

                system("cls");//limpa o ecra
                efetuarRequisicao(hashingLiv, listaReq, hashingReq, listaNumRequisicoes);
                break;//sai do switch
            }
            case 2://se o utilizador escolheu a 2
            {
                //devolve um livro escolhido pelo utiliazador

                devolverUmLivro(hashingLiv, hashingReq);
                break;//sai do switch
            }
            case 3://se o utilizador escolheu a 3
            {
                //apresenta todas as requisicoes por data

                apresentarRequisicoesPorData(hashingReq);
                break;//sai do switch
            }
            case 4://se o utilizador escolheu a 4
            {
                //lista todos os livros requisitados por area

                listarLivrosRequisitadosPorArea(hashingLiv, hashingReq);
                break;//sai do switch
            }
            default://se o utilizador nao escolheu nenhuma das anteriores
            {
                printf("\nOpção inválida!");
                break;//sai do switch
            }
        }
    }while(i!=0); //repete o menu ate o utilizador escolher a opcao 0
}

//MENU PRINCIPAL (main)
int main()
{
    int i=1;
    //carregamento inicial do programa
    setlocale(LC_ALL, ""); //acentos
    printf("A carregar o programa...\n");
    HASHING_LIVRO *hashingLiv = criarHashingLivros();//cria o hashing dos livros vazio (aloca espaco)
    LISTA_REQUISITANTES *listaReq = criarListaRequisitante();//cria a lista de requisitantes vazia (aloca espaco)
    HASHING_REQUISICOES *hashingReq = criarHashingRequisicoes();//cria o hashing das requisicoes vazio (aloca espaco)
    LISTA_FREGUESIAS *listaFreg = criarListaFreguesias();//cria a lista de freguesias (aloca espaco)
    LISTA_NUM_REQUISICOES *listaNumRequisicoes = criarListaNumRequisicoes();//cria a lista com os numeros de requisicoes de cada requisitante vazia (aloca espaco)
    lerFicheiroFreguesias(listaFreg); //le o ficheiro das freguesias e insere os seus dados na memoria
    lerFicheiroRequisitantes(listaReq, listaFreg); //le o ficheiro dos requisitantes e insere os seus dados na memoria
    lerFicheiroLivros(hashingLiv); //le o ficheiro dos livros e insere os seus dados na memoria
    lerFicheiroRequisicoes(hashingLiv, hashingReq, listaReq); //le o ficheiro das requisicoes e insere os seus dados na memoria
    lerNumRequisicoes(listaNumRequisicoes, listaReq); //le o ficheiro dos numeros de requisicoes e insere os seus dados na memoria
    system("cls");//limpa o ecra

    //apresenta o menu depois de carregar tudo
    do
    {
        //Opcoes apra o utilizador escolher
        printf("BIBLIOTECA\n");
        printf("\nDigite o número da opção que deseja");
        printf("\n1. Livros");
        printf("\n2. Requesitantes");
        printf("\n3. Requisições");
        printf("\n4. Data atual");
        printf("\n5. Gravar");
        printf("\n6. Exportar dados para um ficheiro XML");
        printf("\n0. Sair\n");
        scanf("%d", &i);//le a opcao que o utilizador escolheu
        switch(i)//ve qual a opcao
        {
            case 0://se o utilizador escolheu a 0
            {
                //sai do programa

                system("cls");//limpa o ecra
                printf("Obrigado pelo seu tempo!\n");
                break;//sai do switch
            }
            case 1://se o utilizador escolheu a 1
            {
                //abre o menu de opcoes dos livros

                system("cls");//limpa o ecra
                livros(hashingLiv);
                break;//sai do switch
            }
            case 2://se o utilizador escolheu a 2
            {
                //abre o menu de opcoes dos requisitantes

                system("cls");//limpa o ecra
                requisitantes(listaReq, hashingReq);
                break;//sai do switch
            }
            case 3://se o utilizador escolheu a 3
            {
                //abre o menu de opcoes das requisicoes

                system("cls");//limpa o ecra
                requisicoes(hashingReq, hashingLiv, listaReq, listaNumRequisicoes);
                break;//sai do switch
            }
            case 4://se o utilizador escolheu a 4
            {
                //apresenta a data atual

                //vai buscar a data atual
                time_t t = time(NULL);
                struct tm tm = *localtime(&t);
                printf("\nA data atual é %02d-%02d-%d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
                break;//sai do switch
            }
            case 5://se o utilizador escolheu a 5
            {
                //grava toda a informacao contida na memoria para os ficheiros

                system("cls");//limpa o ecra
                printf("A guardar a informacao...");
                gravarFicheiroLivros(hashingLiv);//grava a informacao relativa aos livros no ficheiro livros.txt
                gravarRequisitantes(listaReq);//grava a informacao relativa aos requisitantes no ficheiro requisitantes.txt
                gravarNumRequisicoes(listaNumRequisicoes);//grava a informacao relativa aos numeros de requisicoes no ficheiro numRequisicoes.txt
                gravarRequisicoes(hashingReq);//grava a informacao relativa as requisicoes no ficheiro requisicoes.txt
                system("cls");//limpa o ecra
                printf("\nDados gravados com sucesso!\n");
                break;//sai do switch
            }
            case 6:
            {
                //exporta todos os dados num ficheiro XML

                char nomeFicheiro[100];
                printf("\nEscolha o nome do ficheiro(sem o .xml): ");
                scanf("%s", nomeFicheiro);
                char mensagem[1000];
                strcpy(mensagem, "A seguinte funcao podera demorar algum tempo a ser executada dependendo do numero de dados. Tem acerteza que deseja continuar?");
                if(mensagemConfirmacao(mensagem)==1) // se confirmar || 0 - nao confirmou | 1 - confirmou
                {
                    gravarFicheiroXML(hashingLiv, listaReq, hashingReq, listaNumRequisicoes, nomeFicheiro);
                }
                break;

            }
            default://se o utilizador nao escolheu nenhuma das anteriores
            {
                printf("\nOpção inválida!");
                break;//sai do switch
            }
        }
    }while(i!=0);//repete o menu ate o utilizador escolher a opcao 0
    gravarFicheiroLivros(hashingLiv);//grava a informacao relativa aos livros no ficheiro livros.txt
    gravarRequisitantes(listaReq);//grava a informacao relativa aos requisitantes no ficheiro requisitantes.txt
    gravarNumRequisicoes(listaNumRequisicoes);//grava a informacao relativa aos numeros de requisicoes no ficheiro numRequisicoes.txt
    gravarRequisicoes(hashingReq);//grava a informacao relativa as requisicoes no ficheiro requisicoes.txt
    libertarMemoriaLivros(hashingLiv);
    libertarMemoriaListaFreguesias(listaFreg);
    libertarMemoriaListaNumRequisicoes(listaNumRequisicoes);
    libertarMemoriaListaRequisitantes(listaReq);
    libertarMemoriaRequisicoes(hashingReq);
    return 0;
}

#endif
