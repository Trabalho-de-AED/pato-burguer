#ifndef RELATORIO_CONSUMO_H
#define RELATORIO_CONSUMO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[51];
    int quantidade;
} IngredienteConsumido;

typedef struct NO {
    IngredienteConsumido dados;
    int alt; 
    struct NO *esq;
    struct NO *dir;
} NO;

typedef NO* ArvAVL;

ArvAVL* criarAVL();

void liberaAVL(ArvAVL* raiz);

int estah_vaziaAVL(ArvAVL* raiz);

int inserir_ou_atualizar_consumo(ArvAVL* raiz, const char* nome, int quantidade);

IngredienteConsumido* buscar_consumo(ArvAVL* raiz, const char* nome);

void listar_consumo_alfabeticamente(ArvAVL* raiz);

void gerarRnkConsumo(ArvAVL* raiz);

#endif
