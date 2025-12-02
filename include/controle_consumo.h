#ifndef CONTROLE_CONSUMO_H
#define CONTROLE_CONSUMO_H

#include "dados.h"

// Estrutura para rastrear o consumo de um único ingrediente durante o dia
typedef struct {
    int id_ingrediente;
    char nome[51];
    int quantidade;
} ConsumoDiario;

// Inicializa o controle de consumo para um novo dia
void inicializar_consumo_diario();

// Registra que uma unidade de um ingrediente foi consumida
void registrar_consumo_diario(int id_ingrediente, const char* nome, int quantidade);

// Retorna um ponteiro para a lista de consumo do dia e o número de itens
const ConsumoDiario* get_consumo_do_dia(int* num_itens);

#endif // CONTROLE_CONSUMO_H
