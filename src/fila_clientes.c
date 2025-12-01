#include "../include/fila_clientes.h"
#include <stdio.h>
#include <stdlib.h>

FilaClientes* criar_fila_clientes() {
    FilaClientes* fila = (FilaClientes*) malloc(sizeof(FilaClientes));
    if (fila != NULL) {
        fila->inicio = NULL;
        fila->fim = NULL;
    }
    return fila;
}

void enfileirar_cliente(FilaClientes* fila, Cliente cliente) {
    NoCliente* novo_no = (NoCliente*) malloc(sizeof(NoCliente));
    if (novo_no == NULL) {
        return; 
    }
    novo_no->cliente = cliente;
    novo_no->proximo = NULL;

    if (fila_clientes_vazia(fila)) {
        fila->inicio = novo_no;
    } else {
        fila->fim->proximo = novo_no;
    }
    fila->fim = novo_no;
}

int desenfileirar_cliente(FilaClientes* fila, Cliente* cliente_removido) {
    if (fila_clientes_vazia(fila)) {
        return 0; 
    }

    NoCliente* no_removido = fila->inicio;
    *cliente_removido = no_removido->cliente;

    fila->inicio = fila->inicio->proximo;

    if (fila->inicio == NULL) { 
        fila->fim = NULL;
    }

    free(no_removido);
    return 1; 
}

int fila_clientes_vazia(const FilaClientes* fila) {
    return (fila == NULL || fila->inicio == NULL);
}

void exibir_fila_clientes(FilaClientes* fila) {
    if (fila_clientes_vazia(fila)) {
        printf("Fila de clientes está vazia.\n");
        return;
    }
    printf("--- Fila de Clientes ---\n");
    NoCliente* atual = fila->inicio;
    while (atual != NULL) {
        printf("Cliente: %s | Pedido (ID Hamburguer): %d\n", 
               cliente_get_nome(&atual->cliente), 
               cliente_get_id_hamburguer_preferido(&atual->cliente));
        atual = atual->proximo;
    }
    printf("------------------------\n");
}

void destruir_fila_clientes(FilaClientes* fila) {
    if (fila == NULL) return;

    NoCliente* atual = fila->inicio;
    while (atual != NULL) {
        NoCliente* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    free(fila);
}
