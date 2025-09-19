#include "../include/pedido.h"
#include <stdio.h>

Pedido criar_pedido(int id, int id_cliente, int id_hamburguer, int hora_pedido) {
    Pedido p;
    p.id = id;
    p.id_cliente = id_cliente;
    p.id_hamburguer = id_hamburguer;
    p.status = EM_ESPERA;
    p.hora_pedido = hora_pedido;
    return p;
}

int pedido_get_id(const Pedido* p) {
    return p->id;
}

int pedido_get_id_cliente(const Pedido* p) {
    return p->id_cliente;
}

int pedido_get_id_hamburguer(const Pedido* p) {
    return p->id_hamburguer;
}

StatusPedido pedido_get_status(const Pedido* p) {
    return p->status;
}

int pedido_get_hora_pedido(const Pedido* p) {
    return p->hora_pedido;
}
