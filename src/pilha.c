#include "pilha.h" //Inclui a definição da struct tp_pilha e o tipo tp_item
#include <stdio.h> // Inclui a biblioteca que permite usar o printf na função imprimirPilha

void inicializarPilha(tp_pilha *p){
    p->topo = -1; // Inicializa o topo da pilha como -1, indicando que a pilha está vazia
}

int pilhaVazia(tp_pilha *p){
    return (p->topo == -1); // Retorna 1 se a pilha estiver vazia, caso contrário retorna 0
}

int pilhaCheia(tp_pilha *p){
    return (p->topo == MAX - 1); // Retorna 1 se a pilha estiver cheia, caso contrário retorna 0
}

int empilhar(tp_pilha *p, tp_item e){
    if (pilhaCheia(p)) return 0; // Verifica se a pilha está cheia
    p->topo++; // Incrementa o índice do topo, movendo o proximo elemento para cima
    p->item[p->topo] = e; // Adiciona o elemento no topo da pilha
    return 1;
}

int desempilhar(tp_pilha *p, tp_item *e){
    if(pilhaVazia(p)) return 0;; // Olha se a pilha está vazia, dai ele não pode desempilhar
    *e = p->item[p->topo]; // Vai até o elemento do topo na variável apontada por e
    p->topo--; // Decrementa o índice do topo, movend-o para baixo
    return 1;
}

void imprimirPilha(tp_pilha p){
    tp_item e;
    printf("Elementos da pilha:\n");

    tp_pilha temp; // Pilha temporária para armazenar os elementos sem perder os originais
    inicializaPilha(&temp);

    while(!pilhaVazia(&p)){ //desempilha os elementos da original e empilha na temporaria (temp)
        desempilhar(&p, &e);
        empilhar(&temp, &e);
        printf(" %p\n", e); // Imprime o endereço da pilha
    }

    while(!pilhaVazia(&temp)){ //devolve os elementos para a original
        desempilhar(&temp, &e);
        empilhar(&p, &e);
    }
}