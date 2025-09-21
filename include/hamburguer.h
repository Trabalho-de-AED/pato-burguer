#ifndef HAMBURGUER_H
#define HAMBURGUER_H

#define MAX_INGREDIENTES 10

typedef struct {
    int id;
    char nome[50];
    float preco_venda;
    int ingredientes[MAX_INGREDIENTES];
    int qtd_ingredientes;
} Hamburguer;

Hamburguer criar_hamburguer(
    int id, 
    const char* nome, 
    float preco_venda, 
    int* ingredientes,
     int qtd_ingredientes
);

int hamburguer_get_id(const Hamburguer* h);
const char* hamburguer_get_nome(const Hamburguer* h);
float hamburguer_get_preco_venda(const Hamburguer* h);
const int* hamburguer_get_ingredientes(const Hamburguer* h);
int hamburguer_get_qtd_ingredientes(const Hamburguer* h);

#endif
