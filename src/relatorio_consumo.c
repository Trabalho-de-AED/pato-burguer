#include "../include/relatorio_consumo.h"
#include <stdlib.h> // Para abs

// --- Funções Auxiliares da AVL ---

// Retorna a altura de um nó
int alt_no(NO_Consumo* no) {
    if (no == NULL) return -1;
    return no->alt;
}

// Retorna o maior de dois inteiros
int maior(int x, int y) {
    return (x > y) ? x : y;
}

// Calcula o fator de balanceamento de um nó
int fb_no(NO_Consumo* no) {
    if (no == NULL) return 0;
    return abs(alt_no(no->esq) - alt_no(no->dir));
}

// --- Rotações ---

void RotacaoLL(ArvConsumo* raiz) {
    NO_Consumo* no;
    no = (*raiz)->esq;
    (*raiz)->esq = no->dir;
    no->dir = *raiz;
    (*raiz)->alt = maior(alt_no((*raiz)->esq), alt_no((*raiz)->dir)) + 1;
    no->alt = maior(alt_no(no->esq), (*raiz)->alt) + 1;
    *raiz = no;
}

void RotacaoRR(ArvConsumo* raiz) {
    NO_Consumo* no;
    no = (*raiz)->dir;
    (*raiz)->dir = no->esq;
    no->esq = *raiz;
    (*raiz)->alt = maior(alt_no((*raiz)->esq), alt_no((*raiz)->dir)) + 1;
    no->alt = maior(alt_no(no->dir), (*raiz)->alt) + 1;
    *raiz = no;
}

void RotacaoLR(ArvConsumo* raiz) {
    RotacaoRR(&(*raiz)->esq);
    RotacaoLL(raiz);
}

void RotacaoRL(ArvConsumo* raiz) {
    RotacaoLL(&(*raiz)->dir);
    RotacaoRR(raiz);
}

// --- Funções Principais ---

ArvConsumo* criar_arvore_consumo() {
    ArvConsumo* raiz = (ArvConsumo*)malloc(sizeof(ArvConsumo));
    if (raiz != NULL) {
        *raiz = NULL;
    }
    return raiz;
}

void libera_no_consumo(NO_Consumo* no) {
    if (no == NULL) return;
    libera_no_consumo(no->esq);
    libera_no_consumo(no->dir);
    free(no);
}

void liberar_arvore_consumo(ArvConsumo* raiz) {
    if (raiz == NULL) return;
    libera_no_consumo(*raiz);
    free(raiz);
}

int esta_vazia_arvore_consumo(ArvConsumo* raiz) {
    if (raiz == NULL) return 1;
    if (*raiz == NULL) return 1;
    return 0;
}

int inserir_ou_atualizar_consumo(ArvConsumo* raiz, const char* nome, int quantidade) {
    if (raiz == NULL) return 0;

    int res;
    if (*raiz == NULL) { // Árvore vazia ou nó folha
        NO_Consumo* novo = (NO_Consumo*)malloc(sizeof(NO_Consumo));
        if (novo == NULL) return 0;

        strcpy(novo->dados.nome, nome);
        novo->dados.quantidade = quantidade;
        novo->alt = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    NO_Consumo* atual = *raiz;
    int cmp = strcmp(nome, atual->dados.nome);

    if (cmp < 0) { // Inserir na sub-árvore esquerda
        if ((res = inserir_ou_atualizar_consumo(&(atual->esq), nome, quantidade)) == 1) {
            if (fb_no(atual) >= 2) {
                if (strcmp(nome, (*raiz)->esq->dados.nome) < 0) {
                    RotacaoLL(raiz);
                } else {
                    RotacaoLR(raiz);
                }
            }
        }
    } else if (cmp > 0) { // Inserir na sub-árvore direita
        if ((res = inserir_ou_atualizar_consumo(&(atual->dir), nome, quantidade)) == 1) {
            if (fb_no(atual) >= 2) {
                if (strcmp(nome, (*raiz)->dir->dados.nome) > 0) {
                    RotacaoRR(raiz);
                } else {
                    RotacaoRL(raiz);
                }
            }
        }
    } else { // Nó já existe, apenas atualiza a quantidade
        atual->dados.quantidade += quantidade;
        return 2; // Indica que foi uma atualização
    }

    atual->alt = maior(alt_no(atual->esq), alt_no(atual->dir)) + 1;
    return res;
}

IngredienteConsumido* buscar_consumo(ArvConsumo* raiz, const char* nome) {
    if (raiz == NULL || *raiz == NULL) return NULL;

    NO_Consumo* atual = *raiz;
    while (atual != NULL) {
        int cmp = strcmp(nome, atual->dados.nome);
        if (cmp == 0) {
            return &(atual->dados);
        }
        if (cmp < 0) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }
    return NULL; // Não encontrado
}

void _listar_in_order(ArvConsumo raiz) {
    if (raiz == NULL) return;
    _listar_in_order(raiz->esq);
    printf("  - %-20s | Quantidade: %d\n", raiz->dados.nome, raiz->dados.quantidade);
    _listar_in_order(raiz->dir);
}

void listar_consumo_alfabeticamente(ArvConsumo* raiz) {
    if (esta_vazia_arvore_consumo(raiz)) {
        printf("Nenhum ingrediente consumido ainda.\n");
        return;
    }
    printf("\n--- Relatorio de Consumo (Ordem Alfabetica) ---\\n");
    _listar_in_order(*raiz);
    printf("-------------------------------------------------\n");
}

// --- Funções de Ranking ---

void _contar_nos(ArvConsumo raiz, int* count) {
    if (raiz == NULL) return;
    (*count)++;
    _contar_nos(raiz->esq, count);
    _contar_nos(raiz->dir, count);
}

void _preencher_array(ArvConsumo raiz, IngredienteConsumido* array, int* index) {
    if (raiz == NULL) return;
    _preencher_array(raiz->esq, array, index);
    array[*index] = raiz->dados;
    (*index)++;
    _preencher_array(raiz->dir, array, index);
}

int comparar_ingredientes(const void* a, const void* b) {
    IngredienteConsumido* ingA = (IngredienteConsumido*)a;
    IngredienteConsumido* ingB = (IngredienteConsumido*)b;
    return ingB->quantidade - ingA->quantidade; // Ordem decrescente
}

void gerar_ranking_consumo(ArvConsumo* raiz) {
    if (esta_vazia_arvore_consumo(raiz)) {
        printf("Nenhum ingrediente para ranquear.\n");
        return;
    }

    int total_nos = 0;
    _contar_nos(*raiz, &total_nos);
    if(total_nos == 0) return;

    IngredienteConsumido* ranking_array = (IngredienteConsumido*)malloc(total_nos * sizeof(IngredienteConsumido));
    if (ranking_array == NULL) {
        fprintf(stderr, "Erro de alocação de memória para o ranking.\n");
        return;
    }

    int index = 0;
    _preencher_array(*raiz, ranking_array, &index);

    qsort(ranking_array, total_nos, sizeof(IngredienteConsumido), comparar_ingredientes);

    printf("\n--- Ranking de Ingredientes Mais Consumidos ---\n");
    for (int i = 0; i < total_nos; i++) {
        printf("%3d. %-20s | Quantidade: %d\n", i + 1, ranking_array[i].nome, ranking_array[i].quantidade);
    }
    printf("-------------------------------------------------\n");

    free(ranking_array);
}
