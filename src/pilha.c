#include "pilha.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief Inicializa a Pilha, preparando-a para uso.
 *        Define o topo da pilha como 0, indicando que está vazia.
 * @param p Ponteiro para a estrutura Pilha a ser inicializada.
 */
void inicializarPilha(Pilha *p) {
    p->topo = 0;
}

/**
 * @brief Insere um valor no topo da Pilha.
 *        Verifica se a pilha não está cheia antes de inserir.
 * @param p Ponteiro para a estrutura Pilha onde o valor será inserido.
 * @param valor O valor inteiro a ser inserido na pilha.
 */
void push(Pilha *p, int valor) {
    if (p->topo < 50) {
        p->dados[p->topo++] = valor;
    }
}

/**
 * @brief Remove um valor do topo da Pilha.
 *        Verifica se a pilha não está vazia antes de remover.
 * @param p Ponteiro para a estrutura Pilha de onde o valor será removido.
 * @param valor Ponteiro para um inteiro onde o valor removido será armazenado.
 * @return 1 se a remoção for bem-sucedida, 0 se a pilha estiver vazia.
 */
int pop(Pilha *p, int *valor) {
    if (p->topo > 0) {
        *valor = p->dados[--p->topo];
        return 1;
    }
    return 0;
}

/**
 * @brief Retorna o número de elementos atualmente na Pilha.
 * @param p Ponteiro constante para a estrutura Pilha.
 * @return O número de elementos na pilha.
 */
int tamanho(const Pilha *p) {
    return p->topo;
}

Pilha* pilha_duplicar(const Pilha* p) {
    Pilha* nova_pilha = (Pilha*) malloc(sizeof(Pilha));
    if (nova_pilha != NULL) {
        memcpy(nova_pilha, p, sizeof(Pilha));
    }
    return nova_pilha;
}