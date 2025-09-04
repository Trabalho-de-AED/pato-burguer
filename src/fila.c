#include "fila.h" //Inclui a definição da struct tp_fiila e o tipo tp_item
#include <stdio.h> // Inclui a biblioteca que permite usar o printf na função imprimeFila

// Inicializa a fila circular, preparando-a para uso
// Ao inicializar, definimos ini e fim como MAX-1, indicando que a fila está vazia.
// A fila é considerada vazia sempre que ini e fim forem iguais.
// Essa inicialização também garante que não haja lixo de memória na fila
void inicializaFila(tp_fila *f){
    f-> ini = f-> fim = MAX-1;
}

// Verifica se a fila está vazia.
// Uma fila está vazia quando não há nenhum elemento entre os índices ini e fim.
// Como usamos uma fila circular, ini e fim são iguais quando não há elementos.
// Retorna 1 se a fila estiver vazia, ou 0 se a fila não estiver vazia.
int filaVazia(tp_fila *f){
    return (f->ini==f->fim);
}

// Calcula a próxima posição na fila circular.
// Em uma fila circular, quando chegamos ao final do array, precisamos voltar ao início para reutilizar posições livres.
// A operação (pos + 1) % MAX garante que, se pos for MAX-1, a próxima posição será 0, mantendo a circularidade da fila.
// Retorna o índice da próxima posição disponível.
int proximo (int pos){
    return (pos+1) % MAX;
}

// Verifica se a fila circular está cheia.
// Em uma fila circular, a fila está cheia quando a Próxima posição do índice fim encontra o índice ini
// A função proximo(f->fim) calcula o próximo índice após o fim.
// Se esse próximo índice for igual a ini, significa que a fila não pode receber mais elementos.
// Retorna 1 se a fila estiver cheia, ou 0 se a fila não estiver cheia.
int filaCheia(tp_fila *f){
    return (proximo(f->fim)==f->ini);
}

// Remove um elemento da fila circular.
// Retorna 1 se a remoção for bem-sucedida, ou 0 se a fila estiver vazia.
int removeFila (tp_fila *f, tp_item *e){
    if(filaVazia(f)) return 0; // Verifica se a fila está vazia usando filaVazia(f).
    f->ini = proximo(f->ini); // Na fila, quando removemos um elemento o ini avança para a próxima posição da fila.
    *e = f-> item[f->ini]; // Armazena na variável apontada por e o elemento removido da fila.
    return 1;
}

// Imprime todos os elementos da fila.
// Atenção: a fila é passada por cópia valor, então a original não é alterada.
// A função remove os elementos temporariamente da cópia da fila e os imprime.
void imprimeFila(tp_fila f){
    tp_item e;
    while(!filaVazia(&f)){
        removeFila(&f, &e);
        printf("\n%d", e);
    }
}

// Insere um elemento na fila circular.
// Ao inserir, o índice fim é avançado para a próxima posição da fila,
// e o novo elemento é armazenado nessa posição.
// Retorna 1 se a inserção for bem-sucedida, ou 0 se a fila estiver cheia.
int insereFila(tp_fila *f, tp_item e){
    if(filaCheia(f)) return 0;          // Verifica se há espaço
    f->fim = proximo(f->fim);           // Na fila quando adicionamos um elemento o fim avança para a próxima posição da fila.
    f->item[f->fim] = e;                // Insere o elemento na posição fim
    return 1;
}
