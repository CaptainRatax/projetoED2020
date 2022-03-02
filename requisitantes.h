//ESTRUTURAS DOS REQUISITANTES
typedef struct requisitante //armazena os dados do requisitante
{
    char id_requisitante[9];//guarda o id do requitante
    int dia;//guarda o dia da data de nascimento
    char nome[50];//guarda o nome do requisitante
    int mes;//guarda o mes da data de nascimento
    int ano;//guarda o ano da data de nascimento
    char id_freguesia[6];//guarda o id da freguesia
    int n_requisicoes;//guarda o n_requisicoes do requisitante

} REQUISITANTE;

typedef struct no_requisitante //armazena o no do requisitante
{
    struct no_requisitante *seg, *ant;//aponta para no seguinte e anterior na lista
    REQUISITANTE *requisitante;//aponta para o requisitante

} NO_REQUISITANTE;

typedef struct lista_requisitantes //armazena a lista dos requisitantes
{
    NO_REQUISITANTE *inicio;// aponta para o primeiro elemento da lista dos requisitantes
    int nel;//guarda o numero de elementos da lista dos requisitantes
    int ultimoIdRequisitante;//guarda o ultimo Id do requisitante

} LISTA_REQUISITANTES;
