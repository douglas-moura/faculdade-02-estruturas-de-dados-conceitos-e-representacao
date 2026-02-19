#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct NoBST {
    char valor[50];
    struct NoBST* esquerda;
    struct NoBST* direita;
} NoBST;

NoBST* criarNoBTS(const char* valor) {
    // aloca espaço para o novo nó
    NoBST* novo = (NoBST*) malloc(sizeof(NoBST));
    // inicializa os campos do nó com a string passada e ponteiros nulos
    strcpy(novo->valor, valor);
    novo->esquerda = NULL;
    novo->direita = NULL;
    // retorna o ponteiro para o novo nó criado
    return novo;
}

NoBST* inserir(NoBST* raiz, const char* valor) {
    if (raiz == NULL) return criarNoBTS(valor);
    if (strcmp(valor, raiz->valor) < 0) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    } else if (strcmp(valor, raiz->valor) > 0) {
        raiz->direita = inserir(raiz->direita, valor);
    }
}

bool buscarBST(NoBST* raiz, const char* chave) {
    if (raiz == NULL) return false;
    
    if (strcmp(chave, raiz->valor) == 0) {
        return true;
    }
    
    if (strcmp(chave, raiz->valor) < 0) {
        return buscarBST(raiz->esquerda, chave);
    } else {
        return buscarBST(raiz->direita, chave);
    }
}

void emOrdemBST(NoBST* raiz) {
    if (raiz != NULL) {
        emOrdemBST(raiz->esquerda);
        printf("%s ", raiz->valor);
        emOrdemBST(raiz->direita);
    }
}

void liberarBST(NoBST* raiz) {
    if (raiz != NULL) {
        liberarBST(raiz->esquerda);
        liberarBST(raiz->direita);
        free(raiz);
    }
}

#define TAMANHO_ALFABETO 26

typedef struct NoTrie {
    struct NoTrie* filhos[TAMANHO_ALFABETO];
    bool ehFimPalavra;
} NoTrie;

NoTrie* criarNoTrie() {
    NoTrie* novoNo = (NoTrie*) malloc(sizeof(NoTrie));

    novoNo->ehFimPalavra = false;

    for (int i = 0; i < TAMANHO_ALFABETO; i++) {
        novoNo->filhos[i] = NULL;
    }

    return novoNo;
}

void normalizar(const char* entrada, char* saida) {
    int j = 0;
    for (int i = 0; entrada[i] != '\0'; i++) {
        char c = entrada[i];
        if (c >= 'A' && c <= 'Z') c += 32; // Converte para minúsculo
        if (c >= 'a' && c <= 'z') saida[j++] = c; // Mantém apenas letras
    }
    saida[j] = '\0';
}

void inserirTrie(NoTrie* raiz, const char* palavra) {
    NoTrie* atual = raiz;

    for (int i = 0; palavra[i] != '\0'; i++) {
        int indice = palavra[i] - 'a';

        if (atual->filhos[indice] == NULL) {
            atual->filhos[indice] = criarNoTrie();
        }

        atual = atual->filhos[indice];
    }

    atual->ehFimPalavra = true;
}

bool buscarTrie(NoTrie* raiz, const char* palavra) {
    NoTrie* atual = raiz;

    for (int i = 0; palavra[i] != '\0'; i++) {
        int indice = palavra[i] - 'a';

        if (atual->filhos[indice] == NULL) {
            return false;
        }

        atual = atual->filhos[indice];
    }

    return atual != NULL && atual->ehFimPalavra;
}

void listarPalavrasTrie(NoTrie* raiz, char* buffer, int nivel) {
    if (raiz->ehFimPalavra) {
        buffer[nivel] = '\0';
        printf("%s\n", buffer);
    }

    for (int i = 0; i < TAMANHO_ALFABETO; i++) {
        if (raiz->filhos[i] != NULL) {
            buffer[nivel] = 'a' + i;
            listarPalavrasTrie(raiz->filhos[i], buffer, nivel + 1);
        }
    }
}

void liberarTrie(NoTrie* raiz) {
    if (raiz != NULL) {
        for (int i = 0; i < TAMANHO_ALFABETO; i++) {
            liberarTrie(raiz->filhos[i]);
        }
        free(raiz);
    }
}

int main() {
    printf("=== BTS ===\n");
    NoBST* raizBTS = NULL;
    raizBTS = inserir(raizBTS, "Pegadas de lama");
    raizBTS = inserir(raizBTS, "Chave perdida");
    raizBTS = inserir(raizBTS, "Livro com pagina faltando");
    raizBTS = inserir(raizBTS, "Lencol manchado");
    raizBTS = inserir(raizBTS, "Gaveta perdida");

    printf("Em ordem (BTS): ");
    emOrdemBST(raizBTS);
    printf("\nBusca por 'Lencol manchado' (BST): %s\n", buscarBST(raizBTS, "Lencol manchado") ? "Encontrado" : "Não encontrado");
    printf("Busca por 'Oculos' (BST): %s\n", buscarBST(raizBTS, "Oculos") ? "Encontrado" : "Não encontrado");
    
    printf("\n\n=== Trie ===\n");
    NoTrie* raizTrie = criarNoTrie();
    char normalizada[100];

    normalizar("Pegadas de Lama", normalizada);
    inserirTrie(raizTrie, normalizada);
    normalizar("Chave perdida", normalizada);
    inserirTrie(raizTrie, normalizada);
    normalizar("Livro com página faltando", normalizada);
    inserirTrie(raizTrie, normalizada);
    normalizar("Lencol manchado", normalizada);
    inserirTrie(raizTrie, normalizada);
    normalizar("Gaveta perdida", normalizada);
    inserirTrie(raizTrie, normalizada);

    printf("Palavras na Trie:\n");
    char buffer[100];

    listarPalavrasTrie(raizTrie, buffer, 0);
    printf("\n");
    normalizar("Lencol manchado", normalizada);
    printf("Busca por 'lencolmanchado' (Trie): %s\n", buscarTrie(raizTrie, normalizada) ? "Encontrado" : "Não encontrado");
    normalizar("Oculos", normalizada);
    printf("Busca por 'oculos' (Trie): %s\n", buscarTrie(raizTrie, normalizada) ? "Encontrado" : "Não encontrado");

    liberarBST(raizBTS);
    liberarTrie(raizTrie);

    return 0;
}