#ifndef CAIXA_H
#define CAIXA_H


typedef struct Caixa {
    float saldoTotal;
} Caixa;


void inicializar_caixa();
void atualizar_caixa(float valor);
int debitar_do_caixa(float valor); 
float get_saldo_caixa();

#endif 
