#include "../include/caixa.h"
#include "../include/config.h"
#include "../include/ui.h"


static Caixa g_caixa;


void inicializar_caixa() {
    g_caixa.saldoTotal = 100.0f; 
    g_caixa.saldo_inicio_dia = 100.0f;
}

void caixa_iniciar_dia() {
    g_caixa.saldo_inicio_dia = g_caixa.saldoTotal;
}

float caixa_get_lucro_dia() {
    return g_caixa.saldoTotal - g_caixa.saldo_inicio_dia;
}


void atualizar_caixa(float valor) {
    g_caixa.saldoTotal += valor;
}


int debitar_do_caixa(float valor) {
    g_caixa.saldoTotal -= valor;
    return 1; 
}


float get_saldo_caixa() {
    return g_caixa.saldoTotal;
}

int verificar_e_aplicar_limite_saldo_caixa() {
    if (g_caixa.saldoTotal < CAIXA_LIMITE_SALDO_NEGATIVO) {
        g_caixa.saldoTotal = 1000.0f;
        ui_exibir_mensagem_importante("O governo teve que empenhar a sua loja devido a divida alta.");
        return 1;
    }
    return 0;
}
