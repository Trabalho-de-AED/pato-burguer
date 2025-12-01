#ifndef UI_H
#define UI_H

#include <stdbool.h> // Adicionado para usar o tipo bool

#include "caixa.h"
#include "fila.h"
#include "hamburguer.h"
#include "ingrediente.h"
#include "fila_clientes.h"
#include "pilha_ingredientes.h"
#include "loja.h"

void ui_limpar_tela();
void ui_mostrar_status();
void ui_mostrar_fila_clientes(const FilaClientes* fila_de_clientes);

void ui_mostrar_pedidos(const Fila* filaPedidos);

void ui_mostrar_estoque(const Ingrediente ingredientes[], int num_ingredientes);
void ui_mostrar_cardapio(const Hamburguer cardapio[], int num_hamburguers, const Ingrediente ingredientes[], int num_ingredientes);

void ui_mostrar_loja(const Loja* loja, float saldo_caixa);

void ui_mostrar_ajuda();

void ui_iniciar_tela_montagem(const Hamburguer* hamburguer_gabarito, bool mostrar_receita);

void ui_exibir_hamburguer_montado(PilhaIngredientes* pilha_jogador);

void ui_exibir_resultado_validacao(int erros, float penalidade_total, float preco_final);

char ui_obter_comando();

int ui_obter_id_ingrediente();

void ui_pressionar_enter_para_continuar();


void ui_mensagem_preparando_pedido(int id);

void ui_mensagem_sem_pedidos();

void ui_mensagem_gerando_clientes();

void ui_mensagem_gerando_pedidos();


void ui_mensagem_comando_invalido();

void ui_mensagem_id_invalido();

void ui_mensagem_ingrediente_sem_estoque();


void ui_mensagem_saindo();



// Funções para a interface de venda

void ui_iniciar_tela_venda(const Ingrediente ingredientes[], int num_ingredientes);

int ui_pedir_id_ingrediente_venda();

int ui_pedir_quantidade_venda();



#endif
