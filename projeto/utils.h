#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int lerInteiro() {
    int valor;
    int lidos = scanf("%d", &valor); 
    limparBuffer();
    if (lidos != 1) {
        return -1;
    }
    return valor;
}

float lerDecimal() {
    float valor;
    int lidos = scanf("%f", &valor);
    limparBuffer();
    if (lidos != 1) {
        return -1;
    }
    return valor;
}

void pausar() {
    printf("\nPressione ENTER para continuar...");
    getchar();
}

#endif
