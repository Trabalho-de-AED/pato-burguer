#include "../include/tempo.h"
#include "../include/gerenciador_pedido.h"
#include "../include/ui.h"
#include "../include/loja.h"
#include "../include/dados.h"
#include "../include/pedido.h"
#include "../include/fila.h"
#include "../include/caixa.h"
#include <stdio.h>

#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define WHITE   "\x1b[37m"
#define BOLD    "\x1b[1m"
#define BG_GREEN "\x1b[42m"

const int XP_POR_PEDIDO = 15;
const float PENALIDADE_SATISFACAO_CLIENTE_NAO_ATENDIDO = 2.5f;
const float IMPOSTO_BASE = 20.0f;
int dia_atual = 1;

void avancarDia() {
    char nome_arquivo[50];
    sprintf(nome_arquivo, "historico_vendas_dia_%d.txt", dia_atual);
    FILE* arquivo_historico = fopen(nome_arquivo, "w");

    int pedidos_concluidos = 0;
    float satisfacao_total_dia = 0;
    float media_satisfacao_dia = 0;

    if (arquivo_historico != NULL) {
        Fila fila_temp;
        inicializaFila(&fila_temp);
        tp_item ptr;

        while(removeFila(&filaPedidosProntos, &ptr)) {
            Pedido* p = (Pedido*) ptr;
            insereFila(&fila_temp, p);
            pedidos_concluidos++;
            satisfacao_total_dia += pedido_get_satisfacao(p);
        }

        while(removeFila(&fila_temp, &ptr)) {
            Pedido* p = (Pedido*) ptr;
            fprintf(arquivo_historico, "ID Pedido: %d, ID Cliente: %d, ID Hamburguer: %d, Valor: %.2f, Satisfacao: %.0f%%\n",
                    pedido_get_id(p),
                    pedido_get_id_cliente(p),
                    pedido_get_id_hamburguer(p),
                    pedido_get_valor_pago(p),
                    pedido_get_satisfacao(p));
            free(p);
        }
        fclose(arquivo_historico);
    }

    ui_limpar_tela(); 

    printf(CYAN BOLD "==============================================\n");
    printf("       FECHAMENTO DE CAIXA - DIA %02d\n", dia_atual);
    printf("==============================================" RESET "\n\n");

    float lucro = caixa_get_lucro_dia();
    printf(BOLD " RESUMO FINANCEIRO:" RESET "\n");
    if (lucro >= 0) {
        printf(GREEN " [+] Lucro Operacional:      R$ %6.2f" RESET "\n", lucro);
    } else {
        printf(RED " [-] Prejuizo Operacional:   R$ %6.2f" RESET "\n", lucro);
    }

    if (pedidos_concluidos > 0) {
        media_satisfacao_dia = satisfacao_total_dia / pedidos_concluidos;
        loja_de_ingredientes.satisfacao_media_clientes = (loja_de_ingredientes.satisfacao_media_clientes * 0.8f) + (media_satisfacao_dia * 0.2f);
        
        printf(BLUE " [*] Satisfacao Média (Hoje):      %3.0f%%" RESET "\n", media_satisfacao_dia);
    }

    int clientes_nao_atendidos = (filaPedidos.fim - filaPedidos.ini + MAX) % MAX;
    if (clientes_nao_atendidos > 0) {
        float penalidade_satisfacao = clientes_nao_atendidos * PENALIDADE_SATISFACAO_CLIENTE_NAO_ATENDIDO;
        loja_de_ingredientes.satisfacao_media_clientes -= penalidade_satisfacao;
        
        printf(RED " [!] Clientes Nao Atendidos:       %3d" RESET "\n", clientes_nao_atendidos);
        printf(RED "     > Penalidade de Satisfacao:  -%.0f%%" RESET "\n", penalidade_satisfacao);
    }

    if(loja_de_ingredientes.satisfacao_media_clientes < 0) loja_de_ingredientes.satisfacao_media_clientes = 0;

    float satisfacao_atual = loja_get_satisfacao_media(&loja_de_ingredientes);
    float imposto_diario = IMPOSTO_BASE + (IMPOSTO_BASE * ((100.0f - satisfacao_atual) / 100.0f));
    
    if (imposto_diario > 0) {
        printf(RED " [-] Imposto (Gov. Pato):    R$ %6.2f" RESET, imposto_diario);

        if(satisfacao_atual < 100){
            printf(YELLOW " - Penalidade sobre a satisfacao %.0f%%\n" RESET, satisfacao_atual);
        }else{
            printf("\n");
        }

        debitar_do_caixa(imposto_diario);
    }
    
    printf(CYAN "----------------------------------------------" RESET "\n");

    int xp_ganho = pedidos_concluidos * XP_POR_PEDIDO;
    if (media_satisfacao_dia < 70 && pedidos_concluidos > 0) {
        xp_ganho *= 0.5;
        printf(YELLOW " [!] Baixa satisfacao reduziu o XP ganho pela metade!\n" RESET);
    }
    
    loja_de_ingredientes.experiencia_total += xp_ganho;
    printf(MAGENTA BOLD " [+] XP Ganho: +%d XP" RESET " (Total: %d / %d)\n", 
           xp_ganho, 
           loja_de_ingredientes.experiencia_total, 
           loja_de_ingredientes.xp_para_proximo_nivel);

    if (loja_de_ingredientes.experiencia_total >= loja_de_ingredientes.xp_para_proximo_nivel) {
        loja_de_ingredientes.nivel_atual++;
        loja_de_ingredientes.experiencia_total -= loja_de_ingredientes.xp_para_proximo_nivel;
        loja_de_ingredientes.xp_para_proximo_nivel *= 1.5;
        
        printf("\n");
        printf(YELLOW BOLD " ############################################\n");
        printf(YELLOW BOLD " #            LEVEL UP! NIVEL %d             #\n", loja_de_ingredientes.nivel_atual);
        printf(YELLOW BOLD " ############################################\n" RESET);
    }

    printf("\n");
    printf(WHITE "Arquivo de log 'historico_vendas_dia_%d.txt' salvo.\n" RESET, dia_atual);

    dia_atual++;
    loja_atualizar_precos();
    caixa_iniciar_dia();
    pedido_manager_inicializar_pedidos();

    printf(CYAN "\n>>> Pressione [ENTER] para iniciar o dia %d..." RESET, dia_atual);
    
    while(getchar() != '\n'); 
    getchar();
}

int getDia() {
    return dia_atual;
}