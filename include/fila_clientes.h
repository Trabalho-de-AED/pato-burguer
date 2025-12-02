#ifndef FILA_CLIENTES_H
#define FILA_CLIENTES_H

#include "clientes.h"

typedef struct NoCliente {
    Cliente cliente;
    struct NoCliente* proximo;
} NoCliente;

typedef struct FilaClientes {
    NoCliente* inicio;
    NoCliente* fim;
} FilaClientes;

FilaClientes* criar_fila_clientes();

void enfileirar_cliente(FilaClientes* fila, Cliente cliente);

int desenfileirar_cliente(FilaClientes* fila, Cliente* cliente_removido);

int fila_clientes_vazia(const FilaClientes* fila);

void exibir_fila_clientes(FilaClientes* fila);

void destruir_fila_clientes(FilaClientes* fila);

#endif 
