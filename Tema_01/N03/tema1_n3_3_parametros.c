#include <stdio.h>

void dobrar(int x) {
    x = x * 2;
    printf("Dentro da função, o valor da cóia é %d\n", x);
}

int main() {
    int numero = 5;
    printf("Andes de chamar a função, o valor original é: %d\n", numero);
    dobrar(numero);
    printf("Depois de chamar a função, o valor original é: %d\n", numero);
    return 0;
}