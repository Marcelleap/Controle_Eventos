/*PROJETO DE ALGORITMO E ESTRUTURA DE DADOS II - 2023/1 */
/*DUPLA: Hadassa Alves de Gouvea e Marcelle Andrade Pereira */

//Escopo do projeto: Gerenciador evento/participantes que
//opera as funcionalidades CRUD (Criar, Ler, Alterar e Remover).

//Recursos da disciplina utilizados:Ponteiros, Fun��es, Lista (LSE) e Arquivo.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"

int main(void)
{
    srand(time(NULL));

    LSE_Evento lista;
    criaListas(&lista);


    int op1, op2,op3,op5;
    char nomeEvento[20];
    char  novoNomeEvento[20], nomeParticipante[40], novoNomeParticipante[40];

    do
    {
        printf("\n------------------------------\n");
        printf("GERENCIADOR DE EVENTOS:\n");
        printf("[1] Visualizar cadastros\n");
        printf("[2] Cadastrar novo evento\n");
        printf("[3] Alterar cadastro\n");
        printf("[4] Remover cadastro\n");
        printf("[5] Sair\n");
        printf("Opcao: ");
        scanf("%d", &op1);

// clearscr();// funcao para limpar no linux

        do
        {
            switch(op1)
            {
            case 1:
                imprimeCadastros(&lista);
                break;

            case 2:
                cadastro(&lista);
                printf("\nCadastro realizado!\n");
                break;

            case 3:
                do
                {
                    printf("Deseja alterar evento?\n");
                    printf("[1] Sim\n");
                    printf("[2] Nao\n");
                    printf("Opcao: ");
                    scanf("%d", &op2);

                    if (op2 == 1)

                    {
                      //IMPRESSAO PARA CONSULTA
                        imprimeCadastros(&lista);
                        printf("\n\nInsira o nome do evento que deseja alterar: ");
                        scanf("%s", nomeEvento);
                        strcpy(nomeEvento, "EVENTO: ");
                        printf("\nInsira o novo nome para o evento: ");
                        scanf("%s", novoNomeEvento);
                        strcpy(novoNomeEvento, "EVENTO: ");


                        printf("\n\nDeseja alterar participantes?\n");
                        printf("[1] Sim - Para Alterar Participante\n");
                        printf("[2] Nao \n");
                        printf("Opcao: ");
                        scanf("%d", &op3);

                        if (op3 == 1)
                        {
                           printf("\n\nInsira o nome do participante que deseja alterar: ");
                            scanf("%s", nomeParticipante);
                            strcpy(nomeParticipante, "PARTICIPANTE: ");
                            printf("\nInsira o novo nome para o participante: ");
                            scanf("%s", novoNomeParticipante);
                            strcpy(novoNomeParticipante, "PARTICIPANTE: ");

                            alteraCadastroParticipante(nomeParticipante, novoNomeParticipante);
                        }

                        if (op3 != 1)
                        {
                            printf("\n\n Opcao invalida ");

                        }

                    }
                    if (op2 != 2 || op1!=1)
                    {
                        printf("Opcao invalida\n");
                    }
                }
                while (op2 != 1 && op2 != 2);
                break;

            case 4:
                imprimeCadastros(&lista);
                printf("\nInsira os dados para a remocao:\n");
                printf("ID do evento: ");
                scanf("%d", &op5);
                printf("Nome do evento: ");
                scanf("%s", nomeEvento);
                removeEDesarquivaCadastro(&lista, nomeEvento, op2);
                break;

            case 5:
                exit(1);

            default:
                printf("\nOpcao invalida! Digite novamente.\n");
                break;
            }
        }
        while(op1 != 1 && op1 != 2 && op1 != 3 && op1 != 4);
    }
    while(op1 != 4);

    return 0;
}
