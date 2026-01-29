//desafio detective quest nivel novato


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//criação da estrutura do nó
typedef struct no
{
    char nome[50];
    struct no *esquerda;
    struct no *direita;
} No;


//função que cria a sala(cria novo nó)
No *criarSala(char nome[])
{
    No *nova = (No *)malloc(sizeof(No));

    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;

    return nova;
}

//função que permite o jogador percorrer as salas
void explorarSala(No *atual)
{
    char op;
    while (atual != NULL)
    {
        printf("Voce esta em : %s\n", atual->nome);

        //verifica se o jogador chegou no ultimo nó
        if (atual->esquerda == NULL && atual->direita == NULL)
        {
            printf("Voce chegou ao comodo final.\n");
            break;
        }

        if (atual->esquerda != NULL)
        {
            printf("e - Ir para esquerda\n");
        }
        if (atual->direita != NULL)
        {
            printf("d - Ir para direita\n");
        }
        printf("s - Sair\n");

        scanf(" %c", &op);

        //menu de navegação 
        switch (op)
        {
        case 'e':
            if (atual->esquerda != NULL)
            {
                atual = atual->esquerda;
            }
            else
            {
                printf("Nao ha caminho a esquerda.\n");
            }
            break;

        case 'd':
            if (atual->direita != NULL)
            {
                atual = atual->direita;
            }
            else
            {
                printf("Nao ha caminho a direita.\n");
            }
            break;
        case 's':
            printf("Saindo...");
            return;

        default:
            printf("Opcao invalida.\n");
        }
    }
}

int main()
{
    //aqui cria um nó para cada 'sala'
    No *hall = criarSala("Hall de entrada");
    No *sala = criarSala("Sala de estar");
    No *cozinha = criarSala("Cozinha");
    No *quarto = criarSala("Quarto");
    No *banheiro = criarSala("Banheiro");
    No *jardim = criarSala("Jardim");

    //aqui organiza a estrutura da arvore 
    hall->esquerda = sala;
    hall->direita = cozinha;

    sala->esquerda = quarto;
    sala->direita = banheiro;

    cozinha->direita = jardim;

    //aqui chama a função de exploração da sala
    explorarSala(hall);

    return 0;
}