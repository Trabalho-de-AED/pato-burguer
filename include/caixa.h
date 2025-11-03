#ifndef CAIXA_H
#define CAIXA_H

// Estrutura para representar o caixa
typedef struct Caixa {
    float saldoTotal;
} Caixa;

// Funções para manipular o caixa
void inicializar_caixa();
void atualizar_caixa(float valor);
int debitar_do_caixa(float valor); // 1 para sucesso, 0 para falha
float get_saldo_caixa();

#endif // CAIXA_H
