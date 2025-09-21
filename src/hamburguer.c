#include "../include/hamburguer.h"
#include <stdio.h>
#include <string.h>

Hamburguer criar_hamburguer(int id, const char* nome, float preco_venda, int* ingredientes, int qtd_ingredientes) {
    Hamburguer h;
    int i;
    h.id = id;
    strncpy(h.nome, nome, sizeof(h.nome) - 1);
    h.nome[sizeof(h.nome) - 1] = '\0';
    h.preco_venda = preco_venda;
    h.qtd_ingredientes = (qtd_ingredientes < MAX_INGREDIENTES) ? qtd_ingredientes : MAX_INGREDIENTES;

    for (i = 0; i < h.qtd_ingredientes; i++) {
        h.ingredientes[i] = ingredientes[i];
    }

    return h;
}

int hamburguer_get_id(const Hamburguer* h) {
    return h->id;
}

const char* hamburguer_get_nome(const Hamburguer* h) {
    return h->nome;
}

float hamburguer_get_preco_venda(const Hamburguer* h) {
    return h->preco_venda;
}

const int* hamburguer_get_ingredientes(const Hamburguer* h) {
    return h->ingredientes;
}

int hamburguer_get_qtd_ingredientes(const Hamburguer* h) {
    return h->qtd_ingredientes;
}
