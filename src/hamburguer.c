#include "../include/hamburguer.h"
#include "../include/pilha.h"
#include "../include/ingrediente.h"
#include "../include/dados.h"
#include <string.h>
#include <stdio.h>

Hamburguer criar_hamburguer(int id, const char* nome, float preco, const int* ing_ids, int qtd) {
    Hamburguer h;
    h.id = id;
    strncpy(h.nome, nome, sizeof(h.nome));
    h.nome[sizeof(h.nome)-1] = '\0'; 
    h.preco_venda = preco;
    inicializarPilha(&h.ingredientes);
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

float hamburguer_get_custo(const Hamburguer* h) {
    float custo_total = 0.0f;
    Pilha* copia_ingredientes = pilha_duplicar(&h->ingredientes);
    
    int id_ing;
    while(pop(copia_ingredientes, &id_ing)) {
        Ingrediente* ing = buscar_ingrediente_por_id(id_ing);
        if (ing) {
            custo_total += ingrediente_get_preco_compra(ing);
        }
    }
    
    free(copia_ingredientes);
    return custo_total;
}

int hamburguer_get_qtd_ingredientes(const Hamburguer* h){
    return tamanho(&h->ingredientes); 
}

Pilha hamburguer_get_ingredientes(Hamburguer* h){
    return h->ingredientes;
}