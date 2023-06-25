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
} CSE_Participante;

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
    CSE_Participante *listaParticipantes;
} CSE_Evento;

void criaListas(CSE_Evento *e);
void cadastro(CSE_Evento *e);
void insereEArquiva(CSE_Evento *e, Evento *evento, int nParticipantes);
int imprimeCadastros(CSE_Evento *e);
Evento *pesquisaEvento(CSE_Evento *e, char nomeEvento[20], int idEvento);
void removeEDesarquivaCadastro(CSE_Evento *e, Evento *evento);

#endif
