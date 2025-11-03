#include "../include/caixa.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float saldo_total;
    int numTransacoes;
}tp_caixa;

tp_caixa* incializaCaixa(){
    tp_caixa* c = (tp_caixa*) malloc(sizeof(tp_caixa));
    if(c == NULL)
    {   
        printf("Não foi possivel alocar memoria para o caixa\n");
        exit(1);
    }
    c->saldo_total = 0.0;
    c->numTransacoes = 0;
    return c;
}

int atualizaCaixa(tp_caixa *c,int valor){
    int NovoSaldo;
    if(c == NULL){
        printf("Caixa não inializado\n");
        return 0;
    }
    NovoSaldo = c->saldo_total + valor;
    if(NovoSaldo < 0){
        printf("Operação invalida! O saldo nao pode ser negativo.\n");
        return 0;
    }
    
    c->saldo_total = NovoSaldo;
    c->numTransacoes++;
}

int exibirCaixa(tp_caixa *c){
    
    printf("\n=== SALDO ATUAL DO CAIXA ===\n");
    printf("Saldo total: R$ %.2f\n", c->saldo_total);
    printf("Transações registradas: %d\n", c->numTransacoes);
    printf("============================\n\n");
    
}
    
int liberarCaixa(tp_caixa *c){
    if(c != NULL){
        free(c);
        printf("memoria liberada com sucesso");
    }
    
}