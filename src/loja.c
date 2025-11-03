#include "loja.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dados.h"
#include "caixa.h"

void inicializar_loja(Loja* loja) {
    loja->ingredientes = malloc(sizeof(IngredienteLoja) * 10); 
    if (!loja->ingredientes) {
        perror("Falha ao alocar memoria para loja");
        exit(EXIT_FAILURE);
    }
    loja->num_ingredientes = 0;
    loja->capacidade = 10;
}

void adicionar_ingrediente_loja(Loja* loja, int id, const char* nome, float preco, int estoque) {
    if (loja->num_ingredientes >= loja->capacidade) {
        
        loja->capacidade *= 2;
        loja->ingredientes = realloc(loja->ingredientes, sizeof(IngredienteLoja) * loja->capacidade);
        if (!loja->ingredientes) {
            perror("Falha ao realocar memoria para loja");
            exit(EXIT_FAILURE);
        }
    }

    IngredienteLoja* novo = &loja->ingredientes[loja->num_ingredientes++];
    novo->id_ingrediente = id;
    strncpy(novo->nome, nome, 49);
    novo->nome[49] = '\0';
    novo->preco_unitario = preco;
    novo->estoque_inicial = estoque;
}

int comprar_ingrediente(int id_ingrediente, int quantidade) {

    IngredienteLoja* item_loja = NULL;

    for (int i = 0; i < loja_de_ingredientes.num_ingredientes; i++) {

        if (loja_de_ingredientes.ingredientes[i].id_ingrediente == id_ingrediente) {

            item_loja = &loja_de_ingredientes.ingredientes[i];

            break;

        }

    }

    if (item_loja == NULL) {

        printf("Erro: Ingrediente nao encontrado na loja.\n");

        return 0; 

    }

    float custo_total = item_loja->preco_unitario * quantidade;

    if (!debitar_do_caixa(custo_total)) {

        printf("Compra falhou: Saldo insuficiente!\n");

        return 0; 

    }

    Ingrediente* ingrediente_estoque = buscar_ingrediente_por_id(id_ingrediente);

    if (ingrediente_estoque == NULL) {

        printf("Erro: Ingrediente nao encontrado no estoque principal.\n");

        atualizar_caixa(custo_total);

        return 0; 

    }

    ingrediente_aumentar_estoque(ingrediente_estoque, quantidade);

    printf("Compra de %d unidade(s) de %s realizada com sucesso!\n", quantidade, item_loja->nome);

    return 1; 

}

void exibir_loja(const Loja* loja) {
    
    printf("Funcao 'exibir_loja' ainda nao implementada.\n");
}

void destruir_loja(Loja* loja) {
    if (loja && loja->ingredientes) {
        free(loja->ingredientes);
        loja->ingredientes = NULL;
        loja->num_ingredientes = 0;
        loja->capacidade = 0;
    }
}
