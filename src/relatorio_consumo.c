#include "../include/relatorio_consumo.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define WHITE   "\x1b[37m"
#define BOLD    "\x1b[1m"


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
    
    printf("  " CYAN ">" RESET " %-20s " CYAN ".................." RESET BOLD " %3d" RESET " un\n", 
           raiz->dados.nome, raiz->dados.quantidade);
           
    listarOrdem(raiz->dir);
}

static void escreverOrdem(ArvAVL raiz, FILE* fp) {
    if (raiz == NULL) return;
    escreverOrdem(raiz->esq, fp);
    fprintf(fp, "%-20s : %3d un\n", raiz->dados.nome, raiz->dados.quantidade);
    escreverOrdem(raiz->dir, fp);
}

int salvar_consumo_para_arquivo(ArvAVL* raiz, const char* filename) {
    if (raiz == NULL || *raiz == NULL) {
        return 0; 
    }

    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Erro ao abrir arquivo para escrita");
        return 0; 
    }

    fprintf(fp, "RELATORIO DE CONSUMO\n");
    escreverOrdem(*raiz, fp);
    fclose(fp);
    return 1; 
}


void listar_consumo_alfabeticamente(ArvAVL* raiz) {
    if (estah_vaziaAVL(raiz)) {
        printf(YELLOW "\n[!] Nenhum ingrediente consumido ainda.\n" RESET);
        return;
    }
    printf(BLUE BOLD "\n=== RELATORIO DE CONSUMO (A-Z) ===" RESET "\n");
    printf(BLUE "----------------------------------------------" RESET "\n");
    listarOrdem(*raiz);
    printf(BLUE "----------------------------------------------" RESET "\n");
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
        printf(YELLOW "\n[!] Nenhum ingrediente para ranquear.\n" RESET);
        return;
    }

    int total_nos = 0;
    contarNOs(*raiz, &total_nos);
    if(total_nos == 0) return;

    IngredienteConsumido* ranking_array = (IngredienteConsumido*)malloc(total_nos * sizeof(IngredienteConsumido));
    if (ranking_array == NULL) {
        fprintf(stderr, RED "Erro fatal: Falha de alocacao de memoria.\n" RESET);
        return;
    }

    int index = 0;
    preencherArry(*raiz, ranking_array, &index);

    qsort(ranking_array, total_nos, sizeof(IngredienteConsumido), comparar_ingredientes);

    printf(YELLOW BOLD "\n=== RANKING DOS MAIS CONSUMIDOS ===" RESET "\n");
    printf(YELLOW "----------------------------------------------" RESET "\n");
    printf(" Pos | Ingrediente          | Qtd Total \n");
    printf("-----|----------------------|-----------\n");

    for (int i = 0; i < total_nos; i++) {
        char* cor_pos = RESET;
        char* medalha = " ";
        
        if (i == 0) { cor_pos = YELLOW BOLD; medalha = "*"; }
        else if (i == 1) { cor_pos = CYAN BOLD; medalha = "**"; }
        else if (i == 2) { cor_pos = MAGENTA BOLD; medalha = "***"; }

        printf(" %s%s%02d.%s | %-20s | " BOLD "%3d" RESET " un.\n", 
               cor_pos, medalha, i + 1, RESET, 
               ranking_array[i].nome, 
               ranking_array[i].quantidade);
    }
    printf(YELLOW "----------------------------------------------" RESET "\n");

    free(ranking_array);
}