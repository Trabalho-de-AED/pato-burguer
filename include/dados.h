#ifndef DADOS_H
#define DADOS_H

#include "ingrediente.h"
#include "hamburguer.h"

#define MAX_INGREDIENTES 10
#define MAX_HAMBURGUERS 12

extern Ingrediente ingredientes[MAX_INGREDIENTES];
extern Hamburguer cardapio[MAX_HAMBURGUERS];

void inicializa_dados();

#endif
