#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "config.h"
#include "pedido.h"
#include "pilha.h"

/**
 * @brief Limpa a tela do console.
 */
void ui_limpar_tela() {
    system("cls");
}

/**
 * @brief Exibe as informações de status do jogo.
 */
void ui_mostrar_status() {
    printf("............................\n");
    printf("PATOBURGUER -  STATUS\n");
    printf("Pontuacao: 0 | Moedas: 100 | Satisfacao: 50%%\n");
    printf("Cronometro: 00:00 | Nivel: 1\n");
    printf("............................\n\n");
}

/**
 * @brief Exibe os pedidos atualmente na fila.
 * @param filaPedidos Ponteiro constante para a fila de pedidos a ser exibida.
 */
void ui_mostrar_pedidos(const Fila* filaPedidos) {
    printf("............................\n");
    printf("PATOBURGUER - PEDIDOS DO DIA\n");

    Fila copia = *filaPedidos;
    tp_item ptr;

    int count = 1;
    while(removeFila(&copia, &ptr)) {
        Pedido* p = (Pedido*) ptr;
        printf("%d: C#%03d H%d %02dh | ", 
                count++,
                    pedido_get_id_cliente(p),
                        pedido_get_id_hamburguer(p),
                            pedido_get_hora_pedido(p));
    }

    if (filaVazia(filaPedidos)) {
        printf("Nenhum pedido na fila.");
    }

    printf("\n............................\n\n");
}

/**
 * @brief Exibe o estoque atual de ingredientes.
 * @param ingredientes Array constante de ingredientes a serem exibidos.
 * @param num_ingredientes Número de ingredientes no array.
 */
void ui_mostrar_estoque(const Ingrediente ingredientes[], int num_ingredientes) {
    printf("............................\n");
    printf("PATOBURGUER - ESTOQUE\n");

    for(int i = 0; i < num_ingredientes; i++) {
        printf("%d.%s(%d) | ", 
                ingrediente_get_id(&ingredientes[i]), 
                    ingrediente_get_nome(&ingredientes[i]), 
                        ingrediente_get_quantidade(&ingredientes[i]));

        if ((i + 1) % 3 == 0) printf("\n");
    }

    printf("\n............................\n\n");
}

/**
 * @brief Exibe o cardápio de hambúrgueres, incluindo seus ingredientes.
 * @param cardapio Array constante de hambúrgueres a serem exibidos.
 * @param num_hamburguers Número de hambúrgueres no cardápio.
 * @param ingredientes Array constante de ingredientes para buscar os nomes dos ingredientes.
 * @param num_ingredientes Número de ingredientes no array de ingredientes.
 */
void ui_mostrar_cardapio(const Hamburguer cardapio[], int num_hamburguers, const Ingrediente ingredientes[], int num_ingredientes) {
    printf("............................\n");
    printf("PATOBURGUER - CARDAPIO\n");
    
    for(int i = 0; i < num_hamburguers; i++) {
        printf("H%d: %s (P$%.1f)\n", 
                hamburguer_get_id(&cardapio[i]), 
                    hamburguer_get_nome(&cardapio[i]), 
                        hamburguer_get_preco_venda(&cardapio[i]));
        
        Pilha copia = cardapio[i].ingredientes;
        int ing_id;
        
        printf("   Ingredientes: ");
        
        while(pop(&copia, &ing_id)) {
            
            for(int k = 0; k < num_ingredientes; k++) {
                
                if(ingrediente_get_id(&ingredientes[k]) == ing_id) {
                    printf("%s, ", ingrediente_get_nome(&ingredientes[k]));
                    break;
                }

            }

        }

        printf("\b\b  \n\n");
    }
    printf(".....................\n\n");
}

/**
 * @brief Exibe as opções de comando disponíveis para o jogador.
 */
void ui_mostrar_ajuda() {
    printf("....... JOGO .......\n\n");
    printf("Comandos:\n");
    printf("  'p' - Preparar proximo pedido\n");
    printf("  'r' - Gerar novos pedidos de teste\n");
    printf("  'q' - Sair do jogo\n\n");
    printf(".....................\n\n");
}

/**
 * @brief Obtém um comando de caractere do usuário.
 * @return O caractere digitado pelo usuário.
 */
char ui_obter_comando() {
    char ch;
    printf("Digite um comando: ");
    scanf(" %c", &ch);
    return ch;
}

/**
 * @brief Pausa a execução e aguarda o usuário pressionar Enter para continuar.
 */
void ui_pressionar_enter_para_continuar() {
    printf("\nPressione Enter para continuar...");
    while(getchar() != '\n');
    getchar();
}

/**
 * @brief Exibe uma mensagem informando que um pedido está sendo preparado.
 * @param id O ID do pedido que está sendo preparado.
 */
void ui_mensagem_preparando_pedido(int id) {
    printf("\nPedido #%d em preparo!\n", id);
}

/**
 * @brief Exibe uma mensagem informando que não há pedidos na fila.
 */
void ui_mensagem_sem_pedidos() {
    printf("\nNao ha pedidos na fila!\n");
}

/**
 * @brief Exibe uma mensagem informando que novos pedidos estão sendo gerados.
 */
void ui_mensagem_gerando_pedidos() {
    printf("\nGerando novos pedidos...\n");
}

/**
 * @brief Exibe uma mensagem de erro para um comando não reconhecido.
 */
void ui_mensagem_comando_invalido() {
    printf("\nComando nao reconhecido.\n");
}

/**
 * @brief Exibe uma mensagem de despedida ao sair do jogo.
 */
void ui_mensagem_saindo() {
    printf("\nSaindo do Pato Burguer...\n");
}