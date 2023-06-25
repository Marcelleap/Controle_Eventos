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

    int op1, op2;
    char nomeEvento[20];

    Evento *retornoEvento;

    do
    {
        printf("\n------------------------------\n");
        printf("GERENCIADOR DE EVENTOS:\n");
        printf("[1] Visualizar cadastros\n");
        printf("[2] Cadastrar novo evento\n");
        printf("[3] Remover evento\n");
        printf("[4] Sair\n");
        printf("Opcao: ");
        scanf("%d", &op1);

        clearscr();// FUNÇÃO PARA LIMPAR TELA DO LINUX POR ISSO PODE SER QUE AO TESTAR NO WIN APARECA UM WARNING. 

        switch (op1)
        {
        case 1:
            imprimeCadastros(&lista);
            break;

        case 2:
            cadastro(&lista);
            printf("\nCadastro realizado!\n");
            break;

        case 3:
            printf("\nLista de consulta de ID e Nome de eventos:\n");
            imprimeConsulta(&lista);
            printf("\nInsira os dados para a remocao:\n");
            printf("ID do evento: ");
            scanf("%d", &op2);
            printf("Nome do evento: ");
            scanf("%s", nomeEvento);
            retornoEvento = pesquisaEvento(&lista, nomeEvento, op2);
            removeEDesarquivaCadastro(&lista, retornoEvento);

            if (retornoEvento != NULL)
                printf("\nExclusao realizada!\n");
            break;

        case 4:
            exit(1);

        default:
            printf("\nOpcao invalida! Digite novamente.\n");
            break;

        }
    }
    while (op1 != 4);

    return 0;
}

