// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variaveis Globais
#define MAX_LIVROS 50
#define MAX_EMPRESTIMOS 100
#define TAM_STRING 100

// Estruturas
struct Livro {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
    int disponivel;
};

struct Emprestimo {
    int indiceLivro;;
    char nomeUsuario[TAM_STRING];
};

// Protótipos de funções
void limparBuffeEntrada();
void exibirMenu();
void cadastrarLivro(struct Livro *biblioteca, int *totalLivros);
void listarLivros(const struct Livro *biblioteca, int totalLivros);
void realizarEmprestimo(struct Livro *biblioteca, int totalLivros, struct Emprestimo *emprestimos); // Não deu pra ver o resto do código na videoaula, parametros faltando
void listarEmrpestimos(const struct Livro *biblioteca, const struct Emrpestimo *emprestimo); // Não deu pra ver o resto do código na videoaula, parametros faltando
void liberarMemoria(struct  Livro *biblioteca, struct Emprestimo *emprestimos);

// Funções

// Principal
int main() {
    struct Livro *biblioteca = (struct Livro *) calloc(MAX_LIVROS, sizeof(struct  Livro));
    struct Emprestimo *emprestimos = (struct Emprestimo *) malloc(MAX_EMPRESTIMOS * sizeof(struct Emprestimo)); // também não seu pra ver tudo na viadeo aula, mas acho q esta certo

    // Verificação
    if (biblioteca == NULL || emprestimos == NULL) {
        printf("Erro: Falha ao alocar memória.\n");
        return 1;
    }

    int totalLivros = 0;
    int totalEmprestimos = 0;
    int opcao;

    do {
        exibirMenu();
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                cadastrarLivro(biblioteca, &totalLivros);
                break;
            case 2:
                listarLivros(biblioteca, totalLivros);
                break;
            case 3:
                realizarEmprestimo(biblioteca, totalLivros, emprestimos, &totalEmprestimos);
                break;
            case 4:
                listarEmprestimos(biblioteca, emprestimos, totalEmprestimos);
                break;
            case 0:
                printf("\nSaindo do sistema...\n");
                break;
            default:
                printf("\nOPção invalida!\n");
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
        }
    } while (opcao != 0);

    liberarMemoria(biblioteca, emprestimos);

    return 0;
}

// Limpar o buffer
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void exibirMenu() {
    printf("================================\n");
    printf("--- BIBLIOTECA ---\n");
    printf("================================\n");
    printf("1 - Cadastrar novo livro\n");
    printf("2 - Listar todos os livros\n");
    printf("3 - Realizar emprestimo\n");
    printf("4 - Listar emprestimos\n");
    printf("0 - Sair\n");
    printf("--------------------------------\n");
    printf("Escolha uma opção: \n");
}

void cadastrarLivro(struct Livro *biblioteca, int *totalLivros) {
    printf("--- Cadastro de Novo Livro ---\n\n");

    if (*totalLivros < MAX_LIVROS) {
        int indice = *totalLivros;

        printf("Digite o nome do livro: ");
        fgets(biblioteca[indice].nome, TAM_STRING, stdin);

        printf("Digite o autor do livro: ");
        fgets(biblioteca[indice].autor, TAM_STRING, stdin);

        printf("Digite a editora: ");
        fgets(biblioteca[indice].editora, TAM_STRING, stdin);

        biblioteca[indice].nome[strcspn(biblioteca[indice].nome, "\n")] = '\0';
        biblioteca[indice].autor[strcspn(biblioteca[indice].autor, "\n")] = '\0';
        biblioteca[indice].editora[strcspn(biblioteca[indice].editora, "\n")] = '\0';

        printf("Digite a edicao: ");
        scanf("%d", &biblioteca[indice].edicao);
        limparBufferEntrada();

        biblioteca[indice].disponivel = 1;

        totalLivros++;
        printf("\nLivro cadastrado com sucesso!\n");
    } else {
        printf("Biblioteca cheia!\n");
    }
    printf("\nPressione Enter para continuar...");
    getchar();
}

void listarLivros(const struct Livro *biblioteca, int totalLivros) {
    printf("--- Lista de Livros Cadastrados ---\n\n");
    if (totalLivros == 0) {
        printf("Nenhum livro cadastrado ainda.\n");
    } else {
        for (int i = 0; i < totalLivros; i++) {
            printf("---------------------\n");
            printf("LIVRO %d\n", i + 1);
            printf("Nome: %s\n", biblioteca[i].nome);
            printf("Autor: %s\n", biblioteca[i].autor);
            printf("Status: %s\n", biblioteca[i].disponivel ? "Disponível" : "Emprestado");
        }
        printf("---------------------\n");
    }
    printf("\nPressione Enter para continuar...");
    getchar();
}

void realizarEmprestimo(struct Livro *biblioteca, int totalLivros, struct Emprestimo * emprestimos, int *totalEmprestimos) { // Não deu pra ver o resto do código no video, então chutei o ultimo parametro como achei q deveria ser
    printf("--- Realizar Emprestimo ---\n\n");
    if (*totalEmprestimos >= MAX_EMPRESTIMOS) {
        printf("Limite de emprestimos atingido!\n");
    } else {
        printf("Livros disponíveis:\n");
        int disponiveis = 0;
        for (int i = 0; i < totalLivros; i++) {
            if (biblioteca[i].disponivel) {
                printf("%d - %s\n", i + 1, biblioteca[i].nome);
                disponiveis++;

            }
        }

        if (disponiveis == 0) {
            printf("Nenhum livro disponível para emprestimo.\n");
        } else  {
            printf("\nDigite o numero do livro que deseja emprestar: ");
            int numLivro;
            scanf("%d", &numLivro);
            limparBufferEntrada();

            int indice = numLivro - 1;

            // Validação daa escolha do usuário
            // Problemas relacionados ao parametro não especificado corretamente, eu poderia pedir pra IA resolver, mas vou deixar assim
            if (indice >= 0 && indice < totalLivros && biblioteca[indice].disponivel) {
                printf("Difite o nome do usuario que esta pegando o livro: ");
                fgets(emprestimos[totalEmprestimos].nomeUsuario, TAM_STRING, stdin);
                emprestimos[totalEmprestimos].nomeUsuario[strcspn(emprestimos[totalEmprestimos].nomeUsuario, "\n")] = '\0';

                emprestimos[totalEmprestimos].indiceLivro = indice;

                biblioteca[indice].disponivel = 0;

                totalEmprestimos++;
                printf("\nEmprestimo realizado com sucesso!\n");
            } else {
                printf("\nNumero do livro invalido ou indisponivel.\n");
            }
        }
    }
    printf("\nPressione Enter para continuar...");
    getchar();
}

listarEmprestimos(const struct Livro *biblioteca, const struct Emprestimo *emprestimos, int totalEmprestimos) {
    printf("--- Listar Emprestimos ---\n\n");
    if (totalEmprestimos == 0) {
        printf("Nenhum emprestimo realizado.\n");
    } else {
        for (int i = 0; i < totalEmprestimos; i++) {
            int indiceLivro = emprestimos[i].indiceLivro;
            printf("---------------------\n");
            printf("Emprestimo %d\n", i + 1);
            printf("Livro: %s\n", biblioteca[indiceLivro].nome);
            printf("Usuário: %S\n", emprestimos[i].nomeUsuario);
        }
        printf("---------------------\n");
    }
    printf("\nPressione Enter para continuar...");
    getchar();
}

void liberarMemoria(struct Livro *biblioteca, struct Emprestimo * emprestimos) {
    // Liberação de memória
    free(biblioteca);
    free(emprestimos);

    printf("Memória libverada com sucesso!");
}