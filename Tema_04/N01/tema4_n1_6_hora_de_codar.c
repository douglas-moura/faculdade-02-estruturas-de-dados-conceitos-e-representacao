#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char valor[50];         // valor armazenado no nó
    struct No* esquerda;    // Ponteiro para o filho esquerdo
    struct No* direita;     // Ponteiro para o filho direito
} No;

No* criarNo(const char* valor) {
    No* novo = (No*) malloc(sizeof(No));

    if (novo == NULL) {
        printf("Erro ao alocar memória para o nó.\n");
        exit(1);
    }

    strcpy(novo->valor, valor);     // Copia o valor para o campo do nó
    // Inicializa os ponteiros dos filhos como NULL
    novo->esquerda = NULL;
    novo->direita = NULL;

    return novo;
}

No* inserir(No* raiz, const char* valor) {
    if (raiz == NULL) {
        return criarNo(valor);
    }

    // Compara o valor a ser inserido com o valor do nó atual
    if (strcmp(valor, raiz->valor) < 0) {
        // Se o valor for menor, insere na subárvore esquerda
        raiz->esquerda = inserir(raiz->esquerda, valor);
    } else if (strcmp(valor, raiz->valor) > 0) {
        // Se o valor for maior, insere na subárvore direita
        raiz->direita = inserir(raiz->direita, valor);
    }

    return raiz;
}

void preOrdem(No* raiz) {
    if (raiz != NULL) {
        printf("%s ", raiz->valor);  // Visita o nó atual
        preOrdem(raiz->esquerda);    // Visita a subárvore esquerda
        preOrdem(raiz->direita);     // Visita a subárvore direita
    }
}

void emOrdem(No* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);     // Visita a subárvore esquerda
        printf("%s ", raiz->valor);  // Visita o nó atual
        emOrdem(raiz->direita);     // Visita a subárvore direita
    }
}

void posOrdem(No* raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esquerda);   // Visita a subárvore esquerda
        posOrdem(raiz->direita);    // Visita a subárvore direita
        printf("%s ", raiz->valor);  // Visita o nó atual
    }
}

void liberar(No* raiz) {
    if (raiz != NULL) {
        liberar(raiz->esquerda);    // Libera a subárvore esquerda
        liberar(raiz->direita);     // Libera a subárvore direita
        free(raiz);                 // Libera o nó atual
    }
}

int main() {
    No* raiz = NULL;

    raiz = inserir(raiz, "Hall de Entrada");
    raiz = inserir(raiz, "Sala de Estar");
    raiz = inserir(raiz, "Biblioteca");
    raiz = inserir(raiz, "Quarto");

    printf("Percurso em pré-ordem: ");
    preOrdem(raiz);
    printf("\n");

    printf("\nPercurso em ordem: ");
    emOrdem(raiz);
    printf("\n");

    printf("\nPercurso em pós-ordem: ");
    posOrdem(raiz);
    printf("\n");

    liberar(raiz);  // Libera a memória alocada para a árvore

    return 0;
}