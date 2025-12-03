#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
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
#include "loja.h"

#define CLIENTES_POR_DIA 10

#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define WHITE   "\x1b[37m"
#define BOLD    "\x1b[1m"
#define BG_BLUE "\x1b[44m"

int main() {
    srand(time(NULL) ^ GetCurrentProcessId());

    inicializar_caixa();
    inicializa_dados();
    caixa_iniciar_dia();
    pedido_manager_inicializar_pedidos();
    inicializar_consumo_diario();

    ArvAVL* arvore_consumo = criarAVL();

    FilaClientes* fila_de_clientes = criar_fila_clientes();
    gerar_clientes_na_fila(fila_de_clientes, CLIENTES_POR_DIA);

    char ch;

    do {
        if (verificar_falencia()) {
            ui_limpar_tela();
            ui_tela_falencia();
            printf("\nPressione [ENTER] para aceitar seu destino...");
            while(getchar() != '\n');
            getchar();
            ch = 'q';
            continue;
        }

        ui_limpar_tela();
        ui_mostrar_logo_grande();
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
                    
                    printf(GREEN BOLD "\nSUCESSO:" RESET " Cliente " CYAN "%s" RESET " atendido!\n", 
                           cliente_get_nome(&cliente_atendido));
                    printf("    Pedido " MAGENTA BOLD "H%d" RESET " enviado para a cozinha.\n", 
                           cliente_get_id_hamburguer_preferido(&cliente_atendido));
                           
                } else {
                    printf(YELLOW BOLD "\n[!] ATENCAO:" RESET " Nao ha mais clientes na fila hoje.\n");
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
                            ui_menu_comprar(&id_compra, &qtd_compra);

                            if (id_compra != 0 && qtd_compra > 0) {
                                Ingrediente* ing_comprado = buscar_ingrediente_por_id(id_compra);
                                if (ing_comprado != NULL) {
                                    float custo_total = ing_comprado->preco_compra * qtd_compra;
                                    if (get_saldo_caixa() < custo_total) { 
                                        ui_mensagem_compra_erro_saldo(); 
                                    } else {
                                        if(comprar_ingrediente(id_compra, qtd_compra)) {
                                            ui_mensagem_compra_sucesso(qtd_compra, custo_total);
                                        } else {
                                            ui_mensagem_compra_erro_saldo(); 
                                        }
                                    }
                                } else {
                                    printf(RED BOLD "[!] ERRO:" RESET " Ingrediente nao encontrado. Tente novamente.\n");
                                }
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
                            printf(BLUE "\n>>> Voltando para o balcao principal..." RESET "\n");
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
                ui_linha_divisoria();
                printf(BOLD " SELECIONE O RELATORIO:" RESET "\n");
                printf(" " CYAN "[1]" RESET " Lista em Ordem Alfabetica\n");
                printf(" " CYAN "[2]" RESET " Ranking de Mais Consumidos\n");
                printf(" " RED  "[0]" RESET " Voltar\n\n");
                
                printf(BOLD "> Opcao: " RESET);
                scanf(" %c", &tipo_relatorio);

                switch(tipo_relatorio) {
                    case '1':
                        listar_consumo_alfabeticamente(arvore_consumo);
                        break;
                    case '2':
                        gerarRnkConsumo(arvore_consumo);
                        break;
                    default:
                        break;
                }
                ui_pressionar_enter_para_continuar();
                break;
            }
            case 'f': {
                int num_consumidos = 0;
                const ConsumoDiario* consumos = get_consumo_do_dia(&num_consumidos);

                ui_limpar_tela();
                printf(BG_BLUE WHITE BOLD "           ENCERRANDO O EXPEDIENTE           " RESET "\n\n");
                
                printf(GREEN "[+]" RESET " Consolidando relatorios de vendas...\n");
                for (int i = 0; i < num_consumidos; i++) {
                    inserir_ou_atualizar_consumo(arvore_consumo, consumos[i].nome, consumos[i].quantidade);
                }
                
                printf(GREEN "[+]" RESET " Calculando penalidades e lucro...\n");
                avancarDia();
                
                printf(GREEN "[+]" RESET " Limpando a cozinha...\n");
                inicializar_consumo_diario();
                
                printf(GREEN "[+]" RESET " Gerando fila de clientes para amanha...\n");
                gerar_clientes_na_fila(fila_de_clientes, CLIENTES_POR_DIA); 
                
                printf(YELLOW BOLD "\n>>> DIA FINALIZADO COM SUCESSO!" RESET "\n");
                
                ui_pressionar_enter_para_continuar();
                break;
            }
            case 'q':
                ui_cabecalho_relatorio_final();
                gerarRnkConsumo(arvore_consumo); 
                
                printf("\n");
                ui_linha_divisoria();
                ui_mensagem_saindo();
                
                ui_pressionar_enter_para_continuar();
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
    liberaAVL(arvore_consumo);

    return 0;
}