#include "../include/hamburguer.h"
#include "../include/pilha.h"
#include <string.h>
#include <stdio.h>

Hamburguer criar_hamburguer(int id, const char* nome, float preco, const int* ing_ids, int qtd) {
    Hamburguer h;
    h.id = id;
    strncpy(h.nome, nome, sizeof(h.nome));
    h.nome[sizeof(h.nome)-1] = '\0';  // segurança
    h.preco_venda = preco;
    inicializarPilha(&h.ingredientes); // use o nome correto da função da pilha
    for(int i=0;i<qtd;i++){
        push(&h.ingredientes, ing_ids[i]);
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

int hamburguer_get_qtd_ingredientes(const Hamburguer* h){
    return tamanho(&h->ingredientes);  // função da pilha
}

Pilha hamburguer_get_ingredientes(Hamburguer* h){
    return h->ingredientes;  // retorna cópia da pilha
}

