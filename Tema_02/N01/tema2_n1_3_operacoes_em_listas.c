#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

struct No {
    int dado;
    struct No* proximo;
};

void inserirNoInicio(struct No** inicio, int valor) {
    /*
    malloc → cria memória
    sizeof → define o tamanho
    (struct No*) → diz o tipo do endereço
    novo → guarda o endereço
    */
    struct No* novo = (struct No*) malloc(sizeof(struct No));

    if (novo == NULL) {
        printf("Erro: Falha ao alocar memória.\n");
        return;
    }

    novo->dado = valor;

    novo->proximo = *inicio;

    *inicio = novo;
}

void removerDoInicio(struct No** inicio) {
    if (inicio == NULL || *inicio == NULL) {
        printf("A lista já esta vazia, Nada a remover.\n");
        return;
    }

    struct No* noParaRemover = *inicio;

    *inicio = (*inicio)->proximo;

    free(noParaRemover);
}

void listar(struct No* inicio) {
    struct No* atual = inicio;

    if (atual == NULL) {
        printf("A lista esta vazia.\n");
        return;
    }

    printf("Elementos da lista.\n");

    while (atual != NULL) {
        printf("%d\n", atual->dado);
        atual = atual->proximo;
    }
}

