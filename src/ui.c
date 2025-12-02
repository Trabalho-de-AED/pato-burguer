#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "ui.h"
#include "config.h"
#include "pedido.h"
#include "pilha.h"
#include "clientes.h"
#include "dados.h"
#include "ListaSE.h" 
#include "loja.h"    

void ui_limpar_tela() {
    system("cls");
}

void ui_mostrar_status() {
    printf("............................\n");
    printf("PATOBURGUER -  STATUS\n");
    printf("Caixa: R$%.2f\n", get_saldo_caixa());
    printf("Pontuacao: 0 | Moedas: 100 | Satisfacao: 50%%\n");
    printf("Cronometro: 00:00 | Nivel: 1\n");
    printf("............................\n\n");
}

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

    printf("Ingredientes Disponiveis para Compra:\n");
    tp_lista_encadeada* atual = loja->ingredientes_disponiveis;
    while (atual != NULL) {
        Ingrediente* ing = buscar_ingrediente_por_id(atual->info);
        if (ing != NULL) {
            printf("ID: %d | %-15s | Preco de Compra: R$%.2f\n",
                   ingrediente_get_id(ing),
                   ingrediente_get_nome(ing),
                   ingrediente_get_preco_compra(ing));
        }
        atual = atual->prox;
    }

    printf("\n............................\n");
    printf("Opcoes:\n");
    printf("  'c' - Comprar ingrediente\n");
    printf("  'v' - Vender ingrediente\n");
    printf("  's' - Sair da loja\n");
    printf("............................\n");
}

void ui_mostrar_ajuda() {
    printf("....... JOGO .......\n\n");
    printf("Comandos:\n");
    printf("  'c' - Atender proximo cliente\n");
    printf("  'p' - Preparar proximo pedido\n");
    printf("  'l' - Ir para a Loja Patonica (comprar/vender ingredientes)\n");
    printf("  'r' - Exibir relatorio de consumo\n");
    printf("  'f' - Finalizar o dia\n");
    printf("  'q' - Sair do jogo\n\n");
    printf(".....................\n\n");
}

void ui_iniciar_tela_montagem(const Hamburguer* hamburguer_gabarito, bool mostrar_receita) {
    ui_limpar_tela();
    printf("........................................\n");
    printf("..     TELA DE MONTAGEM DE PEDIDO     ..\n");
    printf("........................................\n\n");
    printf("HAMBURGUER A SER MONTADO: %s\n\n", hamburguer_get_nome(hamburguer_gabarito));

    if (mostrar_receita) {
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
    }
    
    printf("Digite o ID do ingrediente para adicionar a pilha.\n");
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

void ui_pressionar_enter_para_continuar() {
    printf("\nPressione Enter para continuar...");
    while(getchar() != '\n');
    getchar();
}


void ui_mensagem_preparando_pedido(int id) {
    
}

void ui_mensagem_sem_pedidos() {
    printf("\nNao ha pedidos na fila para preparar!\n");
}

void ui_mensagem_gerando_clientes() {
    printf("\nGerando nova fila de clientes...\n");
}

void ui_mensagem_gerando_pedidos() {
    printf("\nGerando novos pedidos...\n");
}

void ui_mensagem_comando_invalido() {
    printf("\nComando nao reconhecido.\n");
}

void ui_mensagem_id_invalido() {
    printf("\nID de ingrediente invalido ou nao encontrado na receita! Tente novamente.\n");
}

void ui_mensagem_ingrediente_sem_estoque() {
    printf("\nIngrediente sem estoque!\n");
}

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



void ui_iniciar_tela_venda(const Ingrediente ingredientes[], int num_ingredientes) {

    ui_limpar_tela();

    printf("............................\n");

    printf("PATOBURGUER - VENDA DE INGREDIENTES\n");

    printf("Seu estoque atual:\n");

    ui_mostrar_estoque(ingredientes, num_ingredientes);

    printf("............................\n\n");

    printf("Digite o ID do ingrediente que deseja vender e a quantidade.\n");

    printf("Digite '0' para voltar.\n");

}



int ui_pedir_id_ingrediente_venda() {

    int id;

    printf("> ID do ingrediente para vender: ");

    scanf("%d", &id);

    return id;

}



int ui_pedir_quantidade_venda() {

    int qtd;

    printf("> Quantidade: ");

    scanf("%d", &qtd);

    return qtd;

}
