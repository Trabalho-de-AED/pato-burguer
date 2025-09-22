#ifndef GERENCIADOR_PEDIDO_H
#define GERENCIADOR_PEDIDO_H

#include "fila.h"
#include "pedido.h"
#include "hamburguer.h"
#include "ingrediente.h"
#include "config.h"

extern Fila filaPedidos;

void pedido_manager_inicializar_pedidos();
void pedido_manager_gerar_pedidos(Pedido pedidos[], int n);
int pedido_manager_processar_proximo_pedido();

#endif