#include "../include/hamburguer.h"
#include "../include/pilha.h"
#include <string.h>
#include <stdio.h>

/**
 * @brief Cria e inicializa uma nova estrutura Hamburguer.
 *        Os ingredientes são empilhados na ordem fornecida.
 * @param id Identificador único do hambúrguer.
 * @param nome Nome do hambúrguer.
 * @param preco Preço de venda do hambúrguer.
 * @param ing_ids Array de IDs de ingredientes que compõem o hambúrguer.
 * @param qtd Quantidade de ingredientes no array `ing_ids`.
 * @return Uma nova estrutura Hamburguer inicializada com os valores fornecidos.
 */
Hamburguer criar_hamburguer(int id, const char* nome, float preco, const int* ing_ids, int qtd) {
    Hamburguer h;
    h.id = id;
    strncpy(h.nome, nome, sizeof(h.nome));
    h.nome[sizeof(h.nome)-1] = '\0'; 
    h.preco_venda = preco;
    inicializarPilha(&h.ingredientes);
    for(int i=0;i<qtd;i++){
        push(&h.ingredientes, ing_ids[i]);
    }
    return h;
}

/**
 * @brief Retorna o ID do hambúrguer.
 * @param h Ponteiro constante para a estrutura Hamburguer.
 * @return O ID do hambúrguer.
 */
int hamburguer_get_id(const Hamburguer* h) {
    return h->id;
}

/**
 * @brief Retorna o nome do hambúrguer.
 * @param h Ponteiro constante para a estrutura Hamburguer.
 * @return O nome do hambúrguer como uma string constante.
 */
const char* hamburguer_get_nome(const Hamburguer* h) {
    return h->nome;
}

/**
 * @brief Retorna o preço de venda do hambúrguer.
 * @param h Ponteiro constante para a estrutura Hamburguer.
 * @return O preço de venda do hambúrguer.
 */
float hamburguer_get_preco_venda(const Hamburguer* h) {
    return h->preco_venda;
}

/**
 * @brief Retorna a quantidade de ingredientes no hambúrguer.
 * @param h Ponteiro constante para a estrutura Hamburguer.
 * @return A quantidade de ingredientes na pilha do hambúrguer.
 */
int hamburguer_get_qtd_ingredientes(const Hamburguer* h){
    return tamanho(&h->ingredientes); 
}

/**
 * @brief Retorna uma cópia da pilha de ingredientes do hambúrguer.
 * @param h Ponteiro para a estrutura Hamburguer.
 * @return Uma cópia da Pilha de ingredientes.
 */
Pilha hamburguer_get_ingredientes(Hamburguer* h){
    return h->ingredientes;
}