#ifndef PILHA_H
#define PILHA_H
#define MAX 100 // Tamanho máximo da pilha

typedef void* tp_item;

typedef struct{
    tp_item item[MAX];
    int topo; // Índice do topo da pilha (último elemento inserido)
} Pilha;


void inicializarPilha(Pilha *p);
int pilhaVazia(Pilha *p);
int pilhaCheia(Pilha *p);
int empilhar(Pilha *p, tp_item e);
int desempilhar(Pilha *p, tp_item *e);
void imprimirPilha(Pilha p);


#endif// tp_item é definido como void* para permitir armazenar qualquer tipo de dado na pilha