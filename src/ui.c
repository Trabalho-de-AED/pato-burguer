#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "config.h"
#include "pedido.h"
#include "pilha.h"
#include "clientes.h"
#include "dados.h"

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
    printf("Caixa: R$%.2f\n", get_saldo_caixa());
    printf("Pontuacao: 0 | Moedas: 100 | Satisfacao: 50%%\n");
    printf("Cronometro: 00:00 | Nivel: 1\n");
    printf("............................\n\n");
}

/**
 * @brief Exibe a fila de clientes que aguardam atendimento.
 * @param fila_de_clientes Ponteiro para a fila de clientes.
 */
void ui_mostrar_fila_clientes(const FilaClientes* fila_de_clientes) {
    printf("............................\n");
    printf("PATOBURGUER - FILA DE CLIENTES\n");

    if (fila_clientes_vazia(fila_de_clientes)) {
        printf("Nenhum cliente na fila.\n");
    } else {
        NoCliente* atual = fila_de_clientes->inicio;
        int count = 1;
        while (atual != NULL) {
            printf("%d: %s (H%d) | ", 
                   count++,
                   cliente_get_nome(&atual->cliente), 
                   cliente_get_id_hamburguer_preferido(&atual->cliente));
            atual = atual->proximo;
        }
    }

    printf("\n............................\n\n");
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

void ui_mostrar_loja(const Loja* loja, float saldo_caixa) {
    ui_limpar_tela();
    printf("............................\n");
    printf("PATOBURGUER - LOJA DE INGREDIENTES\n");
    printf("Seu saldo: R$%.2f\n", saldo_caixa);
    printf("............................\n\n");

    for (int i = 0; i < loja->num_ingredientes; i++) {
        printf("ID: %d | %-15s | Preco: R$%.2f\n", 
               loja->ingredientes[i].id_ingrediente, 
               loja->ingredientes[i].nome, 
               loja->ingredientes[i].preco_unitario);
    }

    printf("\n............................\n");
    printf("Digite o ID do ingrediente e a quantidade (ex: 1 10).\n");
    printf("Digite 0 0 para voltar.\n");
}

/**
 * @brief Exibe as opções de comando disponíveis para o jogador.
 */
void ui_mostrar_ajuda() {
    printf("....... JOGO .......\n\n");
    printf("Comandos:\n");
    printf("  'c' - Atender proximo cliente\n");
    printf("  'p' - Preparar proximo pedido\n");
    printf("  'l' - Ir para a loja de ingredientes\n");
    printf("  'q' - Sair do jogo\n\n");
    printf(".....................\n\n");
}

void ui_iniciar_tela_montagem(const Hamburguer* hamburguer_gabarito) {
    ui_limpar_tela();
    printf("========================================\n");
    printf("==     TELA DE MONTAGEM DE PEDIDO     ==\n");
    printf("========================================\n\n");
    printf("HAMBURGUER A SER MONTADO: %s\n\n", hamburguer_get_nome(hamburguer_gabarito));
    printf("RECEITA (Ingredientes Necessários):\n");

    Pilha copia_receita = hamburguer_gabarito->ingredientes;
    int ing_id;
    while(pop(&copia_receita, &ing_id)) {
        Ingrediente* ing = buscar_ingrediente_por_id(ing_id);
        if (ing != NULL) {
            printf("  ID: %d - %s\n", ingrediente_get_id(ing), ingrediente_get_nome(ing));
        }
    }
    printf("\n----------------------------------------\n");
    printf("Digite o ID do ingrediente para adicionar à pilha.\n");
    printf("Digite '0' para finalizar a montagem.\n");
    printf("----------------------------------------\n");
}

void ui_exibir_hamburguer_montado(PilhaIngredientes* pilha_jogador) {
    printf("\n--- SEU HAMBURGUER MONTADO ---\n");
    Ingrediente ing_temp;
    while (desempilhar_ingrediente(pilha_jogador, &ing_temp)) {
        printf("  - %s\n", ingrediente_get_nome(&ing_temp));
    }
    printf("--------------------------------------------------\n");
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

int ui_obter_id_ingrediente() {
    int id;
    printf("> Digite o ID do ingrediente: ");
    scanf("%d", &id);
    return id;
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
    // Esta mensagem pode ser removida ou adaptada, pois agora entramos na tela de montagem
}

/**
 * @brief Exibe uma mensagem informando que não há pedidos na fila.
 */
void ui_mensagem_sem_pedidos() {
    printf("\nNao ha pedidos na fila para preparar!\n");
}

/**
 * @brief Exibe uma mensagem informando que novos clientes estão sendo gerados.
 */
void ui_mensagem_gerando_clientes() {
    printf("\nGerando nova fila de clientes...\n");
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

void ui_mensagem_id_invalido() {
    printf("\nID de ingrediente invalido ou nao encontrado na receita! Tente novamente.\n");
}

/**
 * @brief Exibe uma mensagem de despedida ao sair do jogo.
 */
void ui_mensagem_saindo() {
    printf("\nSaindo do Pato Burguer...\n");
}

void ui_exibir_resultado_validacao(int erros, float penalidade_total, float preco_final) {
    printf("\n--- RESULTADO DO PREPARO ---\n");
    printf("Erros na montagem: %d\n", erros);
    printf("Penalidade total: R$%.2f\n", penalidade_total);
    printf("Valor final do pedido: R$%.2f\n", preco_final);
    printf("--------------------------------\n");
}