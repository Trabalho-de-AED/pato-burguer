#include "dados.h"
#include "config.h"
#include <stdlib.h>

/**
 * @brief Array global de ingredientes disponíveis no jogo.
 *        Contém todos os ingredientes com suas propriedades e quantidades iniciais.
 */
Ingrediente ingredientes[MAX_INGREDIENTES];

/**
 * @brief Array global de hambúrgueres disponíveis no cardápio.
 *        Contém todos os hambúrgueres com suas receitas e preços.
 */
Hamburguer cardapio[MAX_HAMBURGUERS];

/**
 * @brief Inicializa todos os dados do jogo, incluindo ingredientes e cardápio.
 *        Esta função deve ser chamada uma vez no início do programa para popular
 *        as estruturas de dados globais com valores pré-definidos.
 */
void inicializa_dados() {
    ingredientes[0] = criar_ingrediente(1,"Pao",50,1.0,2.0,1,1);
    ingredientes[1] = criar_ingrediente(2,"Carne",50,2.0,4.0,2,1);
    ingredientes[2] = criar_ingrediente(3,"Queijo",40,1.5,3.0,1,2);
    ingredientes[3] = criar_ingrediente(4,"Alface",40,0.5,1.0,1,2);
    ingredientes[4] = criar_ingrediente(5,"Molho",30,0.2,0.5,1,1);
    ingredientes[5] = criar_ingrediente(6,"Bacon",30,1.5,3.5,2,2);
    ingredientes[6] = criar_ingrediente(7,"Tomate",25,0.5,1.0,1,2);
    ingredientes[7] = criar_ingrediente(8,"Ovo",20,0.7,1.5,1,2);
    ingredientes[8] = criar_ingrediente(9,"Cebola",20,0.3,0.8,1,2);
    ingredientes[9] = criar_ingrediente(10,"Pepperoni",15,1.0,2.5,1,3);

    int ids1[] = {1,2,6};
    int ids2[] = {1,2,3};
    int ids3[] = {1,2,3,6};
    int ids4[] = {1,2,3,4,5};
    int ids5[] = {1,2,3,4,6,7};
    int ids6[] = {1,3,4,7,9};
    int ids7[] = {1,3,4,8};
    int ids8[] = {1,2,6,6};
    int ids9[] = {1,2,3,4,5,6,7,8};
    int ids10[] = {1,2,3,3};
    int ids11[] = {1,2,6,8};
    int ids12[] = {1,2,3,4,5,6,7,8,9,10};

    cardapio[0] = criar_hamburguer(1,"Bit and Bacon",12.0,ids1,3);
    cardapio[1] = criar_hamburguer(2,"Duck Cheese",13.0,ids2,3);
    cardapio[2] = criar_hamburguer(3,"Quackteirao",15.0,ids3,4);
    cardapio[3] = criar_hamburguer(4,"Big Pato",16.0,ids4,5);
    cardapio[4] = criar_hamburguer(5,"Pato Deluxe",18.0,ids5,6);
    cardapio[5] = criar_hamburguer(6,"Pato Veggie",14.0,ids6,5);
    cardapio[6] = criar_hamburguer(7,"Pato Chicken",15.0,ids7,4);
    cardapio[7] = criar_hamburguer(8,"Quack Bacon",16.0,ids8,4);
    cardapio[8] = criar_hamburguer(9,"Pato Supreme",20.0,ids9,8);
    cardapio[9] = criar_hamburguer(10,"Cheesy Duck",14.0,ids10,4);
    cardapio[10] = criar_hamburguer(11,"Bacon Egg Duck",17.0,ids11,4);
    cardapio[11] = criar_hamburguer(12,"Pato Especial",22.0,ids12,10);
}