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
        return; 
    }
    novo_no->ingrediente = ingrediente;
    novo_no->proximo = pilha->topo;
    pilha->topo = novo_no;
}

int desempilhar_ingrediente(PilhaIngredientes* pilha, Ingrediente* ingrediente_removido) {
    if (pilha == NULL || pilha->topo == NULL) {
        return 0; 
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
    while (desempilhar_ingrediente(pilha, &ing_temp)); 
    free(pilha); 
}

PilhaIngredientes* duplicar_pilha_ingredientes(const PilhaIngredientes* original) {
    if (original == NULL) return NULL;

    PilhaIngredientes* nova_pilha = criar_pilha_ingredientes();
    if (nova_pilha == NULL) return NULL;

    NoPilhaIngrediente* atual = original->topo;
    PilhaIngredientes* pilha_temp = criar_pilha_ingredientes(); 

    
    while (atual != NULL) {
        empilhar_ingrediente(pilha_temp, atual->ingrediente);
        atual = atual->proximo;
    }

    
    Ingrediente ing_temp;
    while (desempilhar_ingrediente(pilha_temp, &ing_temp)) {
        empilhar_ingrediente(nova_pilha, ing_temp);
    }

    destruir_pilha_ingredientes(pilha_temp);
    return nova_pilha;
}

int pilha_ingredientes_vazia(const PilhaIngredientes* pilha) {
    return (pilha == NULL || pilha->topo == NULL);
}

int pilha_ingredientes_tamanho(const PilhaIngredientes* pilha) {
    if (pilha == NULL) return 0;
    int tamanho = 0;
    NoPilhaIngrediente* atual = pilha->topo;
    while (atual != NULL) {
        tamanho++;
        atual = atual->proximo;
    }
    return tamanho;
}

