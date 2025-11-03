#ifndef PILHA_INGREDIENTES_H
#define PILHA_INGREDIENTES_H

#include "ingrediente.h"

/**
 * @brief Nó da pilha dinâmica de ingredientes.
 */
typedef struct NoPilhaIngrediente {
    Ingrediente ingrediente;
    struct NoPilhaIngrediente* proximo;
} NoPilhaIngrediente;

/**
 * @brief Estrutura da pilha dinâmica de ingredientes.
 */
typedef struct {
    NoPilhaIngrediente* topo;
} PilhaIngredientes;

/**
 * @brief Cria e inicializa uma nova pilha de ingredientes.
 * @return Ponteiro para a nova pilha criada.
 */
PilhaIngredientes* criar_pilha_ingredientes();

/**
 * @brief Empilha um ingrediente no topo da pilha.
 * @param pilha Ponteiro para a pilha.
 * @param ingrediente O ingrediente a ser empilhado.
 */
void empilhar_ingrediente(PilhaIngredientes* pilha, Ingrediente ingrediente);

/**
 * @brief Desempilha um ingrediente do topo da pilha.
 * @param pilha Ponteiro para a pilha.
 * @param ingrediente_removido Ponteiro para uma struct onde o ingrediente do topo será copiado.
 * @return 1 se a operação for bem-sucedida, 0 se a pilha estiver vazia.
 */
int desempilhar_ingrediente(PilhaIngredientes* pilha, Ingrediente* ingrediente_removido);

/**
 * @brief Libera toda a memória alocada para a pilha e seus nós.
 * @param pilha Ponteiro para a pilha a ser destruída.
 */
void destruir_pilha_ingredientes(PilhaIngredientes* pilha);

/**
 * @brief Duplica uma pilha de ingredientes, criando uma cópia independente.
 * @param original Ponteiro para a pilha a ser duplicada.
 * @return Ponteiro para a nova pilha duplicada.
 */
PilhaIngredientes* duplicar_pilha_ingredientes(const PilhaIngredientes* original);

/**
 * @brief Verifica se a pilha de ingredientes está vazia.
 * @param pilha Ponteiro para a pilha.
 * @return 1 se a pilha estiver vazia, 0 caso contrário.
 */
int pilha_ingredientes_vazia(const PilhaIngredientes* pilha);

/**
 * @brief Retorna o número de elementos na pilha de ingredientes.
 * @param pilha Ponteiro para a pilha.
 * @return O número de ingredientes na pilha.
 */
int pilha_ingredientes_tamanho(const PilhaIngredientes* pilha);

#endif 
