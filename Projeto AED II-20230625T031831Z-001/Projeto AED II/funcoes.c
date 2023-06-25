#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

//Fun��o para criar e inicializar as listas LSE de eventos e participantes
int criaListas(LSE_Evento *e)
{
    // Inicializa os ponteiros de inicio e fim da Lista LSE de eventos
    e->inicio = NULL;
    e->fim = NULL;
    e->tam = 0;

    // Inicializa os ponteiros de inicio e fim da Lista LSE de participantes
    e->listaParticipantes.inicio = NULL;
    e->listaParticipantes.fim = NULL;

    return 0;
}

//Fun��o para realizar o cadastro das informa��es dos eventos e participantes
int cadastro(LSE_Evento *e)
{
    //Vari�veis auxiliares
    int nParticipantes;
    char nomeEvento[20], data[11], hora[6];
    char nomeParticipante[40], telefone[16], email[30];

//CADASTRO DO EVENTO
    //Aloca��o din�mica na mem�ria para o evento
    Evento *evento = (Evento *)malloc(sizeof(Evento));

    if (evento == NULL)
        exit(1);

    //Cadastro das informa��es do evento
    printf("\n----------\nCADASTRO DO EVENTO:\n\n");
    printf("NOME DO EVENTO: ");
    scanf("%s", nomeEvento);
    printf("DATA: ");
    scanf("%s", data);
    printf("HORA: ");
    scanf("%s", hora);

    do
    {
        printf("QUANTIDADE DE PARTICIPANTES (Max.: 4): ");
        scanf("%d", &nParticipantes);

        if(nParticipantes < 1 || nParticipantes > 4)
            printf("\nQuantidade de participantes invalida!\n");

        else
            evento->nParticipantes = nParticipantes;
    }
    while(nParticipantes < 1 || nParticipantes > 4);

    //Registrando as informa��es inseridas no n� evento
    evento->idEvento = rand() % 100; //Fun��o para gerar um n�mero aleat�rio como ID do evento
    strcpy(evento->nomeEvento, nomeEvento);
    strcpy(evento->data, data);
    strcpy(evento->hora, hora);

//CADASTRO DOS PARTICIPANTES
    //Aloca��o din�mica na mem�ria para o participante
    Participante *participante = malloc(nParticipantes * sizeof(Participante));

    if(participante == NULL)
        exit(1);

    //Cadastro das informa��es do evento
    printf("\n-----\nPARTICIPANTES:");
    for(int i = 0; i < nParticipantes; i++)
    {
        printf("\n\nNOME DO PARTICIPANTE: ");
        scanf("%s", nomeParticipante);
        printf("TELEFONE: ");
        scanf("%s", telefone);
        printf("E-MAIL: ");
        scanf("%s", email);

        //Registrando as informa��es inseridas no n� participante
        strcpy(evento->participantes[i].nomeParticipante, nomeParticipante);
        strcpy(evento->participantes[i].telefone, telefone);
        strcpy(evento->participantes[i].email, email);
    }

    //Chamando a fun��o para inserir os n�s nas listas e no arquivo
    insereEArquiva(e, evento);

    return 0;
}

//Fun��o para inserir e arquivar um evento na lista
int insereEArquiva(LSE_Evento *e, Evento *evento)
{
    /*Como a aloca��o din�mica de mem�ria do evento e dos participantes �
     feita na fun��o de cadastro, esta fun��o ir� apenas inserir os n�s nas
     listas e copi�-los no arquivo.*/

    //Abertura do arquivo em modo append
    FILE *arquivo = fopen("arquivo.txt", "a");

    if (arquivo == NULL)
        exit(1);

//INSER��O DO EVENTO NA LISTA
    //Caso 1 - Primeiro elemento da lista
    if(e->inicio == NULL)
    {
        e->inicio = evento; //In�cio da lista recebe o n� evento
        e->fim = evento; //Fim da lista recebe o n� evento
        evento->prox = NULL; //Ponteiro *prox do n� evento aponta para NULL
    }

    //Caso 2- A partir do segundo elemento o n� evento � inserido no fim
    else
    {
        e->fim->prox = evento; //Ponteiro *prox do n� que est� no fim da lista aponta para o n� evento
        e->fim = evento; //Fim da lista recebe o n� evento
        evento->prox = NULL; //Ponteiro *prox do n� evento aponta para NULL
    }

    //Inser��o das informa��es cadastradas do evento no arquivo de maneira formatada
    fprintf(arquivo, "\n\n----------\nID: %d\n", evento->idEvento);
    fprintf(arquivo, "EVENTO: %s\n", evento->nomeEvento);
    fprintf(arquivo, "DATA: %s\n", evento->data);
    fprintf(arquivo, "HORA: %s", evento->hora);


//INSER��O DOS PARTICIPANTES NA LISTA
    //Loop para repetir a inser��o de participante na lista conforme o desejo do usu�rio
    for(int i = 0; i < evento->nParticipantes; i++)
    {
        //Caso 1 - Primeiro elemento da lista
        if(e->listaParticipantes.inicio == NULL)
        {
            e->listaParticipantes.inicio = &evento->participantes[i]; //In�cio da lista recebe o n� participante
            e->listaParticipantes.fim = &evento->participantes[i]; //Fim da lista recebe o n� participante
            evento->participantes[i].prox = NULL; //Ponteiro *prox do n� participante aponta para NULL
        }

        //Caso 2- A partir do segundo elemento insere no fim
        else
        {
            e->listaParticipantes.fim->prox = &evento->participantes[i]; //Ponteiro *prox do n� que est� no fim da lista aponta para o n� participante
            e->listaParticipantes.fim = &evento->participantes[i]; //Fim da lista recebe o n� participante
            evento->participantes[i].prox = NULL; //Ponteiro *prox do n� participante aponta para NULL
        }

        //Inser��o das informa��es cadastradas do participante no arquivo de maneira formatada
        fprintf(arquivo, "\n\nPARTICIPANTE: %s\n", evento->participantes[i].nomeParticipante);
        fprintf(arquivo, "TELEFONE: %s\n", evento->participantes[i].telefone);
        fprintf(arquivo, "E-MAIL: %s\n", evento->participantes[i].email);
    }

    //Fecha o arquivo
    fclose(arquivo);

    return 0;
}

//Fun��o para imprimir os cadastros arquivados
int imprimeCadastros(LSE_Evento *e)
{
    //Abertura do arquivo em modo leitura
    FILE *arquivo = fopen("arquivo.txt", "r");

    if (arquivo == NULL)
        exit(1);

    //Vari�vel auxiliar para ler as linhas do arquivo
    char linha[100];

    //Impress�o do arquivo
    printf("\n----------\nLISTA DE CADASTROS:\n");

    //Se a lista LSE de eventos e o arquivo estiverem vazios, a lista de cadastros est� vazia
    if (e->inicio == NULL && fgets(linha, sizeof(linha), arquivo) == NULL)
    {
        printf("\nA lista de cadastros esta vazia!\n");
        return 1;
    }

    //Loop para ler e imprimir as linhas do arquivo
    while (fgets(linha, sizeof(linha), arquivo) != NULL)
        printf("%s", linha);

    //Fecha o arquivo
    fclose(arquivo);

    return 0;
}

//Fun��o para remover e desarquivar um evento e seus participantes
int removeEDesarquivaCadastro(LSE_Evento *e, char nomeEvento[20], int idEvento)
{
    //Abertura do arquivo original em modo leitura
    FILE *arquivoOriginal = fopen("arquivo.txt", "r");

    //Abertura de um arquivo temporario em modo escrita
    FILE *arquivoTemporario = fopen("temporario.txt", "w");

    if (arquivoOriginal == NULL || arquivoTemporario == NULL)
    {
        fclose(arquivoOriginal);
        exit(1);
    }

    //Vari�veis auxiliares
    Evento *atual = e->inicio; //Vari�vel para percorrer a lista de eventos
    char linha[100]; //Vari�vel para ler as linhas do evento
    int encontrado = 0; //Vari�vel para monitorar se o evento a ser removido foi encontrado
    int n = 0;

    //Loop para percorrer a lista de eventos e procurar o ID e nome do evento que ser� removido na MEM�RIA
    while (atual != NULL)
    {
        //Se encontrar o evento que deve ser removido
        if (strcmp(atual->nomeEvento, nomeEvento) == 0 && atual->idEvento == idEvento)
        {
            //Remove participantes associados ao evento da mem�ria
            for (int i = 0; i < atual->nParticipantes; i++)
                free(atual->participantes[i].prox);

            //Remove evento da mem�ria
            //Caso 1 - Remo��o do primeiro elemento da lista
            if (atual == e->inicio)
                e->inicio = atual->prox; //In�cio da lista recebe o *prox do n� evento

            //Caso 2 - Remo��o do �ltimo elemento da lista
            if (atual == e->fim)
            {
                Evento *penultimo = e->inicio; //Vari�vel auxiliar para guardar o penultimo n� da lista
                //Enquanto n�o chegar no fim da lista a vari�vel continua percorrendo
                while (penultimo->prox != NULL)
                    penultimo = penultimo->prox;

                //Quando chegar no fim da lista
                penultimo->prox = NULL; //Ponteiro *prox do pen�ltimo n� aponta para NULL
                e->fim = penultimo; //Fim da lista aponta para o pen�ltimo n�
            }

            //Caso 3 - Remo��o de um elemento no meio da lista
            if(atual != e->inicio && atual != e->fim)
            {
                Evento *anteriorMeio = e->inicio; //Vari�vel auxiliar para guardar o anterior do n� que ser� removido

                //Enquanto n�o chegar no fim da lista a vari�vel continua percorrendo
                while (anteriorMeio->prox != e->fim)
                {
                    anteriorMeio = anteriorMeio->prox;

                    if(anteriorMeio == atual)
                        anteriorMeio->prox = atual->prox;

                }
            }

            free(atual);
            encontrado = 1;
            printf("\nCadastro removido com sucesso!\n");
        }

        //Se n�o encontrar o evento que deve ser removido, copia o cadastro para o arquivo tempor�rio
        else
        {
            //Escreve evento no arquivo tempor�rio
            fprintf(arquivoTemporario, "EVENTO: %s\n", atual->nomeEvento);
            fprintf(arquivoTemporario, "ID: %d\n", atual->idEvento);
            fprintf(arquivoTemporario, "Data: %s\n", atual->data);
            fprintf(arquivoTemporario, "Hora: %s\n", atual->hora);
            fprintf(arquivoTemporario, "N� Participantes: %d\n", atual->nParticipantes);

            //Escreve participantes no arquivo tempor�rio
            for (int i = 0; i < atual->nParticipantes; i++)
            {
                fprintf(arquivoTemporario, "PARTICIPANTE %d:\n", i + 1);
                fprintf(arquivoTemporario, "Nome: %s\n", atual->participantes[i].nomeParticipante);
                fprintf(arquivoTemporario, "Telefone: %s\n", atual->participantes[i].telefone);
                fprintf(arquivoTemporario, "Email: %s\n", atual->participantes[i].email);
            }
            n++;
        }
        atual = atual->prox;
    }

    //Se o evento n�o for encontrado na mem�ria, pesquisa no arquivo original
    if(encontrado == 0)
    {
        char eventoBuscado[100]; //Vari�vel para ler as linhas do arquivo

        //Enquanto o arquivo n�o chegar ao fim
        while (fgets(linha, sizeof(linha), arquivoOriginal) != NULL)
        {
            //Se o evento for encontrado
            if (strcmp(linha, eventoBuscado) == 0)
                encontrado = 1;
            printf("Evento removido com sucesso do arquivo!\n");
            return 0;
        }
    }

//Se o evento n�o for encontrado na mem�ria e nem no arquivo
    if (encontrado == 0)
    {
        printf("\nCadastro n�o encontrado!\n");
        remove("temporario.txt");
        return 1;
    }

//Se foi encontrado ou na mem�ria ou no arquivo
    else
    {
        //Fechando os arquivos abertos
        fclose(arquivoOriginal);
        fclose(arquivoTemporario);

        //Renomeia arquivo tempor�rio para substituir o arquivo original
        rename("temporario.txt", "arquivo.txt");
        remove("temporario.txt");

        printf("Evento removido com sucesso do arquivo!\n");

        return 0;
    }
}
