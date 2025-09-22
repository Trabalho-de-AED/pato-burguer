#ifndef HAMBURGUER_H
#define HAMBURGUER_H

#define MAX_INGREDIENTES 10

#include "pilha.h"

typedef struct {
    int id;
    char nome[50];
    float preco_venda;
    Pilha ingredientes; // agora é uma pilha
} Hamburguer;

// Cria um hambúrguer a partir de array de ids de ingredientes
Hamburguer criar_hamburguer(
    int id, 
    const char* nome, 
    float preco, 
    const int* ing_ids, 
    int qtd
);



int hamburguer_get_id(const Hamburguer* h);
const char* hamburguer_get_nome(const Hamburguer* h);
float hamburguer_get_preco_venda(const Hamburguer* h);
int hamburguer_get_qtd_ingredientes(const Hamburguer* h);
Pilha hamburguer_get_ingredientes(Hamburguer* h); // ou retorna Pilha por cópia

#endif
