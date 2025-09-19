#ifndef CARDAPIO_H
#define CARDAPIO_H

#include "hamburguer.h"

#define MAX_HAMBURGUERES 20

typedef struct {
    Hamburguer hamburgueres[MAX_HAMBURGUERES];
    int quantidade;
} Cardapio;

void inicializar_cardapio(Cardapio* c);
int adicionar_hamburguer(Cardapio* c, Hamburguer h);

int cardapio_get_quantidade(const Cardapio* c);
const Hamburguer* cardapio_get_hamburguer(const Cardapio* c, int index);

#endif
