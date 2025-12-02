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
#include "relatorio_consumo.h"
#include "controle_consumo.h"
#include "caixa.h"

#define CLIENTES_POR_DIA 10

int main() {
    srand(time(NULL));

    // Inicialização dos módulos
    inicializar_caixa();
    inicializa_dados();
    pedido_manager_inicializar_pedidos();
    inicializar_consumo_diario();

    // Inicialização do relatório de consumo (apenas em memória)
    ArvConsumo* arvore_consumo = criar_arvore_consumo();

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
                char opcao_loja;
                do {
                    ui_mostrar_loja(&loja_de_ingredientes, get_saldo_caixa());
                    opcao_loja = ui_obter_comando();
                    ui_limpar_tela();

                    switch (opcao_loja) {
                        case 'c': {
                            int id_compra, qtd_compra;
                            printf("--- MODO COMPRA ---\nDigite o ID do ingrediente e a quantidade (ex: 1 10).\nDigite 0 0 para voltar.\n> ");
                            scanf("%d %d", &id_compra, &qtd_compra);
                            if (id_compra != 0 && qtd_compra > 0) {
                                comprar_ingrediente(id_compra, qtd_compra);
                            }
                            ui_pressionar_enter_para_continuar();
                            break;
                        }
                        case 'v': {
                            int id_venda, qtd_venda;
                            ui_iniciar_tela_venda(ingredientes, MAX_INGREDIENTES);
                            id_venda = ui_pedir_id_ingrediente_venda();
                            if (id_venda != 0) {
                                qtd_venda = ui_pedir_quantidade_venda();
                                if (qtd_venda > 0) {
                                    vender_ingrediente(id_venda, qtd_venda);
                                }
                            }
                            ui_pressionar_enter_para_continuar();
                            break;
                        }
                        case 's':
                            printf("Saindo da loja...\n");
                            break;
                        default:
                            ui_mensagem_comando_invalido();
                            ui_pressionar_enter_para_continuar();
                            break;
                    }
                } while (opcao_loja != 's');
                break;
            }
            case 'r': {
                char tipo_relatorio;
                printf("\n--- RELATORIO DE CONSUMO ---\n");
                printf("1 - Ordem Alfabetica\n");
                printf("2 - Mais Consumidos\n");
                printf("Qualquer outra tecla para voltar.\n");
                printf("> ");
                scanf(" %c", &tipo_relatorio);

                switch(tipo_relatorio) {
                    case '1':
                        listar_consumo_alfabeticamente(arvore_consumo);
                        break;
                    case '2':
                        gerar_ranking_consumo(arvore_consumo);
                        break;
                    default:
                        break; // Volta ao menu principal
                }
                ui_pressionar_enter_para_continuar();
                break;
            }
            case 'f': {
                // Processa o fim do dia
                int num_consumidos = 0;
                const ConsumoDiario* consumos = get_consumo_do_dia(&num_consumidos);

                printf("\n--- FIM DO DIA ---\nRegistrando consumo total...\n");
                for (int i = 0; i < num_consumidos; i++) {
                    inserir_ou_atualizar_consumo(arvore_consumo, consumos[i].nome, consumos[i].quantidade);
                }
                
                // Prepara para o próximo dia
                avancarDia();
                inicializar_consumo_diario();
                gerar_clientes_na_fila(fila_de_clientes, CLIENTES_POR_DIA); // Novos clientes para o novo dia
                ui_pressionar_enter_para_continuar();
                break;
            }
            case 'q':
                if (get_saldo_caixa() < 0) {
                    printf("\n--- FALENCIA ---\n");
                    printf("Voce faliu! O Pato-Burguer fechou as portas.\n");
                }
                printf("\n--- SAINDO DO JOGO ---\n");
                gerar_ranking_consumo(arvore_consumo);
                ui_pressionar_enter_para_continuar();
                ui_mensagem_saindo();
                break;
            default: 
                ui_mensagem_comando_invalido();
                ui_pressionar_enter_para_continuar();
        }
    } while(ch != 'q');

    // Limpeza de memória
    if (fila_de_clientes != NULL) {
        destruir_fila_clientes(fila_de_clientes);
    }
    destruir_loja(&loja_de_ingredientes);
    liberar_arvore_consumo(arvore_consumo); // Libera a árvore de consumo

    return 0;
}