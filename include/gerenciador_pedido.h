#ifndef GERENCIADOR_PEDIDO_H
#define GERENCIADOR_PEDIDO_H

#include "fila.h"
#include "pedido.h"
#include "hamburguer.h"
#include "ingrediente.h"
#include "config.h"

/**
 * @brief Fila global que armazena os pedidos do sistema.
 *        Gerenciada exclusivamente pelo módulo gerenciador_pedido.
 */
extern Fila filaPedidos;

/**
 * @brief Inicializa a fila de pedidos global.
 *        Deve ser chamada antes de qualquer operação com a fila de pedidos.
 */
void pedido_manager_inicializar_pedidos();

/**
 * @brief Gera um número especificado de pedidos aleatórios e os insere na fila de pedidos.
 *        Os pedidos são gerados com IDs de cliente, IDs de hambúrguer e horas de pedido aleatórios.
 * @param pedidos Array de Pedido onde os pedidos gerados serão armazenados temporariamente.
 * @param n O número de pedidos a serem gerados.
 */
void pedido_manager_gerar_pedidos(Pedido pedidos[], int n);

/**
 * @brief Processa o próximo pedido da fila de pedidos.
 *        Remove o pedido mais antigo da fila e atualiza seu status para EM_PREPARO.
 * @return O ID do pedido processado, ou 0 se a fila estiver vazia.
 */
int pedido_manager_processar_proximo_pedido();

#endif
