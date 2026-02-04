#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 10

// ----------------------------
// ESTRUTURA DA SALA (ÁRVORE BINÁRIA)
// ----------------------------
typedef struct Sala {
    char nome[50];
    char pista[80];
    struct Sala *esq;
    struct Sala *dir;
} Sala;

// ----------------------------
// BST DE PISTAS
// ----------------------------
typedef struct PistaNode {
    char pista[80];
    struct PistaNode *esq;
    struct PistaNode *dir;
} PistaNode;

// ----------------------------
// HASH: pista -> suspeito
// ----------------------------
typedef struct HashNode {
    char pista[80];
    char suspeito[30];
    struct HashNode *prox;
} HashNode;

HashNode* tabelaHash[TAM_HASH];

// ----------------------------
// FUNÇÃO HASH
// ----------------------------
int funcaoHash(char *str) {
    int soma = 0;
    for (int i = 0; str[i] != '\0'; i++)
        soma += str[i];
    return soma % TAM_HASH;
}

// ----------------------------
// CRIAR SALA
// ----------------------------
Sala* criarSala(char *nome, char *pista) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);
    nova->esq = NULL;
    nova->dir = NULL;
    return nova;
}

// ----------------------------
// INSERIR PISTA NA BST
// ----------------------------
PistaNode* inserirPista(PistaNode *raiz, char *pista) {
    if (raiz == NULL) {
        PistaNode *novo = (PistaNode*) malloc(sizeof(PistaNode));
        strcpy(novo->pista, pista);
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }

    if (strcmp(pista, raiz->pista) < 0)
        raiz->esq = inserirPista(raiz->esq, pista);
    else if (strcmp(pista, raiz->pista) > 0)
        raiz->dir = inserirPista(raiz->dir, pista);

    return raiz;
}

// ----------------------------
// INSERIR NA HASH
// ----------------------------
void inserirNaHash(char *pista, char *suspeito) {
    int pos = funcaoHash(pista);

    HashNode *novo = (HashNode*) malloc(sizeof(HashNode));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);
    novo->prox = tabelaHash[pos];
    tabelaHash[pos] = novo;
}

// ----------------------------
// BUSCAR SUSPEITO DA PISTA
// ----------------------------
char* encontrarSuspeito(char *pista) {
    int pos = funcaoHash(pista);
    HashNode *aux = tabelaHash[pos];

    while (aux != NULL) {
        if (strcmp(aux->pista, pista) == 0)
            return aux->suspeito;
        aux = aux->prox;
    }

    return NULL;
}

// ----------------------------
// EXIBIR PISTAS (EM ORDEM)
// ----------------------------
void exibirPistas(PistaNode *raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esq);
        printf("- %s\n", raiz->pista);
        exibirPistas(raiz->dir);
    }
}

// ----------------------------
// CONTAR PISTAS DE UM SUSPEITO
// ----------------------------
int contarPistas(PistaNode *raiz, char *suspeito) {
    if (raiz == NULL)
        return 0;

    int total = 0;

    char *resp = encontrarSuspeito(raiz->pista);
    if (resp != NULL && strcmp(resp, suspeito) == 0)
        total = 1;

    return total +
           contarPistas(raiz->esq, suspeito) +
           contarPistas(raiz->dir, suspeito);
}

// ----------------------------
// EXPLORAR SALAS
// ----------------------------
void explorarSalas(Sala *atual, PistaNode **bst) {

    char op;

    while (atual != NULL) {

        printf("\nVoce esta em: %s\n", atual->nome);

        if (strlen(atual->pista) > 0) {
            printf("Pista encontrada: %s\n", atual->pista);
            *bst = inserirPista(*bst, atual->pista);
        }

        printf("\n[e] Esquerda | [d] Direita | [s] Sair: ");
        scanf(" %c", &op);

        if (op == 'e')
            atual = atual->esq;
        else if (op == 'd')
            atual = atual->dir;
        else
            break;
    }
}

// ----------------------------
// MOSTRAR SUSPEITOS
// ----------------------------
void mostrarSuspeitos() {
    printf("\nSuspeitos:\n");
    printf("- Carlos\n");
    printf("- Ana\n");
    printf("- Bruno\n");
}

// ----------------------------
// JULGAMENTO FINAL
// ----------------------------
void verificarSuspeitoFinal(PistaNode *bst) {

    char suspeitoFinal[30];

    mostrarSuspeitos();

    printf("\nQuem voce acusa? ");
    scanf(" %[^\n]", suspeitoFinal);

    int qtd = contarPistas(bst, suspeitoFinal);

    if (qtd >= 2)
        printf("\n%s eh o culpado!\n", suspeitoFinal);
    else
        printf("\nNao ha provas suficientes contra %s.\n", suspeitoFinal);
}

// ----------------------------
// MAIN
// ----------------------------
int main() {

    for (int i = 0; i < TAM_HASH; i++)
        tabelaHash[i] = NULL;

    // MANSÃO
    Sala *hall = criarSala("Hall de Entrada", "");
    Sala *cozinha = criarSala("Cozinha", "Faca suja");
    Sala *biblioteca = criarSala("Biblioteca", "Livro rasgado");
    Sala *quarto = criarSala("Quarto", "Pegadas no chao");
    Sala *jardim = criarSala("Jardim", "Luvas pretas");

    hall->esq = cozinha;
    hall->dir = biblioteca;
    cozinha->esq = quarto;
    cozinha->dir = jardim;

    // HASH pista -> suspeito
    inserirNaHash("Faca suja", "Carlos");
    inserirNaHash("Livro rasgado", "Ana");
    inserirNaHash("Pegadas no chao", "Carlos");
    inserirNaHash("Luvas pretas", "Bruno");

    PistaNode *bstPistas = NULL;

    explorarSalas(hall, &bstPistas);

    printf("\nPistas coletadas:\n");
    exibirPistas(bstPistas);

    verificarSuspeitoFinal(bstPistas);

    return 0;
}
