#ifndef DADOS_H
#define DADOS_H

#include "ingrediente.h"
#include "hamburguer.h"
#include "loja.h"

#define MAX_INGREDIENTES 10
#define MAX_HAMBURGUERS 12

#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define WHITE   "\x1b[37m"
#define BOLD    "\x1b[1m"
#define BG_BLUE "\x1b[44m"

extern Ingrediente ingredientes[MAX_INGREDIENTES];
extern Hamburguer cardapio[MAX_HAMBURGUERS];
extern Loja loja_de_ingredientes;

void inicializa_dados();

Hamburguer* buscar_hamburguer_por_id(int id);

int get_total_ingredientes();

Ingrediente* buscar_ingrediente_por_id(int id);

#endif
