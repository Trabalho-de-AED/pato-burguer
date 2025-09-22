#ifndef UI_H
#define UI_H

#include "fila.h"
#include "hamburguer.h"
#include "ingrediente.h"

void ui_limpar_tela();
void ui_mostrar_status();
void ui_mostrar_pedidos(const Fila* filaPedidos);
void ui_mostrar_estoque(const Ingrediente ingredientes[], int num_ingredientes);
void ui_mostrar_cardapio(const Hamburguer cardapio[], int num_hamburguers, const Ingrediente ingredientes[], int num_ingredientes);
void ui_mostrar_ajuda();

char ui_obter_comando();
void ui_pressionar_enter_para_continuar();

void ui_mensagem_preparando_pedido(int id);
void ui_mensagem_sem_pedidos();
void ui_mensagem_gerando_pedidos();
void ui_mensagem_comando_invalido();
void ui_mensagem_saindo();

#endif