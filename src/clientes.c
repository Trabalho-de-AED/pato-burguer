#include "../include/clientes.h"
#include "../include/fila_clientes.h"
#include "../include/dados.h"
#include <string.h>
#include <stdlib.h>

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

void gerar_clientes_na_fila(FilaClientes* fila, int quantidade) {
    const char* nomes[] = {"Alice", "Beto", "Carla", "Daniel", "Elisa", "Fernando", "Gabriela", "Heitor"};
    int num_nomes = sizeof(nomes) / sizeof(nomes[0]);

    for (int i = 0; i < quantidade; i++) {
        const char* nome_aleatorio = nomes[rand() % num_nomes];
        int id_hamburguer_aleatorio = (rand() % MAX_HAMBURGUERS) + 1;

        Cliente novo_cliente = criar_cliente(i + 1, nome_aleatorio, id_hamburguer_aleatorio, 100, 50);
        
        enfileirar_cliente(fila, novo_cliente);
    }
}