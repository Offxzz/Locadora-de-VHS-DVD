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
// Autor: Integrante A - LEONARDO BARTOSZEWSKI PINHEIRO - RGM 04735271-0

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
// Autor: Integrante B - MATHEUS SOUZA DOS SANTOS - RGM 04783082-4

void cadastrarFilme() {
    filmes[total].id = total + 1;
    printf("Titulo, ano e preco: ");
    scanf("%s %d %f", filmes[total].titulo, &filmes[total].ano, &filmes[total].preco);
    total++;
}

void listarFilmes() {
    int i;
    for (i = 0; i < total; i++) {
        printf("%d - %s - %d - R$ %.2f\n", filmes[i].id, filmes[i].titulo, filmes[i].ano, filmes[i].preco);
    }
}

void moduloFilmes() {
    int opcao;
    do {
        printf("\n1. Cadastrar\n2. Listar\n3. Editar\n4. Remover\n0. Voltar\nOpcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: cadastrarFilme(); break;
            case 2: listarFilmes(); break;
            case 3: case 4: printf("[Em construcao]\n"); break;
        }
    } while (opcao != 0);
}

int main() {
    int opcao;
    do {
        printf("\n1. Catalogo de Filmes\n0. Sair\nOpcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: moduloFilmes(); break;
        }
    } while (opcao != 0);
    return 0;
}

// MÓDULO 1: COMPRA DE MÍDIAS E FORNECEDORES
// Autor: Integrante C - JAISON ALAN - RGM 04762834-1

struct CompraMidia {
    int idCompra;
    char descricao[40];
    char fornecedor[40];
    float custoCompra;
    int quantidade;
};
struct CompraMidia registroCompras[50];
int totalCompras = 0;

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




