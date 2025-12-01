#ifndef LISTASE_H
#define LISTASE_H

#include <stdio.h>
#include <stdlib.h>

typedef int tp_item_listase;

typedef struct tp_no {
    tp_item_listase info;
    struct tp_no* prox;
} tp_lista_encadeada;

tp_lista_encadeada* inicializa_listase();
int listase_vazia(tp_lista_encadeada* lista);
tp_lista_encadeada* aloca_listase();
int insere_listase_no_fim(tp_lista_encadeada** l, tp_item_listase e);
void imprime_listase(tp_lista_encadeada* lista);
int remove_listase(tp_lista_encadeada** lista, tp_item_listase e);
tp_lista_encadeada* busca_listase(tp_lista_encadeada* lista, tp_item_listase e);
int tamanho_listase(tp_lista_encadeada* lista);
void destroi_listase(tp_lista_encadeada** l);

#endif