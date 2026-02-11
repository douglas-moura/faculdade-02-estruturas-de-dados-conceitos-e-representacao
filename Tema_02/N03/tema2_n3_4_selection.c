// Poucas trocas, muitas comparações
void selectionSort(int vetor[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        int indiceMenor = i;

        for (int j = i + 1; j < tamanho; j++) {
            if (vetor[j] < vetor[indiceMenor]) {
                indiceMenor = j;
            }
        }

        if (indiceMenor != i) {
            trocar(&vetor[i], &vetor[indiceMenor]);
        }
    }
}