#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAMANHO_ALFABETO 26

typedef struct NoTrie {
    struct NoTrie* filhos[TAMANHO_ALFABETO];
    bool ehFimPalavra;
} NoTrie;

NoTrie* criarNo() {
    NoTrie* novoNo = (NoTrie*) malloc(sizeof(NoTrie));

    novoNo->ehFimPalavra = false;

    for (int i = 0; i < TAMANHO_ALFABETO; i++) {
        novoNo->filhos[i] = NULL;
    }

    return novoNo;
}

void inserirLetra(NoTrie* raiz, const char* palavra) {
    NoTrie* atual = raiz;

    for (int i = 0; palavra[i] != '\0'; i++) {
        int indice = palavra[i] - 'a';

        if (atual->filhos[indice] == NULL) {
            atual->filhos[indice] = criarNo();
        }

        atual = atual->filhos[indice];
    }

    atual->ehFimPalavra = true;
}

bool buscar(NoTrie* raiz, const char* palavra) {
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

void listarPalavras(NoTrie* raiz, char* buffer, int nivel) {
    if (raiz->ehFimPalavra) {
        buffer[nivel] = '\0';
        printf("%s\n", buffer);
    }

    for (int i = 0; i < TAMANHO_ALFABETO; i++) {
        if (raiz->filhos[i] != NULL) {
            buffer[nivel] = 'a' + i;
            listarPalavras(raiz->filhos[i], buffer, nivel + 1);
        }
    }
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

int main() {
    NoTrie* raiz = criarNo();
    char normalizada[100];
 
    normalizar("Pegadas de Lama", normalizada);
    inserirLetra(raiz, normalizada);
 
    normalizar("Chave perdida", normalizada);
    inserirLetra(raiz, normalizada);
 
    normalizar("Livro com página faltando", normalizada);
    inserirLetra(raiz, normalizada);
 
    normalizar("Lençol manchado", normalizada);
    inserirLetra(raiz, normalizada);
 
    normalizar("Gaveta perdida", normalizada);
    inserirLetra(raiz, normalizada);

    char buffer[100]; // Tamanho máximo de palavra suportado
    listarPalavras(raiz, buffer, 0);

    return 0;
}