#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


void clearscr(void)
{
    printf("\033c");
    printf("\033[H\033[J");
    return;
}

void criaListas(CSE_Evento *e)
{
    e->inicio = NULL;
    e->fim = NULL;

    e->listaParticipantes = (CSE_Participante *)malloc(sizeof(CSE_Participante));

    if (e->listaParticipantes == NULL)
        exit(1);

    e->listaParticipantes->inicio = NULL;
    e->listaParticipantes->fim = NULL;
}

void cadastro(CSE_Evento *e)
{
    int nParticipantes;
    char nomeEvento[20], data[11], hora[6];
    char nomeParticipante[40], telefone[16], email[30];

    printf("\nInsira os dados do evento:\n");
    printf("Nome do evento: ");
    scanf("%s", nomeEvento);
    printf("Data (dd/mm/aaaa): ");
    scanf("%s", data);
    printf("Hora (hh:mm): ");
    scanf("%s", hora);
    printf("Numero de participantes (max. 4): ");
    scanf("%d", &nParticipantes);

    Evento *evento = (Evento *)malloc(sizeof(Evento));

    if (evento == NULL)
        exit(1);

    evento->idEvento = rand() % 1000 + 1;
    strcpy(evento->nomeEvento, nomeEvento);
    strcpy(evento->data, data);
    strcpy(evento->hora, hora);
    evento->nParticipantes = nParticipantes;

    for (int i = 0; i < nParticipantes; i++)
    {
        printf("\nInsira os dados do participante %d:\n", i + 1);
        printf("Nome: ");
        scanf("%s", nomeParticipante);
        printf("Telefone: ");
        scanf("%s", telefone);
        printf("Email: ");
        scanf("%s", email);

        Participante *participante = (Participante *)malloc(sizeof(Participante));

        if (participante == NULL)
            exit(1);

        strcpy(participante->nomeParticipante, nomeParticipante);
        strcpy(participante->telefone, telefone);
        strcpy(participante->email, email);

        evento->participantes[i] = participante;
    }

    evento->prox = NULL;

    insereEArquiva(e, evento, nParticipantes);
}

void insereEArquiva(CSE_Evento *e, Evento *evento, int nParticipantes)
{
    if (e->inicio == NULL)
    {
        e->inicio = evento;
        e->fim = evento;
    }
    else
    {
        e->fim->prox = evento;
        e->fim = evento;
    }

    for (int i = 0; i < nParticipantes; i++)
    {
        if (e->listaParticipantes->inicio == NULL)
        {
            e->listaParticipantes->inicio = evento->participantes[i];
            e->listaParticipantes->fim = evento->participantes[i];
        }
        else
        {
            e->listaParticipantes->fim->prox = evento->participantes[i];
            e->listaParticipantes->fim = evento->participantes[i];
        }
    }
}

int imprimeCadastros(CSE_Evento *e)
{
    if (e->inicio == NULL)
    {
        printf("\nNenhum evento cadastrado.\n");
        return 0;
    }

    Evento *atual = e->inicio;
    int count = 1;

    printf("\nEVENTOS CADASTRADOS:\n");

    while (atual != NULL)
    {
        printf("\nEvento %d:\n", count);
        printf("ID: %d\n", atual->idEvento);
        printf("Nome: %s\n", atual->nomeEvento);
        printf("Data: %s\n", atual->data);
        printf("Hora: %s\n", atual->hora);

        printf("\nParticipantes:\n");

        for (int i = 0; i < atual->nParticipantes; i++)
        {
            printf("Participante %d:\n", i + 1);
            printf("Nome: %s\n", atual->participantes[i]->nomeParticipante);
            printf("Telefone: %s\n", atual->participantes[i]->telefone);
            printf("Email: %s\n", atual->participantes[i]->email);
        }

        atual = atual->prox;
        count++;
    }

    return count - 1;
}

Evento *pesquisaEvento(CSE_Evento *e, char nomeEvento[20], int idEvento)
{
    if (e->inicio == NULL)
    {
        printf("\nNenhum evento cadastrado.\n");
        return NULL;
    }

    Evento *atual = e->inicio;

    while (atual != NULL)
    {
        if (strcmp(atual->nomeEvento, nomeEvento) == 0 && atual->idEvento == idEvento)
            return atual;

        atual = atual->prox;
    }

    printf("\nEvento nao encontrado.\n");
    return NULL;
}

void removeEDesarquivaCadastro(CSE_Evento *e, Evento *evento)
{
    int i;
    if (evento == NULL)
        return;

    Evento *atual = e->inicio;
    Evento *anterior = NULL;

    while (atual != NULL)
    {
        if (atual == evento)
        {
            if (anterior == NULL)
                e->inicio = atual->prox;
            else
                anterior->prox = atual->prox;

            free(atual);
            break;
        }

        anterior = atual;
        atual = atual->prox;
    }

    Participante *participanteAtual = e->listaParticipantes->inicio;
    Participante *participanteAnterior = NULL;

    while (participanteAtual != NULL)
    {
        if (participanteAtual == evento->participantes[i])
        {
            if (participanteAnterior == NULL)
                e->listaParticipantes->inicio = participanteAtual->prox;
            else
                participanteAnterior->prox = participanteAtual->prox;

            free(participanteAtual);
            break;
        }

        participanteAnterior = participanteAtual;
        participanteAtual = participanteAtual->prox;
    }
}
