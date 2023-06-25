//PROJETO DE ALGORITMO E ESTRUTURA DE DADOS II - 2023/1//
//DUPLA: Hadassa ALves de Gouvea

//Escopo do projeto: Gerenciador evento/participantes que
//opera as funcionalidades CRUD (Criar, Ler, Alterar e Remover).

//Recursos da disciplina utilizados:Ponteiros, Fun��es, Lista (LSE) e Arquivo.

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
    char nomeEvento[20], nomeParticipante[40];

//CADASTRO DO EVENTO
    //Aloca��o din�mica na mem�ria para o evento
    Evento *evento = (Evento *)malloc(sizeof(Evento));

    if (evento == NULL)
        exit(1);

    //Cadastro do nome do evento
    printf("\n----------\nCADASTRO DO EVENTO:\n");
    printf("\nNOME DO EVENTO: ");
    scanf("%s", nomeEvento);

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

    //Registrando as informa��es n� evento
    strcpy(evento->nomeEvento, nomeEvento);

//CADASTRO DOS PARTICIPANTES
    //Aloca��o din�mica na mem�ria para o participante
    Participante *participante = malloc(nParticipantes * sizeof(Participante));

    if(participante == NULL)
        exit(1);

    //Cadastro das informa��es do evento
    printf("\nPARTICIPANTES:");
    for(int i = 0; i < nParticipantes; i++)
    {
        printf("\nNOME DO PARTICIPANTE: ");
        scanf("%s", nomeParticipante);

        //Registrando as informa��es inseridas no n� participante
        strcpy(evento->participantes[i].nomeParticipante, nomeParticipante);
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
    fprintf(arquivo, "\n\n\nEVENTO: %s\n", evento->nomeEvento);

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
        fprintf(arquivo, "\nPARTICIPANTE: %s", evento->participantes[i].nomeParticipante);
    }

    //Fecha o arquivo
    fclose(arquivo);

    printf("\nCadastro realizado!\n");
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
    printf("\n\nLISTA DE CADASTROS:");

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

//Fun��o para pesquisar e retornar um evento na MEMORIA
Evento *pesquisaEvento(LSE_Evento *e, char nome[20])
{
    //Vari�vel auxiliar para percorrer a lista de eventos
    Evento *atual = e->inicio;

    //Loop para percorrer at� o fim
    while(atual != NULL)
    {
        //Se o nome do n� atual foi igual ao nome do evento procurado, retorna atual
        if(strcmp(atual->nomeEvento, nome) == 0)
            return atual;

        atual = atual->prox;
    }

    atual = NULL;
    return atual;
}

// Fun��o para alterar um evento e seus participantes no ARQUIVO
int alteraCadastro(char nomeEvento[20], char novoNomeEvento[20])
{
    // Abertura do arquivo original em modo leitura
    FILE *arquivoOriginal = fopen("arquivo.txt", "r");

    // Abertura de um arquivo temporario em modo escrita
    FILE *arquivoTemporario = fopen("temporario.txt", "w");

    if (arquivoOriginal == NULL || arquivoTemporario == NULL)
    {
        fclose(arquivoOriginal);
        exit(1);
    }

    char linha[100];

    // Loop para ler o arquivo
    while (fgets(linha, sizeof(linha), arquivoOriginal) != NULL)
    {
        // Verifica se a linha come�a com "EVENTO: "
        if (strstr(linha, "EVENTO: ") == linha)
        {
            // Substitui o nome do evento na linha pelo novo nome
            fprintf(arquivoTemporario, "EVENTO: %s\n", novoNomeEvento);
        }
        else
        {
            // Copia a linha original para o arquivo temporario
            fputs(linha, arquivoTemporario);
        }
    }

    // Fecha os arquivos
    fclose(arquivoOriginal);
    fclose(arquivoTemporario);

    // Remove o arquivo original
    remove("arquivo.txt");

    // Renomeia o arquivo temporario para o nome original
    rename("temporario.txt", "arquivo.txt");

    printf("\nCadastro alterado!\n");
    return 0;
}

//Fun��o para remover um evento inteiro NO ARQUIVO
int removeCadastro(char nome[20])
{
    // Abertura do arquivo original em modo leitura
    FILE *arquivoOriginal = fopen("arquivo.txt", "r");

    // Abertura de um arquivo temporario em modo escrita
    FILE *arquivoTemporario = fopen("temporario.txt", "w");

    if (arquivoOriginal == NULL || arquivoTemporario == NULL)
    {
        fclose(arquivoOriginal);
        exit(1);
    }

    //Vari�vel auxiliar para ler as linhas do arquivo
    char linha[100];

    //Loop para ler o arquivo
    while (fgets(linha, sizeof(linha), arquivoOriginal) != NULL)
    {

        //Verifica se a linha cont�m o nome do evento/participante a ser removido
        if (strstr(linha, nome) == NULL)
        {
            //Copiar a linha original para o arquivo temporario
            fprintf(arquivoTemporario, "%s", linha);
        }
    }

    // Fechar os arquivos
    fclose(arquivoOriginal);
    fclose(arquivoTemporario);

    // Remover o arquivo original
    remove("arquivo.txt");

    // Renomear o arquivo temporario para o nome original
    rename("temporario.txt", "arquivo.txt");

    printf("Remocao realizada!\n");

    return 0;
}

//Fun��o para desalocar um cadastro de evento e participantes da MEM�RIA
int desalocaCadastro(LSE_Evento *e, Evento *evento)
{
//Vari�vel para percorrer a lista de eventos
    Evento *atual = e->inicio;

//Loop para percorrer a lista de eventos at� o fim
    while (atual != NULL)
    {
        //Se encontrar o evento que deve ser removido
        if (strcmp(atual->nomeEvento, evento->nomeEvento) == 0)
        {
            //Remove todos os participantes alocados dentro do evento da mem�ria
            for (int i = 0; i < atual->nParticipantes; i++)
                free(&atual->participantes[i]);

            //Remove evento da mem�ria
            //Caso 1 - Remo��o do primeiro elemento da lista
            if (atual == e->inicio)
                e->inicio = atual->prox; //In�cio da lista recebe o *prox do n� evento

            //Caso 2 - Remo��o do �ltimo elemento da lista
            if (atual == e->fim)
            {
                //Vari�vel auxiliar para guardar o penultimo n� da lista
                Evento *penultimo = e->inicio;

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
                //Vari�vel auxiliar para guardar o anterior do n� que ser� removido
                Evento *anteriorMeio = e->inicio;

                //Enquanto n�o chegar no fim da lista a vari�vel continua percorrendo
                while(anteriorMeio->prox != atual)
                    anteriorMeio = anteriorMeio->prox;

                //Se encontrar o n� anterior ao n� que deve ser removido, "costura" a lista
                if(anteriorMeio->prox == atual)
                    anteriorMeio->prox = atual->prox;
            }

            free(atual);
            printf("\nCadastro desalocado da memoria com sucesso!\n");
        }
    }

    return 0;
}
