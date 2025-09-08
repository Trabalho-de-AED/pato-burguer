#ifndef INGREDIENTE_H
#define INGREDIENTE_H

typedef struct {
    char nome[50];
    float valor;            // Moedas patonicas
    int tempo_preparo;      // em segundos
    int nivel_desbloqueio;  // fase em que aparece
    int disponivel;         // 1 = sim, 0 = esgotado
} Ingrediente;

// Funções "públicas"
Ingrediente criarIngrediente(
    const char *nome,       // Nome do ingrediente
    float valor,            // Valor do ingrediente em reais
    int tempo_preparo,      // Tempo necessário para prepar em segundos
    int nivel_desbloqueio,  // Fase do jogo em que o ingrediente se torna disponível
    int disponivel          // Indica se o ingrediente está disponível
);

#endif
