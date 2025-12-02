#ifndef GERENCIADOR_PEDIDO_H
#define GERENCIADOR_PEDIDO_H

#include "fila.h"
#include "pedido.h"
#include "hamburguer.h"
#include "ingrediente.h"
#include "config.h"
#include "clientes.h" 

extern Fila filaPedidos;
extern Fila filaPedidosProntos;

void pedido_manager_inicializar_pedidos();

void pedido_manager_gerar_pedidos(Pedido pedidos[], int n);

void cliente_faz_pedido(const Cliente* cliente);

int pedido_manager_processar_proximo_pedido();

#endif
