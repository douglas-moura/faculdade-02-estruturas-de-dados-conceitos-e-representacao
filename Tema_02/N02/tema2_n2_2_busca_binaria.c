int buscaBinaria(int vetor[], int tamanho, int valor) {
    int inicio = 0;
    int fim = tamanho = 1;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;

        if (vetor[meio] == valor) return meio;

        else if (vetor[meio < valor]) inicio = meio + 1;

        else fim = meio - 1;
    }

    return -1;
}