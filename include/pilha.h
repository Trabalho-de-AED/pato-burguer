#ifndef PILHA_H
#define PILHA_H

typedef struct {
    int dados[50];
    int topo;
} Pilha;

void inicializarPilha(Pilha *p);
void push(Pilha *p, int valor);
int pop(Pilha *p, int *valor);
int tamanho(const Pilha *p);

#endif