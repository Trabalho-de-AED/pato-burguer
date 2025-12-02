#include "loja.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dados.h"
#include "caixa.h"
#include "ListaSE.h"

void inicializar_loja(Loja* loja) {
    loja->ingredientes_disponiveis = inicializa_listase(); 
    
    insere_listase_no_fim(&(loja->ingredientes_disponiveis), 1);
    insere_listase_no_fim(&(loja->ingredientes_disponiveis), 2);
    insere_listase_no_fim(&(loja->ingredientes_disponiveis), 3); 
    insere_listase_no_fim(&(loja->ingredientes_disponiveis), 4);
    insere_listase_no_fim(&(loja->ingredientes_disponiveis), 5);
    insere_listase_no_fim(&(loja->ingredientes_disponiveis), 6); 
    insere_listase_no_fim(&(loja->ingredientes_disponiveis), 7); 
    insere_listase_no_fim(&(loja->ingredientes_disponiveis), 8);
    insere_listase_no_fim(&(loja->ingredientes_disponiveis), 9); 
    insere_listase_no_fim(&(loja->ingredientes_disponiveis), 10);
}

int comprar_ingrediente(int id_ingrediente, int quantidade) {
    tp_lista_encadeada* no_ingrediente = busca_listase(loja_de_ingredientes.ingredientes_disponiveis, id_ingrediente);
    
    if (no_ingrediente == NULL) {
        printf("Erro: Ingrediente %d nao encontrado na loja.\n", id_ingrediente);
        return 0; 
    }

    Ingrediente* ingrediente_info = buscar_ingrediente_por_id(id_ingrediente);
    if (ingrediente_info == NULL) {
        printf("Erro interno: Informacoes do ingrediente %d nao encontradas.\n", id_ingrediente);
        return 0;
    }

    float custo_total = ingrediente_info->preco_compra * quantidade;

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
    printf("Compra de %d unidade(s) de %s realizada com sucesso!\n", quantidade, ingrediente_info->nome);
    return 1; 
}


void destruir_loja(Loja* loja) {
    if (loja) {
        destroi_listase(&(loja->ingredientes_disponiveis));
    }
}

int vender_ingrediente(int id_ingrediente, int quantidade) {
    Ingrediente* ingrediente_estoque = buscar_ingrediente_por_id(id_ingrediente);

    if (ingrediente_estoque == NULL) {
        printf("Erro: Ingrediente %d nao encontrado no estoque.\n", id_ingrediente);
        return 0;
    }

    if (ingrediente_get_quantidade(ingrediente_estoque) < quantidade) {
        printf("Erro: Voce nao tem %d unidade(s) de %s para vender. Estoque atual: %d.\n",
               quantidade, ingrediente_get_nome(ingrediente_estoque), ingrediente_get_quantidade(ingrediente_estoque));
        return 0;
    }

    float preco_venda_unitario = ingrediente_estoque->preco_compra * 0.8; 
    float valor_total_venda = preco_venda_unitario * quantidade;

    ingrediente_diminuir_estoque(ingrediente_estoque, quantidade);
    atualizar_caixa(valor_total_venda); 

    printf("Venda de %d unidade(s) de %s realizada com sucesso por R$%.2f!\n",
           quantidade, ingrediente_get_nome(ingrediente_estoque), valor_total_venda);
    return 1;
}

