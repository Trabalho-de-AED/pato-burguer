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

#define MAX_PEDIDOS 6

Fila filaPedidos;

void inicializar_pedidos() {
    inicializaFila(&filaPedidos);
}

void insereFilaPorHora(Fila* f, Pedido* p) {
    Fila temp;
    inicializaFila(&temp);

    tp_item ptr;
    int inserido = 0;

    while (removeFila(f, &ptr)) {
        Pedido* atual = (Pedido*) ptr;
        if (!inserido && pedido_get_hora_pedido(p) < pedido_get_hora_pedido(atual)) {
            insereFila(&temp, p);  // insere o novo pedido antes do atual
            inserido = 1;
        }
        insereFila(&temp, atual);
    }

    if (!inserido) {
        insereFila(&temp, p);
    }

    *f = temp;
}

void gerar_pedidos(Pedido pedidos[], int n) {
    for (int i = 0; i < n; i++) {
        int id_cliente = rand() % 999 + 1;
        int id_hamburguer = rand() % MAX_HAMBURGUERS + 1;
        int hora_pedido = rand() % 24;
        pedidos[i] = criar_pedido(i + 1, id_cliente, id_hamburguer, hora_pedido);
        insereFilaPorHora(&filaPedidos, &pedidos[i]);
    }
}

int processar_proximo_pedido() {
    tp_item ptr;
    if(removeFila(&filaPedidos, &ptr)) {
        Pedido* p = (Pedido*) ptr;
        p->status = EM_PREPARO;
        return pedido_get_id(p);
    } 
    return 0;
}


int main() {

    srand(time(NULL));

    inicializa_dados();

    Pedido pedidos[MAX_PEDIDOS];
    inicializar_pedidos();
    gerar_pedidos(pedidos, MAX_PEDIDOS);

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
                int pedido_id = processar_proximo_pedido();
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
                inicializar_pedidos(); 
                gerar_pedidos(pedidos, MAX_PEDIDOS);
                ui_pressionar_enter_para_continuar();
                break;
            case 'q':
                ui_mensagem_saindo();
                break;
        }

    } while(ch != 'q');

    return 0;
}