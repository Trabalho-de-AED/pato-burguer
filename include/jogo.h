#ifndef JOGO_H
#define JOGO_H

#include "cardapio.h"
#include "common/fila.h"
#include "common/pilha.h"

typedef struct {
    Cardapio cardapio;
    Fila fila_pedidos;
    Pilha pilha_ingredientes_consumidos;
    int dia;
    float moedas;
} Jogo;

void inicializar_jogo(Jogo* jogo);
void executar_dia(Jogo* jogo);
void finalizar_jogo(Jogo* jogo);

#endif
