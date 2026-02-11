#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char tipo;
    int id;
} Peca;

#define TAM_FILA 5

typedef struct {
    Peca itens[TAM_FILA];
    int inicio;
    int fim;
    int total;
} FilaPecas;

void inicializarFila(FilaPecas *fila) {
    fila->inicio = 0;
    fila->fim = 0;
    fila->total = 0;
}

int filaCheia(FilaPecas *fila) {
    return fila->total == TAM_FILA;
}

int filaVazia(FilaPecas *fila) {
    return fila->total == 0;
}

Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;

    nova.tipo = tipos[rand() % 4];
    nova.id = id;

    return nova;
}

void inserirPeca(FilaPecas *fila, Peca peca) {
    if (filaCheia(fila)) {
        printf("Fila cheia! Não é possível inserir nova peça.\n");
        return;
    }

    fila->itens[fila->fim] = peca;
    fila->fim = (fila->fim + 1) % TAM_FILA;
    fila->total++;
}

void jogarPeca(FilaPecas *fila) {
    if (filaVazia(fila)) {
        printf("Fila vazia! Nenhuma peça para jogar.\n");
        return;
    }

    Peca jogada = fila->itens[fila->inicio];
    printf("Peça jogada: [%c %d]\n", jogada.tipo, jogada.id);

    fila->inicio = (fila->inicio + 1) % TAM_FILA;
    fila->total--;
}

void mostrarFila(FilaPecas *fila) {
    printf("\nFila de peças:\n");

    if (filaVazia(fila)) {
        printf("Fila vazia.\n");
        return;
    }

    for (int i = 0, idx = fila->inicio; i < fila->total; i++) {
        printf("[%c %d] ", fila->itens[idx].tipo, fila->itens[idx].id);
        idx = (idx + 1) % TAM_FILA;
    }
    printf("\n");
}

int main() {
    FilaPecas fila;
    int opcao;
    int contadorId = 0;

    inicializarFila(&fila);

    // Inicializa a fila com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        inserirPeca(&fila, gerarPeca(contadorId++));
    }

    do {
        mostrarFila(&fila);

        printf("\nOpções:\n");
        printf("1 - Jogar peça\n");
        printf("2 - Inserir nova peça\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                jogarPeca(&fila);
                break;

            case 2:
                inserirPeca(&fila, gerarPeca(contadorId++));
                break;

            case 0:
                printf("Encerrando o jogo...\n");
                break;

            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}