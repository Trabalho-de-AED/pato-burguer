#include "controle_consumo.h"
#include <string.h>

// Array para armazenar o consumo do dia. MAX_INGREDIENTES é o número máximo de tipos de ingredientes.
static ConsumoDiario consumo_do_dia[MAX_INGREDIENTES];
static int num_itens_consumidos = 0;

void inicializar_consumo_diario() {
    num_itens_consumidos = 0;
    // Limpa o array para evitar dados do dia anterior
    for (int i = 0; i < MAX_INGREDIENTES; i++) {
        consumo_do_dia[i].id_ingrediente = 0;
        consumo_do_dia[i].quantidade = 0;
        strcpy(consumo_do_dia[i].nome, "");
    }
}

void registrar_consumo_diario(int id_ingrediente, const char* nome, int quantidade) {
    // Procura se o ingrediente já foi consumido hoje
    for (int i = 0; i < num_itens_consumidos; i++) {
        if (consumo_do_dia[i].id_ingrediente == id_ingrediente) {
            consumo_do_dia[i].quantidade += quantidade;
            return;
        }
    }

    // Se não encontrou, adiciona um novo registro (se houver espaço)
    if (num_itens_consumidos < MAX_INGREDIENTES) {
        consumo_do_dia[num_itens_consumidos].id_ingrediente = id_ingrediente;
        strncpy(consumo_do_dia[num_itens_consumidos].nome, nome, 50);
        consumo_do_dia[num_itens_consumidos].nome[50] = '\0';
        consumo_do_dia[num_itens_consumidos].quantidade = quantidade;
        num_itens_consumidos++;
    }
}

const ConsumoDiario* get_consumo_do_dia(int* num_itens) {
    *num_itens = num_itens_consumidos;
    return consumo_do_dia;
}
