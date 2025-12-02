#ifndef PILHA_INGREDIENTES_H
#define PILHA_INGREDIENTES_H

#include "ingrediente.h"

typedef struct NoPilhaIngrediente {
    Ingrediente ingrediente;
    struct NoPilhaIngrediente* proximo;
} NoPilhaIngrediente;

typedef struct {
    NoPilhaIngrediente* topo;
} PilhaIngredientes;

PilhaIngredientes* criar_pilha_ingredientes();

void empilhar_ingrediente(PilhaIngredientes* pilha, Ingrediente ingrediente);

int desempilhar_ingrediente(PilhaIngredientes* pilha, Ingrediente* ingrediente_removido);

void destruir_pilha_ingredientes(PilhaIngredientes* pilha);

PilhaIngredientes* duplicar_pilha_ingredientes(const PilhaIngredientes* original);

int pilha_ingredientes_vazia(const PilhaIngredientes* pilha);

int pilha_ingredientes_tamanho(const PilhaIngredientes* pilha);

#endif 
