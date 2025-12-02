#include "pilha.h"
#include <stdlib.h>
#include <string.h>

void inicializarPilha(Pilha *p) {
    p->topo = 0;
}

void push(Pilha *p, int valor) {
    if (p->topo < 50) {
        p->dados[p->topo++] = valor;
    }
}

int pop(Pilha *p, int *valor) {
    if (p->topo > 0) {
        *valor = p->dados[--p->topo];
        return 1;
    }
    return 0;
}

int tamanho(const Pilha *p) {
    return p->topo;
}

Pilha* pilha_duplicar(const Pilha* p) {
    Pilha* nova_pilha = (Pilha*) malloc(sizeof(Pilha));
    if (nova_pilha != NULL) {
        memcpy(nova_pilha, p, sizeof(Pilha));
    }
    return nova_pilha;
}