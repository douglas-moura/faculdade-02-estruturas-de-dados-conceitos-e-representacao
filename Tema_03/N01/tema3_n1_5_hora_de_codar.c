#include <stdio.h>
#include <stdlib.h>

// Estrutura do elemento
typedef struct {
    char nome[30];
    int idade;
} Pessoa;

#define MAX 5

// Estrutura da fila
typedef struct {
    Pessoa itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

// inicializando a fila, ou ponteiro, sei lá...
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int filaCheia(Fila *f) {
    return f->total == MAX;
}

int filaVazia(Fila *f) {
    return f->total == 0;
}

void inserir(Fila *f, Pessoa p) {
    if (filaCheia(f)) {
        printf("Fila cheia, Não é possivel inserir.\n");
        return;
    }

    f->itens[f->fim] = p;

    f->fim = (f->fim + 1) % MAX;

    f->total++;
}

void remover(Fila *f, Pessoa *p) {
    if (filaVazia(f)) {
        printf("Fila vazia, Não é possivel remover.\n");
        return;
    }

    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
}

void mostrarFila(Fila *f) {
    printf("Fila: ");
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
        printf("[%s, %d] ", f->itens[idx].nome, f->itens[idx].idade);
    }
    printf("\n");
}

int main() {
    // novo elemento fila criado sem dados com o struct Fila
    Fila f;

    // inciializa a fila
    inicializarFila(&f);

    // cria algumas pessoas com o struct Pessoa
    Pessoa p1 = {"João", 25};
    Pessoa p2 = {"Maria", 30};

    // inserindo as Pessoas na Fila
    inserir(&f, p1);
    inserir(&f, p2);

    mostrarFila(&f);

    // novo elemento criando sem dados com o struct Pessoa
    Pessoa removida;

    // remove pessoa da fila e coloca no elemento Pessoa que foi ccriado acima
    remover(&f, &removida);

    printf("Pessoa removida: %s, %d\n", removida.nome, removida.idade);

    mostrarFila(&f);

    return 0;
}