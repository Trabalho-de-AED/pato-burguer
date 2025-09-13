#include "clientes.h"
#include <string.h>

typedef struct {
    int id;
    char nome[50];
    char preferencia[50];
    int paciencia;
    int MoedasDisponiveis;
}tp_cliente;

void CriarCliente(tp_cliente *cliente, int id, const char *nome, const char *preferencia, int paciencia, int moedas){
    cliente->id = id;
    strcpy(cliente->nome,nome);
    strcpy(cliente->preferencia,preferencia);
    cliente->paciencia = paciencia;
    cliente->MoedasDisponiveis = moedas;
}
/*
void GetnomeCliente(tp_cliente *cliente, char *nome){// função que retorna o nome do cliente
    strcpy(nome, cliente->nome); 
    return nome;
}

void GetprefCliente(tp_cliente *cliente, char *preferencia){
    strcpy(preferencia, cliente->preferencia);
    return preferencia;
}

void GetpaciCliente(tp_cliente *cliente, int *paciencia){
    paciencia = cliente->paciencia;
    return paciencia;
}

void dimPaciencia(tp_cliente *cliente){
    cliente->paciencia--;
}
*/