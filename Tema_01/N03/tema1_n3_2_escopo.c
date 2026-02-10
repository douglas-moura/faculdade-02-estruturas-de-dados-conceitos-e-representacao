// ESCOPO LOCAL
void minhaFuncao() {
    int x = 10;
    printf("Dentro da função, x = %d\n", x);
}

// ESCOPO GLOBAL
int contador_global = 0;

void incrementar() {
    contador_global++;
}

// ESCOPO GLOBAL E LOCAL
#include <stdio.h>

int global = 10;

void mostrarGlobal() {
    printf("Na função mostrarGlobal: %d\n", global);
    // ERRO
    //printf("%d", local);
}

int main() {
    int local = 5;

    printf("na função main (local): %d\n", local);
    printf("na função main (global): %d\n", global);

    mostrarGlobal();

    return 0;
}