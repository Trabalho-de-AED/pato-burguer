#include "../include/clientes.h"
#include "../include/fila_clientes.h"
#include "../include/dados.h"
#include <string.h>
#include <stdlib.h>

/**
 * @brief Cria e inicializa uma nova estrutura Cliente.
 * @param id Identificador único do cliente.
 * @param nome Nome do cliente.
 * @param id_hamburguer_preferido ID do hambúrguer preferido do cliente.
 * @param paciencia Nível de paciência do cliente.
 * @param moedas_disponiveis Quantidade de moedas que o cliente possui.
 * @return Uma nova estrutura Cliente inicializada com os valores fornecidos.
 */
Cliente criar_cliente(int id, const char* nome, int id_hamburguer_preferido, int paciencia, int moedas_disponiveis) {
    Cliente c;
    c.id = id;
    strcpy(c.nome, nome);
    c.id_hamburguer_preferido = id_hamburguer_preferido;
    c.paciencia = paciencia;
    c.moedas_disponiveis = moedas_disponiveis;
    return c;
}

/**
 * @brief Retorna o ID do cliente.
 * @param cliente Ponteiro constante para a estrutura Cliente.
 * @return O ID do cliente.
 */
int cliente_get_id(const Cliente* cliente) {
    return cliente->id;
}

/**
 * @brief Retorna o nome do cliente.
 * @param cliente Ponteiro constante para a estrutura Cliente.
 * @return O nome do cliente como uma string constante.
 */
const char* cliente_get_nome(const Cliente* cliente) {
    return cliente->nome;
}

/**
 * @brief Retorna o ID do hambúrguer preferido do cliente.
 * @param cliente Ponteiro constante para a estrutura Cliente.
 * @return O ID do hambúrguer preferido.
 */
int cliente_get_id_hamburguer_preferido(const Cliente* cliente) {
    return cliente->id_hamburguer_preferido;
}

/**
 * @brief Retorna o nível de paciência do cliente.
 * @param cliente Ponteiro constante para a estrutura Cliente.
 * @return O nível de paciência do cliente.
 */
int cliente_get_paciencia(const Cliente* cliente) {
    return cliente->paciencia;
}

/**
 * @brief Retorna a quantidade de moedas disponíveis do cliente.
 * @param cliente Ponteiro constante para a estrutura Cliente.
 * @return A quantidade de moedas disponíveis.
 */
int cliente_get_moedas_disponiveis(const Cliente* cliente) {
    return cliente->moedas_disponiveis;
}

/**
 * @brief Gera uma quantidade de clientes com nomes e pedidos aleatórios e os insere na fila.
 * @param fila Ponteiro para a fila de clientes onde os novos clientes serão adicionados.
 * @param quantidade O número de clientes a serem gerados.
 */
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