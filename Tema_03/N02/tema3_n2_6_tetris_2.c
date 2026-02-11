#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

typedef struct {
    char tipo;
    int id;
} Peca;

typedef struct {
    Peca itens[TAM_FILA];
    int inicio;
    int fim;
    int total;
} FilaPecas;

typedef struct {
    Peca itens[TAM_PILHA];
    int topo;
} PilhaReserva;

Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.tipo = tipos[rand() % 4];
    p.id = id;
    return p;
}

void inicializarFila(FilaPecas *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

void inserirNaFila(FilaPecas *f, Peca p) {
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->total++;
}

Peca removerDaFila(FilaPecas *f) {
    Peca removida = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->total--;
    return removida;
}

void inicializarPilha(PilhaReserva *p) {
    p->topo = -1;
}

int pilhaCheia(PilhaReserva *p) {
    return p->topo == TAM_PILHA - 1;
}

int pilhaVazia(PilhaReserva *p) {
    return p->topo == -1;
}

void push(PilhaReserva *p, Peca nova) {
    if (pilhaCheia(p)) {
        printf("Pilha de reserva cheia!\n");
        return;
    }
    p->topo++;
    p->itens[p->topo] = nova;
}

Peca pop(PilhaReserva *p) {
    Peca removida = p->itens[p->topo];
    p->topo--;
    return removida;
}

void mostrarEstado(FilaPecas *fila, PilhaReserva *pilha) {
    printf("\nFila de peças: ");
    for (int i = 0, idx = fila->inicio; i < fila->total; i++, idx = (idx + 1) % TAM_FILA) {
        printf("[%c %d] ", fila->itens[idx].tipo, fila->itens[idx].id);
    }

    printf("\nPilha de reserva (Topo -> Base): ");
    if (pilhaVazia(pilha)) {
        printf("vazia");
    } else {
        for (int i = pilha->topo; i >= 0; i--) {
            printf("[%c %d] ", pilha->itens[i].tipo, pilha->itens[i].id);
        }
    }
    printf("\n");
}

int main() {
    srand(time(NULL));

    FilaPecas fila;
    PilhaReserva pilha;
    int opcao;
    int contadorId = 0;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    for (int i = 0; i < TAM_FILA; i++) {
        inserirNaFila(&fila, gerarPeca(contadorId++));
    }

    do {
        mostrarEstado(&fila, &pilha);

        printf("\n1 - Jogar peça");
        printf("\n2 - Reservar peça");
        printf("\n3 - Usar peça reservada");
        printf("\n0 - Sair");
        printf("\nOpcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            Peca jogada = removerDaFila(&fila);
            printf("Peça jogada: [%c %d]\n", jogada.tipo, jogada.id);
            inserirNaFila(&fila, gerarPeca(contadorId++));
        }
        else if (opcao == 2) {
            if (pilhaCheia(&pilha)) {
                printf("Reserva cheia! Não foi possível reservar.\n");
            } else {
                Peca reservada = removerDaFila(&fila);
                push(&pilha, reservada);
                inserirNaFila(&fila, gerarPeca(contadorId++));
            }
        }
        else if (opcao == 3) {
            if (pilhaVazia(&pilha)) {
                printf("Reserva vazia!\n");
            } else {
                Peca usada = pop(&pilha);
                printf("Peça reservada usada: [%c %d]\n", usada.tipo, usada.id);
            }
        }

    } while (opcao != 0);

    return 0;
}