#include "../include/caixa.h"

// Instância global do caixa
static Caixa g_caixa;

// Inicializa o caixa com saldo zero
void inicializar_caixa() {
    g_caixa.saldoTotal = 100.0f; // Saldo inicial para testes
}

// Adiciona um valor ao saldo do caixa
void atualizar_caixa(float valor) {
    g_caixa.saldoTotal += valor;
}

// Debita um valor do saldo do caixa
int debitar_do_caixa(float valor) {
    if (g_caixa.saldoTotal >= valor) {
        g_caixa.saldoTotal -= valor;
        return 1; // Sucesso
    }
    return 0; // Saldo insuficiente
}

// Retorna o saldo atual do caixa
float get_saldo_caixa() {
    return g_caixa.saldoTotal;
}
