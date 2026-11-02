#include <stdio.h>
#include <stdlib.h>


// PARTE 1: MODELAGEM DE DADOS 


//1. Perspectiva do integrante A: CLIENTES DA LOCADORA DE VHS/DVD
struct Cliente {
    int idCliente;
    char nome[50];
    char telefone[20];
    int locacoesAtivas;
    float multaPendente; // multa por atraso (R$)
    int ativo; // 1 = Ativo, 0 = Removido
};

struct Cliente listaClientes[50];
int totalClientes = 0;

// 2. Perspectiva do integrante B: CADASTRO DO CATÁLOGO DE FILMES
struct Filme {
    int id;
    char titulo[50];
    int ano;
    float preco;
    int ativo;
};

struct Filme filmes[50];
int total = 0;

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
    int idClienteLocador;  
    int idFilmeAlugado;    
    int tipoMidia;         
    int diasLocacao;
    float valorTotal;
    int devolvido;        
};

struct Locacao historicoLocacoes[50];
int totalLocacoes = 0;


// MÓDULO 1: PERSPECTIVA DE CLIENTES
// Autor: Integrante A - LEONARDO BARTOSZEWSKI PINHEIRO

void moduloClientes() {
    int opcaoCliente;
    do {
        printf("\n--- [MODULO 1: GESTAO DE CLIENTES (Integrante A)] ---\n");
        printf("1. Cadastrar Novo Cliente\n");
        printf("2. Listar / Buscar Clientes\n");
        printf("3. Editar Dados de Cliente\n");
        printf("4. Remover Cliente\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcaoCliente);

        switch (opcaoCliente) {
            case 1:
                printf("\n[Em construcao] Rotina de Cadastro de Cliente...\n");
                break;
            case 2:
                printf("\n[Em construcao] Rotina de Busca e Listagem de Clientes...\n");
                break;
            case 3:
                printf("\n[Em construcao] Rotina de Edicao de Cliente por ID...\n");
                break;
            case 4:
                printf("\n[Em construcao] Rotina de Remocao de Cliente...\n");
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida no Modulo de Clientes!\n");
        }
    } while (opcaoCliente != 0);
}


// MÓDULO 2: CATÁLOGO DE FILMES
// Autor: Integrante B - MATHEUS SOUZA DOS SANTOS - RGM 47830824

void cadastrarFilme() {
    if (total >= 50) {
        printf("Catalogo cheio!\n");
        return;
    }
    filmes[total].id = total + 1;
    printf("Titulo: ");
    scanf("%s", filmes[total].titulo);
    printf("Ano: ");
    scanf("%d", &filmes[total].ano);
    printf("Preco: ");
    scanf("%f", &filmes[total].preco);
    filmes[total].ativo = 1;
    total++;
    printf("Filme cadastrado!\n");
}

void listarFilmes() {
    int i;
    for (i = 0; i < total; i++) {
        if (filmes[i].ativo == 1) {
            printf("%d - %s - %d - R$ %.2f\n", filmes[i].id, filmes[i].titulo, filmes[i].ano, filmes[i].preco);
        }
    }
}

void editarFilme() {
    int id;
    printf("ID do filme: ");
    scanf("%d", &id);
    if (id < 1 || id > total || filmes[id - 1].ativo == 0) {
        printf("Filme nao encontrado!\n");
        return;
    }
    printf("Novo preco: ");
    scanf("%f", &filmes[id - 1].preco);
}

void removerFilme() {
    int id;
    printf("ID do filme: ");
    scanf("%d", &id);
    if (id < 1 || id > total || filmes[id - 1].ativo == 0) {
        printf("Filme nao encontrado!\n");
        return;
    }
    filmes[id - 1].ativo = 0;
}

void moduloFilmes() {
    int opcao;
    do {
        printf("\n--- CATALOGO DE FILMES ---\n");
        printf("1. Cadastrar\n2. Listar\n3. Editar\n4. Remover\n0. Voltar\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: cadastrarFilme(); break;
            case 2: listarFilmes(); break;
            case 3: editarFilme(); break;
            case 4: removerFilme(); break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

int main() {
    int opcao;
    do {
        printf("\n=== LOCADORA VHS ===\n");
        printf("1. Catalogo de Filmes\n0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: moduloFilmes(); break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
    return 0;
}

// MÓDULO 1: COMPRA DE MÍDIAS E FORNECEDORES
// Autor: Integrante C - JAISON ALAN - RGM 

void moduloCompras() {
    int opcaoCompra;
    int i;
    float totalGeral;

    do {
        printf("\n--- [MODULO 3: COMPRAS DE MIDIAS / FORNECEDORES (Integrante C)] ---\n");
        printf("1. Registrar Compra de Midias\n");
        printf("2. Consultar Compras Realizadas\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcaoCompra);

        switch (opcaoCompra) {
            case 1:
                if (totalCompras >= 50) {
                    printf("\n[ERRO] Limite de 50 compras atingido!\n");
                    break;
                }
                registroCompras[totalCompras].idCompra = totalCompras + 1;

                printf("\nDescricao da midia (ex.: Matrix (VHS)): ");
                scanf(" %39[^\n]", registroCompras[totalCompras].descricao);

                printf("Fornecedor: ");
                scanf(" %39[^\n]", registroCompras[totalCompras].fornecedor);

                printf("Custo de cada unidade (R$): ");
                scanf("%f", &registroCompras[totalCompras].custoCompra);

                printf("Quantidade comprada: ");
                scanf("%d", &registroCompras[totalCompras].quantidade);

                printf("\n[OK] Compra %d registrada! Total: R$ %.2f\n",
                       registroCompras[totalCompras].idCompra,
                       registroCompras[totalCompras].custoCompra * registroCompras[totalCompras].quantidade);

                printf("[Em construcao] Enviando midias para o estoque...\n");

                totalCompras++;
                break;
            case 2:
                printf("\n--- Compras Registradas ---\n");
                if (totalCompras == 0) {
                    printf("Nenhuma compra registrada.\n");
                    break;
                }
                totalGeral = 0;
                for (i = 0; i < totalCompras; i++) {
                    printf("Compra %d | %s | Fornecedor: %s | Qtd: %d | Unidade: R$ %.2f | Total: R$ %.2f\n",
                           registroCompras[i].idCompra,
                           registroCompras[i].descricao,
                           registroCompras[i].fornecedor,
                           registroCompras[i].quantidade,
                           registroCompras[i].custoCompra,
                           registroCompras[i].custoCompra * registroCompras[i].quantidade);
                    totalGeral = totalGeral + registroCompras[i].custoCompra * registroCompras[i].quantidade;
                }
                printf("Total geral das compras: R$ %.2f\n", totalGeral);
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
// Autor: Integrante D - IAN LEUCHE - RGM

void exibirCabecalho() {
    printf("\n======================================================\n");
    printf("   RETRO VIDEO LOCADORA - SISTEMA DE GESTAO (VHS/DVD) \n");
    printf("======================================================\n");
}


void moduloLocacoesRelatorios() {
    int opcaoLocacao;
    do {
        printf("\n--- [LOCACOES E RELATORIOS ANALITICOS] ---\n");
        printf("1. Registrar Nova Locacao no Balcao (Cruza Cliente + Filme)\n");
        printf("2. Registrar Devolucao (Calcula Atraso e Multa)\n");
        printf("3. Cancelar / Estornar Locacao\n");
        printf("4. [RELATORIO] Filme Mais Alugado\n");
        printf("5. [RELATORIO] Cliente VIP (Maior Numero de Locacoes)\n");
        printf("6. [RELATORIO] Locacoes Realizadas por um Cliente Especifico\n");
        printf("7. [RELATORIO] Locacoes em Aberto (Nao Devolvidas)\n");
        printf("0. Encerrar o Sistema\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcaoLocacao);

        switch (opcaoLocacao) {
            case 1:
                printf("\n[Em construcao] Lancamento de locacao vinculando ID Cliente e ID Filme...\n");
                printf("Campos previstos: ID Locacao, ID Cliente, ID Filme, Midia, Dias.\n");
                break;
            case 2:
                printf("\n[Em construcao] Devolucao de midia e calculo de multa por atraso...\n");
                break;
            case 3:
                printf("\n[Em construcao] Estorno de locacao por ID...\n");
                break;
            case 4:
                printf("\n[Em construcao] Calculando ranking do filme mais alugado...\n");
                break;
            case 5:
                printf("\n[Em construcao] Identificando cliente com maior volume de locacoes...\n");
                break;
            case 6:
                printf("\n[Em construcao] Filtrando filmes alugados por um ID de cliente...\n");
                break;
            case 7:
                printf("\n[Em construcao] Listando locacoes ainda nao devolvidas...\n");
                break;
            case 0:
                printf("\nEncerrando o sistema Retro Video Locadora... Ate logo!\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida no Modulo de Locacoes!\n");
        }
    } while (opcaoLocacao != 0);
}




