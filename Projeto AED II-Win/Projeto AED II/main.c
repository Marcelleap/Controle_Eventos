#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"

int main(void)
{
    //Inicialização da função rand()
    srand(time(NULL));

    //Inicialização das listas LSE para eventos e participantes
    LSE_Evento lista;
    criaListas(&lista);

    //Variáveis auxiliares
    int op1, op2;
    char nomeEvento[20];

    //Loop do menu principal
    do
    {
        printf("\n------------------------------\n");
        printf("GERENCIADOR DE EVENTOS:\n");
        printf("[1] Visualizar cadastros\n");
        printf("[2] Cadastrar novo evento\n");
        printf("[3] Remover cadastro\n");
        printf("[4] Sair\n");
        printf("Opcao: ");
        scanf("%d", &op1);

        do
        {
            //Switch-case para chamar as funções conforme o desejo do usuário
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
                imprimeCadastros(&lista);
                printf("\nInsira os dados para a remocao:\n");
                printf("ID do evento: ");
                scanf("%d", &op2);
                printf("Nome do evento: ");
                scanf("%s", nomeEvento);
                removeEDesarquivaCadastro(&lista, nomeEvento, op2);
                break;

            case 4:
                exit(1);

            default:
                printf("\nOpcao invalida! Digite novamente.\n");
                break;
            }
        }
        while(op1 < 1 || op1 > 4);
    }
    while(op1 != 4);

    return 0;
}
