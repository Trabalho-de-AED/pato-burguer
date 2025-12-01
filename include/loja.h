#ifndef LOJA_H
#define LOJA_H

#include "ingrediente.h"
#include "ListaSE.h" 

typedef struct {
    tp_lista_encadeada* ingredientes_disponiveis; 
} Loja;

void inicializar_loja(Loja* loja);
int comprar_ingrediente(int id_ingrediente, int quantidade);
int vender_ingrediente(int id_ingrediente, int quantidade);
void destruir_loja(Loja* loja);

#endif
