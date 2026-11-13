#include <stdio.h>
#include <string.h>

//3. Perspectiva do integrante C: COMPRA DE MIDIAS/FORNECEDORES
struct CompraMidia {
    int idCompra;
    char descricao[40];
    char fornecedor[40];
    float custoCompra;
    int quantidade;
    int idFilme;
};
struct CompraMidia registroCompras[50];
int totalCompras = 0;

int lerNumeroCompra() {
    int numero;
    int resultado = scanf("%d", &numero);
    if (resultado == EOF) {
        return 0;
    }
    if (resultado != 1) {
        scanf("%*[^\n]");
        return -1;
    }
    return numero;
}

float lerDecimalCompra() {
    float numero;
    int resultado = scanf("%f", &numero);
    if (resultado != 1) {
        scanf("%*[^\n]");
        return -1;
    }
    return numero;
}

void lerTextoCompra(char destino[]) {
    int i;
    destino[0] = '\0';
    scanf(" %39[^\n]", destino);
    for (i = 0; destino[i] != '\0'; i++) {
        if (destino[i] == ';') {
            destino[i] = ',';
        }
    }
}

void pausarCompra() {
    printf("\nPressione ENTER para continuar...");
    getchar();
    getchar();
}

int filmeExisteCompra(int idFilme) {
    int i;
    for (i = 0; i < totalFilmes; i++) {
        if (filmes[i].id == idFilme) {
            return 1;
        }
    }
    return 0;
}

void atualizarEstoqueCompra(int idFilme, int variacao) {
    int i;
    for (i = 0; i < totalFilmes; i++) {
        if (filmes[i].id == idFilme) {
            filmes[i].quantidade = filmes[i].quantidade + variacao;
            if (filmes[i].quantidade < 0) {
                filmes[i].quantidade = 0;
            }
            salvarFilmesCSV();   
            return;
        }
    }
}

void salvarComprasCSV() {
    int i;
    FILE *arq = fopen("compras.csv", "w");
    if (arq == NULL) {
        printf("\n[ERRO] Nao foi possivel salvar o arquivo compras.csv!\n");
        return;
    }
    for (i = 0; i < totalCompras; i++) {
        fprintf(arq, "%d;%s;%s;%.2f;%d;%d\n",
                registroCompras[i].idCompra,
                registroCompras[i].descricao,
                registroCompras[i].fornecedor,
                registroCompras[i].custoCompra,
                registroCompras[i].quantidade,
                registroCompras[i].idFilme);
    }
    fclose(arq);
}

void criarArquivoInicialCompras() {
    FILE *arq = fopen("compras.csv", "w");
    if (arq == NULL) {
        return;
    }
    fprintf(arq, "1;Matrix (VHS);Video Atacado;25.50;5;1\n");
    fprintf(arq, "2;O Rei Leao (DVD);Locadora Fita Dourada;39.90;10;2\n");
    fprintf(arq, "3;Titanic (VHS);Video Atacado;22.00;8;3\n");
    fprintf(arq, "4;Toy Story (DVD);Distribuidora Cine Max;34.90;6;4\n");
    fprintf(arq, "5;Jurassic Park (VHS);Locadora Fita Dourada;27.80;4;5\n");
    fprintf(arq, "6;Shrek (DVD);Distribuidora Cine Max;36.50;7;6\n");
    fprintf(arq, "7;De Volta para o Futuro (DVD);Video Atacado;41.00;3;7\n");
    fprintf(arq, "8;Os Caca-Fantasmas (VHS);Locadora Fita Dourada;24.90;5;8\n");
    fclose(arq);
}

void carregarComprasCSV() {
    FILE *arq = fopen("compras.csv", "r");
    if (arq == NULL) {
        criarArquivoInicialCompras();
        arq = fopen("compras.csv", "r");
    }
    totalCompras = 0;
    if (arq == NULL) {
        return;
    }
    while (totalCompras < 50 &&
           fscanf(arq, "%d;%39[^;];%39[^;];%f;%d;%d\n",
                  &registroCompras[totalCompras].idCompra,
                  registroCompras[totalCompras].descricao,
                  registroCompras[totalCompras].fornecedor,
                  &registroCompras[totalCompras].custoCompra,
                  &registroCompras[totalCompras].quantidade,
                  &registroCompras[totalCompras].idFilme) == 6) {
        totalCompras++;
    }
    fclose(arq);
}

int posicaoCompra(int idCompra) {
    int i;
    for (i = 0; i < totalCompras; i++) {
        if (registroCompras[i].idCompra == idCompra) {
            return i;
        }
    }
    return -1;
}

void imprimirCompra(int i) {
    printf("Compra %d | %s | Fornecedor: %s | Filme ID: %d | Qtd: %d | Unidade: R$ %.2f | Total: R$ %.2f\n",
           registroCompras[i].idCompra,
           registroCompras[i].descricao,
           registroCompras[i].fornecedor,
           registroCompras[i].idFilme,
           registroCompras[i].quantidade,
           registroCompras[i].custoCompra,
           registroCompras[i].custoCompra * registroCompras[i].quantidade);
}

void cadastrarCompra() {
    struct CompraMidia c;

    printf("\n--- Registrar Compra de Midias ---\n");
    if (totalCompras >= 50) {
        printf("[ERRO] Limite de 50 compras atingido!\n");
        return;
    }

    if (totalCompras == 0) {
        c.idCompra = 1;
    } else {
        c.idCompra = registroCompras[totalCompras - 1].idCompra + 1;
    }

    printf("ID do filme comprado (catalogo): ");
    c.idFilme = lerNumeroCompra();
    if (filmeExisteCompra(c.idFilme) == 0) {
        printf("[ERRO] Filme nao encontrado no catalogo!\n");
        return;
    }

    printf("Descricao da midia (ex.: Matrix (VHS)): ");
    lerTextoCompra(c.descricao);
    printf("Fornecedor: ");
    lerTextoCompra(c.fornecedor);
    printf("Custo de cada unidade (R$): ");
    c.custoCompra = lerDecimalCompra();
    printf("Quantidade comprada: ");
    c.quantidade = lerNumeroCompra();

    if (c.custoCompra <= 0 || c.quantidade <= 0) {
        printf("[ERRO] Custo e quantidade devem ser maiores que zero!\n");
        return;
    }

    registroCompras[totalCompras] = c;
    totalCompras++;
    atualizarEstoqueCompra(c.idFilme, c.quantidade);
    salvarComprasCSV();

    printf("\n[OK] Compra %d registrada! Total: R$ %.2f\n", c.idCompra, c.custoCompra * c.quantidade);
    printf("Estoque do filme %d atualizado (+%d copias).\n", c.idFilme, c.quantidade);
}

void listarCompras() {
    int i;
    float totalGeral = 0;

    printf("\n--- Compras Registradas ---\n");
    if (totalCompras == 0) {
        printf("Nenhuma compra registrada.\n");
        return;
    }
    for (i = 0; i < totalCompras; i++) {
        imprimirCompra(i);
        totalGeral = totalGeral + registroCompras[i].custoCompra * registroCompras[i].quantidade;
    }
    printf("Total geral das compras: R$ %.2f\n", totalGeral);
}

void buscarCompras() {
    char termo[40];
    int i;
    int achou = 0;

    printf("\n--- Buscar Compra ---\n");
    printf("Digite parte da descricao ou do fornecedor: ");
    lerTextoCompra(termo);

    for (i = 0; i < totalCompras; i++) {
        if (strstr(registroCompras[i].descricao, termo) != NULL ||
            strstr(registroCompras[i].fornecedor, termo) != NULL) {
            imprimirCompra(i);
            achou = 1;
        }
    }
    if (achou == 0) {
        printf("Nenhuma compra encontrada para '%s'.\n", termo);
    }
}

void editarCompra() {
    int id;
    int pos;
    int novaQuantidade;
    float novoCusto;
    char novoFornecedor[40];

    printf("\n--- Editar Compra ---\n");
    printf("ID da compra: ");
    id = lerNumeroCompra();
    pos = posicaoCompra(id);
    if (pos == -1) {
        printf("[ERRO] Compra nao encontrada!\n");
        return;
    }
    imprimirCompra(pos);

    printf("\nNovo fornecedor: ");
    lerTextoCompra(novoFornecedor);
    printf("Novo custo de cada unidade (R$): ");
    novoCusto = lerDecimalCompra();
    printf("Nova quantidade: ");
    novaQuantidade = lerNumeroCompra();

    if (novoCusto <= 0 || novaQuantidade <= 0) {
        printf("[ERRO] Custo e quantidade devem ser maiores que zero!\n");
        return;
    }

    atualizarEstoqueCompra(registroCompras[pos].idFilme, novaQuantidade - registroCompras[pos].quantidade);
    strcpy(registroCompras[pos].fornecedor, novoFornecedor);
    registroCompras[pos].custoCompra = novoCusto;
    registroCompras[pos].quantidade = novaQuantidade;
    salvarComprasCSV();

    printf("\n[OK] Compra %d atualizada e arquivo salvo!\n", id);
}

void removerCompra() {
    int id;
    int pos;
    int i;

    printf("\n--- Remover Compra ---\n");
    printf("ID da compra: ");
    id = lerNumeroCompra();
    pos = posicaoCompra(id);
    if (pos == -1) {
        printf("[ERRO] Compra nao encontrada!\n");
        return;
    }

    atualizarEstoqueCompra(registroCompras[pos].idFilme, -registroCompras[pos].quantidade);
    for (i = pos; i < totalCompras - 1; i++) {
        registroCompras[i] = registroCompras[i + 1];
    }
    totalCompras--;
    salvarComprasCSV();

    printf("\n[OK] Compra %d removida e arquivo atualizado!\n", id);
}

void relatorioFornecedores() {
    char nomes[50][40];
    float matriz[50][2];
    char nomeAux[40];
    float aux;
    int totalForn = 0;
    int i, j, achou;

    printf("\n--- Ranking de Fornecedores (maior gasto primeiro) ---\n");
    if (totalCompras == 0) {
        printf("Nenhuma compra registrada.\n");
        return;
    }

    for (i = 0; i < totalCompras; i++) {
        achou = -1;
        for (j = 0; j < totalForn; j++) {
            if (strcmp(nomes[j], registroCompras[i].fornecedor) == 0) {
                achou = j;
            }
        }
        if (achou == -1) {
            strcpy(nomes[totalForn], registroCompras[i].fornecedor);
            matriz[totalForn][0] = 0;
            matriz[totalForn][1] = 0;
            achou = totalForn;
            totalForn++;
        }
        matriz[achou][0] = matriz[achou][0] + registroCompras[i].quantidade;
        matriz[achou][1] = matriz[achou][1] + registroCompras[i].custoCompra * registroCompras[i].quantidade;
    }

    for (i = 0; i < totalForn - 1; i++) {
        for (j = 0; j < totalForn - 1 - i; j++) {
            if (matriz[j][1] < matriz[j + 1][1]) {
                aux = matriz[j][0];
                matriz[j][0] = matriz[j + 1][0];
                matriz[j + 1][0] = aux;

                aux = matriz[j][1];
                matriz[j][1] = matriz[j + 1][1];
                matriz[j + 1][1] = aux;

                strcpy(nomeAux, nomes[j]);
                strcpy(nomes[j], nomes[j + 1]);
                strcpy(nomes[j + 1], nomeAux);
            }
        }
    }

    for (i = 0; i < totalForn; i++) {
        printf("%d. %s | Midias compradas: %.0f | Total gasto: R$ %.2f\n",
               i + 1, nomes[i], matriz[i][0], matriz[i][1]);
    }
}

// MODULO 3: COMPRA DE MIDIAS E FORNECEDORES
// Autor: Integrante C - JAISON ALAN - RGM 04762834-1

void moduloCompras() {
    int opcaoCompra;
    do {
        limparTela();
        printf("\n--- [MODULO 3: COMPRAS DE MIDIAS / FORNECEDORES (Integrante C)] ---\n");
        printf("1. Registrar Compra de Midias\n");
        printf("2. Listar Compras Realizadas\n");
        printf("3. Buscar Compra (descricao ou fornecedor)\n");
        printf("4. Editar Compra\n");
        printf("5. Remover Compra\n");
        printf("6. [RELATORIO] Ranking de Fornecedores\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        opcaoCompra = lerNumeroCompra();

        limparTela();
        switch (opcaoCompra) {
            case 1:
                cadastrarCompra();
                break;
            case 2:
                listarCompras();
                break;
            case 3:
                buscarCompras();
                break;
            case 4:
                editarCompra();
                break;
            case 5:
                removerCompra();
                break;
            case 6:
                relatorioFornecedores();
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida no Modulo de Compras!\n");
        }
        if (opcaoCompra != 0) {
            pausarCompra();
        }
    } while (opcaoCompra != 0);
}
