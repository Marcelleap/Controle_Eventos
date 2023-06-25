//HADASSA E MARCELLE 

#ifndef HEADER_H
#define HEADER_H

//Nó para participantes
typedef struct participante
{
    char nomeParticipante[40];
    char telefone[16];
    char email[30];
    struct participante *prox;
} Participante;

//Lista LSE para participantes
typedef struct
{
    Participante *inicio;
    Participante *fim;
} LSE_Participante;

//Nó para eventos que inclui 4 disponíveis para armazenar nós para participantes
typedef struct evento
{
    int idEvento;
    char nomeEvento[20];
    char data[11];
    char hora[6];
    Participante participantes[4];
    int nParticipantes;
    struct evento *prox;
} Evento;

//Lista LSE para eventos que inclui uma lista LSE para participantes
typedef struct
{
    Evento *inicio;
    Evento *fim;
    int tam;
    LSE_Participante listaParticipantes;
} LSE_Evento;

//Função para criar e inicializar as listas LSE de eventos e participantes
int criaListas(LSE_Evento *e);
//Função para realizar o cadastro das informações dos eventos e participantes
int cadastro(LSE_Evento *e);
//Função para inserir e arquivar um evento na lista
int insereEArquiva(LSE_Evento *e, Evento *evento);
//Função para imprimir os cadastros arquivados
int imprimeCadastros(LSE_Evento *e);
//Função para remover e desarquivar um evento e seus participantes
int removeEDesarquivaCadastro(LSE_Evento *e, char nomeEvento[20], int idEvento);
int i;

#endif
