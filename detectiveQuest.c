//nivel aventureiro

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------- Estrutura da Mansao ---------- */

typedef struct Sala {
    char nome[50];
    char pista[100];   // string vazia se nao houver pista
    struct Sala *esq;
    struct Sala *dir;
} Sala;

/* ---------- Estrutura da BST de Pistas ---------- */

typedef struct PistaNode {
    char pista[100];
    struct PistaNode *esq;
    struct PistaNode *dir;
} PistaNode;

/* ---------- Cria sala dinamicamente ---------- */
Sala* criarSala(char nome[], char pista[]) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));

    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);

    nova->esq = NULL;
    nova->dir = NULL;

    return nova;
}

/* ---------- Insere pista na BST ---------- */
PistaNode* inserirPista(PistaNode *raiz, char pista[]) {

    if (raiz == NULL) {
        PistaNode *novo = (PistaNode*) malloc(sizeof(PistaNode));
        strcpy(novo->pista, pista);
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }

    if (strcmp(pista, raiz->pista) < 0)
        raiz->esq = inserirPista(raiz->esq, pista);
    else
        raiz->dir = inserirPista(raiz->dir, pista);

    return raiz;
}

/* ---------- Exibe pistas em ordem alfabetica ---------- */
void exibirPistas(PistaNode *raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esq);
        printf("- %s\n", raiz->pista);
        exibirPistas(raiz->dir);
    }
}

/* ---------- Exploração da mansao ---------- */
void explorarSalasComPistas(Sala *atual, PistaNode **pistas) {

    char opcao;

    while (atual != NULL) {

        printf("\nVoce esta em: %s\n", atual->nome);

        if (strlen(atual->pista) > 0) {
            printf("Pista encontrada: %s\n", atual->pista);
            *pistas = inserirPista(*pistas, atual->pista);
        }

        printf("Ir para esquerda (e), direita (d) ou sair (s): ");
        scanf(" %c", &opcao);

        if (opcao == 'e')
            atual = atual->esq;
        else if (opcao == 'd')
            atual = atual->dir;
        else if (opcao == 's')
            break;
        else
            printf("Opcao invalida!\n");
    }
}

/* ---------- Main ---------- */
int main() {

    /* Montagem da mansao */

    Sala *hall = criarSala("Hall de Entrada", "");
    Sala *sala = criarSala("Sala de Estar", "Pegadas perto da janela");
    Sala *cozinha = criarSala("Cozinha", "Faca suja de sangue");
    Sala *quarto = criarSala("Quarto", "Carta rasgada");
    Sala *jardim = criarSala("Jardim", "Terra remexida");

    hall->esq = sala;
    hall->dir = cozinha;
    sala->esq = quarto;
    sala->dir = jardim;

    PistaNode *pistas = NULL;

    explorarSalasComPistas(hall, &pistas);

    printf("\n=== PISTAS COLETADAS ===\n");
    exibirPistas(pistas);

    return 0;
}
