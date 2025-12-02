#ifndef FILA_H
#define FILA_H

#define MAX 100

typedef void* tp_item; 

typedef struct {
    tp_item item[MAX];  
    int ini, fim;       
} Fila;

void inicializaFila(Fila *f);

int filaVazia(const Fila *f);

int filaCheia(const Fila *f);

int insereFila(Fila *f, tp_item e);

int removeFila(Fila *f, tp_item *e);

#endif