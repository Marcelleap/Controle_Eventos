/*PROJETO DE ALGORITMO E ESTRUTURA DE DADOS II - 2023/1 */
/*DUPLA: Hadassa Alves de Gouvea e Marcelle Andrade Pereira */

//Escopo do projeto: Gerenciador evento/participantes que
//opera as funcionalidades CRUD (Criar, Ler, Alterar e Remover).

//Recursos da disciplina utilizados:Ponteiros, Fun��es, Lista (LSE) e Arquivo.

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

//Função para criar e inicializar as listas LSE
int criaListas(LSE_Evento *e)
{
    // Inicializa os ponteiros de inicio e fim da Lista LSE de eventos
    e->inicio = NULL;
    e->fim = NULL;
    e->tam = 0;

    // Inicializa os ponteiros de inicio e fim da Lista LSE de participantes
    e->listaParticipantes.inicio = NULL;
    e->listaParticipantes.fim = NULL;

    printf("\nInicializao bem-sucedida!\n");
    return 0;
}

//Função para inserir e arquivar um evento na lista
int insereEArquiva(LSE_Evento *e, Evento *evento)
{
    /*Como a alocação dinâmica de memória do evento e dos participantes já foi
     feita na função de cadastro, esta função irá apenas inserir os nós nas
     listas e arquivá-los.*/

    //Abertura do arquivo em modo append
    FILE *arquivo = fopen("arquivo.txt", "a");

    if (arquivo == NULL)
        exit(1);

//INSERÇÃO DO EVENTO NA LISTA
    //Caso 1 - Primeiro elemento da lista
    if(e->inicio == NULL)
    {
        e->inicio = evento;
        e->fim = evento;
        evento->prox = NULL;
    }

    //Caso 2- A partir do segundo elemento insere no fim
    else
    {
        e->fim->prox = evento;
        e->fim = evento;
        evento->prox = NULL;
    }

    //Inserção das informações do evento no arquivo de maneira formatada
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
            e->listaParticipantes.inicio = &evento->participantes[i];
            e->listaParticipantes.fim = &evento->participantes[i];
            evento->participantes[i].prox = NULL;
        }

        //Caso 2- A partir do segundo elemento insere no fim
        else
        {
            e->listaParticipantes.fim->prox = &evento->participantes[i];
            e->listaParticipantes.fim = &evento->participantes[i];
            evento->participantes[i].prox = NULL;
        }

        //Inserção das informações do participante no arquivo de maneira formatada
        fprintf(arquivo, "\n\nPARTICIPANTE: %s\n", evento->participantes[i].nomeParticipante);
        fprintf(arquivo, "TELEFONE: %s\n", evento->participantes[i].telefone);
        fprintf(arquivo, "E-MAIL: %s\n", evento->participantes[i].email);
    }

    //Fecha o arquivo
    fclose(arquivo);

    printf("\nInsercao bem-sucedida!\n");
    return 0;
}



int cadastro(LSE_Evento *e)
{
    //Variáveis auxiliares
    int nParticipantes;
    char nomeEvento[20], data[11], hora[6];
    char nomeParticipante[40], telefone[16], email[30];

//CADASTRO DO EVENTO
    //Alocação dinâmica na memória do evento
    Evento *evento = (Evento *)malloc(sizeof(Evento));

    if (evento == NULL)
        exit(1);

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

    //Passando os dados do evento para o nó
    evento->idEvento = rand() % 100;
    strcpy(evento->nomeEvento, nomeEvento);
    strcpy(evento->data, data);
    strcpy(evento->hora, hora);

//CADASTRO DOS PARTICIPANTES
    Participante *participante = malloc(nParticipantes * sizeof(Participante));

    if(participante == NULL)
        exit(1);

    printf("\n-----\nPARTICIPANTES:");
    for(int i = 0; i < nParticipantes; i++)
    {
        printf("\n\nNOME DO PARTICIPANTE: ");
        scanf("%s", nomeParticipante);
        printf("TELEFONE: ");
        scanf("%s", telefone);
        printf("E-MAIL: ");
        scanf("%s", email);

        //Passando os dados do participante para o nó
        strcpy(evento->participantes[i].nomeParticipante, nomeParticipante);
        strcpy(evento->participantes[i].telefone, telefone);
        strcpy(evento->participantes[i].email, email);
    }

    //Chama a função para inserir os nós nas listas e no arquivo
    insereEArquiva(e, evento);

    printf("\nCadastro bem-sucedido!\n");
    return 0;
}

//Função para imprimir os cadastros arquivados
int imprimeCadastros(LSE_Evento *e)
{
    //Abertura do arquivo em modo read
    FILE *arquivo = fopen("arquivo.txt", "r");

    if (arquivo == NULL)
        exit(1);

    //Variável auxiliar para ler linha por linha
    char linha[100];

    //Impressão do arquivo
    printf("\n----------\nLISTA DE CADASTROS:\n");

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

    printf("\nImpressao bem-sucedida!\n");
    return 0;
}


void removeEDesarquivaCadastro(LSE_Evento *e, char nomeEvento[20], int idEvento)
{
    char linha[100];
    int encontrado = 0;
    int n = 0;

    Evento *atual = e->inicio;

    FILE *arquivoOriginal = fopen("arquivo.txt", "r");

    if (arquivoOriginal == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    FILE *arquivoTemporario = fopen("temporario.txt", "w");

    if (arquivoTemporario == NULL)
    {
        printf("Erro ao abrir o arquivo temporário!\n");
        fclose(arquivoOriginal);
        exit(1);
    }

    while (atual != NULL)
    {
        if (strcmp(atual->nomeEvento, nomeEvento) == 0 && atual->idEvento == idEvento)
        {
            // Remover participantes associados ao evento da memória
            for (int i = 0; i < atual->nParticipantes; i++)
            {
                free(atual->participantes[i].prox);
            }

            // Remover evento da memória
            if (atual == e->inicio)
            {
                e->inicio = atual->prox;
            }
            else
            {
                Evento *anterior = e->inicio;
                while (anterior->prox != atual)
                {
                    anterior = anterior->prox;
                }
                anterior->prox = atual->prox;
            }

            if (atual == e->fim)
            {
                e->fim = NULL;
            }

            free(atual);
            encontrado = 1;
            printf("Evento removido com sucesso da memória!\n");
        }
        else
        {
            // Escrever evento no arquivo temporário
            fprintf(arquivoTemporario, "EVENTO: %s\n", atual->nomeEvento);
            fprintf(arquivoTemporario, "ID: %d\n", atual->idEvento);
            fprintf(arquivoTemporario, "Data: %s\n", atual->data);
            fprintf(arquivoTemporario, "Hora: %s\n", atual->hora);
            fprintf(arquivoTemporario, "Nº Participantes: %d\n", atual->nParticipantes);

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

    // Pesquisar no arquivo original se o evento não foi encontrado na memória
    if (!encontrado)
    {
        char eventoBuscado[100];
        sprintf(eventoBuscado, "EVENTO: %s\n", nomeEvento);

        while (fgets(linha, sizeof(linha), arquivoOriginal) != NULL)
        {
            if (strcmp(linha, eventoBuscado) == 0)
            {
                encontrado = 1;
                break;
            }
        }
    }

    fclose(arquivoOriginal);
    fclose(arquivoTemporario);

    if (!encontrado)
    {
        printf("O evento especificado não existe!\n");
        remove("temporario.txt");
    }

    else
    {
        fclose(arquivoOriginal);
        // Renomear arquivo temporário para substituir o arquivo original
        if (rename("temporario.txt", "arquivo.txt") != 0)
        {
            printf("Erro ao renomear o arquivo temporário!\n");
            remove("temporario.txt");
            exit(1);
        }
        else
        {
            printf("Evento removido com sucesso do arquivo!\n");
        }
    }
}



// Fun��o para alterar um evento no ARQUIVO
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
// Fun��o para alterar um participante no ARQUIVO
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
        // Verifica se a linha come�a com "EVENTO: "
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

