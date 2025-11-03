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

/**
 * @brief Busca um hambúrguer no cardápio pelo seu ID.
 * @param id O ID do hambúrguer a ser buscado.
 * @return Ponteiro para o hambúrguer se encontrado, NULL caso contrário.
 */
Hamburguer* buscar_hamburguer_por_id(int id);

/**
 * @brief Busca um ingrediente na lista de ingredientes pelo seu ID.
 * @param id O ID do ingrediente a ser buscado.
 * @return Ponteiro para o ingrediente se encontrado, NULL caso contrário.
 */
Ingrediente* buscar_ingrediente_por_id(int id);

#endif
