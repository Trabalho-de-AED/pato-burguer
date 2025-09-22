#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hamburguer.h"
#include "ingrediente.h"
#include "pedido.h"
#include "fila.h"
#include "pilha.h"
#include "config.h"
#include "dados.h"
#include "ui.h"
#include "gerenciador_pedido.h"

#define MAX_PEDIDOS 6

int main() {

    srand(time(NULL));

    inicializa_dados();

    Pedido pedidos[MAX_PEDIDOS];
    pedido_manager_inicializar_pedidos();
    pedido_manager_gerar_pedidos(pedidos, MAX_PEDIDOS);

    char ch;

    do {

        ui_limpar_tela();
        ui_mostrar_status();
        ui_mostrar_pedidos(&filaPedidos);
        ui_mostrar_estoque(ingredientes, MAX_INGREDIENTES);
        ui_mostrar_cardapio(cardapio, MAX_HAMBURGUERS, ingredientes, MAX_INGREDIENTES);
        ui_mostrar_ajuda();

        ch = ui_obter_comando();

        switch(ch) {

            case 'p': {
                int pedido_id = pedido_manager_processar_proximo_pedido();
                if (pedido_id > 0) {
                    ui_mensagem_preparando_pedido(pedido_id);
                } else {
                    ui_mensagem_sem_pedidos();
                }
                ui_pressionar_enter_para_continuar();
                break;
            }
            case 'r':
                ui_mensagem_gerando_pedidos();
                pedido_manager_inicializar_pedidos(); 
                pedido_manager_gerar_pedidos(pedidos, MAX_PEDIDOS);
                ui_pressionar_enter_para_continuar();
                break;
            case 'q':
                ui_mensagem_saindo();
                break;
            default:
                ui_mensagem_comando_invalido();
                ui_pressionar_enter_para_continuar();
        }

    } while(ch != 'q');

    return 0;
}