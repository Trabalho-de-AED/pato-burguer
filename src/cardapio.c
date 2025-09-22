#include "../include/cardapio.h"
#include <stdio.h>

/**
 * @brief Inicializa a estrutura do cardápio.
 *        Define a quantidade de hambúrgueres no cardápio como zero.
 * @param c Ponteiro para a estrutura Cardapio a ser inicializada.
 */
void inicializar_cardapio(Cardapio* c) {
    c->quantidade = 0;
}

/**
 * @brief Adiciona um hambúrguer ao cardápio.
 *        Verifica se há espaço disponível antes de adicionar.
 * @param c Ponteiro para a estrutura Cardapio onde o hambúrguer será adicionado.
 * @param h O hambúrguer a ser adicionado.
 * @return 1 se o hambúrguer foi adicionado com sucesso, 0 se o cardápio estiver cheio.
 */
int adicionar_hamburguer(Cardapio* c, Hamburguer h) {
    if (c->quantidade < MAX_HAMBURGUERES) {
        c->hamburgueres[c->quantidade] = h;
        c->quantidade++;
        return 1;
    }
    return 0; 
}

/**
 * @brief Retorna a quantidade atual de hambúrgueres no cardápio.
 * @param c Ponteiro constante para a estrutura Cardapio.
 * @return A quantidade de hambúrgueres no cardápio.
 */
int cardapio_get_quantidade(const Cardapio* c) {
    return c->quantidade;
}

/**
 * @brief Retorna um ponteiro para um hambúrguer específico no cardápio.
 *        Verifica se o índice é válido antes de retornar o hambúrguer.
 * @param c Ponteiro constante para a estrutura Cardapio.
 * @param index O índice do hambúrguer desejado no array.
 * @return Ponteiro constante para o hambúrguer, ou NULL se o índice for inválido.
 */
const Hamburguer* cardapio_get_hamburguer(const Cardapio* c, int index) {
    if (index >= 0 && index < c->quantidade) {
        return &c->hamburgueres[index];
    }
    return NULL;
}