#include <stdlib.h>
#include <time.h>
#include "gerenciador_pedido.h"
#include "fila.h"
#include "pedido.h"
#include "hamburguer.h"
#include "ingrediente.h"
#include "config.h"
#include "dados.h"

Fila filaPedidos;

void pedido_manager_inicializar_pedidos() {

    inicializaFila(&filaPedidos);
    
}

static void insereFilaPorHora(Fila* f, Pedido* p) {

    Fila temp;
    inicializaFila(&temp);

    tp_item ptr;
    int inserido = 0;

    while (removeFila(f, &ptr)) {

        Pedido* atual = (Pedido*) ptr;

        if (!inserido && pedido_get_hora_pedido(p) < pedido_get_hora_pedido(atual)) {

            insereFila(&temp, p);
            inserido = 1;
        }

        insereFila(&temp, atual);

    }

    if (!inserido) {

        insereFila(&temp, p);

    }

    *f = temp;
}

void pedido_manager_gerar_pedidos(Pedido pedidos[], int n) {

    for (int i = 0; i < n; i++) {

        int id_cliente = rand() % 999 + 1;

        int id_hamburguer = rand() % MAX_HAMBURGUERS + 1;

        int hora_pedido = rand() % 24;

        pedidos[i] = criar_pedido(i + 1, id_cliente, id_hamburguer, hora_pedido);

        insereFilaPorHora(&filaPedidos, &pedidos[i]);

    }
}

int pedido_manager_processar_proximo_pedido() {
    
    tp_item ptr
    ;

    if(removeFila(&filaPedidos, &ptr)) {

        Pedido* p = (Pedido*) ptr;
        p->status = EM_PREPARO;
        return pedido_get_id(p);
        
    } 

    return 0;
}