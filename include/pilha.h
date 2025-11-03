#ifndef PILHA_H
#define PILHA_H

#include <stdlib.h>

/**
 * @file pilha.h
 * @brief Definição da estrutura de dados Pilha e suas operações.
 *
 * Este arquivo define uma pilha que armazena inteiros e suas operações básicas.
 */

/**
 * @brief Estrutura que representa uma Pilha.
 *        Os dados são armazenados em um array de tamanho fixo.
 */
typedef struct {
    int dados[50];  
    int topo;       
} Pilha;

/**
 * @brief Inicializa a Pilha, preparando-a para uso.
 * @param p Ponteiro para a estrutura Pilha a ser inicializada.
 */
void inicializarPilha(Pilha *p);

/**
 * @brief Insere um valor no topo da Pilha.
 * @param p Ponteiro para a estrutura Pilha onde o valor será inserido.
 * @param valor O valor inteiro a ser inserido na pilha.
 */
void push(Pilha *p, int valor);

/**
 * @brief Remove um valor do topo da Pilha.
 * @param p Ponteiro para a estrutura Pilha de onde o valor será removido.
 * @param valor Ponteiro para um inteiro onde o valor removido será armazenado.
 * @return 1 se a remoção for bem-sucedida, 0 se a pilha estiver vazia.
 */
int pop(Pilha *p, int *valor);

/**
 * @brief Retorna o número de elementos atualmente na Pilha.
 * @param p Ponteiro constante para a estrutura Pilha.
 * @return O número de elementos na pilha.
 */
int tamanho(const Pilha *p);

/**
 * @brief Duplica uma pilha, criando uma cópia independente.
 * @param p Ponteiro constante para a pilha a ser duplicada.
 * @return Ponteiro para a nova pilha duplicada.
 */
Pilha* pilha_duplicar(const Pilha* p);

#endif
