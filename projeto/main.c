#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "utils.h"
#include "filmes - Matheus Souza dos Santos/filmes.h"
#include "clientes - Leonardo Bartoszewski Pinheiro/clientes.h"

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

//4. Perspectiva do integrante D: LOCAÇÕES E RELATÓRIOS
struct Locacao {
    int idLocacao;
    int idCliente;  
    int idFilme;    
    int tipoMidia;         
    int diasLocacao;
    float valorTotal;
    int devolvido;        
};

struct Locacao historicoLocacoes[50];
int totalLocacoes = 0;


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

// MÓDULO 1: lOCAÇÕES E RELATÓRIOS
// Autor: Integrante D - IAN LEUCHE - RGM 04806941-8

void registrarLocacao() {
    struct Locacao nova;
    float valorDiaria;

    if (totalLocacoes >= 50) {
        printf("\n[ERRO] Limite de locacoes atingido!\n");
        return;
    }

    nova.idLocacao = totalLocacoes + 1;

    printf("\nID do cliente: ");
    scanf("%d", &nova.idCliente);
    printf("ID do filme: ");
    scanf("%d", &nova.idFilme);
    printf("Quantidade de dias: ");
    scanf("%d", &nova.diasLocacao);

    printf("Valor da diaria: ");
    scanf("%f", &valorDiaria);

    nova.valorTotal = nova.diasLocacao * valorDiaria;
    nova.devolvido = 0;

    historicoLocacoes[totalLocacoes] = nova;
    totalLocacoes++;

    printf("\nLocacao %d registrada! Total: R$ %.2f\n", nova.idLocacao, nova.valorTotal);
}

void listarLocacoes() {
    int i;

    if (totalLocacoes == 0) {
        printf("\nNenhuma locacao registrada ainda.\n");
        return;
    }

    printf("\n--- LOCACOES REGISTRADAS ---\n");
    for (i = 0; i < totalLocacoes; i++) {
        printf("Locacao %d | Cliente %d | Filme %d | %d dia(s) | R$ %.2f | %s\n",
               historicoLocacoes[i].idLocacao,
               historicoLocacoes[i].idCliente,
               historicoLocacoes[i].idFilme,
               historicoLocacoes[i].diasLocacao,
               historicoLocacoes[i].valorTotal,
               historicoLocacoes[i].devolvido ? "Devolvido" : "Em aberto");
    }
}

void moduloLocacoesRelatorios() {
    int opcao;

    do {
        printf("\n======================================\n");
        printf("   RETRO VIDEO LOCADORA - LOCACOES    \n");
        printf("======================================\n");
        printf("1. Registrar Nova Locacao\n");
        printf("2. Listar Locacoes\n");
        printf("3. Registrar Devolucao\n");
        printf("4. Relatorios\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                registrarLocacao();
                break;
            case 2:
                listarLocacoes();
                break;
            case 3:
                printf("\n[Em construcao] Devolucao de filme...\n");
                break;
            case 4:
                printf("\n[Em construcao] Relatorios de locacoes...\n");
                break;
            case 0:
                printf("\nEncerrando o sistema... Ate logo!\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida!\n");
        }
    } while (opcao != 0);

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

    do {
        exibirCabecalho();
        printf("SELECIONE A PERSPECTIVA DO SISTEMA:\n");
        printf("1. Modulo de Clientes (Integrante A)\n");
        printf("2. Modulo de Filmes / Catalogo (Integrante B)\n");
        printf("3. Modulo de Compras / Fornecedores (Integrante C)\n");
        printf("4. Modulo de Locacoes e Relatorios (Integrante D)\n");
        printf("0. Encerrar o Sistema\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcaoPrincipal);

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
