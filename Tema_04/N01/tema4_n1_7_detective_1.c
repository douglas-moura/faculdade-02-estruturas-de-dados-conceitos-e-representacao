#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char valor[50];         // valor armazenado no nó
    struct Sala* esquerda;    // Ponteiro para o filho esquerdo
    struct Sala* direita;     // Ponteiro para o filho direito
} Sala;

Sala* criarSala(const char* valor) {
    Sala* novo = (Sala*) malloc(sizeof(Sala));

    if (novo == NULL) {
        printf("Erro ao alocar memória para o nó.\n");
        exit(1);
    }

    // Copia o valor para o campo do nó
    strcpy(novo->valor, valor);
    // Inicializa os ponteiros dos filhos como NULL
    novo->esquerda = NULL;
    novo->direita = NULL;

    return novo;
}

Sala* inserirNovaSala(Sala* raiz, const char* valor) {
    if (raiz == NULL) {
        return criarSala(valor);
    }

    // Compara o valor a ser inserido com o valor do nó atual (ordem lexicográfica)
    if (strcmp(valor, raiz->valor) < 0) {
        // Se o valor for menor, insere na subárvore esquerda
        raiz->esquerda = inserirNovaSala(raiz->esquerda, valor);
    } else if (strcmp(valor, raiz->valor) > 0) {
        // Se o valor for maior, insere na subárvore direita
        raiz->direita = inserirNovaSala(raiz->direita, valor);
    }

    return raiz;
}

void liberar(Sala* raiz) {
    if (raiz != NULL) {
        liberar(raiz->esquerda);    // Libera a subárvore esquerda
        liberar(raiz->direita);     // Libera a subárvore direita
        free(raiz);                 // Libera o nó atual
    }
}

void menu(char* localAtual) {
    printf("\nVocê está no %s.\n", localAtual);
    printf("Escolha um lado para investigar:\n");
    printf("1 - Esquerda\n");
    printf("2 - Direita\n");
    printf("0 - Sair\n");
    printf("Opcao: ");
}

int main() {
    // Raiz da árvore binária
    Sala* raiz = NULL;
    int opcao;
    
    // Inserção de valores na árvore
    raiz = inserirNovaSala(raiz, "Hall de Entrada");
    raiz = inserirNovaSala(raiz, "Sala de Estar");
    raiz = inserirNovaSala(raiz, "Biblioteca");
    raiz = inserirNovaSala(raiz, "Quarto");
    
    menu(raiz->valor);  // Exibe o menu para o local inicial (raiz)

    do {
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            if (raiz->esquerda != NULL) {
                raiz = raiz->esquerda;  // Move para o filho esquerdo
                menu(raiz->valor);  // Exibe o menu para o local atual
            } else {
                printf("Não há mais locais para investigar à esquerda.\n");
                opcao = 0; // Volta para o menu principal
            }
            break;
        case 2:
            if (raiz->direita != NULL) {
                raiz = raiz->direita;  // Move para o filho direito
                menu(raiz->valor);  // Exibe o menu para o local atual
            } else {
                printf("Não há mais locais para investigar à direita.\n");
                opcao = 0; // Volta para o menu principal
            }
            break;
        
        case 0:
            printf("Saindo do programa.\n");
            break;
        
        default:
            printf("opção inválida, tente novamente.\n");
            break;
        }
    } while (opcao != 0);

    liberar(raiz);  // Libera a memória alocada para a árvore

    return 0;
}