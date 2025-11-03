#ifndef FILA_CLIENTES_H
#define FILA_CLIENTES_H

#include "clientes.h"

/**
 * @brief Nó da fila de clientes, armazena um cliente e o ponteiro para o próximo nó.
 */
typedef struct NoCliente {
    Cliente cliente;
    struct NoCliente* proximo;
} NoCliente;

/**
 * @brief Estrutura da fila de clientes, com ponteiros para o início e o fim.
 */
typedef struct FilaClientes {
    NoCliente* inicio;
    NoCliente* fim;
} FilaClientes;

/**
 * @brief Cria e inicializa uma nova fila de clientes.
 * @return Ponteiro para a nova fila criada.
 */
FilaClientes* criar_fila_clientes();

/**
 * @brief Insere um cliente no final da fila.
 * @param fila Ponteiro para a fila de clientes.
 * @param cliente O cliente a ser adicionado.
 */
void enfileirar_cliente(FilaClientes* fila, Cliente cliente);

/**
 * @brief Remove um cliente do início da fila.
 * @param fila Ponteiro para a fila de clientes.
 * @param cliente_removido Ponteiro para uma struct Cliente onde os dados do cliente removido serão copiados.
 * @return 1 se a remoção for bem-sucedida, 0 se a fila estiver vazia.
 */
int desenfileirar_cliente(FilaClientes* fila, Cliente* cliente_removido);

/**
 * @brief Verifica se a fila de clientes está vazia.
 * @param fila Ponteiro para a fila de clientes.
 * @return 1 se a fila estiver vazia, 0 caso contrário.
 */
int fila_clientes_vazia(const FilaClientes* fila);

/**
 * @brief Exibe no terminal todos os clientes da fila.
 * @param fila Ponteiro para a fila de clientes.
 */
void exibir_fila_clientes(FilaClientes* fila);

/**
 * @brief Libera toda a memória alocada para a fila e seus nós.
 * @param fila Ponteiro para a fila de clientes a ser destruída.
 */
void destruir_fila_clientes(FilaClientes* fila);

#endif // FILA_CLIENTES_H
