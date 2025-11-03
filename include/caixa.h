#ifndef CAIXA_H
#define CAIXA_H

typedef struct{
    float saldo_total;
    int numTransacoes;
}tp_caixa;

tp_caixa* incializaCaixa();
// Função para inicializar o caixa
//retorna um tp_caixa com saldo zero e zero transações

int atualizaCaixa(tp_caixa *c,int valor);
// Função para atualizar o saldo do caixa
//recebe um ponteiro para o caixa e o valor a ser adicionado (positivo ou negativo)
//retorna 0 em caso de erro (caixa não inicializado ou saldo negativo), caso contrário não retorna nada

int exibirCaixa(tp_caixa *c);
// Função para exibir o saldo atual do caixa e o número de transações
//recebe um ponteiro para o caixa
//exibe o saldo e o número de transações no console

int liberarCaixa(tp_caixa *c);
// Função para liberar a memória alocada para o caixa
//recebe um ponteiro para o caixa

#endif