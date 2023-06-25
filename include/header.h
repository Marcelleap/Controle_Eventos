#ifndef HEADER_H
#define HEADER_H

typedef struct participante
{
    char nomeParticipante[40];
    char telefone[16];
    char email[30];
    struct participante *prox;
} Participante;

typedef struct
{
    Participante *inicio;
    Participante *fim;
} LSE_Participante;

typedef struct evento
{
    int idEvento;
    char nomeEvento[20];
    char data[11];
    char hora[6];
    Participante *participantes[4];
    int nParticipantes;
    struct evento *prox;
} Evento;

typedef struct
{
    Evento *inicio;
    Evento *fim;
    LSE_Participante *listaParticipantes;
} LSE_Evento;

void criaListas(LSE_Evento *e);
void cadastro(LSE_Evento *e);
void insereEArquiva(LSE_Evento *e, Evento *evento, int nParticipantes);
int imprimeCadastros(LSE_Evento *e);
int imprimeConsulta(LSE_Evento *e);
Evento *pesquisaEvento(LSE_Evento *e, char nomeEvento[20], int idEvento);
void removeEDesarquivaCadastro(LSE_Evento *e, Evento *evento);
int i;

#endif

