#ifndef LOJA_H
#define LOJA_H

#include "ingrediente.h"

// Estrutura para representar um ingrediente disponível na loja
typedef struct {
    int id_ingrediente; // ID para vincular ao ingrediente principal
    char nome[50];
    float preco_unitario;
    int estoque_inicial; // Quantidade que a loja oferece para compra
} IngredienteLoja;

// Estrutura para representar a loja
typedef struct {
    IngredienteLoja* ingredientes;
    int num_ingredientes;
    int capacidade;
} Loja;

// Funções para manipular a loja
void inicializar_loja(Loja* loja);
void adicionar_ingrediente_loja(Loja* loja, int id, const char* nome, float preco, int estoque);
int comprar_ingrediente(int id_ingrediente, int quantidade);
void exibir_loja(const Loja* loja);
void destruir_loja(Loja* loja);

#endif // LOJA_H
