int buscaBinariaRecursiva(int vetor[], int inicio, int fim, int valor) {
    if (inicio > fim) {
        return -1;
    }

    int meio = inicio + (fim - inicio) / 2;

    if (vetor[meio] == valor) {
        return meio;
    }

    else if (vetor[meio] < valor) {
        return buscaBinariaRecursiva(vetor, meio + 1, fim, valor);
    }

    else {
        return buscaBinariaRecursiva(vetor, inicio, meio - 1, valor);
    }
}

// o que é estouro de pilha?