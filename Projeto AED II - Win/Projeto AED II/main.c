#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"

int main(void)
{
    //Inicialização das listas LSE para eventos e participantes
    LSE_Evento lista;
    criaListas(&lista);

    //Variáveis auxiliares
    int op1, op3, op4, op5;
    char nomeEvento[20], novoNomeEvento[20], nomeParticipante[40], novoNomeParticipante[40];
    char nomeRemoverE[20], nomeRemoverP[4][40];

    printf("PROJETO DE ALGORITMO E ESTRUTURA DE DADOS II - 2023/1\n");
    printf("DUPLA: Hadassa Alves de Gouvea e Marcelle Andrade Pereira\n\n");
    printf("\n-------------------------------------------\n");
    printf("\tGERENCIADOR DE EVENTOS:\n");
    printf("\n-------------------------------------------\n");


    //Loop do menu principal
    do
    {
        printf("\nMENU:\n");
        printf("[1] Cadastrar novo evento\n");
        printf("[2] Visualizar cadastros\n");
        printf("[3] Remover cadastro\n");
        printf("[4] Alterar cadastro\n");
        printf("[5] Sair\n");
        printf("Opcao: ");
        scanf("%d", &op1);

        do
        {
            //Switch-case para chamar as funções conforme o desejo do usuário
            switch(op1)
            {
            case 1:
                cadastro(&lista);
                break;

            case 2:
                imprimeCadastros(&lista);
                break;

            case 3:
                imprimeCadastros(&lista);

                printf("\nInsira o nome do evento que deseja remover: \n");
                scanf("%s", nomeRemoverE);

                do
                {
                    printf("Insira a quantidade de participantes do evento: ");
                    scanf("%d", &op4);
                }
                while(op4 != 1 && op4 != 2 && op4 != 3 && op4 != 4);

                removeCadastro(nomeRemoverE);

                int cont = 0;
                for(int i = 0; i < op4; i++)
                {
                    cont++;
                    printf("\nInsira o nome do participante %d do evento: \n", cont);
                    scanf("%s", nomeRemoverP[i]);
                    desalocaCadastro(&lista, pesquisaEvento(&lista, nomeRemoverP[i]));
                }

                desalocaCadastro(&lista, pesquisaEvento(&lista, nomeRemoverE));
                break;

            case 4:
                do
                {
                    printf("\nQual estrutura voce gostaria de alterar:\n");
                    printf("[1] Evento\n");
                    printf("[2] Participante\n");
                    printf("Opcao: ");
                    scanf("%d", &op3);

                    if(op3 != 1 && op3 != 2)
                        printf("\nOpcao invalida!\n");

                }
                while(op3 != 1 && op3 != 2);

                if(op3 == 1) //Alterar evento
                {
                    printf("\n\nInsira o nome do evento que deseja alterar: ");
                    scanf("%s", nomeEvento);
                    strcpy(nomeEvento, "EVENTO: ");
                    printf("\n\nInsira o novo nome para o evento: ");
                    scanf("%s", novoNomeEvento);
                    strcpy(nomeEvento, "EVENTO: ");

                    alteraCadastro(nomeEvento, novoNomeEvento);
                }

                if(op3 == 2) //Alterar participante
                {
                    printf("\n\nInsira o nome do participante que deseja alterar: ");
                    scanf("%s", nomeParticipante);
                    strcpy(nomeParticipante, "PARTICIPANTE: ");
                    printf("\n\nInsira o novo nome para o evento: ");
                    scanf("%s", novoNomeParticipante);
                    strcpy(novoNomeParticipante, "PARTICIPANTE: ");

                    alteraCadastro(nomeParticipante, novoNomeParticipante);
                }
                break;

            case 5:
                exit(1);

            default:
                printf("\nOpcao invalida! Digite novamente.\n");
                break;
            }
        }
        while(op1 != 1 && op1 != 2 && op1 != 3 && op1 != 4 && op1 != 5);

    }
    while(op1 != 5 && continuar == 1);

    return 0;
}
