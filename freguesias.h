//ESTRUTURAS DAS FREGUESIAS
typedef struct freguesia //armazena os dados da freguesia
{
    char nome[100]; //guarda o nome da freguesia
    char id_freguesia[6]; //guarda o id da freguesia
} FREGUESIA;

typedef struct no_freguesia
{
    struct no_freguesia *seg; //aponta para o no seguinte
    FREGUESIA *freguesia; //aponta para a respetiva freguesia
} NO_FREGUESIA;

typedef struct lista_freguesias //lista das freguesias
{
    NO_FREGUESIA *inicio; //aponta para o primeiro elemento (no_freguesia) da lista das freguesias
    int nel; //guarda o numero de elementos da lista
} LISTA_FREGUESIAS;
