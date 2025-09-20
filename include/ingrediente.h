#ifndef INGREDIENTE_H
#define INGREDIENTE_H

typedef struct {
    int id;
    char nome[50];
    int quantidade;
    float preco_compra;
    float valor;
    int tempo_preparo;
    int nivel_desbloqueio;
    int disponivel;
} Ingrediente;

Ingrediente criar_ingrediente(
    int id,
    const char* nome,
    int quantidade,
    float preco_compra,
    float valor,
    int tempo_preparo,
    int nivel_desbloqueio
);

int ingrediente_get_id(const Ingrediente* ing);
const char* ingrediente_get_nome(const Ingrediente* ing);
int ingrediente_get_quantidade(const Ingrediente* ing);
float ingrediente_get_preco_compra(const Ingrediente* ing);
float ingrediente_get_valor(const Ingrediente* ing);
int ingrediente_get_tempo_preparo(const Ingrediente* ing);
int ingrediente_get_nivel_desbloqueio(const Ingrediente* ing);
int ingrediente_get_disponivel(const Ingrediente* ing);

#endif