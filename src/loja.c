#include "loja.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dados.h"
#include "caixa.h"
#include "ListaSE.h"



void loja_inicializar(Loja* loja) {
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

    loja->nivel_atual = 1;
    loja->experiencia_total = 0;
    loja->xp_para_proximo_nivel = 100;
    loja->satisfacao_media_clientes = 100.0f;
}

int loja_get_nivel(const Loja* loja) {
    return loja->nivel_atual;
}

float loja_get_satisfacao_media(const Loja* loja) {
    return loja->satisfacao_media_clientes;
}

float obter_percentual_penalidade_por_nivel(int nivel) {
    float penalidade = 0.11f - (nivel * 0.01f);
    return (penalidade > 0.01f) ? penalidade : 0.01f;
}

int comprar_ingrediente(int id_ingrediente, int quantidade) {
    tp_lista_encadeada* no_ingrediente = busca_listase(loja_de_ingredientes.ingredientes_disponiveis, id_ingrediente);
    
    if (no_ingrediente == NULL) {
        printf(RED BOLD "[!] ERRO:" RESET " Ingrediente ID %d nao consta no catalogo da loja.\n", id_ingrediente);
        return 0; 
    }

    Ingrediente* ingrediente_info = buscar_ingrediente_por_id(id_ingrediente);
    if (ingrediente_info == NULL) {
        printf(RED "[!] ERRO CRITICO:" RESET " Dados do ingrediente %d corrompidos ou inexistentes.\n", id_ingrediente);
        return 0;
    }

    float custo_total = ingrediente_info->preco_compra * quantidade;

    if (!debitar_do_caixa(custo_total)) {
        printf(RED BOLD "[X] COMPRA RECUSADA:" RESET " Saldo insuficiente para gastar " RED "R$ %.2f" RESET ".\n", custo_total);
        return 0; 
    }

    Ingrediente* ingrediente_estoque = buscar_ingrediente_por_id(id_ingrediente);
    if (ingrediente_estoque == NULL) {
        printf(RED "[!] ERRO:" RESET " Falha ao localizar estoque fisico. O dinheiro foi estornado.\n");
        atualizar_caixa(custo_total);
        return 0; 
    }

    ingrediente_aumentar_estoque(ingrediente_estoque, quantidade);
    
    printf(CYAN "[+] ESTOQUE:" RESET " Voce comprou " BOLD "%d un." RESET " de " CYAN "%s" RESET ".\n", 
           quantidade, ingrediente_info->nome);
           
    return 1; 
}

void destruir_loja(Loja* loja) {
    if (loja) {
        destroi_listase(&(loja->ingredientes_disponiveis));
    }
}

void loja_atualizar_precos() {
    printf(YELLOW BOLD "\n>>> MERCADO:" RESET YELLOW " Os fornecedores atualizaram os precos para o novo dia!" RESET "\n");
    
    for (int i = 0; i < MAX_INGREDIENTES; i++) {
        Ingrediente* ing = &ingredientes[i];
        
        float fator = 1.0f + ((rand() % 31) - 15) / 100.0f;
        ing->preco_compra *= fator;

        if (ing->preco_compra < 0.5f) {
            ing->preco_compra = 0.5f;
        }
    }
}

int vender_ingrediente(int id_ingrediente, int quantidade) {
    Ingrediente* ingrediente_estoque = buscar_ingrediente_por_id(id_ingrediente);

    if (ingrediente_estoque == NULL) {
        printf(RED "[!] ERRO:" RESET " Ingrediente %d nao encontrado no estoque.\n", id_ingrediente);
        return 0;
    }

    int qtd_atual = ingrediente_get_quantidade(ingrediente_estoque);

    if (qtd_atual < quantidade) {
        printf(YELLOW BOLD "[!] ESTOQUE INSUFICIENTE:" RESET " Tentou vender " BOLD "%d" RESET ", mas so tem " BOLD "%d" RESET " de %s.\n",
               quantidade, qtd_atual, ingrediente_get_nome(ingrediente_estoque));
        return 0;
    }

    float preco_venda_unitario = ingrediente_estoque->preco_compra * 0.8; 
    float valor_total_venda = preco_venda_unitario * quantidade;

    ingrediente_diminuir_estoque(ingrediente_estoque, quantidade);
    atualizar_caixa(valor_total_venda); 

    printf(GREEN BOLD "[$] VENDA:" RESET " %d x %s vendidos por " GREEN BOLD "R$ %.2f" RESET "!\n",
           quantidade, ingrediente_get_nome(ingrediente_estoque), valor_total_venda);
           
    return 1;
}

int verificar_falencia() {
    if (get_total_ingredientes() <= 0 && get_saldo_caixa() <= 0) {
        return 1;
    }
    return 0;
}