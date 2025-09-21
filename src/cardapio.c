#include "../include/cardapio.h"
#include <stdio.h>

void inicializar_cardapio(Cardapio* c) {
    c->quantidade = 0;
}

int adicionar_hamburguer(Cardapio* c, Hamburguer h) {
    if (c->quantidade < MAX_HAMBURGUERES) {
        c->hamburgueres[c->quantidade] = h;
        c->quantidade++;
        return 1;
    }
    return 0; 
}

int cardapio_get_quantidade(const Cardapio* c) {
    return c->quantidade;
}

const Hamburguer* cardapio_get_hamburguer(const Cardapio* c, int index) {
    if (index >= 0 && index < c->quantidade) {
        return &c->hamburgueres[index];
    }
    return NULL;
}

