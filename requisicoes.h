//ESTRUTURAS DAS REQUISICOES
typedef struct requisicao //armazena os dados da requisicao
{
    REQUISITANTE* requisitante; //aponta para o requisitante da requisicao
    LIVRO* livro; //aponta para o livro requisitado
    DATA* dataInicio; //data de Inicio da requisicao
    DATA* dataFim; //data limite da requisicao / data da devolucao
    int estado;//0 - inativa / 1 - ativa /

} REQUISICAO;

typedef struct no_requisicao
{
   struct no_requisicao *ant,*seg; //ponteiros que apontam para o no anterior e o seguinte na lista das requisicoes
   REQUISICAO *requisicao; //aponta para a requisicao

} NO_REQUISICAO;

typedef struct lista_requisicoes //lista das requisicoes de uma determinada data
{
    NO_REQUISICAO *inicio; //aponta para o primeiro elemento (no_requisicao) da lista de requisicoes
    int nel; //numero de elementos da lista de requisicoes

} LISTA_REQUISICOES;

//hashing das requisicoes

typedef struct no_hashing_requisicao
{
    DATA *data; //aponta para a data de inicio da requisicao (o hashing e separado por por data)
    LISTA_LIVROS *listaReq; //aponta para a lista que contem as requisicoes pertencentes a esta data
    struct no_hashing_requisicao *ant,*seg; //aponta para o no anterior e seguinte no hashing

} NO_HASHING_REQUISICAO;

typedef struct hashing_requisicoes //hashing que guarda todas as requisicoes
{
    NO_HASHING_REQUISICAO *inicio; //aponta para o primeiro no do hashing
    int nel; //numero de elementos do hashing

} HASHING_REQUISICOES;

/*Estrutura de requisicoes auxiliar que guarda o numero de requisicoes de cada requisitante*/

typedef struct num_requisicoes //guarda o numero de requisicoes de um determinado requisitante
{
    REQUISITANTE* requisitante; //aponta para um requisitante especifico
    int num; //numero de requisicoes desse requisitante

}NUM_REQUISICOES;

typedef struct no_num_requisicoes
{
    struct no_num_requisicoes* seg; //aponta para o no seguinte na lista
    NUM_REQUISICOES* num_requisicoes; //aponta para a estrutura que guarda o numero de requisicoes de um requisitante

}NO_NUM_REQUISICOES;

typedef struct lista_num_requisicoes //lista que guarda todos os numeros de requisicoes de todos os requisitantes
{
    NO_NUM_REQUISICOES* inicio; //aponta para o primeiro no da lista
    int nel; //numero de elementos da lista

}LISTA_NUM_REQUISICOES;
