#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

// ---------- ESTRUTURA DA PEÇA ----------
typedef struct {
    char tipo; // I, O, T, L
    int id;
} Peca;

// ---------- FILA CIRCULAR ----------
typedef struct {
    Peca itens[TAM_FILA];
    int inicio;
    int fim;
    int total;
} FilaPecas;

// ---------- PILHA ----------
typedef struct {
    Peca itens[TAM_PILHA];
    int topo;
} PilhaReserva;

// ---------- GERADOR ----------
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.tipo = tipos[rand() % 4];
    p.id = id;
    return p;
}

// ---------- FILA ----------
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

Peca acessarFila(FilaPecas *f, int posicao) {
    int indice = (f->inicio + posicao) % TAM_FILA;
    return f->itens[indice];
}

void substituirFila(FilaPecas *f, int posicao, Peca p) {
    int indice = (f->inicio + posicao) % TAM_FILA;
    f->itens[indice] = p;
}

// ---------- PILHA ----------
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
    p->topo++;
    p->itens[p->topo] = nova;
}

Peca pop(PilhaReserva *p) {
    Peca removida = p->itens[p->topo];
    p->topo--;
    return removida;
}

// ---------- EXIBIÇÃO ----------
void mostrarEstado(FilaPecas *fila, PilhaReserva *pilha) {
    printf("\nFila de peças: ");
    for (int i = 0; i < fila->total; i++) {
        Peca p = acessarFila(fila, i);
        printf("[%c %d] ", p.tipo, p.id);
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

// ---------- MAIN ----------
int main() {
    srand(time(NULL));

    FilaPecas fila;
    PilhaReserva pilha;
    int opcao;
    int idAtual = 0;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    // Fila inicial cheia
    for (int i = 0; i < TAM_FILA; i++) {
        inserirNaFila(&fila, gerarPeca(idAtual++));
    }

    do {
        mostrarEstado(&fila, &pilha);

        printf("\n1 - Jogar peça da fila");
        printf("\n2 - Enviar peça da fila para reserva");
        printf("\n3 - Usar peça da reserva");
        printf("\n4 - Trocar peça da frente com topo da pilha");
        printf("\n5 - Trocar 3 primeiras da fila com as 3 da pilha");
        printf("\n0 - Sair");
        printf("\nOpcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            Peca jogada = removerDaFila(&fila);
            printf("Peça jogada: [%c %d]\n", jogada.tipo, jogada.id);
            inserirNaFila(&fila, gerarPeca(idAtual++));
        }

        else if (opcao == 2) {
            if (pilhaCheia(&pilha)) {
                printf("Reserva cheia!\n");
            } else {
                Peca p = removerDaFila(&fila);
                push(&pilha, p);
                inserirNaFila(&fila, gerarPeca(idAtual++));
            }
        }

        else if (opcao == 3) {
            if (pilhaVazia(&pilha)) {
                printf("Reserva vazia!\n");
            } else {
                Peca usada = pop(&pilha);
                printf("Peça usada da reserva: [%c %d]\n", usada.tipo, usada.id);
            }
        }

        else if (opcao == 4) {
            if (!pilhaVazia(&pilha)) {
                Peca frenteFila = acessarFila(&fila, 0);
                Peca topoPilha = pop(&pilha);

                substituirFila(&fila, 0, topoPilha);
                push(&pilha, frenteFila);

                printf("Troca simples realizada.\n");
            } else {
                printf("Pilha vazia, troca impossível.\n");
            }
        }

        else if (opcao == 5) {
            if (fila.total >= 3 && pilha.topo >= 2) {
                for (int i = 0; i < 3; i++) {
                    Peca tempFila = acessarFila(&fila, i);
                    Peca tempPilha = pilha.itens[pilha.topo - i];

                    substituirFila(&fila, i, tempPilha);
                    pilha.itens[pilha.topo - i] = tempFila;
                }
                printf("Troca múltipla realizada.\n");
            } else {
                printf("Troca múltipla impossível.\n");
            }
        }

    } while (opcao != 0);

    return 0;
}
