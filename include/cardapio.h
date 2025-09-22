#ifndef CARDAPIO_H
#define CARDAPIO_H

#include "hamburguer.h"

/**
 * @brief Define o número máximo de hambúrgueres que o cardápio pode conter.
 */
#define MAX_HAMBURGUERES 20

/**
 * @brief Estrutura que representa o cardápio do restaurante.
 */
typedef struct {
    Hamburguer hamburgueres[MAX_HAMBURGUERES];
    int quantidade;
} Cardapio;

/**
 * @brief Inicializa a estrutura do cardápio.
 * @param c Ponteiro para a estrutura Cardapio a ser inicializada.
 */
void inicializar_cardapio(Cardapio* c);

/**
 * @brief Adiciona um hambúrguer ao cardápio.
 * @param c Ponteiro para a estrutura Cardapio onde o hambúrguer será adicionado.
 * @param h O hambúrguer a ser adicionado.
 * @return 1 se o hambúrguer foi adicionado com sucesso, 0 se o cardápio estiver cheio.
 */
int adicionar_hamburguer(Cardapio* c, Hamburguer h);

/**
 * @brief Retorna a quantidade atual de hambúrgueres no cardápio.
 * @param c Ponteiro constante para a estrutura Cardapio.
 * @return A quantidade de hambúrgueres no cardápio.
 */
int cardapio_get_quantidade(const Cardapio* c);

/**
 * @brief Retorna um ponteiro para um hambúrguer específico no cardápio.
 * @param c Ponteiro constante para a estrutura Cardapio.
 * @param index O índice do hambúrguer desejado no array.
 * @return Ponteiro constante para o hambúrguer, ou NULL se o índice for inválido.
 */
const Hamburguer* cardapio_get_hamburguer(const Cardapio* c, int index);

#endif
