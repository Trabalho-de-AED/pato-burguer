#ifndef CAIXA_H
#define CAIXA_H


typedef struct Caixa {
    float saldoTotal;
    float saldo_inicio_dia;
} Caixa;


void inicializar_caixa();
void atualizar_caixa(float valor);
int debitar_do_caixa(float valor); 
float get_saldo_caixa();
void caixa_iniciar_dia();
float caixa_get_lucro_dia();
int verificar_e_aplicar_limite_saldo_caixa();

#endif 
