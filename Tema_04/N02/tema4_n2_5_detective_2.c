#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Sala {
    char nome[50];
    char pista[100];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

typedef struct NoBST {
    char pista[100];
    struct NoBST* esquerda;
    struct NoBST* direita;
} NoBST;

Sala* criarSala(const char* nome, const char* pista) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    if (pista != NULL)
        strcpy(nova->pista, pista);
    else
        nova->pista[0] = '\0';
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

Sala* inserirNovaSala(Sala* raiz, const char* nome) {
    if (raiz == NULL)
        return criarSala(nome, NULL);

    if (strcmp(nome, raiz->nome) < 0)
        raiz->esquerda = inserirNovaSala(raiz->esquerda, nome);
    else
        raiz->direita = inserirNovaSala(raiz->direita, nome);

    return raiz;
}

NoBST* inserir(NoBST* raiz, const char* pista) {
    if (raiz == NULL) {
        NoBST* novo = (NoBST*)malloc(sizeof(NoBST));
        strcpy(novo->pista, pista);
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }

    if (strcmp(pista, raiz->pista) < 0)
        raiz->esquerda = inserir(raiz->esquerda, pista);
    else
        raiz->direita = inserir(raiz->direita, pista);

    return raiz;
}

void explorar(Sala* raiz, NoBST** pistas) {
    Sala* atual = raiz;
    char opcao;

    while (atual != NULL) {

        printf("\nVocê está em: %s\n", atual->nome);

        if (strlen(atual->pista) > 0) {
            printf("Pista encontrada: %s\n", atual->pista);
            *pistas = inserir(*pistas, atual->pista);
            atual->pista[0] = '\0';
        }

        printf("e - esquerda | d - direita | s - sair: ");
        scanf(" %c", &opcao);

        if (opcao == 'e') {
            if (atual->esquerda != NULL)
                atual = atual->esquerda;
            else
                printf("Não existe sala à esquerda!\n");
        }
        else if (opcao == 'd') {
            if (atual->direita != NULL)
                atual = atual->direita;
            else
                printf("Não existe sala à direita!\n");
        }
        else if (opcao == 's') {
            break;
        }
        else {
            printf("Opção inválida!\n");
        }
    }
}

int main() {
    Sala* raiz = NULL;
    NoBST* pistas = NULL;

    raiz = inserirNovaSala(raiz, "Hall de Entrada");
    raiz = inserirNovaSala(raiz, "Sala de Estar");
    raiz = inserirNovaSala(raiz, "Biblioteca");
    raiz = inserirNovaSala(raiz, "Quarto");

    explorar(raiz, &pistas);

    return 0;
}