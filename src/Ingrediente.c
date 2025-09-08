#include "ingrediente.h"
#include <string.h>  // Para strcpy / strncpy

// Cria e inicializa um ingrediente
Ingrediente criarIngrediente(
    const char *nome,
    float valor,
    int tempo_preparo,
    int nivel_desbloqueio,
    int disponivel
) {
    Ingrediente ing;

    // Copia o nome para dentro da struct garantindo null terminator
    strncpy(ing.nome, nome, sizeof(ing.nome) - 1);
    ing.nome[sizeof(ing.nome) - 1] = '\0';

    ing.valor = valor;
    ing.tempo_preparo = tempo_preparo;
    ing.nivel_desbloqueio = nivel_desbloqueio;
    ing.disponivel = disponivel;

    return ing;
}