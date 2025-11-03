#ifndef UI_H
#define UI_H

#include "fila.h"
#include "hamburguer.h"
#include "ingrediente.h"
#include "fila_clientes.h"
#include "pilha_ingredientes.h"

/**
 * @brief Limpa a tela do console.
 *        Utiliza o comando 'cls' para Windows e 'clear' para sistemas Unix-like.
 */
void ui_limpar_tela();

/**
 * @brief Exibe as informações de status do jogo (pontuação, moedas, satisfação, cronômetro, nível).
 */
void ui_mostrar_status();

/**
 * @brief Exibe a fila de clientes que aguardam atendimento.
 * @param fila_de_clientes Ponteiro para a fila de clientes.
 */
void ui_mostrar_fila_clientes(const FilaClientes* fila_de_clientes);

/**
 * @brief Exibe os pedidos atualmente na fila.
 * @param filaPedidos Ponteiro constante para a fila de pedidos a ser exibida.
 */
void ui_mostrar_pedidos(const Fila* filaPedidos);

/**
 * @brief Exibe o estoque atual de ingredientes.
 * @param ingredientes Array constante de ingredientes a serem exibidos.
 * @param num_ingredientes Número de ingredientes no array.
 */
void ui_mostrar_estoque(const Ingrediente ingredientes[], int num_ingredientes);

/**
 * @brief Exibe o cardápio de hambúrgueres, incluindo seus ingredientes.
 * @param cardapio Array constante de hambúrgueres a serem exibidos.
 * @param num_hamburguers Número de hambúrgueres no cardápio.
 * @param ingredientes Array constante de ingredientes para buscar os nomes dos ingredientes.
 * @param num_ingredientes Número de ingredientes no array de ingredientes.
 */
void ui_mostrar_cardapio(const Hamburguer cardapio[], int num_hamburguers, const Ingrediente ingredientes[], int num_ingredientes);

/**
 * @brief Exibe as opções de comando disponíveis para o jogador.
 */
void ui_mostrar_ajuda();

/**
 * @brief Exibe a tela de montagem de um hambúrguer, mostrando a receita.
 * @param hamburguer_gabarito Ponteiro para o hambúrguer que serve como receita.
 */
void ui_iniciar_tela_montagem(const Hamburguer* hamburguer_gabarito);

/**
 * @brief Exibe o hambúrguer montado pelo jogador.
 * @param pilha_jogador A pilha de ingredientes montada pelo jogador.
 */
void ui_exibir_hamburguer_montado(PilhaIngredientes* pilha_jogador);

/**
 * @brief Obtém um comando de caractere do usuário.
 * @return O caractere digitado pelo usuário.
 */
char ui_obter_comando();

/**
 * @brief Obtém a escolha numérica de um ingrediente do jogador.
 * @return O ID do ingrediente escolhido.
 */
int ui_obter_id_ingrediente();

/**
 * @brief Pausa a execução e aguarda o usuário pressionar Enter para continuar.
 */
void ui_pressionar_enter_para_continuar();

/**
 * @brief Exibe uma mensagem informando que um pedido está sendo preparado.
 * @param id O ID do pedido que está sendo preparado.
 */
void ui_mensagem_preparando_pedido(int id);

/**
 * @brief Exibe uma mensagem informando que não há pedidos na fila.
 */
void ui_mensagem_sem_pedidos();

/**
 * @brief Exibe uma mensagem informando que novos clientes estão sendo gerados.
 */
void ui_mensagem_gerando_clientes();

/**
 * @brief Exibe uma mensagem informando que novos pedidos estão sendo gerados.
 */
void ui_mensagem_gerando_pedidos();

/**
 * @brief Exibe uma mensagem de erro para um comando não reconhecido.
 */
void ui_mensagem_comando_invalido();

/**
 * @brief Exibe uma mensagem de erro para um ID de ingrediente inválido.
 */
void ui_mensagem_id_invalido();

/**
 * @brief Exibe uma mensagem de despedida ao sair do jogo.
 */
void ui_mensagem_saindo();

#endif
