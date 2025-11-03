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
#include "caixa.h"


static int proximo_id_pedido = 1;

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
        insereFila(&filaPedidos, &pedidos[i]);
    }
}

void cliente_faz_pedido(const Cliente* cliente) {
    Pedido* novo_pedido = (Pedido*) malloc(sizeof(Pedido));
    if (novo_pedido == NULL) {
        perror("Falha ao alocar memória para novo pedido");
        return;
    }
    *novo_pedido = criar_pedido(
        proximo_id_pedido++,
        cliente_get_id(cliente),
        cliente_get_id_hamburguer_preferido(cliente),
        0
    );
    if (!insereFila(&filaPedidos, novo_pedido)) {
        fprintf(stderr, "AVISO: Fila de pedidos está cheia. O pedido do cliente %s foi perdido.\n", cliente_get_nome(cliente));
        free(novo_pedido);
    }
}

static int contar_erros_montagem(PilhaIngredientes* pilha_jogador, const Hamburguer* hamburguer_gabarito) {
    PilhaIngredientes* pilha_receita = criar_pilha_ingredientes();
    Pilha* pilha_gabarito_copia = pilha_duplicar(&hamburguer_gabarito->ingredientes);

    
    int id_ing;
    while (pop(pilha_gabarito_copia, &id_ing)) {
        Ingrediente* ing = buscar_ingrediente_por_id(id_ing);
        if (ing) {
            empilhar_ingrediente(pilha_receita, *ing);
        }
    }
    free(pilha_gabarito_copia); 

    int erros = 0;
    Ingrediente ing_jogador, ing_receita;

    
    while (!pilha_ingredientes_vazia(pilha_jogador) && !pilha_ingredientes_vazia(pilha_receita)) {
        desempilhar_ingrediente(pilha_jogador, &ing_jogador);
        desempilhar_ingrediente(pilha_receita, &ing_receita);
        if (ingrediente_get_id(&ing_jogador) != ingrediente_get_id(&ing_receita)) {
            erros++;
        }
    }

    
    erros += pilha_ingredientes_tamanho(pilha_jogador);
    erros += pilha_ingredientes_tamanho(pilha_receita);

    destruir_pilha_ingredientes(pilha_receita);
    return erros;
}

int pedido_manager_processar_proximo_pedido() {
    tp_item ptr;
    if(removeFila(&filaPedidos, &ptr)) {
        Pedido* pedido_atual = (Pedido*) ptr;
        pedido_atual->status = EM_PREPARO;

        Hamburguer* hamburguer_gabarito = buscar_hamburguer_por_id(pedido_get_id_hamburguer(pedido_atual));
        if (hamburguer_gabarito == NULL) {
            fprintf(stderr, "ERRO: Hambúrguer com ID %d não encontrado no cardápio.\n", pedido_get_id_hamburguer(pedido_atual));
            free(pedido_atual);
            return 0;
        }

        ui_iniciar_tela_montagem(hamburguer_gabarito);

        PilhaIngredientes* pilha_jogador = criar_pilha_ingredientes();
        int id_ingrediente_escolhido;

        do {
            id_ingrediente_escolhido = ui_obter_id_ingrediente();
            if (id_ingrediente_escolhido != 0) {
                Ingrediente* ing_escolhido = buscar_ingrediente_por_id(id_ingrediente_escolhido);
                if (ing_escolhido != NULL) {
                    if (ingrediente_get_quantidade(ing_escolhido) > 0) {
                        ingrediente_diminuir_estoque(ing_escolhido, 1);
                        empilhar_ingrediente(pilha_jogador, *ing_escolhido);
                        printf("Adicionado: %s\n", ingrediente_get_nome(ing_escolhido));
                    } else {
                        ui_mensagem_ingrediente_sem_estoque();
                    }
                } else {
                    ui_mensagem_id_invalido();
                }
            }
        } while (id_ingrediente_escolhido != 0);
        
        PilhaIngredientes* pilha_jogador_original = duplicar_pilha_ingredientes(pilha_jogador);

        
        int erros = contar_erros_montagem(pilha_jogador, hamburguer_gabarito);
        float preco_base = hamburguer_get_preco_venda(hamburguer_gabarito);
        float penalidade = erros * PENALIDADE_POR_ERRO;
        float preco_final = preco_base - penalidade;
        if (preco_final < 0) {
            preco_final = 0;
        }

        atualizar_caixa(preco_final);
        
        pedido_atual->erros_montagem = erros;
        pedido_atual->valor_pago = preco_final;
        pedido_atual->status = PRONTO;
        
        PilhaIngredientes* pilha_para_exibir = duplicar_pilha_ingredientes(pilha_jogador_original);
        ui_exibir_hamburguer_montado(pilha_para_exibir);
        destruir_pilha_ingredientes(pilha_para_exibir);

        ui_exibir_resultado_validacao(erros, penalidade, preco_final);
        
        destruir_pilha_ingredientes(pilha_jogador);
        destruir_pilha_ingredientes(pilha_jogador_original);


        int id_processado = pedido_get_id(pedido_atual);
        
        

        return id_processado;
    }
    return 0; 
}

