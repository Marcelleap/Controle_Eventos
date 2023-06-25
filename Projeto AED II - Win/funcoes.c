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
    char nomeEvento[20], nomeParticipante[40];

//CADASTRO DO EVENTO
    //Alocação dinâmica na memória para o evento
    Evento *evento = (Evento *)malloc(sizeof(Evento));

    if (evento == NULL)
        exit(1);

    //Cadastro do nome do evento
    printf("\n----------\nCADASTRO DO EVENTO:\n");
    printf("\nNOME DO EVENTO: ");
    scanf("%s", nomeEvento);

    do
    {
        printf("\nQUANTIDADE DE PARTICIPANTES (Max.: 4): ");
        scanf("%d", &nParticipantes);

        if(nParticipantes < 1 || nParticipantes > 4)
            printf("\nQuantidade de participantes invalida!\n");

        else
            evento->nParticipantes = nParticipantes;
    }
    while(nParticipantes < 1 || nParticipantes > 4);

    //Registrando as informações nó evento
    strcpy(evento->nomeEvento, nomeEvento);

//CADASTRO DOS PARTICIPANTES
    //Alocação dinâmica na memória para o participante
    Participante *participante = malloc(nParticipantes * sizeof(Participante));

    if(participante == NULL)
        exit(1);

    //Cadastro das informações do evento
    printf("\nPARTICIPANTES:");
    for(int i = 0; i < nParticipantes; i++)
    {
        printf("\nNOME DO PARTICIPANTE: ");
        scanf("%s", nomeParticipante);

        //Registrando as informações inseridas no nó participante
        strcpy(evento->participantes[i].nomeParticipante, nomeParticipante);
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
    fprintf(arquivo, "\n\nEVENTO: %s", evento->nomeEvento);

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
        fprintf(arquivo, "\nPARTICIPANTE: %s", evento->participantes[i].nomeParticipante);
    }

    //Fecha o arquivo
    fclose(arquivo);

    printf("\nCadastro realizado!\n");
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
    printf("\n\nLISTA DE CADASTROS:");

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

//Função para pesquisar e retornar um evento na MEMORIA
Evento *pesquisaEvento(LSE_Evento *e, char nome[20])
{
    //Variável auxiliar para percorrer a lista de eventos
    Evento *atual = e->inicio;

    //Loop para percorrer até o fim
    while(atual != NULL)
    {
        //Se o nome do nó atual foi igual ao nome do evento procurado, retorna atual
        if(strcmp(atual->nomeEvento, nome) == 0)
            return atual;

        atual = atual->prox;
    }

    atual = NULL;
    return atual;
}

// Função para alterar um evento no ARQUIVO
int alteraCadastroEvento(char nomeEvento[20], char novoNomeEvento[20])
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
        // Verifica se a linha começa com "EVENTO: "
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
// Função para alterar um participante no ARQUIVO
int alteraCadastroParticipante(char nomeParticipante[20], char novoNomeParticipante[20])
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
        // Verifica se a linha começa com "EVENTO: "
        if (strstr(linha, "PARTICIPANTE: ") == linha)
        {
            // Substitui o nome do evento na linha pelo novo nome
            fprintf(arquivoTemporario, "PARTICIPANTE: %s\n", novoNomeParticipante);
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

//Função para remover um evento inteiro NO ARQUIVO
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

    //Variável auxiliar para ler as linhas do arquivo
    char linha[100];

    //Loop para ler o arquivo
    while (fgets(linha, sizeof(linha), arquivoOriginal) != NULL)
    {

        //Verifica se a linha contém o nome do evento/participante a ser removido
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

//Função para desalocar um cadastro de evento e participantes da MEMÓRIA
int desalocaCadastro(LSE_Evento *e, Evento *evento)
{
//Variável para percorrer a lista de eventos
    Evento *atual = e->inicio;

//Loop para percorrer a lista de eventos até o fim
    while (atual != NULL)
    {
        //Se encontrar o evento que deve ser removido
        if (strcmp(atual->nomeEvento, evento->nomeEvento) == 0)
        {
            //Remove todos os participantes alocados dentro do evento da memória
            for (int i = 0; i < atual->nParticipantes; i++)
                free(&atual->participantes[i]);

            //Remove evento da memória
            //Caso 1 - Remoção do primeiro elemento da lista
            if (atual == e->inicio)
                e->inicio = atual->prox; //Início da lista recebe o *prox do nó evento

            //Caso 2 - Remoção do último elemento da lista
            if (atual == e->fim)
            {
                //Variável auxiliar para guardar o penultimo nó da lista
                Evento *penultimo = e->inicio;

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
                //Variável auxiliar para guardar o anterior do nó que será removido
                Evento *anteriorMeio = e->inicio;

                //Enquanto não chegar no fim da lista a variável continua percorrendo
                while(anteriorMeio->prox != atual)
                    anteriorMeio = anteriorMeio->prox;

                //Se encontrar o nó anterior ao nó que deve ser removido, "costura" a lista
                if(anteriorMeio->prox == atual)
                    anteriorMeio->prox = atual->prox;
            }

            free(atual);
            printf("\nCadastro desalocado da memoria com sucesso!\n");
        }
    }

    return 0;
}
