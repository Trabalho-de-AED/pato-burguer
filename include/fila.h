#ifndef FILA_H
#define FILA_H

/**
 * @file fila.h
 * @brief Definição da estrutura de dados Fila (fila circular) e suas operações.
 *
 * Este arquivo define uma fila genérica que pode armazenar ponteiros para qualquer tipo de dado.
 * A implementação é de uma fila circular com tamanho máximo pré-definido.
 */

/**
 * @brief Tamanho máximo da fila. Define a capacidade máxima de elementos que a fila pode armazenar.
 */
#define MAX 100

/**
 * @brief Tipo de item da fila. Definido como `void*` para permitir que a fila armazene ponteiros para qualquer tipo de dado.
 */
typedef void* tp_item; 

/**
 * @brief Estrutura que representa uma fila circular.
 */
typedef struct {
    tp_item item[MAX];  
    int ini, fim;       
} Fila;

/**
 * @brief Inicializa a fila, preparando-a para uso.
 *        Define os índices de início e fim para indicar que a fila está vazia.
 * @param f Ponteiro para a estrutura Fila a ser inicializada.
 */
void inicializaFila(Fila *f);

/**
 * @brief Verifica se a fila está vazia.
 * @param f Ponteiro constante para a estrutura Fila a ser verificada.
 * @return 1 se a fila estiver vazia, 0 caso contrário.
 */
int filaVazia(const Fila *f);

/**
 * @brief Verifica se a fila está cheia.
 * @param f Ponteiro constante para a estrutura Fila a ser verificada.
 * @return 1 se a fila estiver cheia, 0 caso contrário.
 */
int filaCheia(const Fila *f);

/**
 * @brief Insere um elemento na fila.
 * @param f Ponteiro para a estrutura Fila onde o elemento será inserido.
 * @param e O elemento (ponteiro `tp_item`) a ser inserido.
 * @return 1 se a inserção for bem-sucedida, ou 0 se a fila estiver cheia.
 */
int insereFila(Fila *f, tp_item e);

/**
 * @brief Remove um elemento da fila.
 * @param f Ponteiro para a estrutura Fila de onde o elemento será removido.
 * @param e Ponteiro para `tp_item` onde o elemento removido será armazenado.
 * @return 1 se a remoção for bem-sucedida, ou 0 se a fila estiver vazia.
 */
int removeFila(Fila *f, tp_item *e);

#endif