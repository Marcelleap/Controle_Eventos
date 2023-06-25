/*PROJETO DE ALGORITMO E ESTRUTURA DE DADOS II - 2023/1 */
/*DUPLA: Hadassa Alves de Gouvea e Marcelle Andrade Pereira */

//Escopo do projeto: Gerenciador evento/participantes que
//opera as funcionalidades CRUD (Criar, Ler, Alterar e Remover).

//Recursos da disciplina utilizados:Ponteiros, Funções, Lista (LSE) e Arquivo.

#ifndef HEADER_H
#define HEADER_H

//Nó para participantes
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

//Nó para eventos que inclui 4 disponíveis para armazenar nós para participantes
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

//Função para criar e inicializar as listas LSE de eventos e participantes
int criaListas(LSE_Evento *e);
//Função para realizar o cadastro das informações dos eventos e participantes
int cadastro(LSE_Evento *e);
//Função para inserir e arquivar um evento na lista
int insereEArquiva(LSE_Evento *e, Evento *evento);
//Função para imprimir os cadastros arquivados
int imprimeCadastros(LSE_Evento *e);
//Função para pesquisar e retornar um evento na MEMORIA
Evento *pesquisaEvento(LSE_Evento *e, char nome[20]);
//Função para alterar um evento no ARQUIVO
int alteraCadastroEvento(char nomeEvento[20], char novoNomeEvento[20]);
//Função para alterar um participante no ARQUIVO
int alteraCadastroParticipante(char nomeParticipante[20], char novoNomeParticipante[20]);
//Função para remover um evento inteiro NO ARQUIVO
int removeCadastro(char nome[20]);
//Função para desalocar um cadastro de evento e participantes da MEMÓRIA
int desalocaCadastro(LSE_Evento *e, Evento *evento);
int i;

#endif

