#include <stdio.h>

void dobrar(int* x) {
    *x = (*x) * 2;
}

int main() {
    int numero = 5;
    printf("Andes de chamar a função, o valor original é: %d\n", numero);
    dobrar(&numero);
    printf("Depois de chamar a função, o valor original é: %d\n", numero);
    return 0;
}