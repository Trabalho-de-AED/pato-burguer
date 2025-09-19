#include "../include/ingrediente.h"
#include <string.h>

Ingrediente criar_ingrediente(
    int id,
    const char* nome,
    int quantidade,
    float preco_compra,
    float valor,
    int tempo_preparo,
    int nivel_desbloqueio,
    int disponivel
) {
    Ingrediente ing;
    ing.id = id;
    strcpy(c.nome, nome);
    ing.quantidade = quantidade;
    ing.preco_compra = preco_compra;
    ing.valor = valor;
    ing.tempo_preparo = tempo_preparo;
    ing.nivel_desbloqueio = nivel_desbloqueio;
    ing.disponivel = (quantidade > 0) ? 1 : 0; 

    return ing;
}

int ingrediente_get_id(const Ingrediente* ing) {
    return ing->id;
}

const char* ingrediente_get_nome(const Ingrediente* ing) {
    return ing->nome;
}

int ingrediente_get_quantidade(const Ingrediente* ing) {
    return ing->quantidade;
}

float ingrediente_get_preco_compra(const Ingrediente* ing) {
    return ing->preco_compra;
}

float ingrediente_get_valor(const Ingrediente* ing) {
    return ing->valor;
}

int ingrediente_get_tempo_preparo(const Ingrediente* ing) {
    return ing->tempo_preparo;
}

int ingrediente_get_nivel_desbloqueio(const Ingrediente* ing) {
    return ing->nivel_desbloqueio;
}

int ingrediente_get_disponivel(const Ingrediente* ing) {
    return ing->disponivel;
}
