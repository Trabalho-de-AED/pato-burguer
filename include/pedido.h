#ifndef PEDIDO_H
#define PEDIDO_H

typedef enum {
    EM_ESPERA,
    EM_PREPARO,
    PRONTO,
    ENTREGUE
} StatusPedido;

typedef struct {
    int id;
    int id_cliente;
    int id_hamburguer;
    StatusPedido status;
    int hora_pedido;
} Pedido;

Pedido criar_pedido(int id, int id_cliente, int id_hamburguer, int hora_pedido);

int pedido_get_id(const Pedido* p);
int pedido_get_id_cliente(const Pedido* p);
int pedido_get_id_hamburguer(const Pedido* p);
StatusPedido pedido_get_status(const Pedido* p);
int pedido_get_hora_pedido(const Pedido* p);

#endif
