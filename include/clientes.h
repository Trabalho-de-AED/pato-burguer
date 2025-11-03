#ifndef CLIENTES_H
#define CLIENTES_H

// Declaração avançada para resolver dependência circular com fila_clientes.h
struct FilaClientes;

/**
 * @brief Estrutura que representa um cliente no jogo.
 */
typedef struct {
    int id;
    char nome[50];
    int id_hamburguer_preferido;
    int paciencia;
    int moedas_disponiveis; 
} Cliente;

/**
 * @brief Cria e inicializa uma nova estrutura Cliente.
 * @param id Identificador único do cliente.
 * @param nome Nome do cliente.
 * @param id_hamburguer_preferido ID do hambúrguer preferido do cliente.
 * @param paciencia Nível de paciência do cliente.
 * @param moedas_disponiveis Quantidade de moedas que o cliente possui.
 * @return Uma nova estrutura Cliente inicializada com os valores fornecidos.
 */
Cliente criar_cliente(
    int id, 
    const char* nome, 
    int id_hamburguer_preferido, 
    int paciencia, 
    int moedas_disponiveis
);

/**
 * @brief Retorna o ID do cliente.
 * @param cliente Ponteiro constante para a estrutura Cliente.
 * @return O ID do cliente.
 */
int cliente_get_id(const Cliente* cliente);

/**
 * @brief Retorna o nome do cliente.
 * @param cliente Ponteiro constante para a estrutura Cliente.
 * @return O nome do cliente como uma string constante.
 */
const char* cliente_get_nome(const Cliente* cliente);

/**
 * @brief Retorna o ID do hambúrguer preferido do cliente.
 * @param cliente Ponteiro constante para a estrutura Cliente.
 * @return O ID do hambúrguer preferido.
 */
int cliente_get_id_hamburguer_preferido(const Cliente* cliente);

/**
 * @brief Retorna o nível de paciência do cliente.
 * @param cliente Ponteiro constante para a estrutura Cliente.
 * @return O nível de paciência do cliente.
 */
int cliente_get_paciencia(const Cliente* cliente);

/**
 * @brief Retorna a quantidade de moedas disponíveis do cliente.
 * @param cliente Ponteiro constante para a estrutura Cliente.
 * @return A quantidade de moedas disponíveis.
 */
int cliente_get_moedas_disponiveis(const Cliente* cliente);

/**
 * @brief Gera uma quantidade de clientes com nomes e pedidos aleatórios e os insere na fila.
 * @param fila Ponteiro para a fila de clientes onde os novos clientes serão adicionados.
 * @param quantidade O número de clientes a serem gerados.
 */
void gerar_clientes_na_fila(struct FilaClientes* fila, int quantidade);

#endif
