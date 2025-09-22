#ifndef PILHA_H
#define PILHA_H

typedef struct {
    int dados[50];  // exemplo
    int topo;
} Pilha;

void inicializarPilha(Pilha *p); // inicializa
void push(Pilha *p, int valor);
int pop(Pilha *p, int *valor);
int tamanho(Pilha *p);

#endif