#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "utils.h"
#include "clientes - Leonardo Bartoszewski Pinheiro/clientes.h"
#include "filmes - Matheus Souza dos Santos/filmes.h"
#include "locacoes - Ian Leuche/locacoes.h"

//3. Perspectiva do integrante C: COMPRA DE MÍDIAS/FORNECEDORES
struct CompraMidia {
    int idCompra;
    char descricao[40];
    char fornecedor[40];
    float custoCompra;
    int quantidade;
};
struct CompraMidia registroCompras[50];
int totalCompras = 0;


// MÓDULO 1: COMPRA DE MÍDIAS E FORNECEDORES
// Autor: Integrante C - JAISON ALAN - RGM 04762834-1

void moduloCompras() {
    int opcaoCompra;
    do {
        printf("\n--- [MODULO 3: COMPRAS DE MIDIAS / FORNECEDORES (Integrante C)] ---\n");
        printf("1. Registrar Compra de Midias\n");
        printf("2. Consultar Compras Realizadas\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcaoCompra);

        switch (opcaoCompra) {
            case 1:
                printf("\n[Em construcao] Rotina de Registro de Compra...\n");
                printf("Campos previstos: ID, Descricao, Fornecedor, Custo e Quantidade.\n");
                break;
            case 2:
                printf("\n[Em construcao] Rotina de Consulta de Compras...\n");
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida no Modulo de Compras!\n");
        }
    } while (opcaoCompra != 0);
}


void exibirCabecalho() {
    printf("\n====================================================\n");
    printf("   RETRO VIDEO LOCADORA - SISTEMA DE GESTAO\n");
    printf("====================================================\n");
}

int main() {
    int opcaoPrincipal;

    setlocale(LC_CTYPE, "Portuguese"); 
    carregarFilmesCSV();
    iniciarClientes(); 
    carregarLocacoesCSV();

    do {
        limparTela();
        exibirCabecalho();
        printf("SELECIONE A PERSPECTIVA DO SISTEMA:\n");
        printf("1. Modulo de Clientes (Leonardo Bartoszewski Pinheiro)\n");
        printf("2. Modulo de Filmes / Catalogo (Matheus Souza dos Santos)\n");
        printf("3. Modulo de Compras / Fornecedores (Jaison Alan)\n");
        printf("4. Modulo de Locacoes e Relatorios (Ian Leuche)\n");
        printf("0. Encerrar o Sistema\n");
        printf("Digite a opcao desejada: ");
        opcaoPrincipal = lerInteiro();

        switch (opcaoPrincipal) {
            case 1:
                moduloClientes();
                break;
            case 2:
                moduloFilmes();
                limparTela();
                break;
            case 3:
                moduloCompras();
                break;
            case 4:
                moduloLocacoesRelatorios();
                break;
            case 0:
                printf("\nEncerrando o sistema... Ate logo!\n");
                break;
            default:
                printf("\n[ALERTA] Opcao invalida! Digite um numero de 0 a 4.\n");
        }
    } while (opcaoPrincipal != 0);

    return 0;
}
