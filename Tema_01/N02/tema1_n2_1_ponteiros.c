#include <stdio.h>

int main() {
    // & - Obter o endereço
    // * - Declarar ponteiro e valor apontado
    
    int x = 10;
    int* p = &x; // O ponteiro 'p' recebe o endereço de 'x'

    printf("Valor de x: %d\n", x);
    printf("Endereço de x: %p\n", &x);
    printf("Conteúdo de p (o ponteiro): %p\n", p);
    printf("Valor apontado por p: %d\n", *p);

    *p = 20; // Modificando o valor através do ponteiro

    printf("Novo valor de x: %d\n", x);

    return 0;
}