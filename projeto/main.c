#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "utils.h"
#include "clientes - Leonardo Bartoszewski Pinheiro/clientes.h"
#include "filmes - Matheus Souza dos Santos/filmes.h"
#include "compras - Jaison Alan/compras.h"
#include "locacoes - Ian Leuche/locacoes.h"



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
    carregarComprasCSV();

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
