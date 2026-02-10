#include <stdio.h>

// malloc() - Memory Allocation
// calloc() - Clear Allocation
// free() - Liberação de memória

int main() {
    int *a, b;
    b = 10;
    a = (int*)  malloc(sizeof(int)); // Pedimos um espaço
    *a = 20;
    a = &b; // ERRO! Perdemos a referência do espaço alocado na linha 3
    free(a); // ERRO! Tentando liberar memóroia estática (10)

    // Entendi foi nada...

    return 0;
}