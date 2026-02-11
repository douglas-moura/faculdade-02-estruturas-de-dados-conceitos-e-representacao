#include <stdio.h>
#include <stdlib.h>

#define MAX 5

// Estrutura do elemento
typedef struct {
    char nome[30];
    int idade;
} Pessoa;

// Estrutura da pilha
typedef struct {
    Pessoa itens[MAX];
    int topo;
} Pilha;

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == MAX - 1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

void push(Pilha *p, Pessoa nova) {
    if (pilhaCheia(p)) {
        printf("Pilha cheia, Não é possivel inserir.\n");
        return;
    }
    
    // aumenta a pilha
    p->topo++;
    // insere nova pessoa
    p->itens[p->topo] = nova;
}

void pop(Pilha *p, Pessoa *removida) {
    if (pilhaVazia(p)) {
        printf("Pilha vazia, Não é possivel remover.\n");
        return;
    }
    
    // coloca a pessao removida no elemento removida
    *removida = p->itens[p->topo];
    // diminui a pilha
    p->topo--;
}

void peek(Pilha *p, Pessoa *visualizada) {
    if (pilhaVazia(p)) {
        printf("Pilha vazia, Nada para espiar.\n");
        return;
    }
    
    // coloca a pessao visualizada no elemento visualizada
    *visualizada = p->itens[p->topo];
}

void mostrarPilha(Pilha *p) {
    printf("Pilha (topo -> base):\n");
    for (int i = p->topo; i >= 0; i--) {
        printf("[%s, %d]\n", p->itens[i].nome, p->itens[i].idade);
    }
    printf("\n");
}

int main() {

    Pilha p;
    // piha iniciaada com valor -1 (vazia)
    inicializarPilha(&p);

    Pessoa a = {"Ana", 20};
    Pessoa b = {"Bruno", 35};
    Pessoa c = {"Carlos", 28};

    push(&p, a);
    push(&p, b);
    push(&p, c);

    mostrarPilha(&p);

    Pessoa removida;
    pop(&p, &removida);
    printf("Removida: %s, %d\n", removida.nome, removida.idade);
    
    pop(&p, &removida);
    printf("Removida: %s, %d\n", removida.nome, removida.idade);

    mostrarPilha(&p);

    Pessoa topo;
    peek(&p, &topo);
    printf("Topo atual: %s, %d\n", topo.nome, topo.idade);

    return 0;
}