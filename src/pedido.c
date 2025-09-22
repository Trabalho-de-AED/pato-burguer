#include "../include/pedido.h"
#include <stdio.h>

/**
 * @brief Cria e inicializa uma nova estrutura Pedido.
 * @param id Identificador único do pedido.
 * @param id_cliente ID do cliente que fez o pedido.
 * @param id_hamburguer ID do hambúrguer solicitado.
 * @param hora_pedido Hora em que o pedido foi feito.
 * @return Uma nova estrutura Pedido inicializada com os valores fornecidos e status EM_ESPERA.
 */
Pedido criar_pedido(int id, int id_cliente, int id_hamburguer, int hora_pedido) {
    Pedido p;
    p.id = id;
    p.id_cliente = id_cliente;
    p.id_hamburguer = id_hamburguer;
    p.status = EM_ESPERA;
    p.hora_pedido = hora_pedido;
    return p;
}

/**
 * @brief Retorna o ID do pedido.
 * @param p Ponteiro constante para a estrutura Pedido.
 * @return O ID do pedido.
 */
int pedido_get_id(const Pedido* p) {
    return p->id;
}

/**
 * @brief Retorna o ID do cliente que fez o pedido.
 * @param p Ponteiro constante para a estrutura Pedido.
 * @return O ID do cliente.
 */
int pedido_get_id_cliente(const Pedido* p) {
    return p->id_cliente;
}

/**
 * @brief Retorna o ID do hambúrguer solicitado no pedido.
 * @param p Ponteiro constante para a estrutura Pedido.
 * @return O ID do hambúrguer.
 */
int pedido_get_id_hamburguer(const Pedido* p) {
    return p->id_hamburguer;
}

/**
 * @brief Retorna o status atual do pedido.
 * @param p Ponteiro constante para a estrutura Pedido.
 * @return O status do pedido (EM_ESPERA, EM_PREPARO, PRONTO, ENTREGUE).
 */
StatusPedido pedido_get_status(const Pedido* p) {
    return p->status;
}

/**
 * @brief Retorna a hora em que o pedido foi feito.
 * @param p Ponteiro constante para a estrutura Pedido.
 * @return A hora do pedido.
 */
int pedido_get_hora_pedido(const Pedido* p) {
    return p->hora_pedido;
}