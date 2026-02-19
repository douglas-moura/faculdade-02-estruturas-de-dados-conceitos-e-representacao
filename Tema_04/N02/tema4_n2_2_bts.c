#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char valor[50];         // valor armazenado no nó
    struct No* esquerda;    // Ponteiro para o filho esquerdo
    struct No* direita;     // Ponteiro para o filho direito
} No;

int buscar(No* raiz, const char* valor) {
    if (raiz == NULL) {
        return 0; // Valor não encontrado
    }

    if (strcmp(valor, raiz->valor) == 0) {
        return 1; // Valor encontrado
    } else if (strcmp(valor, raiz->valor) < 0) {
        return buscar(raiz->esquerda, valor); // Busca na subárvore esquerda
    } else {
        return buscar(raiz->direita, valor); // Busca na subárvore direita
    }
}