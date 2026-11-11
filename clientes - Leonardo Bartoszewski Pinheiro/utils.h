#ifndef UTILS_H
#define UTILS_H

// ============================================================================
// UTILS.H - Funcoes de apoio compartilhadas pelos modulos do grupo
// (#ifndef/#define/#endif = "guarda": evita incluir este arquivo duas vezes)
// ============================================================================
#include <stdio.h>
#include <stdlib.h>

// Limpa a tela do terminal (cls no Windows, clear no Linux)
void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Descarta o que sobrou digitado ate o ENTER (evita "lixo" no teclado)
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

// Le um numero inteiro. Se o usuario digitar letra, devolve -1.
int lerInteiro() {
    int valor;
    int lidos = scanf("%d", &valor); // scanf devolve quantos valores leu
    limparBuffer();
    if (lidos != 1) {
        return -1;
    }
    return valor;
}

// Le um numero com casas decimais. Se digitar letra, devolve -1.
float lerDecimal() {
    float valor;
    int lidos = scanf("%f", &valor);
    limparBuffer();
    if (lidos != 1) {
        return -1;
    }
    return valor;
}

// Espera o usuario apertar ENTER antes de limpar a tela
void pausar() {
    printf("\nPressione ENTER para continuar...");
    getchar();
}

#endif
