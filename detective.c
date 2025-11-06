#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Estrutura que representa uma sala da mansão
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// Função que cria uma sala dinamicamente
Sala* criarSala(char nome[]) {
    Sala *novaSala = (Sala*) malloc(sizeof(Sala));
    if (novaSala == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

// Função recursiva para liberar memória das salas
void liberarArvore(Sala *raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
}

// Função que permite explorar a mansão
void explorarSalas(Sala *atual) {
    char escolha;

    printf("Você está na sala: %s\n", atual->nome);

    while (1) {
        // Se não tiver caminhos, acabou a exploração
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Você chegou ao fim do caminho! Sala final: %s\n", atual->nome);
            break;
        }

        printf("\nEscolha seu caminho:\n");
        if (atual->esquerda != NULL)
            printf(" - [e] Ir para %s\n", atual->esquerda->nome);
        if (atual->direita != NULL)
            printf(" - [d] Ir para %s\n", atual->direita->nome);
        printf(" - [s] Sair do jogo\n");

        printf("Digite sua opção: ");
        scanf(" %c", &escolha);
        escolha = tolower(escolha);

        if (escolha == 'e' && atual->esquerda != NULL) {
            atual = atual->esquerda;
            printf("\nVocê foi para a sala: %s\n", atual->nome);
        } 
        else if (escolha == 'd' && atual->direita != NULL) {
            atual = atual->direita;
            printf("\nVocê foi para a sala: %s\n", atual->nome);
        } 
        else if (escolha == 's') {
            printf("\nSaindo da exploração...\n");
            break;
        } 
        else {
            printf("\nCaminho inválido! Tente novamente.\n");
        }
    }
}

// Função principal: cria o mapa da mansão e inicia a exploração
int main() {
    // Criação das salas
    Sala *hall = criarSala("Hall de Entrada");
    Sala *salaEstar = criarSala("Sala de Estar");
    Sala *cozinha = criarSala("Cozinha");
    Sala *biblioteca = criarSala("Biblioteca");
    Sala *jardim = criarSala("Jardim");
    Sala *despensa = criarSala("Despensa");
    Sala *salao = criarSala("Salão de Festas");

    // Conexões (montagem da árvore)
    hall->esquerda = salaEstar;
    hall->direita = cozinha;

    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;

    cozinha->esquerda = despensa;
    cozinha->direita = salao;

    // Início da exploração
    printf("=== Detective Quest: Mapa da Mansão ===\n\n");
    explorarSalas(hall);

    // Liberação da memória
    liberarArvore(hall);

    printf("\nFim do jogo! Obrigado por jogar.\n");
    return 0;
}
