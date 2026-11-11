// Matheus Souza dos Santos - RGM 47830824
#ifndef FILMES_H
#define FILMES_H

#include <stdio.h>
#include <string.h>

#define MAX_FILMES 50

void limparTela();

struct Filme {
    int id;
    char titulo[50];
    int ano;
    float preco;
    int quantidade;
};

struct Filme filmes[MAX_FILMES];
int totalFilmes = 0;

// Matheus Souza dos Santos - RGM 47830824
void salvarFilmesCSV() {
    FILE *arq = fopen("filmes.csv", "w");
    int i;
    if (arq == NULL) {
        printf("[ERRO] Nao foi possivel gravar filmes.csv!\n");
        return;
    }
    for (i = 0; i < totalFilmes; i++) {
        fprintf(arq, "%d;%s;%d;%.2f;%d\n", filmes[i].id, filmes[i].titulo,
                filmes[i].ano, filmes[i].preco, filmes[i].quantidade);
    }
    fclose(arq);
}

// Matheus Souza dos Santos - RGM 47830824
void carregarFilmesCSV() {
    FILE *arq = fopen("filmes.csv", "r");
    if (arq == NULL) return;
    totalFilmes = 0;
    while (totalFilmes < MAX_FILMES && fscanf(arq, "%d;%49[^;];%d;%f;%d\n",
           &filmes[totalFilmes].id,
           filmes[totalFilmes].titulo,
           &filmes[totalFilmes].ano,
           &filmes[totalFilmes].preco,
           &filmes[totalFilmes].quantidade) >= 4) {
        totalFilmes++;
    }
    fclose(arq);
}

// Matheus Souza dos Santos - RGM 47830824
int buscarIndiceFilme(int idProcurado) {
    int i;
    for (i = 0; i < totalFilmes; i++) {
        if (filmes[i].id == idProcurado) return i;
    }
    return -1;
}

// Matheus Souza dos Santos - RGM 47830824
void cadastrarFilme() {
    int id;
    if (totalFilmes >= MAX_FILMES) {
        printf("[ERRO] Catalogo lotado!\n");
        return;
    }
    printf("\nID do novo filme: ");
    scanf("%d", &id);
    if (buscarIndiceFilme(id) != -1) {
        printf("[ERRO] Ja existe um filme com o ID %d!\n", id);
        return;
    }
    filmes[totalFilmes].id = id;
    printf("Titulo: ");
    scanf(" %49[^\n]", filmes[totalFilmes].titulo);
    printf("Ano: ");
    scanf("%d", &filmes[totalFilmes].ano);
    printf("Preco da locacao (R$): ");
    scanf("%f", &filmes[totalFilmes].preco);
    printf("Fitas em estoque: ");
    scanf("%d", &filmes[totalFilmes].quantidade);
    totalFilmes++;
    salvarFilmesCSV();
    printf("[OK] Filme salvo em filmes.csv!\n");
}

// Matheus Souza dos Santos - RGM 47830824
void listarFilmes() {
    int i;
    printf("\n--- CATALOGO DE FILMES (%d itens) ---\n", totalFilmes);
    for (i = 0; i < totalFilmes; i++) {
        printf("ID: %d | %-28s | %d | R$ %.2f | Estoque: %d\n", filmes[i].id,
               filmes[i].titulo, filmes[i].ano, filmes[i].preco, filmes[i].quantidade);
    }
}

// Matheus Souza dos Santos - RGM 47830824
void buscarFilmePorTitulo() {
    char termo[50];
    int i, achou = 0;
    printf("\nDigite parte do titulo: ");
    scanf(" %49[^\n]", termo);
    for (i = 0; i < totalFilmes; i++) {
        if (strstr(filmes[i].titulo, termo) != NULL) {
            printf(" -> [%d] %s (%d) - R$ %.2f - Estoque: %d\n", filmes[i].id,
                   filmes[i].titulo, filmes[i].ano, filmes[i].preco, filmes[i].quantidade);
            achou = 1;
        }
    }
    if (achou == 0) printf("Nenhum filme encontrado.\n");
}

// Matheus Souza dos Santos - RGM 47830824
void editarFilme() {
    int id, pos;
    printf("\nID do filme a EDITAR: ");
    scanf("%d", &id);
    pos = buscarIndiceFilme(id);
    if (pos == -1) {
        printf("[ERRO] Filme nao encontrado!\n");
        return;
    }
    printf("Editando '%s'.\nNovo titulo: ", filmes[pos].titulo);
    scanf(" %49[^\n]", filmes[pos].titulo);
    printf("Novo ano: ");
    scanf("%d", &filmes[pos].ano);
    printf("Novo preco (R$): ");
    scanf("%f", &filmes[pos].preco);
    printf("Novo estoque: ");
    scanf("%d", &filmes[pos].quantidade);
    salvarFilmesCSV();
    printf("[OK] Filme atualizado na memoria e no CSV!\n");
}

// Matheus Souza dos Santos - RGM 47830824
void removerFilme() {
    int id, pos, j;
    printf("\nID do filme a REMOVER: ");
    scanf("%d", &id);
    pos = buscarIndiceFilme(id);
    if (pos == -1) {
        printf("[ERRO] Filme nao encontrado!\n");
        return;
    }
    for (j = pos; j < totalFilmes - 1; j++) {
        filmes[j] = filmes[j + 1];
    }
    totalFilmes--;
    salvarFilmesCSV();
    printf("[OK] Filme removido da memoria e do CSV!\n");
}

// Matheus Souza dos Santos - RGM 47830824
void moduloFilmes() {
    int opcao;
    limparTela();
    do {
        printf("\n--- MODULO: CATALOGO DE FILMES ---\n");
        printf("1. Cadastrar\n2. Listar\n3. Buscar por titulo\n4. Editar\n5. Remover\n0. Voltar\nOpcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: cadastrarFilme(); break;
            case 2: listarFilmes(); break;
            case 3: buscarFilmePorTitulo(); break;
            case 4: editarFilme(); break;
            case 5: removerFilme(); break;
            case 0: break;
            default: printf("[ERRO] Opcao invalida!\n");
        }
    } while (opcao != 0);
}

#endif
