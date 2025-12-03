#include "dados.h"
#include "config.h"
#include <stdlib.h>

Ingrediente ingredientes[MAX_INGREDIENTES];

Hamburguer cardapio[MAX_HAMBURGUERS];

Loja loja_de_ingredientes;

void inicializa_dados() {
    ingredientes[0] = criar_ingrediente(1,"Pao",10,1.0,2.0,1,1);
    ingredientes[1] = criar_ingrediente(2,"Carne",10,2.0,4.0,2,1);
    ingredientes[2] = criar_ingrediente(3,"Queijo",10,1.5,3.0,1,2);
    ingredientes[3] = criar_ingrediente(4,"Alface",10,0.5,1.0,1,2);
    ingredientes[4] = criar_ingrediente(5,"Molho",10,0.2,0.5,1,1);
    ingredientes[5] = criar_ingrediente(6,"Bacon",10,1.5,3.5,2,2);
    ingredientes[6] = criar_ingrediente(7,"Tomate",10,0.5,1.0,1,2);
    ingredientes[7] = criar_ingrediente(8,"Ovo",10,0.7,1.5,1,2);
    ingredientes[8] = criar_ingrediente(9,"Cebola",10,0.3,0.8,1,2);
    ingredientes[9] = criar_ingrediente(10,"Pepperoni",10,1.0,2.5,1,3);

    
    loja_inicializar(&loja_de_ingredientes);

    int ids1[] = {1,2,6,1};
    int ids2[] = {1,2,3,1};
    int ids3[] = {1,2,3,6,1};
    int ids4[] = {1,2,3,4,5,1};
    int ids5[] = {1,2,3,4,6,7,1};
    int ids6[] = {1,3,4,7,9,1};
    int ids7[] = {1,3,4,8,1};
    int ids8[] = {1,2,6,6,1};
    int ids9[] = {1,2,3,4,5,6,7,8,1};
    int ids10[] = {1,2,3,3,1};
    int ids11[] = {1,2,6,8,1};
    int ids12[] = {1,2,3,4,5,6,7,8,9,10,1};

    cardapio[0] = criar_hamburguer(1,"Bit and Bacon",12.0,ids1,4);
    cardapio[1] = criar_hamburguer(2,"Duck Cheese",13.0,ids2,4);
    cardapio[2] = criar_hamburguer(3,"Quackteirao",15.0,ids3,5);
    cardapio[3] = criar_hamburguer(4,"Big Pato",16.0,ids4,6);
    cardapio[4] = criar_hamburguer(5,"Pato Deluxe",18.0,ids5,7);
    cardapio[5] = criar_hamburguer(6,"Pato Veggie",14.0,ids6,6);
    cardapio[6] = criar_hamburguer(7,"Pato Chicken",15.0,ids7,5);
    cardapio[7] = criar_hamburguer(8,"Quack Bacon",16.0,ids8,5);
    cardapio[8] = criar_hamburguer(9,"Pato Supreme",20.0,ids9,9);
    cardapio[9] = criar_hamburguer(10,"Cheesy Duck",14.0,ids10,5);
    cardapio[10] = criar_hamburguer(11,"Bacon Egg Duck",17.0,ids11,5);
    cardapio[11] = criar_hamburguer(12,"Pato Especial",22.0,ids12,11);
}

Hamburguer* buscar_hamburguer_por_id(int id) {
    for (int i = 0; i < MAX_HAMBURGUERS; i++) {
        if (hamburguer_get_id(&cardapio[i]) == id) {
            return &cardapio[i];
        }
    }
    return NULL;
}

Ingrediente* buscar_ingrediente_por_id(int id) {
    for (int i = 0; i < MAX_INGREDIENTES; i++) {
        if (ingrediente_get_id(&ingredientes[i]) == id) {
            return &ingredientes[i];
        }
    }
    return NULL;
}

int get_total_ingredientes() {
    int total = 0;
    for (int i = 0; i < MAX_INGREDIENTES; i++) {
        total += ingrediente_get_quantidade(&ingredientes[i]);
    }
    return total;
}