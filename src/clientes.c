#include "../include/clientes.h"
#include <string.h>

Cliente criar_cliente(int id, const char* nome, int id_hamburguer_preferido, int paciencia, int moedas_disponiveis) {
    Cliente c;
    c.id = id;
    strcpy(c.nome, nome);
    c.id_hamburguer_preferido = id_hamburguer_preferido;
    c.paciencia = paciencia;
    c.moedas_disponiveis = moedas_disponiveis;
    return c;
}

int cliente_get_id(const Cliente* cliente) {
    return cliente->id;
}

const char* cliente_get_nome(const Cliente* cliente) {
    return cliente->nome;
}

int cliente_get_id_hamburguer_preferido(const Cliente* cliente) {
    return cliente->id_hamburguer_preferido;
}

int cliente_get_paciencia(const Cliente* cliente) {
    return cliente->paciencia;
}

int cliente_get_moedas_disponiveis(const Cliente* cliente) {
    return cliente->moedas_disponiveis;
}
