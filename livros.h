//ESTRUTURAS DOS LIVROS

typedef struct livro //armazena os dados do livro
{
    int ISBN;
    char area[20];
    char titulo[100];
    char fornecedor[50];
    int ano;
    int estado; //0 - livre | 1 - requisitado
    int n_requisicoes;
} LIVRO;

typedef struct no_livro
{
   struct no_livro *ant,*seg;//aponta para o no seguinte e anterior na lista
   LIVRO *livro;//aponta para o livro

} NO_LIVRO;

typedef struct lista_livros //armazena a lista dos livros
{
    NO_LIVRO *inicio;//aponta para o primeiro elemento da lista
    int nel;//guarda o numero de elementos da lista

} LISTA_LIVROS;

//hashing dos livros

typedef struct no_hashing_livro
{
    char area[20];//guarda a area do livro (o hashing e separado por areas)
    LISTA_LIVROS *listaLiv; //aponta para a lista correspondente a a area
    struct no_hashing_livro *ant,*seg; //aponta para o no seguinte e anterior no hashing
    int n_requisicoes; //numero de requisicoes desta area

} NO_HASHING_LIVRO;

typedef struct hashing_livro //armazena o hashing dos livros
{
    NO_HASHING_LIVRO *inicio;//aponta para o primeiro elemento do hashing
    int nel;//guarda o numero de elementos do hashing

} HASHING_LIVRO;
