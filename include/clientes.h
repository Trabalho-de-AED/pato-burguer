#ifndef CLIENTES_H
#define CLIENTES_H

typedef struct {
    int id;
    char nome[50];
    int id_hamburguer_preferido;
    int paciencia;
    int moedas_disponiveis;
} Cliente;

Cliente criar_cliente(
    int id, 
    const char* nome, 
    int id_hamburguer_preferido, 
    int paciencia, 
    int moedas_disponiveis
);

int cliente_get_id(const Cliente* cliente);
const char* cliente_get_nome(const Cliente* cliente);
int cliente_get_id_hamburguer_preferido(const Cliente* cliente);
int cliente_get_paciencia(const Cliente* cliente);
int cliente_get_moedas_disponiveis(const Cliente* cliente);

#endif