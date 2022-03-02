#ifndef HEADERFILE_H
#define HEADERFILE_H
#include <stdio.h> // main
#include <stdlib.h> // main
#include <string.h> // strings
#include <locale.h> //acentos
#include <time.h> //data atual
#include <stdbool.h>//booleans
#include "livros.h"
#include "requisitantes.c"
#include "requisitantes.h"
#include "auxiliares.c"
#include "auxiliares.h"
#include "freguesias.h"
#include "freguesias.c"
#include "requisicoes.h"

HASHING_LIVRO *criarHashingLivros() //criar hashing vazio (aloca espaco)
{
    HASHING_LIVRO* hashingLiv = (HASHING_LIVRO *)malloc(sizeof(HASHING_LIVRO)); //(aloca espaco)
    hashingLiv->inicio = NULL; //incializa a NULL
    hashingLiv->nel = 0;//inicializa a 0
    return hashingLiv; //retorna a estrutura
}

NO_HASHING_LIVRO* criarNodoHashingLivros() //cria no hashing vazio (aloca espaco)
{
	NO_HASHING_LIVRO* noHashingLiv = (NO_HASHING_LIVRO *)malloc(sizeof(NO_HASHING_LIVRO));//(aloca espaco)
	noHashingLiv->ant = NULL;//incializa a NULL
	noHashingLiv->seg = NULL;//incializa a NULL
	return noHashingLiv;//retorna a estrutura
}

LISTA_LIVROS *criarListaLivro() //cria lista vazia (aloca espaco)
{
    LISTA_LIVROS *listaLiv = (LISTA_LIVROS *)malloc(sizeof(LISTA_LIVROS));//(aloca espaco)
    listaLiv->inicio = NULL;//incializa a NULL
    listaLiv->nel = 0;//inicializa a 0
    return listaLiv;//retorna a estrutura
}

NO_LIVRO *criarNodoLivro() //cria no vaizio (aloca espaco)
{
    NO_LIVRO *noLiv = (NO_LIVRO *)malloc(sizeof(NO_LIVRO));//(aloca espaco)
    noLiv->seg = NULL;//incializa a NULL
    noLiv->ant = NULL;//incializa a NULL
    noLiv->livro = NULL;//incializa a NULL
    return noLiv;//retorna a estrutura
}

LIVRO *criarLivro() //cria livro vazio (aloca espaco)
{
    LIVRO *livro = (LIVRO *)malloc(sizeof(LIVRO));//(aloca espaco)
    livro->ISBN = 0;//inicializa a 0
    livro->ano = 0;//inicializa a 0
    livro->estado = 0;//inicializa a 0
    livro->n_requisicoes = 0;//inicializa a 0
    return livro;//retorna a estrutura
}

void inserirLivroListaPorOrdemAlfabetica(LISTA_LIVROS* listaLiv, LIVRO* livro)
{
	if (!listaLiv) //verifica a lista
    {
        return; //sai
    }
	if (!livro) //verifica o livro
    {
        return; //sai
    }

	NO_LIVRO* noLiv = criarNodoLivro();
	noLiv->livro = livro;

	if (!listaLiv->inicio) //se nao houver nenhum livro na lista
    {
		listaLiv->inicio = noLiv;//coloca em primeiro lugar
	}
	else //se ja houver algum livro na lista
	{

		NO_LIVRO* aux = listaLiv->inicio; //criar auxiliar para guardar o primeiro
		int i = 1;
		while (i)//enquanto nao for 0
		{

			if (strcmp(noLiv->livro->titulo, aux->livro->titulo) >= 0) // se o titulo for maior (na cadeia de ASCII) ou igual
			{
				if (aux->seg)//se nao for o ultimo
				{
					if (strcmp(noLiv->livro->titulo, aux->seg->livro->titulo) <= 0) //se o titulo for menor (na cadeia de ASCII) ou igual
					{
						//insere no meio
						noLiv->seg = aux->seg;
						noLiv->ant = aux;
						aux->seg->ant = noLiv;
						aux->seg = noLiv;
						i = 0;
					}
				}
				else // se for o ultimo
				{
					//insere no fim
					aux->seg = noLiv;
					noLiv->ant = aux;
					i = 0;
				}
			}
			else//se for menor (na cadeia de ASCII)
			{
				//insere no inicio
				noLiv->seg = aux;
				aux->ant = noLiv;
				listaLiv->inicio = noLiv;
				i = 0;
			}

			aux = aux->seg;//passa para o seguinte
		}
	}

	listaLiv->nel++;//incrementa o numero de elementos da lista
}

NO_HASHING_LIVRO* verificarArea(HASHING_LIVRO* hashingLiv, const char* area) //verifica se a area ja existe no hashing
{

	if (!hashingLiv) //verifica o hashing
    {
        return NULL;//sai
    }
	if (!area) //verifica a area
    {
        return NULL; //sai
    }

	NO_HASHING_LIVRO* aux = hashingLiv->inicio;
	while (aux) //percorrer todos as areas
	{
		if (strcmp(aux->area, area) == 0) //se for igual
        {
			return aux;//retorna o no_hashing
		}
		aux = aux->seg;//passa apra o seguitne
	}
	return NULL;//se nao existir retorna null
}

void adicionarLivroHashing(HASHING_LIVRO* hashingLiv, LIVRO* livro, int isReading, int n_requisicoes_area) //adiciona o livro por area ao hashing
{
	if (!hashingLiv) //verifica o hashing
    {
        return; //sai
    }


	if (!livro) //verifica o livro
    {
        return; //sai
    }

	NO_HASHING_LIVRO* noHashingLiv = verificarArea(hashingLiv, livro->area);

	if (!noHashingLiv) //se a area nao existir
    {

		noHashingLiv = criarNodoHashingLivros();

		noHashingLiv->listaLiv = criarListaLivro();
		strcpy(noHashingLiv->area, livro->area);

		if (!hashingLiv->inicio) //se nao houver nenhuma area no hashing
        {
			hashingLiv->inicio = noHashingLiv;//coloca o noHashingLiv no inicio do hashing
		}
		else //se ja houver alguma area no hashing
        {
			NO_HASHING_LIVRO* aux = hashingLiv->inicio; //criar auxiliar para guardar o primeiro
			int i = 1;
			while (i)//enquanto nao for 1
			{

				if (strcmp(noHashingLiv->area, aux->area) >= 0) //se o nome da area for maior (na cadeia de ASCII) ou igual
				{
					if (aux->seg)//se nao for o ultimo
					{
						if (strcmp(noHashingLiv->area, aux->seg->area) <= 0) //se o nome da area for menor (na cadeia de ASCII) ou igual
						{
							//insere no meio
							noHashingLiv->seg = aux->seg;
							noHashingLiv->ant = aux;
							aux->seg->ant = noHashingLiv;
							aux->seg = noHashingLiv;
							i = 0;
						}
					}
					else//se for o ultimo
					{
						//insere no fim
						aux->seg = noHashingLiv;
						noHashingLiv->ant = aux;
						i = 0;
					}
				}
				else //se o nome da area for menor (na cadeia de ASCII)
				{
					//insere no inicio
					noHashingLiv->seg = aux;
					aux->ant = noHashingLiv;
					hashingLiv->inicio = noHashingLiv;

					i = 0;
				}
				aux = aux->seg;//passa ao seguinte
			}
		}
		if(isReading == 1)//se foi a funcao que le o ficheiro dos livros que chamou eta funcao
        {
            noHashingLiv->n_requisicoes = n_requisicoes_area;//ele coloca o numero de requisicoes que o ficheiro devolveu
        }
		hashingLiv->nel++;//incrementa o numero de elementos do hashing
	}

	inserirLivroListaPorOrdemAlfabetica(noHashingLiv->listaLiv, livro); //insere o livrio na lista por ordem alfabetica
}

//cria um livro ja preenchido com os dados que recebe
LIVRO* criarLivroPreenchido(HASHING_LIVRO* Livros, int isbn, const char* titulo, const char* fornecedor, const char* area, int ano, int estado, int n_requisicoes_livro)
{
	LIVRO* livro = criarLivro(); //cria um livro vazio (aloca espaco)

	if (!isbn) //verifica o isbn
    {
		return NULL;//sai
	}
	else //se for valido
	{
		livro->ISBN = isbn; //coloca-o no livro
	}

	if (strlen(titulo)<=1) //verifica o titulo
    {
		return NULL;//sai
	}
	else //se for valido
    {
		strcpy(livro->titulo,titulo);//coloca-o no titulo
	}

	if (strlen(area) <= 1) //verifica a area
    {
		return NULL;//sai
	}
	else //se for valida
    {
		strcpy(livro->area, area);//coloca-a no livro
	}

	strcpy(livro->fornecedor, fornecedor);//preenche o fornecedor
	livro->ano = ano;//preenche o ano
	livro->n_requisicoes = n_requisicoes_livro;//preenche o numero de requisicoes
	livro->estado = estado;//preenche o estado

	return livro;//retorna o livro criado e preenchido
}

void gravarFicheiroLivros(HASHING_LIVRO* hashingLiv) //grava no ficheiro livros.txt todos os livros na memoria
{
    if(!hashingLiv || !hashingLiv->inicio)//verifica o hashing
    {
        return;//sai
    }
    FILE *ficheiro;
    ficheiro = fopen("livros.txt", "w");//abre o ficheiro
    if(!ficheiro)//verifica o ficheiro
    {
        printf("\nNao foi possivel abrir o ficheiro %s\n", "livros.txt");
        return;//sai
    }
    NO_HASHING_LIVRO* noHash = hashingLiv->inicio;
    while(noHash)//percore o hashing todo
    {
        NO_LIVRO *noLiv = noHash->listaLiv->inicio;
        while(noLiv)//percorre todos os livros
        {
            //escreve no ficheiro todos os dados do livro
            fprintf(ficheiro,"%d\t%s\t%d\t%s\t%s\t%d\t%d\t%d\n", noLiv->livro->ISBN, noLiv->livro->area, noHash->n_requisicoes, noLiv->livro->titulo, noLiv->livro->fornecedor, noLiv->livro->ano, noLiv->livro->estado, noLiv->livro->n_requisicoes);
            noLiv=noLiv->seg;//passa para o seguinte
        }
        noHash = noHash->seg;//passa apra o seguinte
    }
    fclose(ficheiro);//fecha o ficheiro
}

void lerFicheiroLivros(HASHING_LIVRO* hashingLiv) //le o ficheiro livros .txt
{
	if (!hashingLiv) { return; }

	FILE* ficheiro;

	if (!(ficheiro = fopen("livros.txt", "r"))) //verifica o ficheiro
    {
		printf("\nNao foi possivel abrir ficheiro livros.txt.");
		return;//sai
	}
	char line[1000];
	char livro[4][1000];

	while (fgets(line, 1000, ficheiro))//enquanto a linha tiver dados
	{
		char* aux = strtok(line, "\t");
		int i,isbn,ano, n_requisicoes_area, n_requisicoes_livro, estado;

		for (i = 0; aux; i++)//percorre dado a dado da linha
		{
			if (i == 0) // se estiver a ler os dados da primeira coluna (ISBN)
			{
				isbn = atoi(aux);
			}
			else if (i == 3) // se estiver a ler os dados da quarta coluna (Titulo)
			{
				strcpy(livro[0], aux);
			}
			else if (i == 4) // se estiver a ler os dados da quinta coluna (Fornecedor)
			{
				strcpy(livro[1], aux);
			}
			else if (i == 1) // se estiver a ler os dados da segunda coluna (Area)
			{
				strcpy(livro[2], aux);
			}
			else if (i == 5) // se estiver a ler os dados da sexta coluna (ano)
			{
				ano = atoi(aux);
			}
			else if (i == 2) // se estiver a ler os dados da terceira coluna (n_requisicoes_area)
            {
                n_requisicoes_area = atoi(aux);
            }
            else if (i == 6) // se estiver a ler os dados da setima coluna (estado)
            {
                estado = atoi(aux);
            }
            else if (i == 7) // se estiver a ler os dados da oitava coluna (n_requisicoes livro)
            {
                n_requisicoes_livro = atoi(aux);
            }

			aux = strtok(NULL, "\t");//passa para a seguinte coluna da linha
		}

		//adiciona livro ao hashing com os dados recebidos da linha
		adicionarLivroHashing(hashingLiv, criarLivroPreenchido(hashingLiv, isbn, livro[0], livro[1], livro[2], ano, estado, n_requisicoes_livro), 1, n_requisicoes_area);
		memset(livro, 0, sizeof(livro));//liberta a memoria ocupada pelo array
	}
	fclose(ficheiro);//fecha o ficheiro
}

void apresentarLivro(LIVRO* livro) //apresenta todos os detalhes do livro
{
    printf("\nOs detalhes do livro sao: ");
    printf("\nISBN: %d", livro->ISBN);
    printf("\nTitulo: %s", livro->titulo);
    printf("\nArea: %s", livro->area);
    printf("\nFornecedor: %s", livro->fornecedor);
    printf("\nAno: %d", livro->ano);
    if(livro->estado == 0) //se estiver livre || 0 - livre | 1 - requisitado
    {
        printf("\nEstado: Livre");
    }else
    {
        printf("\nEstado: Ocupado");
    }
    printf("\nQuantidade de requisicoes: %d", livro->n_requisicoes);
}

void preencherLivro(HASHING_LIVRO* hashingLiv) //apresenta um pequeno form para o utilizador preencher os dados do livro e adiciona-o ao ahshing
{
    int ISBN, ano;
    char area[20], titulo[100], fornecedor[50];
    printf("\nInsira os detalhes do novo livro \nISBN: ");
    scanf("%d", &ISBN);
    printf("\nTitulo: ");
    char temp;
    scanf("%c",&temp);
    scanf("%[^\n]", titulo);
    printf("\nÁrea: ");
    scanf("%s", area);
    printf("\nFornecedor: ");
    scanf("%c",&temp);
    scanf("%[^\n]", fornecedor);
    printf("\nAno: ");
    scanf("%d", &ano);
    LIVRO* livro = criarLivroPreenchido(hashingLiv, ISBN, titulo, fornecedor, area, ano, 0, 0); //cria o livro preenchido
    if(!livro)//verifica o livro
    {
        printf("\nOcorreu um erro ao criar o livro!");
    }
    adicionarLivroHashing(hashingLiv, livro, 0, 0); //adiciona-o ao hashing
    apresentarLivro(livro);//apresenta-o para o utilizador verificar os dados
}

void apresentarLivrosPorArea(HASHING_LIVRO* hashingLiv)
{
    if(!hashingLiv || !hashingLiv->inicio)//verifica o hashing
    {
        return;//sai
    }
    NO_HASHING_LIVRO *noHashing = hashingLiv->inicio;
    while(noHashing)//percorre o hashing
    {
        printf("\n-----------------------> Area: %s <-----------------------\n",noHashing->area);
        NO_LIVRO *noLiv = noHashing->listaLiv->inicio;
        while(noLiv)//percorre todos os livros
        {
            printf("\n");
            apresentarLivro(noLiv->livro);//apresenta os detalhes do livro
            noLiv = noLiv->seg;//passa para o seguinte
        }
        noHashing = noHashing->seg;//passa para o seguinte
    }
 }

LIVRO* pesquisarLivroPorISBN(HASHING_LIVRO *hashingLiv, int ISBN) //pesquisa o livro pelo ISBN e retorna-o
{
    NO_HASHING_LIVRO *noHashing = hashingLiv->inicio;
    while(noHashing)//percorre o hashing
    {
        NO_LIVRO *noLiv = noHashing->listaLiv->inicio;
        while(noLiv)//percorre todos os livros
        {
            if(noLiv->livro->ISBN == ISBN)//se o ISBN for igual
            {
                return noLiv->livro;//retorna o livro
            }
            noLiv = noLiv->seg;//passa para o seguinte
        }
        noHashing = noHashing->seg;//passa para o seguinte
    }
    return NULL;//livro nao foi encontrado entao retorna null
}

void determinarAreaComMaisLivros(HASHING_LIVRO* hashingLiv)
{

    if(!hashingLiv || !hashingLiv->inicio)//verifica o hashing
    {
        return;//sai
    }

    NO_HASHING_LIVRO *noHashing = hashingLiv->inicio;
    int aux = 0, maior = 0, n = 0;
    char areaMaior[20];
    while(noHashing)//percorre o hashing
    {
        NO_LIVRO *noLiv = noHashing->listaLiv->inicio;
        n = 0;
        while(noLiv)//percorre todos os livros
        {
            n++;//incremente o livro de numeros
            noLiv = noLiv->seg;//passa para o seguinte
        }
        if (n>maior)//se o n for maior que maior
        {//significa que a area atual tem mais livros
            maior = n;// maior passa a ser o n
            strcpy(areaMaior, noHashing->area); // guarda o nome da area
        }
        noHashing = noHashing->seg;//passa para a area seguinte
    }
    //apresenta a area maior e o numero de livros dessa area
    printf("\nA area com mais livros e a %s com o total de %d livros.", areaMaior, maior);
}

void apresentarLivrosMaisRecentes(HASHING_LIVRO* hashingLiv)
{
    if(!hashingLiv || !hashingLiv->inicio)//verifica o ahshing
    {
        return;//sai
    }

    NO_HASHING_LIVRO *noHashing = hashingLiv->inicio;
    int aux = 0, anoMaior=0;
    while(noHashing)//percorre o hashing
    {
        NO_LIVRO *noLiv = noHashing->listaLiv->inicio;
        while(noLiv)//precorre todos os livros
        {
            if (noLiv->livro->ano>anoMaior)//se o ano for maior do que o maior
            {
                anoMaior = noLiv->livro->ano;//passa a ser o anoMaior
            }
            noLiv = noLiv->seg;//passa para o seguinte
        }
        noHashing = noHashing->seg;//passa apra o seguinte
    }
    noHashing = hashingLiv->inicio;//coloca o noHashing a apontar para o inicio para voltar a percorrer o hashing
    while(noHashing)//percorre o hashing para verificar se ha varios livros com o mesmo ano maior
    {
        NO_LIVRO *noLiv = noHashing->listaLiv->inicio;
        while(noLiv)//percorre todos os livros
        {
            if(noLiv->livro->ano == anoMaior) //se o ano for igual ao ano maior
            {
                printf("\n");
                apresentarLivro(noLiv->livro);//apresenta o livro
            }
            noLiv = noLiv->seg;//passa ao seguinte
        }
        noHashing = noHashing->seg;//passa ao seguinte
    }
 }

void apresentarLivroMaisRequisitado(HASHING_LIVRO* hashingLiv)
{
    if(!hashingLiv || !hashingLiv->inicio)//verifica o hashing
    {
        return;//sai
    }

    NO_HASHING_LIVRO *noHashing = hashingLiv->inicio;
    int aux = 0, n_requisicoesMaior = 0;
    while(noHashing)//percorre o ahshing
    {
        NO_LIVRO *noLiv = noHashing->listaLiv->inicio;
        while(noLiv)//percorre todos os livros
        {
            if (noLiv->livro->n_requisicoes>n_requisicoesMaior)//se o livro tiver mais requisicoes que o numero de requisicoes maior
            {
                n_requisicoesMaior = noLiv->livro->n_requisicoes;//entao passa a ser o maior numero de requisicoes
            }
            noLiv = noLiv->seg;//passa apra o seguinte
        }
        noHashing = noHashing->seg;//passa para o seguinte
    }
    noHashing = hashingLiv->inicio;//volta a colocar o noHashing a apontar para o inicio apra voltar a percorrer a lista
    while(noHashing)//percorre o hashing
    {
        NO_LIVRO *noLiv = noHashing->listaLiv->inicio;
        while(noLiv)//percorre todos os livros
        {
            if(noLiv->livro->n_requisicoes == n_requisicoesMaior)//se o numero de requisicoes for igual ao numero de requisicoes maior
            {
                printf("\nO livro com mais requisicoes e:");
                apresentarLivro(noLiv->livro);//apresenta o livro
                printf("Com um total de %d requisicoes.", noLiv->livro->n_requisicoes);
                return;//sai da funcao
            }
            noLiv = noLiv->seg;//passa para o seguinte
        }
        noHashing = noHashing->seg;//passa para o seguinte
    }
 }

void apresentarAreaMaisRequisitada(HASHING_LIVRO* hashingLiv)
{
    if(!hashingLiv || !hashingLiv->inicio)//verifica o hashing
    {
        return;//sai
    }

    NO_HASHING_LIVRO *noHashing = hashingLiv->inicio;
    int aux = 0, n_requisicoesMaior=0;
    while(noHashing)//percorre o hashing
    {
        if(noHashing->n_requisicoes > n_requisicoesMaior)//se o numero de requisicoes for maior do que o maior numero de requisicoes
            {
                n_requisicoesMaior = noHashing->n_requisicoes; //passa a seru o numero de requisicoes maior
            }
        noHashing = noHashing->seg;//passa para o seguinte
    }
    noHashing = hashingLiv->inicio;//aponta o noHashing para o inicio para voltar a percorrer o hashing
    while(noHashing)//percorre o hashing
    {
        NO_LIVRO *noLiv = noHashing->listaLiv->inicio;
        if(noHashing->n_requisicoes == n_requisicoesMaior)//se o numero de reqisicoes for igual ao numero de requisicoes guardado
            {
                //apresenta a area com mais requisicoes e o numero de requisicoes
                printf("A area com mais requisicoes e a %s com o total de %d requisicoes");
                return;//sai
            }
        noHashing = noHashing->seg;//passa para o seguinte
    }
 }

void incrementarNumRequisicoesLivro(HASHING_LIVRO* hashingLiv, LIVRO* livro) //incrementa o numero de requisicoes de um certo livro
{
    NO_HASHING_LIVRO *noHashing = hashingLiv->inicio;
    while(noHashing)//percorre o hashing
    {
        NO_LIVRO *noLiv = noHashing->listaLiv->inicio;
        while(noLiv)//percorre todos os livros
        {
            if(noLiv->livro->ISBN == livro->ISBN)//se o ISBN do livro for igual ao do livro recebido
            {
                noHashing->n_requisicoes++;//incrementa o numero de requisicoes do livro
                noLiv->livro->n_requisicoes++;//incrementa o numero de requisicoes da area
            }
            noLiv = noLiv->seg;//passa para o seguinte
        }
        noHashing = noHashing->seg;//passa apra o seguinte
    }
}

void colocarLivroRequisitado(HASHING_LIVRO* hashingLiv, LIVRO* livro) //coloca o estado do livro em requisitado
{
    NO_HASHING_LIVRO *noHashing = hashingLiv->inicio;
    while(noHashing)//percorre o hashing
    {
        NO_LIVRO *noLiv = noHashing->listaLiv->inicio;
        while(noLiv)//percorre todos os livros
        {
            if(noLiv->livro->ISBN == livro->ISBN)//se o ISBN do livro for igual ao ISBN do livro recebido
            {
                noLiv->livro->estado = 1;//colocar o estado requisitado || 0 - livre | 1 - requisitado
            }
            noLiv = noLiv->seg;//passa para o seguinte
        }
        noHashing = noHashing->seg;//passa para o seguinte
    }
}

LIVRO* livroMaisRequisitado(HASHING_LIVRO* hashingLiv) //devove o livro mais requisitado
{
    if(!hashingLiv || !hashingLiv->inicio)//verifica o hashing
    {
        printf("Hashing sem livros!");
        return NULL;//sai
    }
    LIVRO* livro = criarLivro();
    int maior = 0;
    NO_HASHING_LIVRO *noHashing = hashingLiv->inicio;
    while(noHashing)//percorre o hashing
    {
        NO_LIVRO *noLiv = noHashing->listaLiv->inicio;
        while(noLiv)//percorre todos os livros
        {
            if(noLiv->livro->n_requisicoes>maior)//se o numero de requisicoes do livro for maior do que o maior
            {
                maior = noLiv->livro->n_requisicoes;//passa a ser o maior
                livro = noLiv->livro;//guarda o livro atual
            }
            noLiv = noLiv->seg;//passa para o seguinte
        }
        noHashing = noHashing->seg;//passa para o seguinte
    }
    return livro;//retorna o livro encontrado
}

void areaMaisRequisitada(HASHING_LIVRO* hashingLiv)
{
    if(!hashingLiv || !hashingLiv->inicio)//verifica o hashing
    {
        printf("Hashing sem livros!");
        return;//sai
    }

    int maior = 0;
    char area[20];
    NO_HASHING_LIVRO *noHashing = hashingLiv->inicio;
    while(noHashing)//percorre o hashing
    {
        if(noHashing->n_requisicoes>maior)//se o numero de requisicoes do hashing for maior do que a maior
        {
            maior = noHashing->n_requisicoes;//passa a ser o maior
            strcpy(area, noHashing->area);//guarda o nome da area
        }
        noHashing = noHashing->seg;//passa ao seguinte
    }
    if (maior!=0)//verifica se o foi encontrada alguma area com livros requisitados
    {
        //apresenta a area mais requisitada
        printf("\nA area com mais requisicoes e a %s.", area);
    }
    else
    {
        printf("\nAinda nenhum livro foi requsitado");
    }
}

void colocarLivroDevolvido(HASHING_LIVRO* hashingLiv, LIVRO* livro) //coloca o estado de um livro em livre
{
    NO_HASHING_LIVRO *noHashing = hashingLiv->inicio;
    while(noHashing)//percorre o hashing
    {
        NO_LIVRO *noLiv = noHashing->listaLiv->inicio;
        while(noLiv)//precorre todos os livros
        {
            if(noLiv->livro->ISBN == livro->ISBN)//se o ISBN do livro for igual ao do livro recevido
            {
                noLiv->livro->estado = 0;//coloca o estado em livre || 0 - livre | 1 - requisitado
            }
            noLiv = noLiv->seg;//passa para o seguinte
        }
        noHashing = noHashing->seg;//passa para o seguinte
    }
}

void libertarMemoriaLivros(HASHING_LIVRO* hashingLiv)//nao esta a funcionar
{
    if(!hashingLiv || !hashingLiv->inicio)//verifica o hashing
    {
        return;//sai
    }
    NO_HASHING_LIVRO* noHashingLiv = hashingLiv->inicio, *noHashingLivAux = NULL;
    while(noHashingLiv)
    {
        noHashingLivAux = noHashingLiv->seg;
        libertarMemoriaListaLivros(noHashingLiv->listaLiv);
        free(noHashingLiv);
        noHashingLiv = noHashingLivAux;
    }
    free(hashingLiv);
}

void libertarMemoriaListaLivros(LISTA_LIVROS* listaLiv)//nao esta a funcionar
{
    if(!listaLiv || !listaLiv->inicio)
    {
        return;
    }
    NO_LIVRO* noLiv = listaLiv->inicio, *noLivAux = NULL;
    while(noLiv)
    {
        noLivAux = noLiv->seg;
        free(noLiv->livro);
        free(noLiv);
        noLiv = noLivAux;
    }
    free(listaLiv);
}

#endif
