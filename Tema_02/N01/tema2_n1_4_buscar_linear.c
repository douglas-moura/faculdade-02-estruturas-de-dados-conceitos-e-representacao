#include <stddef.h>

struct No {
    int dado;
    struct No* proximo;
};

int buscaLiner(int lista[], int tamanho, int valor) {
    for (int i = 0; i < tamanho; i++) {
        if (lista[i] == valor) {
            return i;
        }
    }

    return -1;
}

int buscaLinerEncadeada(struct No* inicio, int valor) {
    int pos = 0;
    struct No* atual = inicio;

    while (atual != NULL) {
        if (atual->dado == valor) {
            return pos;
        }

        atual = atual->proximo;

        pos++;
    }

    return -1;
}