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
#include "fila_clientes.h"
#include "tempo.h"

#define CLIENTES_POR_DIA 10

int main() {

    srand(time(NULL));

    
    inicializar_caixa();
    inicializa_dados();
    pedido_manager_inicializar_pedidos();

    
    FilaClientes* fila_de_clientes = criar_fila_clientes();
    gerar_clientes_na_fila(fila_de_clientes, CLIENTES_POR_DIA);

    char ch;

    do {
        
        ui_limpar_tela();
        ui_mostrar_status();
        ui_mostrar_fila_clientes(fila_de_clientes);
        ui_mostrar_pedidos(&filaPedidos);
        ui_mostrar_estoque(ingredientes, MAX_INGREDIENTES); 
        ui_mostrar_cardapio(cardapio, MAX_HAMBURGUERS, ingredientes, MAX_INGREDIENTES);
        ui_mostrar_ajuda();

        ch = ui_obter_comando(); 

        switch(ch) {

            case 'c': { 
                Cliente cliente_atendido;
                if (desenfileirar_cliente(fila_de_clientes, &cliente_atendido)) {
                    cliente_faz_pedido(&cliente_atendido);
                    
                    printf("\nCliente %s atendido! Pedido (H%d) enviado para a cozinha.\n", 
                           cliente_get_nome(&cliente_atendido), 
                           cliente_get_id_hamburguer_preferido(&cliente_atendido));
                } else {
                    printf("\nNao ha mais clientes na fila para atender.\n");
                }
                ui_pressionar_enter_para_continuar();
                break;
            }

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

            case 'l': { 
                int id_compra, qtd_compra;
                do {
                    ui_mostrar_loja(&loja_de_ingredientes, get_saldo_caixa());
                    printf("> ");
                    scanf("%d %d", &id_compra, &qtd_compra);
                    if (id_compra != 0 && qtd_compra > 0) {
                        comprar_ingrediente(id_compra, qtd_compra);
                        ui_pressionar_enter_para_continuar();
                    }
                } while (id_compra != 0);
                break;
            }

            case 'f': {
                avancarDia();
                break;
            }

            case 'q': 
                ui_mensagem_saindo();
                break;

            default: 
                ui_mensagem_comando_invalido();
                ui_pressionar_enter_para_continuar();
        }

    } while(ch != 'q');

    
    if (fila_de_clientes != NULL) {
        destruir_fila_clientes(fila_de_clientes);
    }
    destruir_loja(&loja_de_ingredientes);
    

    return 0;
}