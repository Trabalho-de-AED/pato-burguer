#ifndef INGREDIENTE_H
#define INGREDIENTE_H

/**
 * @file ingrediente.h
 * @brief Definição da estrutura de dados Ingrediente e suas operações.
 *
 * Este arquivo define a estrutura de um ingrediente, incluindo suas propriedades
 * como nome, quantidade, preço, valor e tempo de preparo, e funções para criar
 * e acessar essas propriedades.
 */

/**
 * @brief Estrutura que representa um Ingrediente no jogo.
 */
typedef struct {
    int id; /**< Identificador único do ingrediente. */
    char nome[50]; /**< Nome do ingrediente. */
    int quantidade; /**< Quantidade atual do ingrediente em estoque. */
    float preco_compra; /**< Preço de compra do ingrediente. */
    float valor; /**< Valor do ingrediente (pode ser usado para cálculo de preço de venda). */
    int tempo_preparo; /**< Tempo necessário para preparar o ingrediente. */
    int nivel_desbloqueio; /**< Nível do jogo em que o ingrediente é desbloqueado. */
    int disponivel; /**< Flag que indica se o ingrediente está disponível (1) ou não (0). */
} Ingrediente;

/**
 * @brief Cria e inicializa uma nova estrutura Ingrediente.
 * @param id Identificador único do ingrediente.
 * @param nome Nome do ingrediente.
 * @param quantidade Quantidade inicial do ingrediente.
 * @param preco_compra Preço de compra do ingrediente.
 * @param valor Valor do ingrediente.
 * @param tempo_preparo Tempo de preparo do ingrediente.
 * @param nivel_desbloqueio Nível de desbloqueio do ingrediente.
 * @return Uma nova estrutura Ingrediente inicializada com os valores fornecidos.
 */
Ingrediente criar_ingrediente(
    int id,
    const char* nome,
    int quantidade,
    float preco_compra,
    float valor,
    int tempo_preparo,
    int nivel_desbloqueio
);

/**
 * @brief Retorna o ID do ingrediente.
 * @param ing Ponteiro constante para a estrutura Ingrediente.
 * @return O ID do ingrediente.
 */
int ingrediente_get_id(const Ingrediente* ing);

/**
 * @brief Retorna o nome do ingrediente.
 * @param ing Ponteiro constante para a estrutura Ingrediente.
 * @return O nome do ingrediente como uma string constante.
 */
const char* ingrediente_get_nome(const Ingrediente* ing);

/**
 * @brief Retorna a quantidade do ingrediente em estoque.
 * @param ing Ponteiro constante para a estrutura Ingrediente.
 * @return A quantidade do ingrediente.
 */
int ingrediente_get_quantidade(const Ingrediente* ing);

/**
 * @brief Retorna o preço de compra do ingrediente.
 * @param ing Ponteiro constante para a estrutura Ingrediente.
 * @return O preço de compra do ingrediente.
 */
float ingrediente_get_preco_compra(const Ingrediente* ing);

/**
 * @brief Retorna o valor do ingrediente.
 * @param ing Ponteiro constante para a estrutura Ingrediente.
 * @return O valor do ingrediente.
 */
float ingrediente_get_valor(const Ingrediente* ing);

/**
 * @brief Retorna o tempo de preparo do ingrediente.
 * @param ing Ponteiro constante para a estrutura Ingrediente.
 * @return O tempo de preparo do ingrediente.
 */
int ingrediente_get_tempo_preparo(const Ingrediente* ing);

/**
 * @brief Retorna o nível de desbloqueio do ingrediente.
 * @param ing Ponteiro constante para a estrutura Ingrediente.
 * @return O nível de desbloqueio do ingrediente.
 */
int ingrediente_get_nivel_desbloqueio(const Ingrediente* ing);

/**
 * @brief Retorna o status de disponibilidade do ingrediente.
 * @param ing Ponteiro constante para a estrutura Ingrediente.
 * @return 1 se o ingrediente estiver disponível, 0 caso contrário.
 */
int ingrediente_get_disponivel(const Ingrediente* ing);

#endif
