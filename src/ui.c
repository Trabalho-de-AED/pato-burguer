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

#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define WHITE   "\x1b[37m"
#define BOLD    "\x1b[1m"
#define BG_BLUE "\x1b[44m"


void ui_limpar_tela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void ui_linha_divisoria() {
    printf(BLUE "============================================================\n" RESET);
}

void ui_cabecalho_secao(const char* titulo) {
    printf("\n" CYAN BOLD ">>> %s" RESET "\n", titulo);
    printf(CYAN "------------------------------------------------------------" RESET "\n");
}

void ui_mostrar_logo_grande() {
    printf(YELLOW BOLD);
    printf("  ____  _  _______ ____    ____  _   _ ____   ____ _   _ _____ ____  \n");
    printf(" |  _ \\/ \\|__   __/ __ \\  |  _ \\| | | |  _ \\ / ___| | | | ____|  _ \\ \n");
    printf(" | |_) / _ \\ | | | |  | | | |_) | | | | |_) | |  _| | | |  _| | |_) |\n");
    printf(" |  __/ ___ \\| | | |__| | |  _ <| |_| |  _ <| |_| | |_| | |___|  _ < \n");
    printf(" |_| /_/   \\_\\_|  \\____/  |_| \\_\\\\___/|_| \\_\\\\____|\\___/|_____|_| \\_\\\n");
    printf(RESET "\n");
}


void ui_mostrar_status() {
    ui_linha_divisoria();

    printf(BOLD " STATUS ATUAL \n" RESET);
    
    printf(" " GREEN "Caixa: R$ %6.2f" RESET "   |   ", get_saldo_caixa());
    printf(YELLOW "Satisfacao: 50%%" RESET "   |   ");
    printf(MAGENTA "Nivel: 1" RESET "\n");
    
    printf(" " CYAN  "Pontuacao: 0" RESET "        |   ");
    printf(WHITE "Moedas: 100" RESET "       |   ");
    printf("Tempo: 00:00\n");
    
    ui_linha_divisoria();
}

void ui_mostrar_fila_clientes(const FilaClientes* fila_de_clientes) {
    ui_cabecalho_secao("FILA DE CLIENTES");

    if (fila_clientes_vazia(fila_de_clientes)) {
        printf(RED " * O restaurante esta vazio no momento.\n" RESET);
    } else {
        NoCliente* atual = fila_de_clientes->inicio;
        int count = 1;
        while (atual != NULL) {
            printf(BOLD " %d." RESET " %-15s " YELLOW "(Pref: H%d)" RESET "\n", 
                   count++,
                   cliente_get_nome(&atual->cliente), 
                   cliente_get_id_hamburguer_preferido(&atual->cliente));
            atual = atual->proximo;
        }
    }
    printf("\n");
}

void ui_mostrar_pedidos(const Fila* filaPedidos) {
    ui_cabecalho_secao("PEDIDOS NA COZINHA");

    Fila copia = *filaPedidos;
    tp_item ptr;

    int count = 1;
    if (filaVazia(filaPedidos)) {
        printf(GREEN " * Nao ha pedidos pendentes. Tudo limpo!\n" RESET);
    } else {
        printf(" ID  | Cliente | Pedido | Hora \n");
        printf("-----|---------|--------|------\n");
        while(removeFila(&copia, &ptr)) {
            Pedido* p = (Pedido*) ptr;
            printf(" #%02d | " CYAN "C#%03d" RESET "   | " MAGENTA "H%d" RESET "     | %02dh \n", 
                    count++,
                    pedido_get_id_cliente(p),
                    pedido_get_id_hamburguer(p),
                    pedido_get_hora_pedido(p));
        }
    }
    printf("\n");
}

void ui_mostrar_estoque(const Ingrediente ingredientes[], int num_ingredientes) {
    ui_cabecalho_secao("ESTOQUE DE INGREDIENTES");

    for(int i = 0; i < num_ingredientes; i++) {
        char* cor_qtd = GREEN;
        if(ingrediente_get_quantidade(&ingredientes[i]) < 5) cor_qtd = RED; 
        
        printf(" [%02d] %-15s : " BOLD "%s%3d" RESET " un.  ", 
                ingrediente_get_id(&ingredientes[i]), 
                ingrediente_get_nome(&ingredientes[i]),
                cor_qtd, 
                ingrediente_get_quantidade(&ingredientes[i]));

        if ((i + 1) % 2 == 0) printf("\n"); 
    }
    printf("\n");
}

void ui_mostrar_cardapio(const Hamburguer cardapio[], int num_hamburguers, const Ingrediente ingredientes[], int num_ingredientes) {
    ui_cabecalho_secao("CARDAPIO PATO BURGUER");
    
    for(int i = 0; i < num_hamburguers; i++) {
        printf(YELLOW BOLD " H%d: %s" RESET GREEN " (R$ %.2f)\n" RESET, 
                hamburguer_get_id(&cardapio[i]), 
                hamburguer_get_nome(&cardapio[i]), 
                hamburguer_get_preco_venda(&cardapio[i]));
        
        Pilha copia = cardapio[i].ingredientes;
        int ing_id;
        
        printf("    |_ Ingredientes: ");
        
        int first = 1;
        while(pop(&copia, &ing_id)) {
            for(int k = 0; k < num_ingredientes; k++) {
                if(ingrediente_get_id(&ingredientes[k]) == ing_id) {
                    if(!first) printf(", ");
                    printf("%s", ingrediente_get_nome(&ingredientes[k]));
                    first = 0;
                    break;
                }
            }
        }
        printf("\n\n");
    }
}

void ui_mostrar_loja(const Loja* loja, float saldo_caixa) {
    ui_limpar_tela();
    ui_mostrar_logo_grande(); 
    
    printf(BG_BLUE WHITE BOLD "           LOJA DE SUPRIMENTOS PATONICA           " RESET "\n");
    printf(BOLD " SEU SALDO ATUAL: " GREEN "R$ %.2f" RESET "\n\n", saldo_caixa);

    printf(CYAN " ITENS A VENDA:" RESET "\n");
    printf(" ------------------------------------------------\n");
    printf(" ID | Item            | Preco de Compra \n");
    printf(" ---|-----------------|-----------------\n");

    tp_lista_encadeada* atual = loja->ingredientes_disponiveis;
    while (atual != NULL) {
        Ingrediente* ing = buscar_ingrediente_por_id(atual->info);
        if (ing != NULL) {
            printf(" %02d | %-15s | " YELLOW "R$ %.2f" RESET "\n",
                   ingrediente_get_id(ing),
                   ingrediente_get_nome(ing),
                   ingrediente_get_preco_compra(ing));
        }
        atual = atual->prox;
    }

    printf("\n");
    ui_linha_divisoria();
    printf(BOLD " OPCOES DA LOJA:" RESET "\n");
    printf(" " GREEN "[c]" RESET " Comprar ingrediente\n");
    printf(" " RED   "[v]" RESET " Vender ingrediente\n");
    printf(" " BLUE  "[s]" RESET " Sair da loja\n");
    ui_linha_divisoria();
}

void ui_mostrar_ajuda() {
    ui_cabecalho_secao("AJUDA E COMANDOS");
    
    printf(BOLD " TECLAS DE ACAO:" RESET "\n\n");
    printf("  " CYAN "[c]" RESET " : Atender proximo cliente \n");
    printf("  " CYAN "[p]" RESET " : Preparar proximo pedido \n");
    printf("  " CYAN "[l]" RESET " : Ir para a Loja Patonica\n");
    printf("  " CYAN "[r]" RESET " : Relatorio de consumo\n");
    printf("  " CYAN "[f]" RESET " : Finalizar o dia\n");
    printf("  " RED  "[q]" RESET " : Sair do jogo\n\n");
    
    ui_linha_divisoria();
}

void ui_iniciar_tela_montagem(const Hamburguer* hamburguer_gabarito, bool mostrar_receita) {
    ui_limpar_tela();
    printf(BG_BLUE WHITE BOLD "           COZINHA - MONTAGEM           " RESET "\n\n");
    
    printf("META: Preparar " YELLOW BOLD "%s" RESET "\n", hamburguer_get_nome(hamburguer_gabarito));

    if (mostrar_receita) {
        printf(CYAN "\n--- RECEITA  ---" RESET "\n");

        Pilha copia_receita = hamburguer_gabarito->ingredientes;
        int ing_id;
        while(pop(&copia_receita, &ing_id)) {
            Ingrediente* ing = buscar_ingrediente_por_id(ing_id);
            if (ing != NULL) {
                printf("  [ID %d] %s\n", ingrediente_get_id(ing), ingrediente_get_nome(ing));
            }
        }
        printf("--------------------------\n");
    }
    
    printf("\nDigite o " BOLD "ID do ingrediente" RESET " para empilhar.\n");
    printf("Digite " RED "'0'" RESET " para finalizar e servir.\n");
    ui_linha_divisoria();
}

void ui_exibir_hamburguer_montado(PilhaIngredientes* pilha_jogador) {
    printf("\n" MAGENTA "--- SEU HAMBURGUER (Topo para Base) ---" RESET "\n");
    
    Ingrediente ing_temp;
    while (desempilhar_ingrediente(pilha_jogador, &ing_temp)) {
        printf("  (_) %s\n", ingrediente_get_nome(&ing_temp));
    }
    printf("---------------------------------------\n");
}

char ui_obter_comando() {
    char ch;
    printf(BOLD "\n> Digite um comando: " RESET);
    scanf(" %c", &ch);
    return ch;
}

int ui_obter_id_ingrediente() {
    int id;
    printf(BOLD "> Digite o ID: " RESET);
    scanf("%d", &id);
    return id;
}

void ui_pressionar_enter_para_continuar() {
    printf("\n" CYAN "Pressione [ENTER] para continuar..." RESET);
    while(getchar() != '\n');
    getchar();
}

void ui_mensagem_preparando_pedido(int id) {
    printf(YELLOW "\nPreparando pedido #%d...\n" RESET, id);
}

void ui_mensagem_sem_pedidos() {
    printf(RED "\nNao ha pedidos na fila para preparar!\n" RESET);
}

void ui_mensagem_gerando_clientes() {
    printf(BLUE "\n[!] Gerando nova fila de clientes...\n" RESET);
}

void ui_mensagem_gerando_pedidos() {
    printf(BLUE "\n[!] Gerando novos pedidos...\n" RESET);
}

void ui_mensagem_comando_invalido() {
    printf(RED "\n[X] Comando nao reconhecido.\n" RESET);
}

void ui_mensagem_id_invalido() {
    printf(RED "\n[X] ID invalido ou nao encontrado!\n" RESET);
}

void ui_mensagem_ingrediente_sem_estoque() {
    printf(RED BOLD "\n[!] Ingrediente sem estoque!\n" RESET);
}

void ui_mensagem_saindo() {
    printf(MAGENTA "\nObrigado por jogar Pato Burguer! Ate logo...\n" RESET);
}

void ui_exibir_resultado_validacao(int erros, float penalidade_total, float preco_final) {
    printf("\n" GREEN "--- AVALIACAO DO CHEFE ---" RESET "\n");
    
    if (erros == 0) {
        printf(GREEN BOLD "PERFEITO! Nenhum erro." RESET "\n");
    } else {
        printf(RED "Erros na montagem: %d" RESET "\n", erros);
        printf(RED "Multa aplicada: R$ %.2f" RESET "\n", penalidade_total);
    }

    printf(BOLD "Valor liquido recebido: " GREEN "R$ %.2f" RESET "\n", preco_final);
    ui_linha_divisoria();
}

void ui_iniciar_tela_venda(const Ingrediente ingredientes[], int num_ingredientes) {
    ui_limpar_tela();
    ui_cabecalho_secao("VENDA DE EXCEDENTES");
    
    ui_mostrar_estoque(ingredientes, num_ingredientes);
    
    printf("\nDigite o " BOLD "ID" RESET " para vender ou " RED "'0'" RESET " para voltar.\n");
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

void ui_menu_comprar(int* id, int* qtd) {
    ui_linha_divisoria(); // Mantém o contexto da loja em cima
    
    printf(BG_BLUE WHITE BOLD "           CAIXA - COMPRA DE REPOSICAO           " RESET "\n\n");
    
    printf("Instrucoes: Digite o " BOLD "ID" RESET " e a " BOLD "Quantidade" RESET " desejada.\n");
    printf("Exemplo: " CYAN "1 10" RESET " (Comprar 10 unidades do item ID 1)\n");
    printf("Digite " RED "0 0" RESET " para cancelar.\n\n");
    
    printf(BOLD "> Entrada (ID QTD): " RESET);
    scanf("%d %d", id, qtd);
}

void ui_mensagem_compra_sucesso(int qtd, float custo) {
    printf("\n" GREEN BOLD "[OK] Compra realizada com sucesso!" RESET "\n");
    printf("     Adicionado: %d un | Custo total: R$ %.2f\n", qtd, custo);
}

void ui_mensagem_compra_erro_saldo() {
    printf("\n" RED BOLD "[X] Erro: Saldo insuficiente ou ID invalido!" RESET "\n");
}