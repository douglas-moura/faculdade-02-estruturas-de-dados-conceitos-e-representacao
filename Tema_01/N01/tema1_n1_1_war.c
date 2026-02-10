#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TERRITORIOS 5
#define MAX_NOME_TERRITORIO 50
#define MAX_COR_TERRITORIO 20

struct Territorio {
    char nome[MAX_NOME_TERRITORIO];
    char cor[MAX_COR_TERRITORIO];
    int tropas;
};

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    struct Territorio territorio[MAX_TERRITORIOS];
    int totalTerritorios = 0;

    printf("Vamos cadastrar os 5 territórios inciais do nosso mundo.\n");
    
    do {
        if (totalTerritorios >= MAX_TERRITORIOS) {
            printf("Número máximo de territórios atingido.\n");
            break;
        } else {
            printf("-- Cadastrando Territorio ---\n");
            
            printf("Nome do Território: ");
            fgets(territorio[totalTerritorios].nome, MAX_NOME_TERRITORIO, stdin);
            
            printf("Cor do Exército: ");
            fgets(territorio[totalTerritorios].cor, MAX_COR_TERRITORIO, stdin);

            printf("Número de tropas: ");
            scanf("%d", &territorio[totalTerritorios].tropas);
            limparBufferEntrada(); // Limpa o buffer de entrada para evitar problemas com fgets

            territorio[totalTerritorios].nome[strcspn(territorio[totalTerritorios].nome, "\n")] = '\0'; // Remove o newline
            territorio[totalTerritorios].cor[strcspn(territorio[totalTerritorios].cor, "\n")] = '\0'; // Remove o newline

            totalTerritorios++;
        }
    } while (totalTerritorios < MAX_TERRITORIOS);

    printf("\n--- Territórios Cadastrados ---\n");
    printf("\n");

    for (int i = 0; i < totalTerritorios; i++) {
        printf("TERRITÓRIO %d: %s\n", i, territorio[i].nome);
        printf("Cor do Exército: %s\n", territorio[i].cor);
        printf("Número de Tropas: %d\n", territorio[i].tropas);
        printf("-----------------------------\n");
    }

    return 0;
}