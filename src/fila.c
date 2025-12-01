#include "../include/fila.h" 
#include <stdio.h> 

void inicializaFila(Fila *f){
    f-> ini = f-> fim = MAX-1;
}

int filaVazia(const Fila *f){
    return (f->ini==f->fim);
}

int proximo (int pos){
    return (pos+1) % MAX;
}

int filaCheia(const Fila *f){
    return (proximo(f->fim)==f->ini);
}

int removeFila (Fila *f, tp_item *e){
    if(filaVazia(f)) return 0; 
    f->ini = proximo(f->ini); 
    *e = f-> item[f->ini]; 
    return 1;
}

int insereFila(Fila *f, tp_item e){
    if(filaCheia(f)) return 0;          
    f->fim = proximo(f->fim);           
    f->item[f->fim] = e;                
    return 1;
}
