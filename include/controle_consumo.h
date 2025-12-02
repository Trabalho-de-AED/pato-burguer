#ifndef CONTROLE_CONSUMO_H
#define CONTROLE_CONSUMO_H

#include "dados.h"

typedef struct {
    int id_ingrediente;
    char nome[51];
    int quantidade;
} ConsumoDiario;

void inicializar_consumo_diario();

void registrar_consumo_diario(int id_ingrediente, const char* nome, int quantidade);

const ConsumoDiario* get_consumo_do_dia(int* num_itens);

#endif 
