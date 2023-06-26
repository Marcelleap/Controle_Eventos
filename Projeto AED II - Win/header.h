/*PROJETO DE ALGORITMO E ESTRUTURA DE DADOS II - 2023/1 */
/*DUPLA: Hadassa Alves de Gouvea e Marcelle Andrade Pereira */

//Escopo do projeto: Gerenciador evento/participantes que
//opera as funcionalidades CRUD (Criar, Ler, Alterar e Remover).

//Recursos da disciplina utilizados:Ponteiros, Fun��es, Lista (LSE) e Arquivo.

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
    Participante participantes[4];
    int nParticipantes;
    struct evento *prox;
} Evento;

typedef struct
{
    Evento *inicio;
    Evento *fim;
    int tam;
    LSE_Participante listaParticipantes;
} LSE_Evento;

int criaListas(LSE_Evento *e);
int insereEArquiva(LSE_Evento *e, Evento *evento);
int cadastro(LSE_Evento *e);
int imprimeCadastros(LSE_Evento *e);
int imprimeConsulta(LSE_Evento *e);
void removeEDesarquivaCadastro(LSE_Evento *e, char nomeEvento[20], int idEvento);
int alteraCadastroEvento(char nomeEvento[20], char novoNomeEvento[20]);
int alteraCadastroParticipante(char nomeParticipante[20], char novoNomeParticipante[20]);


#endif

