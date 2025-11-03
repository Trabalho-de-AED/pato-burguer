#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "gerenciador_pedido.h"
#include "fila.h"
#include "pedido.h"
#include "hamburguer.h"
#include "ingrediente.h"
#include "config.h"
#include "dados.h"
#include "ui.h"
#include "pilha_ingredientes.h"

// Contador estático para garantir IDs de pedido únicos
static int proximo_id_pedido = 1;

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
        insereFila(&filaPedidos, &pedidos[i]); // Simplificado para não ordenar por hora por enquanto
    }
}

/**
 * @brief Cria um novo pedido com base na preferência de um cliente e o adiciona à fila de pedidos.
 * @param cliente Ponteiro para o cliente que está fazendo o pedido.
 */
void cliente_faz_pedido(const Cliente* cliente) {
    // Precisamos alocar o pedido dinamicamente, pois ele será armazenado em uma fila genérica (void*).
    // Se fosse uma variável local, seu endereço se tornaria inválido ao sair da função.
    Pedido* novo_pedido = (Pedido*) malloc(sizeof(Pedido));
    if (novo_pedido == NULL) {
        // Tratar falha de alocação de memória
        perror("Falha ao alocar memória para novo pedido");
        return;
    }

    *novo_pedido = criar_pedido(
        proximo_id_pedido++,
        cliente_get_id(cliente),
        cliente_get_id_hamburguer_preferido(cliente),
        0 // Hora do pedido pode ser um valor fixo ou baseado em um relógio de jogo
    );

    if (!insereFila(&filaPedidos, novo_pedido)) {
        // Tratar o caso de a fila de pedidos estar cheia
        fprintf(stderr, "AVISO: Fila de pedidos está cheia. O pedido do cliente %s foi perdido.\n", cliente_get_nome(cliente));
        free(novo_pedido); // Liberar a memória se não puder ser enfileirado
    }
}



// ... (código anterior do arquivo) ...

/**
 * @brief Processa o próximo pedido da fila, iniciando o processo de montagem manual.
 *        Remove o pedido da fila, guia o jogador pela montagem e exibe o resultado.
 * @return O ID do pedido processado, ou 0 se a fila estiver vazia.
 */
int pedido_manager_processar_proximo_pedido() {
    tp_item ptr;
    if(removeFila(&filaPedidos, &ptr)) {
        Pedido* pedido_atual = (Pedido*) ptr;
        pedido_atual->status = EM_PREPARO;

        Hamburguer* hamburguer_gabarito = buscar_hamburguer_por_id(pedido_get_id_hamburguer(pedido_atual));
        if (hamburguer_gabarito == NULL) {
            fprintf(stderr, "ERRO: Hambúrguer com ID %d não encontrado no cardápio.\n", pedido_get_id_hamburguer(pedido_atual));
            free(pedido_atual); // Liberar memória do pedido que não pode ser processado
            return 0;
        }

        // Inicia a UI de montagem
        ui_iniciar_tela_montagem(hamburguer_gabarito);

        PilhaIngredientes* pilha_jogador = criar_pilha_ingredientes();
        int id_ingrediente_escolhido;

        // Loop de montagem
        do {
            id_ingrediente_escolhido = ui_obter_id_ingrediente();
            if (id_ingrediente_escolhido != 0) {
                Ingrediente* ing_escolhido = buscar_ingrediente_por_id(id_ingrediente_escolhido);
                if (ing_escolhido != NULL) {
                    empilhar_ingrediente(pilha_jogador, *ing_escolhido);
                    printf("Adicionado: %s\n", ingrediente_get_nome(ing_escolhido));
                } else {
                    ui_mensagem_id_invalido();
                }
            }
        } while (id_ingrediente_escolhido != 0);

        // Exibe o resultado e limpa a memória
        ui_exibir_hamburguer_montado(pilha_jogador);
        destruir_pilha_ingredientes(pilha_jogador);

        int id_processado = pedido_get_id(pedido_atual);
        free(pedido_atual); // Liberar a memória do pedido que foi alocado dinamicamente

        return id_processado;
    } 
    return 0; // Fila de pedidos vazia
}
