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
    int idCliente;  
    int idFilme;    
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
