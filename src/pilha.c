#include "pilha.h"

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

int tamanho(Pilha *p) {
    return p->topo;
}
