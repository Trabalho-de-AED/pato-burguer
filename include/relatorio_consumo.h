#ifndef RELATORIO_CONSUMO_H
#define RELATORIO_CONSUMO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para armazenar os dados de consumo de um ingrediente
typedef struct {
    char nome[51]; // 50 chars para o nome + 1 para o terminador nulo
    int quantidade;
} IngredienteConsumido;

// Estrutura do nó da árvore AVL
typedef struct NO_Consumo {
    IngredienteConsumido dados;
    int alt; // Altura do nó, usada para o balanceamento da árvore
    struct NO_Consumo *esq;
    struct NO_Consumo *dir;
} NO_Consumo;

// A árvore é um ponteiro para o nó raiz
typedef NO_Consumo* ArvConsumo;

// --- Protótipos das Funções ---

/**
 * @brief Aloca memória e inicializa uma nova árvore AVL de consumo.
 * @return Ponteiro para a raiz da árvore recém-criada.
 */
ArvConsumo* criar_arvore_consumo();

/**
 * @brief Libera toda a memória alocada para a árvore e seus nós.
 * @param raiz Ponteiro para a raiz da árvore a ser liberada.
 */
void liberar_arvore_consumo(ArvConsumo* raiz);

/**
 * @brief Verifica se a árvore de consumo está vazia.
 * @param raiz Ponteiro para a raiz da árvore.
 * @return 1 se a árvore estiver vazia, 0 caso contrário.
 */
int esta_vazia_arvore_consumo(ArvConsumo* raiz);

/**
 * @brief Insere um novo ingrediente na árvore ou atualiza a quantidade de um existente.
 *        Mantém a árvore balanceada após a inserção.
 * @param raiz Ponteiro para a raiz da árvore.
 * @param nome O nome do ingrediente a ser inserido/atualizado.
 * @param quantidade A quantidade a ser somada ao total do ingrediente.
 * @return 1 em caso de sucesso (inserção), 2 em caso de atualização, 0 em caso de falha.
 */
int inserir_ou_atualizar_consumo(ArvConsumo* raiz, const char* nome, int quantidade);

/**
 * @brief Busca um ingrediente na árvore pelo nome.
 * @param raiz Ponteiro para a raiz da árvore.
 * @param nome O nome do ingrediente a ser buscado.
 * @return Ponteiro para os dados do ingrediente se encontrado, NULL caso contrário.
 */
IngredienteConsumido* buscar_consumo(ArvConsumo* raiz, const char* nome);

/**
 * @brief Exibe na tela todos os ingredientes consumidos em ordem alfabética.
 * @param raiz Ponteiro para a raiz da árvore.
 */
void listar_consumo_alfabeticamente(ArvConsumo* raiz);

/**
 * @brief Exibe na tela um ranking de ingredientes, ordenados do mais consumido para o menos consumido.
 * @param raiz Ponteiro para a raiz da árvore.
 */
void gerar_ranking_consumo(ArvConsumo* raiz);

#endif // RELATORIO_CONSUMO_H
