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
#include "fila_clientes.h" // Incluir o novo cabeçalho

/**
 * @brief Define o número máximo de pedidos que podem ser gerados ou gerenciados.
 */
#define MAX_PEDIDOS 6
#define CLIENTES_POR_DIA 10 // Definir a quantidade de clientes por dia

/**
 * @brief Função principal do programa Pato Burguer.
 *        Inicializa o jogo, gerencia o loop principal e interage com o usuário.
 * @return 0 se o programa for encerrado com sucesso.
 */
int main() {

    srand(time(NULL));

    inicializa_dados();

    FilaClientes* fila_de_clientes = NULL; // 1. Inicializar como NULL

    Pedido pedidos[MAX_PEDIDOS]; 
    pedido_manager_inicializar_pedidos(); 
    pedido_manager_gerar_pedidos(pedidos, MAX_PEDIDOS);

    char ch;

    do {

        ui_limpar_tela();
        ui_mostrar_status();
        ui_mostrar_fila_clientes(fila_de_clientes); // 2. Mover exibição para o loop principal
        ui_mostrar_pedidos(&filaPedidos);
        ui_mostrar_estoque(ingredientes, MAX_INGREDIENTES); 
        ui_mostrar_cardapio(cardapio, MAX_HAMBURGUERS, ingredientes, MAX_INGREDIENTES);
        ui_mostrar_ajuda();

        ch = ui_obter_comando(); 

        switch(ch) {

            case 'c': // 3. Adicionar novo case para gerar clientes
                ui_mensagem_gerando_clientes();
                if (fila_de_clientes != NULL) {
                    destruir_fila_clientes(fila_de_clientes);
                }
                fila_de_clientes = criar_fila_clientes();
                gerar_clientes_na_fila(fila_de_clientes, CLIENTES_POR_DIA);
                ui_pressionar_enter_para_continuar();
                break;

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

    // 4. Garantir a limpeza final
    if (fila_de_clientes != NULL) {
        destruir_fila_clientes(fila_de_clientes);
    }

    return 0;
}