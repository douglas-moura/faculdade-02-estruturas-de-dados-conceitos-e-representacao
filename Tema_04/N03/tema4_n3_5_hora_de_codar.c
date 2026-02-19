#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_TABELA 10

typedef struct Nodo {
    char valor[50];
    struct Nodo* proximo;
} Nodo;

Nodo* tabela_chaining[TAMANHO_TABELA];

int funcao_hash(const char* chave) {
    int soma = 0;
    
    for (int i = 0; chave[i] != '\0'; i++) {
        soma += chave[i];
    }

    return soma % TAMANHO_TABELA;
}

void inserir_chainig(Nodo* tabela[], const char* valor) {
    int indice = funcao_hash(valor);
    
    Nodo* novo = (Nodo*)malloc(sizeof(Nodo));
    
    strcpy(novo->valor, valor);
    novo->proximo = tabela_chaining[indice];
    tabela_chaining[indice] = novo;
}

Nodo* buscar_chaining(Nodo* tabela[], const char* chave) {
    int indice = funcao_hash(chave);
    
    Nodo* atual = tabela_chaining[indice];
    
    while (atual != NULL) {
        if (strcmp(atual->valor, chave) == 0) {
            return atual;
        }
        atual = atual->proximo;
    }
    
    return NULL;
}

void remover_chaining(const char* chave) {
    int indice = funcao_hash(chave);
    
    Nodo* atual = tabela_chaining[indice];
    Nodo* anterior = NULL;
    
    while (atual != NULL) {
        if (strcmp(atual->valor, chave) == 0) {
            if (anterior == NULL) {
                tabela_chaining[indice] = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            printf("'%s' removido (chaining).\n", chave);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("'%s' não encontrado para remoção (chaining).\n", chave);
}

void mostrar_chaining() {
    printf("Tabela de Hash (Chaining):\n");
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        printf("[%d]: ", i);
        Nodo* atual = tabela_chaining[i];
        while (atual != NULL) {
            printf("%s -> ", atual->valor);
            atual = atual->proximo;
        }
        printf("NULL\n");
    }
}

typedef struct {
    char valor[50];
    int ocupado;
} Entrada;

Entrada tabela_linear[TAMANHO_TABELA];

void inserir_linear(Entrada tabela[], const char* valor) {
    int indice = funcao_hash(valor);
    
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        int pos = (indice + i) % TAMANHO_TABELA;
        
        // Aqui nem deu pra verv o resto do código no video...
        if (tabela[pos].ocupado == 0 || tabela_linear[pos].ocupado == 1) {
            strcpy(tabela[pos].valor, valor);
            tabela[pos].ocupado = 1;
            return;
        }
    }
    
    strcpy(tabela[indice].valor, valor);
    tabela[indice].ocupado = 1;
}

int buscar_linear(const char* valor) {
    int indice = funcao_hash(valor);
    
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        int pos = (indice + i) % TAMANHO_TABELA;
        
        if (tabela_linear[pos].ocupado == 0) {
            return -1; // Não encontrado
        }
        
        if (tabela_linear[pos].ocupado == 1 && strcmp(tabela_linear[pos].valor, valor) == 0) {
            return pos; // Encontrado
        }
    }
    
    return -1; // Não encontrado
}

void remover_linear(const char* valor) {
    int pos = buscar_linear(valor);
    if (pos == -1) {
        printf("'%s' não encontrado para remoção (linear).\n", valor);
        return;
    }
    tabela_linear[pos].ocupado = -1;
    printf("'%s' removido (linear).\n", valor);
}

void mostrar_linear() {
    printf("Tabela de Hash (Linear Probing):\n");
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        printf("[%d]: ", i);
        if (tabela_linear[i].ocupado == 1) {
            printf("%s\n", tabela_linear[i].valor);
        } else if (tabela_linear[i].ocupado == -1) {
            printf("REMOVIDO\n");
        } else {
            printf("[%d]: LIVRE\n", i);
        }
    }
}

int main() {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        tabela_chaining[i] = NULL;
        tabela_linear[i].ocupado = 0;
    }

    const char* palavras[] = {
        "Ana", "Bruno", "Carlos", "Amanda", "Paulo", "Lucas", "Marina", "Joana", "Roberta", "Clara", "Daniel"
    };
    
    int n = sizeof(palavras) / sizeof(palavras[0]);

    for (int i = 0; i < n; i++) {
        inserir_chainig(tabela_chaining, palavras[i]);
        inserir_linear(tabela_linear, palavras[i]);
    }

    mostrar_chaining();
    mostrar_linear();

    printf("\nBuscando 'Bruno' (chaining): %s\n", buscar_chaining(tabela_chaining, "Bruno") ? "Encontrado" : "Não encontrado");
    printf("Buscando 'Joana' (linear): %s\n", buscar_linear("Joana") != -1 ? "Encontrado" : "Não encontrado");
    printf("Buscando 'Zeca' (chaining): %s\n", buscar_chaining(tabela_chaining, "Zeca") ? "Encontrado" : "Não encontrado");

    remover_chaining("Carlos");
    remover_linear("Carlos");
    remover_chaining("Zeca");
    remover_linear("Zeca");

    mostrar_chaining();
    mostrar_linear();

    for (int i = 0; i < TAMANHO_TABELA; i++) {
        Nodo* atual = tabela_chaining[i];
        while (atual != NULL) {
            Nodo* temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }

    return 0;
}