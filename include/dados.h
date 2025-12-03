#ifndef DADOS_H
#define DADOS_H

#include "ingrediente.h"
#include "hamburguer.h"
#include "loja.h"

#define MAX_INGREDIENTES 10
#define MAX_HAMBURGUERS 12

extern Ingrediente ingredientes[MAX_INGREDIENTES];
extern Hamburguer cardapio[MAX_HAMBURGUERS];
extern Loja loja_de_ingredientes;

void inicializa_dados();

Hamburguer* buscar_hamburguer_por_id(int id);

int get_total_ingredientes();

Ingrediente* buscar_ingrediente_por_id(int id);

#endif
