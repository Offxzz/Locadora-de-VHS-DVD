#ifndef CLIENTES_H
#define CLIENTES_H

// ============================================================================
// CLIENTES.H - MODULO 1: PERSPECTIVA DE CLIENTES
// Autor: Integrante A - LEONARDO BARTOSZEWSKI PINHEIRO - RGM 04735271-0
// ============================================================================
#include <stdio.h>
#include <string.h>
#include "utils.h"

#define MAX_CLIENTES 50
#define ARQUIVO_CLIENTES "clientes.csv"

// ----------------------------------------------------------------------------
// MODELAGEM DE DADOS (escopo global)
// ----------------------------------------------------------------------------
struct Cliente {
    int idCliente;
    char nome[50];
    char telefone[20];
    int locacoesAtivas;
    float multaPendente; // multa por atraso (R$)
    int ativo;           // 1 = Ativo, 0 = Removido
};

struct Cliente listaClientes[MAX_CLIENTES];
int totalClientes = 0;

// ----------------------------------------------------------------------------
// FUNCOES DE APOIO
// ----------------------------------------------------------------------------

// Descobre o proximo ID livre (maior ID existente + 1)
int proximoIdCliente() {
    int i;
    int maior = 0;
    for (i = 0; i < totalClientes; i++) {
        if (listaClientes[i].idCliente > maior) {
            maior = listaClientes[i].idCliente;
        }
    }
    return maior + 1;
}

// Coloca um cliente novo no fim do vetor (quem chama confere se ha espaco)
void inserirCliente(char nome[], char telefone[], int locacoes, float multa) {
    struct Cliente novo;
    novo.idCliente = proximoIdCliente();
    strcpy(novo.nome, nome);
    strcpy(novo.telefone, telefone);
    novo.locacoesAtivas = locacoes;
    novo.multaPendente = multa;
    novo.ativo = 1;
    listaClientes[totalClientes] = novo;
    totalClientes++;
}

// Procura um cliente ativo pelo ID. Devolve a posicao no vetor ou -1.
// (Os outros modulos, como Locacoes, podem usar esta funcao.)
int buscarIndiceClientePorId(int id) {
    int i;
    for (i = 0; i < totalClientes; i++) {
        if (listaClientes[i].idCliente == id && listaClientes[i].ativo == 1) {
            return i;
        }
    }
    return -1;
}

// Mostra uma linha com os dados do cliente da posicao i
void exibirCliente(int i) {
    printf("ID: %d | %s | Tel: %s | Locacoes ativas: %d | Multa: R$ %.2f\n",
           listaClientes[i].idCliente,
           listaClientes[i].nome,
           listaClientes[i].telefone,
           listaClientes[i].locacoesAtivas,
           listaClientes[i].multaPendente);
}

// ----------------------------------------------------------------------------
// ARQUIVO CSV (separador ;)  ->  id;nome;telefone;locacoesAtivas;multa;ativo
// ----------------------------------------------------------------------------

// Grava TODO o vetor no arquivo (o "w" apaga o conteudo antigo)
void salvarClientesCSV() {
    FILE *arquivo = fopen(ARQUIVO_CLIENTES, "w");
    int i;

    if (arquivo == NULL) {
        printf("\n[ERRO] Nao foi possivel salvar o arquivo %s!\n", ARQUIVO_CLIENTES);
        return;
    }
    for (i = 0; i < totalClientes; i++) {
        fprintf(arquivo, "%d;%s;%s;%d;%.2f;%d\n",
                listaClientes[i].idCliente,
                listaClientes[i].nome,
                listaClientes[i].telefone,
                listaClientes[i].locacoesAtivas,
                listaClientes[i].multaPendente,
                listaClientes[i].ativo);
    }
    fclose(arquivo);
}

// Le o arquivo para o vetor. Devolve quantos clientes carregou (0 se nao existe).
int carregarClientesCSV() {
    FILE *arquivo = fopen(ARQUIVO_CLIENTES, "r");

    if (arquivo == NULL) {
        return 0; // arquivo ainda nao existe
    }
    totalClientes = 0;
    while (totalClientes < MAX_CLIENTES &&
           fscanf(arquivo, "%d;%49[^;];%19[^;];%d;%f;%d\n",
                  &listaClientes[totalClientes].idCliente,
                  listaClientes[totalClientes].nome,
                  listaClientes[totalClientes].telefone,
                  &listaClientes[totalClientes].locacoesAtivas,
                  &listaClientes[totalClientes].multaPendente,
                  &listaClientes[totalClientes].ativo) == 6) {
        totalClientes++;
    }
    fclose(arquivo);
    return totalClientes;
}

// Cria 8 clientes de exemplo na primeira execucao e grava o CSV
void criarMassaDadosClientes() {
    inserirCliente("Ana Souza",       "(41) 99999-0001", 0, 0.00);
    inserirCliente("Bruno Lima",      "(41) 99999-0002", 2, 0.00);
    inserirCliente("Carla Mendes",    "(41) 99999-0003", 1, 7.50);
    inserirCliente("Diego Santos",    "(41) 99999-0004", 0, 0.00);
    inserirCliente("Elisa Ferreira",  "(41) 99999-0005", 3, 0.00);
    inserirCliente("Felipe Rocha",    "(41) 99999-0006", 0, 15.00);
    inserirCliente("Gabriela Alves",  "(41) 99999-0007", 1, 0.00);
    inserirCliente("Henrique Costa",  "(41) 99999-0008", 0, 3.25);
    salvarClientesCSV();
}

// Chamar UMA vez no inicio do main: carrega o CSV ou cria os dados de exemplo
void iniciarClientes() {
    if (carregarClientesCSV() == 0) {
        criarMassaDadosClientes();
    }
}

// ----------------------------------------------------------------------------
// OPERACOES (CRUD)
// ----------------------------------------------------------------------------

// 1. CADASTRAR
void cadastrarCliente() {
    char nome[50];
    char telefone[20];

    printf("\n--- CADASTRAR CLIENTE ---\n");
    if (totalClientes >= MAX_CLIENTES) {
        printf("[ERRO] Limite de %d clientes atingido!\n", MAX_CLIENTES);
        return;
    }

    printf("Nome: ");
    scanf(" %49[^\n]", nome);
    limparBuffer();
    printf("Telefone: ");
    scanf(" %19[^\n]", telefone);
    limparBuffer();

    // O ';' e o separador do CSV: se aparecesse no nome, quebraria o arquivo
    if (strchr(nome, ';') != NULL || strchr(telefone, ';') != NULL) {
        printf("\n[ERRO] Nao use o caractere ';' no nome ou telefone!\n");
        return;
    }

    inserirCliente(nome, telefone, 0, 0.0);
    salvarClientesCSV();
    printf("\nCliente cadastrado! ID: %d\n", listaClientes[totalClientes - 1].idCliente);
}

// 2. LISTAR (so mostra quem esta ativo)
void listarClientes() {
    int i;
    int achou = 0;

    printf("\n--- LISTA DE CLIENTES ---\n");
    for (i = 0; i < totalClientes; i++) {
        if (listaClientes[i].ativo == 1) {
            exibirCliente(i);
            achou = 1;
        }
    }
    if (achou == 0) {
        printf("Nenhum cliente cadastrado.\n");
    }
}

// 3. BUSCAR por nome (strstr acha um pedaco do nome; diferencia maiuscula)
void buscarClientePorNome() {
    char busca[50];
    int i;
    int achou = 0;

    printf("\n--- BUSCAR CLIENTE POR NOME ---\n");
    printf("Digite o nome (ou parte dele): ");
    scanf(" %49[^\n]", busca);
    limparBuffer();

    for (i = 0; i < totalClientes; i++) {
        if (listaClientes[i].ativo == 1 && strstr(listaClientes[i].nome, busca) != NULL) {
            exibirCliente(i);
            achou = 1;
        }
    }
    if (achou == 0) {
        printf("Nenhum cliente encontrado com \"%s\".\n", busca);
    }
}

// 4. EDITAR por ID
void editarCliente() {
    int id;
    int indice;
    int campo;
    float novaMulta;

    printf("\n--- EDITAR CLIENTE ---\n");
    printf("ID do cliente: ");
    id = lerInteiro();
    indice = buscarIndiceClientePorId(id);
    if (indice == -1) {
        printf("[ERRO] Cliente nao encontrado!\n");
        return;
    }

    exibirCliente(indice);
    printf("\nO que deseja editar?\n");
    printf("1. Nome\n");
    printf("2. Telefone\n");
    printf("3. Multa pendente\n");
    printf("0. Cancelar\n");
    printf("Escolha: ");
    campo = lerInteiro();

    switch (campo) {
        case 1:
            printf("Novo nome: ");
            scanf(" %49[^\n]", listaClientes[indice].nome);
            limparBuffer();
            break;
        case 2:
            printf("Novo telefone: ");
            scanf(" %19[^\n]", listaClientes[indice].telefone);
            limparBuffer();
            break;
        case 3:
            printf("Nova multa (R$): ");
            novaMulta = lerDecimal();
            if (novaMulta < 0) {
                printf("[ERRO] Valor invalido!\n");
                return;
            }
            listaClientes[indice].multaPendente = novaMulta;
            break;
        case 0:
            printf("Edicao cancelada.\n");
            return;
        default:
            printf("[ERRO] Opcao invalida!\n");
            return;
    }

    salvarClientesCSV(); // reflete a edicao no arquivo
    printf("\nCliente atualizado!\n");
}

// 5. REMOVER por ID (remocao logica: ativo = 0)
void removerCliente() {
    int id;
    int indice;
    int confirma;

    printf("\n--- REMOVER CLIENTE ---\n");
    printf("ID do cliente: ");
    id = lerInteiro();
    indice = buscarIndiceClientePorId(id);
    if (indice == -1) {
        printf("[ERRO] Cliente nao encontrado!\n");
        return;
    }

    // Regra de negocio: quem ainda tem filme alugado nao pode sair
    if (listaClientes[indice].locacoesAtivas > 0) {
        printf("[ERRO] %s ainda tem %d locacao(oes) ativa(s)!\n",
               listaClientes[indice].nome, listaClientes[indice].locacoesAtivas);
        return;
    }

    printf("Remover %s? (1 = sim, 0 = nao): ", listaClientes[indice].nome);
    confirma = lerInteiro();
    if (confirma != 1) {
        printf("Remocao cancelada.\n");
        return;
    }

    listaClientes[indice].ativo = 0;
    salvarClientesCSV(); // reflete a remocao no arquivo
    printf("\nCliente removido!\n");
}

// ----------------------------------------------------------------------------
// SUBMENU DO MODULO
// ----------------------------------------------------------------------------
void moduloClientes() {
    int opcaoCliente;

    do {
        limparTela();
        printf("\n--- [MODULO 1: GESTAO DE CLIENTES (Integrante A)] ---\n");
        printf("1. Cadastrar Novo Cliente\n");
        printf("2. Listar Clientes\n");
        printf("3. Buscar Cliente por Nome\n");
        printf("4. Editar Dados de Cliente\n");
        printf("5. Remover Cliente\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        opcaoCliente = lerInteiro();

        switch (opcaoCliente) {
            case 1:
                cadastrarCliente();
                pausar();
                break;
            case 2:
                listarClientes();
                pausar();
                break;
            case 3:
                buscarClientePorNome();
                pausar();
                break;
            case 4:
                editarCliente();
                pausar();
                break;
            case 5:
                removerCliente();
                pausar();
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida no Modulo de Clientes!\n");
                pausar();
        }
    } while (opcaoCliente != 0);
}

#endif
