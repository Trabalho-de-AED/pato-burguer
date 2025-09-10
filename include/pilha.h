#ifndef PILHA_H
#define PILHA_H
#define MAX 100 // Tamanho máximo da pilha

typedef void* tp_item;

typedef struct{
    tp_item item[MAX];
    int topo; // Índice do topo da pilha (último elemento inserido)
} tp_pilha;


void inicializarPilha(tp_pilha *p);
int pilhaVazia(tp_pilha *p);
int pilhaCheia(tp_pilha *p);
int empilhar(tp_pilha *p, tp_item e);
int desempilhar(tp_pilha *p, tp_item *e);
void imprimirPilha(tp_pilha p);


#endif// tp_item é definido como void* para permitir armazenar qualquer tipo de dado na pilha