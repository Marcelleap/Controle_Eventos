//PROJETO DE ALGORITMO E ESTRUTURA DE DADOS II - 2023/1//
//DUPLA: Hadassa ALves de Gouvea

//Escopo do projeto: Gerenciador evento/participantes que
//opera as funcionalidades CRUD (Criar, Ler, Alterar e Remover).

//Recursos da disciplina utilizados:Ponteiros, Fun��es, Lista (LSE) e Arquivo.

#ifndef HEADER_H
#define HEADER_H

//N� para participantes
typedef struct participante
{
    char nomeParticipante[40];
    struct participante *prox;
} Participante;

//Lista LSE para participantes
typedef struct
{
    Participante *inicio;
    Participante *fim;
} LSE_Participante;

//N� para eventos que inclui 4 dispon�veis para armazenar n�s para participantes
typedef struct evento
{
    int nParticipantes;
    char nomeEvento[20];
    Participante participantes[4];
    struct evento *prox;
} Evento;

//Lista LSE para eventos que inclui uma lista LSE para participantes
typedef struct
{
    Evento *inicio;
    Evento *fim;
    LSE_Participante listaParticipantes;
} LSE_Evento;

//Fun��o para criar e inicializar as listas LSE de eventos e participantes
int criaListas(LSE_Evento *e);
//Fun��o para realizar o cadastro das informa��es dos eventos e participantes
int cadastro(LSE_Evento *e);
//Fun��o para inserir e arquivar um evento na lista
int insereEArquiva(LSE_Evento *e, Evento *evento);
//Fun��o para imprimir os cadastros arquivados
int imprimeCadastros(LSE_Evento *e);
//Fun��o para pesquisar e retornar um evento na MEMORIA
Evento *pesquisaEvento(LSE_Evento *e, char nome[20]);
//Fun��o para alterar um evento e seus participantes no ARQUIVO
int alteraCadastro(char nomeEvento[20], char novoNomeEvento[20]);
//Fun��o para remover um evento inteiro NO ARQUIVO
int removeCadastro(char nome[20]);
//Fun��o para desalocar um cadastro de evento e participantes da MEM�RIA
int desalocaCadastro(LSE_Evento *e, Evento *evento);
int i;

#endif
