#include "../include/tempo.h"
#include "../include/gerenciador_pedido.h"
#include "../include/ui.h"
#include <stdio.h>

int dia_atual = 1;

void avancarDia() {
    char nome_arquivo[50];
    sprintf(nome_arquivo, "historico_vendas_dia_%d.txt", dia_atual);
    FILE* arquivo_historico = fopen(nome_arquivo, "w");

    if (arquivo_historico != NULL) {
        tp_item ptr;
        while(removeFila(&filaPedidosProntos, &ptr)) {
            Pedido* p = (Pedido*) ptr;
            fprintf(arquivo_historico, "ID Pedido: %d, ID Cliente: %d, ID Hamburguer: %d, Valor: %.2f\n",
                    pedido_get_id(p),
                    pedido_get_id_cliente(p),
                    pedido_get_id_hamburguer(p),
                    pedido_get_valor_pago(p));
            free(p); // Libera a memória do pedido processado
        }
        fclose(arquivo_historico);
    }

    dia_atual++;

    pedido_manager_inicializar_pedidos();

    printf("\nDia %d finalizado. Iniciando o dia %d.\n", dia_atual - 1, dia_atual);
    ui_pressionar_enter_para_continuar();
}
