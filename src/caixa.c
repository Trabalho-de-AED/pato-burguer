#include "../include/caixa.h"


static Caixa g_caixa;


void inicializar_caixa() {
    g_caixa.saldoTotal = 100.0f; 
}


void atualizar_caixa(float valor) {
    g_caixa.saldoTotal += valor;
}


int debitar_do_caixa(float valor) {
    if (g_caixa.saldoTotal >= valor) {
        g_caixa.saldoTotal -= valor;
        return 1; 
    }
    return 0; 
}


float get_saldo_caixa() {
    return g_caixa.saldoTotal;
}
