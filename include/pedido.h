#ifndef PEDIDO_H
#define PEDIDO_H

/**
 * @file pedido.h
 * @brief Definição da estrutura de dados Pedido e suas operações.
 *
 * Este arquivo define a estrutura de um pedido, incluindo seu status,
 * e funções para criar e acessar suas propriedades.
 */

/**
 * @brief Enumeração para representar o status atual de um pedido.
 */
typedef enum {
    EM_ESPERA, 
    EM_PREPARO, 
    PRONTO, 
    ENTREGUE 
} StatusPedido;

/**
 * @brief Estrutura que representa um Pedido no jogo.
 */
typedef struct {
    int id; 
    int id_cliente; 
    int id_hamburguer; 
    StatusPedido status; 
    int hora_pedido; 
    int erros_montagem; 
    float valor_pago; 
} Pedido;

float pedido_get_valor_pago(const Pedido* p);

/**
 * @brief Cria e inicializa uma nova estrutura Pedido.
 * @param id Identificador único do pedido.
 * @param id_cliente ID do cliente que fez o pedido.
 * @param id_hamburguer ID do hambúrguer solicitado.
 * @param hora_pedido Hora em que o pedido foi feito.
 * @return Uma nova estrutura Pedido inicializada com os valores fornecidos e status EM_ESPERA.
 */
Pedido criar_pedido(int id, int id_cliente, int id_hamburguer, int hora_pedido);

/**
 * @brief Retorna o ID do pedido.
 * @param p Ponteiro constante para a estrutura Pedido.
 * @return O ID do pedido.
 */
int pedido_get_id(const Pedido* p);

/**
 * @brief Retorna o ID do cliente que fez o pedido.
 * @param p Ponteiro constante para a estrutura Pedido.
 * @return O ID do cliente.
 */
int pedido_get_id_cliente(const Pedido* p);

/**
 * @brief Retorna o ID do hambúrguer solicitado no pedido.
 * @param p Ponteiro constante para a estrutura Pedido.
 * @return O ID do hambúrguer.
 */
int pedido_get_id_hamburguer(const Pedido* p);

/**
 * @brief Retorna o status atual do pedido.
 * @param p Ponteiro constante para a estrutura Pedido.
 * @return O status do pedido (EM_ESPERA, EM_PREPARO, PRONTO, ENTREGUE).
 */
StatusPedido pedido_get_status(const Pedido* p);

/**
 * @brief Retorna a hora em que o pedido foi feito.
 * @param p Ponteiro constante para a estrutura Pedido.
 * @return A hora do pedido.
 */
int pedido_get_hora_pedido(const Pedido* p);

#endif