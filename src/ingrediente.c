#include "../include/ingrediente.h"
#include <string.h>

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
) {
    Ingrediente ing;
    ing.id = id;
    strncpy(ing.nome, nome, sizeof(ing.nome) - 1);
    ing.nome[sizeof(ing.nome) - 1] = '\0';
    ing.quantidade = quantidade;
    ing.preco_compra = preco_compra;
    ing.valor = valor;
    ing.tempo_preparo = tempo_preparo;
    ing.nivel_desbloqueio = nivel_desbloqueio;
    ing.disponivel = (quantidade > 0) ? 1 : 0;

    return ing;
}

/**
 * @brief Retorna o ID do ingrediente.
 * @param ing Ponteiro constante para a estrutura Ingrediente.
 * @return O ID do ingrediente.
 */
int ingrediente_get_id(const Ingrediente* ing) {
    return ing->id;
}

/**
 * @brief Retorna o nome do ingrediente.
 * @param ing Ponteiro constante para a estrutura Ingrediente.
 * @return O nome do ingrediente como uma string constante.
 */
const char* ingrediente_get_nome(const Ingrediente* ing) {
    return ing->nome;
}

/**
 * @brief Retorna a quantidade do ingrediente em estoque.
 * @param ing Ponteiro constante para a estrutura Ingrediente.
 * @return A quantidade do ingrediente.
 */
int ingrediente_get_quantidade(const Ingrediente* ing) {
    return ing->quantidade;
}

/**
 * @brief Retorna o preço de compra do ingrediente.
 * @param ing Ponteiro constante para a estrutura Ingrediente.
 * @return O preço de compra do ingrediente.
 */
float ingrediente_get_preco_compra(const Ingrediente* ing) {
    return ing->preco_compra;
}

/**
 * @brief Retorna o valor do ingrediente.
 * @param ing Ponteiro constante para a estrutura Ingrediente.
 * @return O valor do ingrediente.
 */
float ingrediente_get_valor(const Ingrediente* ing) {
    return ing->valor;
}

/**
 * @brief Retorna o tempo de preparo do ingrediente.
 * @param ing Ponteiro constante para a estrutura Ingrediente.
 * @return O tempo de preparo do ingrediente.
 */
int ingrediente_get_tempo_preparo(const Ingrediente* ing) {
    return ing->tempo_preparo;
}

/**
 * @brief Retorna o nível de desbloqueio do ingrediente.
 * @param ing Ponteiro constante para a estrutura Ingrediente.
 * @return O nível de desbloqueio do ingrediente.
 */
int ingrediente_get_nivel_desbloqueio(const Ingrediente* ing) {
    return ing->nivel_desbloqueio;
}

/**

 * @brief Retorna o status de disponibilidade do ingrediente.

 * @param ing Ponteiro constante para a estrutura Ingrediente.

 * @return 1 se o ingrediente estiver disponível, 0 caso contrário.

 */

int ingrediente_get_disponivel(const Ingrediente* ing) {

    return ing->disponivel;

}



/**

 * @brief Aumenta a quantidade de um ingrediente no estoque.

 * @param ing Ponteiro para a estrutura Ingrediente.

 * @param quantidade A quantidade a ser adicionada.

 */

void ingrediente_aumentar_estoque(Ingrediente* ing, int quantidade) {

    if (ing != NULL) {

        ing->quantidade += quantidade;

        if (ing->quantidade > 0) {

            ing->disponivel = 1;

        }

    }

}

/**
 * @brief Diminui a quantidade de um ingrediente no estoque.
 * @param ing Ponteiro para a estrutura Ingrediente.
 * @param quantidade A quantidade a ser removida.
 */
void ingrediente_diminuir_estoque(Ingrediente* ing, int quantidade) {
    if (ing != NULL) {
        ing->quantidade -= quantidade;
        if (ing->quantidade <= 0) {
            ing->quantidade = 0;
            ing->disponivel = 0;
        }
    }
}