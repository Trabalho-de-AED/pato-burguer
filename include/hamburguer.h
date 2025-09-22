#ifndef HAMBURGUER_H
#define HAMBURGUER_H

/**
 * @file hamburguer.h
 * @brief Definição da estrutura de dados Hamburguer e suas operações.
 *
 * Este arquivo define a estrutura de um hambúrguer, incluindo seus ingredientes
 * armazenados em uma pilha, e funções para criar e acessar suas propriedades.
 */

/**
 * @brief Define o número máximo de ingredientes que um hambúrguer pode ter.
 */
#define MAX_INGREDIENTES 10

#include "pilha.h"

/**
 * @brief Estrutura que representa um Hambúrguer no cardápio.
 */
typedef struct {
    int id; /**< Identificador único do hambúrguer. */
    char nome[50]; /**< Nome do hambúrguer. */
    float preco_venda; /**< Preço de venda do hambúrguer. */
    Pilha ingredientes; /**< Pilha de IDs de ingredientes que compõem o hambúrguer. */
} Hamburguer;

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
Hamburguer criar_hamburguer(
    int id, 
    const char* nome, 
    float preco, 
    const int* ing_ids, 
    int qtd
);

/**
 * @brief Retorna o ID do hambúrguer.
 * @param h Ponteiro constante para a estrutura Hamburguer.
 * @return O ID do hambúrguer.
 */
int hamburguer_get_id(const Hamburguer* h);

/**
 * @brief Retorna o nome do hambúrguer.
 * @param h Ponteiro constante para a estrutura Hamburguer.
 * @return O nome do hambúrguer como uma string constante.
 */
const char* hamburguer_get_nome(const Hamburguer* h);

/**
 * @brief Retorna o preço de venda do hambúrguer.
 * @param h Ponteiro constante para a estrutura Hamburguer.
 * @return O preço de venda do hambúrguer.
 */
float hamburguer_get_preco_venda(const Hamburguer* h);

/**
 * @brief Retorna a quantidade de ingredientes no hambúrguer.
 * @param h Ponteiro constante para a estrutura Hamburguer.
 * @return A quantidade de ingredientes na pilha do hambúrguer.
 */
int hamburguer_get_qtd_ingredientes(const Hamburguer* h);

/**
 * @brief Retorna uma cópia da pilha de ingredientes do hambúrguer.
 * @param h Ponteiro para a estrutura Hamburguer.
 * @return Uma cópia da Pilha de ingredientes.
 */
Pilha hamburguer_get_ingredientes(Hamburguer* h);

#endif