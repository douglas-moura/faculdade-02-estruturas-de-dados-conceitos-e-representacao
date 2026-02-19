#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 10

typedef struct Sala {
    char nome[50];
    char pista[100];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

typedef struct NoBST {
    char pista[100];
    struct NoBST* esquerda;
    struct NoBST* direita;
} NoBST;

typedef struct Hash {
    char pista[100];
    char suspeito[50];
    struct Hash* prox;
} Hash;

Hash* tabelaHash[TAM_HASH];

int funcaoHash(const char* chave) {
    int soma = 0;
    for (int i = 0; chave[i] != '\0'; i++)
        soma += chave[i];
    return soma % TAM_HASH;
}

/* cria dinamicamente uma sala da mansão */
Sala* criarSala(const char* nome, const char* pista) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

/* insere uma pista na árvore BST */
NoBST* inserirPista(NoBST* raiz, const char* pista) {
    if (raiz == NULL) {
        NoBST* novo = (NoBST*)malloc(sizeof(NoBST));
        strcpy(novo->pista, pista);
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }

    if (strcmp(pista, raiz->pista) < 0)
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    else
        raiz->direita = inserirPista(raiz->direita, pista);

    return raiz;
}

/* percorre a BST em ordem para listar as pistas */
void listarPistas(NoBST* raiz) {
    if (raiz != NULL) {
        listarPistas(raiz->esquerda);
        printf("- %s\n", raiz->pista);
        listarPistas(raiz->direita);
    }
}

/* insere associação pista -> suspeito na tabela hash */
void inserirNaHash(const char* pista, const char* suspeito) {
    int indice = funcaoHash(pista);

    Hash* novo = (Hash*)malloc(sizeof(Hash));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);
    novo->prox = tabelaHash[indice];
    tabelaHash[indice] = novo;
}

/* busca na hash o suspeito associado à pista */
char* encontrarSuspeito(const char* pista) {
    int indice = funcaoHash(pista);
    Hash* atual = tabelaHash[indice];

    while (atual != NULL) {
        if (strcmp(atual->pista, pista) == 0)
            return atual->suspeito;
        atual = atual->prox;
    }

    return NULL;
}

/* permite explorar a mansão interativamente */
void explorarSalas(Sala* raiz, NoBST** pistas) {
    Sala* atual = raiz;
    char opcao;

    while (atual != NULL) {

        printf("\nVocê está em: %s\n", atual->nome);

        if (strlen(atual->pista) > 0) {
            printf("Pista encontrada: %s\n", atual->pista);
            *pistas = inserirPista(*pistas, atual->pista);
            atual->pista[0] = '\0';
        }

        printf("e - esquerda | d - direita | s - sair: ");
        scanf(" %c", &opcao);

        if (opcao == 'e')
            atual = atual->esquerda;
        else if (opcao == 'd')
            atual = atual->direita;
        else if (opcao == 's')
            break;
        else
            printf("Opção inválida!\n");
    }
}

/* conta recursivamente quantas pistas apontam para o suspeito */
int contarPistasSuspeito(NoBST* raiz, const char* suspeito) {
    if (raiz == NULL)
        return 0;

    int contador = 0;

    char* suspeitoEncontrado = encontrarSuspeito(raiz->pista);

    if (suspeitoEncontrado != NULL &&
        strcmp(suspeitoEncontrado, suspeito) == 0) {
        contador++;
    }

    contador += contarPistasSuspeito(raiz->esquerda, suspeito);
    contador += contarPistasSuspeito(raiz->direita, suspeito);

    return contador;
}

/* etapa final do julgamento */
void verificarSuspeitoFinal(NoBST* pistas) {
    char acusado[50];

    printf("\nPistas coletadas:\n");
    listarPistas(pistas);

    printf("\nDigite o nome do suspeito: ");
    scanf(" %[^\n]", acusado);

    int total = contarPistasSuspeito(pistas, acusado);

    if (total >= 2)
        printf("\nAcusação correta! %s é o culpado.\n", acusado);
    else
        printf("\nEvidências insuficientes contra %s.\n", acusado);
}

int main() {

    for (int i = 0; i < TAM_HASH; i++)
        tabelaHash[i] = NULL;

    NoBST* pistas = NULL;

    Sala* hall = criarSala("Hall de Entrada", "Pegadas de lama");
    Sala* biblioteca = criarSala("Biblioteca", "Livro rasgado");
    Sala* salaEstar = criarSala("Sala de Estar", "Taça quebrada");
    Sala* quarto = criarSala("Quarto", "Bilhete misterioso");
    Sala* cozinha = criarSala("Cozinha", "Faca ensanguentada");

    hall->esquerda = biblioteca;
    hall->direita = salaEstar;

    biblioteca->esquerda = quarto;
    biblioteca->direita = cozinha;

    inserirNaHash("Pegadas de lama", "Carlos");
    inserirNaHash("Livro rasgado", "Ana");
    inserirNaHash("Taça quebrada", "Carlos");
    inserirNaHash("Bilhete misterioso", "Mariana");
    inserirNaHash("Faca ensanguentada", "Carlos");

    printf("=== Detective Quest ===\n");

    explorarSalas(hall, &pistas);

    verificarSuspeitoFinal(pistas);

    return 0;
}
