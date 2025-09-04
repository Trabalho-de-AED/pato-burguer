#ifndef FILA_H
#define FILA_H
#define MAX 100 // Tamanho máximo da fila

// tp_item é definido como void* para permitir armazenar qualquer tipo de dado na fila
typedef void* tp_item; 

// Estrutura da fila circular
typedef struct {
    tp_item item[MAX];  // Array que armazena os elementos da fila
    int ini, fim;       // Índice do início da fila (primeiro elemento a ser removido)
} tp_fila;              // Índice do final da fila (último elemento inserido)


// Funções da fila circular

// Inicializa a fila, preparando-a para uso
void inicializaFila(tp_fila *f);

// Verifica se a fila está vazia
// Retorna 1 se estiver vazia, 0 caso contrário
int filaVazia(tp_fila *f);

// Verifica se a fila está cheia
// Retorna 1 se estiver cheia, 0 caso contrário
int filaCheia(tp_fila *f);

// Insere um elemento na fila
// Retorna 1 se a inserção for bem-sucedida, ou 0 se a fila estiver cheia
int insereFila(tp_fila *f, tp_item e);

// Remove um elemento da fila
// Retorna 1 se a remoção for bem-sucedida, ou 0 se a fila estiver vazia
int removeFila(tp_fila *f, tp_item *e);

// Imprime todos os elementos da fila (passando por valor, a fila original não é alterada)
void imprimeFila(tp_fila f);

#endif
