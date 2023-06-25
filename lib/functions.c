//HADASSA E MARCELLE 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

//Função para criar e inicializar as listas LSE de eventos e participantes
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

//Função para realizar o cadastro das informações dos eventos e participantes
int cadastro(LSE_Evento *e)
{
    //Variáveis auxiliares
    int nParticipantes;
    char nomeEvento[20], data[11], hora[6];
    char nomeParticipante[40], telefone[16], email[30];

//CADASTRO DO EVENTO
    //Alocação dinâmica na memória para o evento
    Evento *evento = (Evento *)malloc(sizeof(Evento));

    if (evento == NULL)
        exit(1);

    //Cadastro das informações do evento
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

    //Registrando as informações inseridas no nó evento
    evento->idEvento = rand() % 100; //Função para gerar um número aleatório como ID do evento
    strcpy(evento->nomeEvento, nomeEvento);
    strcpy(evento->data, data);
    strcpy(evento->hora, hora);

//CADASTRO DOS PARTICIPANTES
    //Alocação dinâmica na memória para o participante
    Participante *participante = malloc(nParticipantes * sizeof(Participante));

    if(participante == NULL)
        exit(1);

    //Cadastro das informações do evento
    printf("\n-----\nPARTICIPANTES:");
    for(int i = 0; i < nParticipantes; i++)
    {
        printf("\n\nNOME DO PARTICIPANTE: ");
        scanf("%s", nomeParticipante);
        printf("TELEFONE: ");
        scanf("%s", telefone);
        printf("E-MAIL: ");
        scanf("%s", email);

        //Registrando as informações inseridas no nó participante
        strcpy(evento->participantes[i].nomeParticipante, nomeParticipante);
        strcpy(evento->participantes[i].telefone, telefone);
        strcpy(evento->participantes[i].email, email);
    }

    //Chamando a função para inserir os nós nas listas e no arquivo
    insereEArquiva(e, evento);

    return 0;
}

//Função para inserir e arquivar um evento na lista
int insereEArquiva(LSE_Evento *e, Evento *evento)
{
    /*Como a alocação dinâmica de memória do evento e dos participantes é
     feita na função de cadastro, esta função irá apenas inserir os nós nas
     listas e copiá-los no arquivo.*/

    //Abertura do arquivo em modo append
    FILE *arquivo = fopen("arquivo.txt", "a");

    if (arquivo == NULL)
        exit(1);

//INSERÇÃO DO EVENTO NA LISTA
    //Caso 1 - Primeiro elemento da lista
    if(e->inicio == NULL)
    {
        e->inicio = evento; //Início da lista recebe o nó evento
        e->fim = evento; //Fim da lista recebe o nó evento
        evento->prox = NULL; //Ponteiro *prox do nó evento aponta para NULL
    }

    //Caso 2- A partir do segundo elemento o nó evento é inserido no fim
    else
    {
        e->fim->prox = evento; //Ponteiro *prox do nó que está no fim da lista aponta para o nó evento
        e->fim = evento; //Fim da lista recebe o nó evento
        evento->prox = NULL; //Ponteiro *prox do nó evento aponta para NULL
    }

    //Inserção das informações cadastradas do evento no arquivo de maneira formatada
    fprintf(arquivo, "\n\n----------\nID: %d\n", evento->idEvento);
    fprintf(arquivo, "EVENTO: %s\n", evento->nomeEvento);
    fprintf(arquivo, "DATA: %s\n", evento->data);
    fprintf(arquivo, "HORA: %s", evento->hora);


//INSERÇÃO DOS PARTICIPANTES NA LISTA
    //Loop para repetir a inserção de participante na lista conforme o desejo do usuário
    for(int i = 0; i < evento->nParticipantes; i++)
    {
        //Caso 1 - Primeiro elemento da lista
        if(e->listaParticipantes.inicio == NULL)
        {
            e->listaParticipantes.inicio = &evento->participantes[i]; //Início da lista recebe o nó participante
            e->listaParticipantes.fim = &evento->participantes[i]; //Fim da lista recebe o nó participante
            evento->participantes[i].prox = NULL; //Ponteiro *prox do nó participante aponta para NULL
        }

        //Caso 2- A partir do segundo elemento insere no fim
        else
        {
            e->listaParticipantes.fim->prox = &evento->participantes[i]; //Ponteiro *prox do nó que está no fim da lista aponta para o nó participante
            e->listaParticipantes.fim = &evento->participantes[i]; //Fim da lista recebe o nó participante
            evento->participantes[i].prox = NULL; //Ponteiro *prox do nó participante aponta para NULL
        }

        //Inserção das informações cadastradas do participante no arquivo de maneira formatada
        fprintf(arquivo, "\n\nPARTICIPANTE: %s\n", evento->participantes[i].nomeParticipante);
        fprintf(arquivo, "TELEFONE: %s\n", evento->participantes[i].telefone);
        fprintf(arquivo, "E-MAIL: %s\n", evento->participantes[i].email);
    }

    //Fecha o arquivo
    fclose(arquivo);

    return 0;
}

//Função para imprimir os cadastros arquivados
int imprimeCadastros(LSE_Evento *e)
{
    //Abertura do arquivo em modo leitura
    FILE *arquivo = fopen("arquivo.txt", "r");

    if (arquivo == NULL)
        exit(1);

    //Variável auxiliar para ler as linhas do arquivo
    char linha[100];

    //Impressão do arquivo
    printf("\n----------\nLISTA DE CADASTROS:\n");

    //Se a lista LSE de eventos e o arquivo estiverem vazios, a lista de cadastros está vazia
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

//Função para remover e desarquivar um evento e seus participantes
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

    //Variáveis auxiliares
    Evento *atual = e->inicio; //Variável para percorrer a lista de eventos
    char linha[100]; //Variável para ler as linhas do evento
    int encontrado = 0; //Variável para monitorar se o evento a ser removido foi encontrado
    int n = 0;

    //Loop para percorrer a lista de eventos e procurar o ID e nome do evento que será removido na MEMÓRIA
    while (atual != NULL)
    {
        //Se encontrar o evento que deve ser removido
        if (strcmp(atual->nomeEvento, nomeEvento) == 0 && atual->idEvento == idEvento)
        {
            //Remove participantes associados ao evento da memória
            for (int i = 0; i < atual->nParticipantes; i++)
                free(atual->participantes[i].prox);

            //Remove evento da memória
            //Caso 1 - Remoção do primeiro elemento da lista
            if (atual == e->inicio)
                e->inicio = atual->prox; //Início da lista recebe o *prox do nó evento

            //Caso 2 - Remoção do último elemento da lista
            if (atual == e->fim)
            {
                Evento *penultimo = e->inicio; //Variável auxiliar para guardar o penultimo nó da lista
                //Enquanto não chegar no fim da lista a variável continua percorrendo
                while (penultimo->prox != NULL)
                    penultimo = penultimo->prox;

                //Quando chegar no fim da lista
                penultimo->prox = NULL; //Ponteiro *prox do penúltimo nó aponta para NULL
                e->fim = penultimo; //Fim da lista aponta para o penúltimo nó
            }

            //Caso 3 - Remoção de um elemento no meio da lista
            if(atual != e->inicio && atual != e->fim)
            {
                Evento *anteriorMeio = e->inicio; //Variável auxiliar para guardar o anterior do nó que será removido

                //Enquanto não chegar no fim da lista a variável continua percorrendo
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

        //Se não encontrar o evento que deve ser removido, copia o cadastro para o arquivo temporário
        else
        {
            //Escreve evento no arquivo temporário
            fprintf(arquivoTemporario, "EVENTO: %s\n", atual->nomeEvento);
            fprintf(arquivoTemporario, "ID: %d\n", atual->idEvento);
            fprintf(arquivoTemporario, "Data: %s\n", atual->data);
            fprintf(arquivoTemporario, "Hora: %s\n", atual->hora);
            fprintf(arquivoTemporario, "Nº Participantes: %d\n", atual->nParticipantes);

            //Escreve participantes no arquivo temporário
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

    //Se o evento não for encontrado na memória, pesquisa no arquivo original
    if(encontrado == 0)
    {
        char eventoBuscado[100]; //Variável para ler as linhas do arquivo

        //Enquanto o arquivo não chegar ao fim
        while (fgets(linha, sizeof(linha), arquivoOriginal) != NULL)
        {
            //Se o evento for encontrado
            if (strcmp(linha, eventoBuscado) == 0)
                encontrado = 1;
            printf("Evento removido com sucesso do arquivo!\n");
            return 0;
        }
    }

//Se o evento não for encontrado na memória e nem no arquivo
    if (encontrado == 0)
    {
        printf("\nCadastro não encontrado!\n");
        remove("temporario.txt");
        return 1;
    }

//Se foi encontrado ou na memória ou no arquivo
    else
    {
        //Fechando os arquivos abertos
        fclose(arquivoOriginal);
        fclose(arquivoTemporario);

        //Renomeia arquivo temporário para substituir o arquivo original
        rename("temporario.txt", "arquivo.txt");
        remove("temporario.txt");

        printf("Evento removido com sucesso do arquivo!\n");

        return 0;
    }
}