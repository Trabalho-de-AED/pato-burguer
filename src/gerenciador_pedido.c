#include <stdlib.h>
#include <time.h>
#include "gerenciador_pedido.h"
#include "fila.h"
#include "pedido.h"
#include "hamburguer.h"
#include "ingrediente.h"
#include "config.h"
#include "dados.h"

/**
 * @brief Fila global que armazena os pedidos do sistema.
 *        Gerenciada exclusivamente por este módulo.
 */
Fila filaPedidos;

/**
 * @brief Inicializa a fila de pedidos global.
 *        Deve ser chamada antes de qualquer operação com a fila de pedidos.
 */
void pedido_manager_inicializar_pedidos() {
    inicializaFila(&filaPedidos);
}

/**
 * @brief Função auxiliar para inserir pedidos na fila ordenados por hora.
 * @param f Ponteiro para a fila onde o pedido será inserido.
 * @param p Ponteiro para o pedido a ser inserido.
 */
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

/**
 * @brief Gera um número especificado de pedidos aleatórios e os insere na fila de pedidos.
 *        Os pedidos são gerados com IDs de cliente, IDs de hambúrguer e horas de pedido aleatórios.
 *        Os pedidos são inseridos na fila ordenados por hora de pedido.
 * @param pedidos Array de Pedido onde os pedidos gerados serão armazenados temporariamente.
 * @param n O número de pedidos a serem gerados.
 */
void pedido_manager_gerar_pedidos(Pedido pedidos[], int n) {
    for (int i = 0; i < n; i++) {
        int id_cliente = rand() % 999 + 1;
        int id_hamburguer = rand() % MAX_HAMBURGUERS + 1;
        int hora_pedido = rand() % 24;
        pedidos[i] = criar_pedido(i + 1, id_cliente, id_hamburguer, hora_pedido);
        insereFilaPorHora(&filaPedidos, &pedidos[i]);
    }
}

/**
 * @brief Processa o próximo pedido da fila de pedidos.
 *        Remove o pedido mais antigo da fila e atualiza seu status para EM_PREPARO.
 * @return O ID do pedido processado, ou 0 se a fila estiver vazia.
 */
int pedido_manager_processar_proximo_pedido() {
    tp_item ptr;
    if(removeFila(&filaPedidos, &ptr)) {
        Pedido* p = (Pedido*) ptr;
        p->status = EM_PREPARO;
        return pedido_get_id(p);
    } 
    return 0;
}
