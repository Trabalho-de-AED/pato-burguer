#include "../include/relatorio_consumo.h"
#include <stdlib.h>


static int alt_NO(NO* no) {
    if (no == NULL) return -1;
    return no->alt;
}

static int maior(int x, int y) {
    return (x > y) ? x : y;
}

static int fb_NO(NO* no) {
    if (no == NULL) return 0;
    return abs(alt_NO(no->esq) - alt_NO(no->dir));
}

static void RotacaoLL(ArvAVL* raiz) {
    NO* no;
    no = (*raiz)->esq;
    (*raiz)->esq = no->dir;
    no->dir = *raiz;
    (*raiz)->alt = maior(alt_NO((*raiz)->esq), alt_NO((*raiz)->dir)) + 1;
    no->alt = maior(alt_NO(no->esq), (*raiz)->alt) + 1;
    *raiz = no;
}

static void RotacaoRR(ArvAVL* raiz) {
    NO* no;
    no = (*raiz)->dir;
    (*raiz)->dir = no->esq;
    no->esq = *raiz;
    (*raiz)->alt = maior(alt_NO((*raiz)->esq), alt_NO((*raiz)->dir)) + 1;
    no->alt = maior(alt_NO(no->dir), (*raiz)->alt) + 1;
    *raiz = no;
}

static void RotacaoLR(ArvAVL* raiz) {
    RotacaoRR(&(*raiz)->esq);
    RotacaoLL(raiz);
}

static void RotacaoRL(ArvAVL* raiz) {
    RotacaoLL(&(*raiz)->dir);
    RotacaoRR(raiz);
}

ArvAVL* criarAVL() {
    ArvAVL* raiz = (ArvAVL*)malloc(sizeof(ArvAVL));
    if (raiz != NULL) {
        *raiz = NULL;
    }
    return raiz;
}

void liberaNO(NO* no) {
    if (no == NULL) return;
    liberaNO(no->esq);
    liberaNO(no->dir);
    free(no);
}

void liberaAVL(ArvAVL* raiz) {
    if (raiz == NULL) return;
    liberaNO(*raiz);
    free(raiz);
}

int estah_vaziaAVL(ArvAVL* raiz) {
    if (raiz == NULL) return 1;
    if (*raiz == NULL) return 1;
    return 0;
}

int inserir_ou_atualizar_consumo(ArvAVL* raiz, const char* nome, int quantidade) {
    if (raiz == NULL) return 0;

    int res;
    if (*raiz == NULL) {
        NO* novo = (NO*)malloc(sizeof(NO));
        if (novo == NULL) return 0;

        strcpy(novo->dados.nome, nome);
        novo->dados.quantidade = quantidade;
        novo->alt = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    NO* atual = *raiz;
    int cmp = strcmp(nome, atual->dados.nome);

    if (cmp < 0) {
        if ((res = inserir_ou_atualizar_consumo(&(atual->esq), nome, quantidade)) == 1) {
            if (fb_NO(atual) >= 2) {
                if (strcmp(nome, (*raiz)->esq->dados.nome) < 0) {
                    RotacaoLL(raiz);
                } else {
                    RotacaoLR(raiz);
                }
            }
        }
    } else if (cmp > 0) {
        if ((res = inserir_ou_atualizar_consumo(&(atual->dir), nome, quantidade)) == 1) {
            if (fb_NO(atual) >= 2) {
                if (strcmp(nome, (*raiz)->dir->dados.nome) > 0) {
                    RotacaoRR(raiz);
                } else {
                    RotacaoRL(raiz);
                }
            }
        }
    } else {
        atual->dados.quantidade += quantidade;
        return 2; 
    }

    atual->alt = maior(alt_NO(atual->esq), alt_NO(atual->dir)) + 1;
    return res;
}

IngredienteConsumido* buscar_consumo(ArvAVL* raiz, const char* nome) {
    if (raiz == NULL || *raiz == NULL) return NULL;

    NO* atual = *raiz;
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
    return NULL;
}

void listarOrdem(ArvAVL raiz) {
    if (raiz == NULL) return;
    listarOrdem(raiz->esq);
    printf("  - %-20s | Quantidade: %d\n", raiz->dados.nome, raiz->dados.quantidade);
    listarOrdem(raiz->dir);
}

void listar_consumo_alfabeticamente(ArvAVL* raiz) {
    if (estah_vaziaAVL(raiz)) {
        printf("Nenhum ingrediente consumido ainda.\n");
        return;
    }
    printf("\n--- Relatorio de Consumo (Ordem Alfabetica) ---\n");
    listarOrdem(*raiz);
    printf("-------------------------------------------------\n");
}

void contarNOs(ArvAVL raiz, int* count) {
    if (raiz == NULL) return;
    (*count)++;
    contarNOs(raiz->esq, count);
    contarNOs(raiz->dir, count);
}

void preencherArry(ArvAVL raiz, IngredienteConsumido* array, int* index) {
    if (raiz == NULL) return;
    preencherArry(raiz->esq, array, index);
    array[*index] = raiz->dados;
    (*index)++;
    preencherArry(raiz->dir, array, index);
}

int comparar_ingredientes(const void* a, const void* b) {
    IngredienteConsumido* ingA = (IngredienteConsumido*)a;
    IngredienteConsumido* ingB = (IngredienteConsumido*)b;
    return ingB->quantidade - ingA->quantidade; 
}

void gerarRnkConsumo(ArvAVL* raiz) {
    if (estah_vaziaAVL(raiz)) {
        printf("Nenhum ingrediente para ranquear.\n");
        return;
    }

    int total_nos = 0;
    contarNOs(*raiz, &total_nos);
    if(total_nos == 0) return;

    IngredienteConsumido* ranking_array = (IngredienteConsumido*)malloc(total_nos * sizeof(IngredienteConsumido));
    if (ranking_array == NULL) {
        fprintf(stderr, "Erro de alocação de memória para o ranking.\n");
        return;
    }

    int index = 0;
    preencherArry(*raiz, ranking_array, &index);

    qsort(ranking_array, total_nos, sizeof(IngredienteConsumido), comparar_ingredientes);

    printf("\n--- Ranking de Ingredientes Mais Consumidos ---\n");
    for (int i = 0; i < total_nos; i++) {
        printf("%3d. %-20s | Quantidade: %d\n", i + 1, ranking_array[i].nome, ranking_array[i].quantidade);
    }
    printf("-------------------------------------------------\n");

    free(ranking_array);
}