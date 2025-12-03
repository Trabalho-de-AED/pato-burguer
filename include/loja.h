#ifndef LOJA_H
#define LOJA_H

#include "ingrediente.h"
#include "ListaSE.h" 

typedef struct {
    tp_lista_encadeada* ingredientes_disponiveis;
    int nivel_atual;
    int experiencia_total;
    int xp_para_proximo_nivel;
    float satisfacao_media_clientes;
} Loja;

void loja_inicializar(Loja* loja);
int loja_get_nivel(const Loja* loja);
float loja_get_satisfacao_media(const Loja* loja);
float obter_percentual_penalidade_por_nivel(int nivel);


int comprar_ingrediente(int id_ingrediente, int quantidade);
int vender_ingrediente(int id_ingrediente, int quantidade);
void loja_atualizar_precos();
void destruir_loja(Loja* loja);

int verificar_falencia();

#endif
