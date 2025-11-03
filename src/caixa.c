#include "../include/caixa.h"

// Instância global do caixa
static Caixa g_caixa;

// Inicializa o caixa com saldo zero
void inicializar_caixa() {
    g_caixa.saldoTotal = 0.0f;
}

// Adiciona um valor ao saldo do caixa
void atualizar_caixa(float valor) {
    g_caixa.saldoTotal += valor;
}

// Retorna o saldo atual do caixa
float get_saldo_caixa() {
    return g_caixa.saldoTotal;
}
