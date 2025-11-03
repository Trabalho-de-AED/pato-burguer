#include "../include/pilha_ingredientes.h"
#include <stdlib.h>

PilhaIngredientes* criar_pilha_ingredientes() {
    PilhaIngredientes* pilha = (PilhaIngredientes*) malloc(sizeof(PilhaIngredientes));
    if (pilha != NULL) {
        pilha->topo = NULL;
    }
    return pilha;
}

void empilhar_ingrediente(PilhaIngredientes* pilha, Ingrediente ingrediente) {
    NoPilhaIngrediente* novo_no = (NoPilhaIngrediente*) malloc(sizeof(NoPilhaIngrediente));
    if (novo_no == NULL) {
        return; // Falha na alocação
    }
    novo_no->ingrediente = ingrediente;
    novo_no->proximo = pilha->topo;
    pilha->topo = novo_no;
}

int desempilhar_ingrediente(PilhaIngredientes* pilha, Ingrediente* ingrediente_removido) {
    if (pilha == NULL || pilha->topo == NULL) {
        return 0; // Pilha vazia
    }
    NoPilhaIngrediente* no_removido = pilha->topo;
    *ingrediente_removido = no_removido->ingrediente;
    pilha->topo = no_removido->proximo;
    free(no_removido);
    return 1;
}

void destruir_pilha_ingredientes(PilhaIngredientes* pilha) {
    if (pilha == NULL) return;
    Ingrediente ing_temp;
    while (desempilhar_ingrediente(pilha, &ing_temp)); // Esvazia a pilha, liberando os nós
    free(pilha); // Libera a estrutura da pilha em si
}
