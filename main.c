#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "hamburguer.h"
#include "ingrediente.h"
#include "pedido.h"
#include "fila.h"
#include "pilha.h"
#include "config.h"
#include "dados.h"

#define MAX_PEDIDOS 6

// ---------- FILA DE PEDIDOS ----------
Fila filaPedidos;

void inicializar_pedidos() {
    inicializaFila(&filaPedidos);
}

// Gera pedidos aleatórios e insere na fila
void gerar_pedidos(Pedido pedidos[], int n) {
    for (int i = 0; i < n; i++) {
        int id_cliente = rand() % 999 + 1;
        int id_hamburguer = rand() % MAX_HAMBURGUERS + 1;
        int hora_pedido = rand() % 24;
        pedidos[i] = criar_pedido(i + 1, id_cliente, id_hamburguer, hora_pedido);
        insereFila(&filaPedidos, &pedidos[i]);
    }
}

// Mostra os pedidos da fila
void mostrar_pedidos(WINDOW* win) {
    werase(win);
    box(win, 0, 0);
    mvwprintw(win, 0, 2, " Pedidos do Dia ");

    int linha = 2;
    int coluna = 2;
    int colunas = 3;
    int espacamento = 20;

    Fila copia = filaPedidos;
    tp_item ptr;
    int count = 1;

    while(removeFila(&copia, &ptr)) {
        Pedido* p = (Pedido*) ptr;
        mvwprintw(win, linha, coluna, "%d: C#%03d H%d %02dh",
                  count++,
                  pedido_get_id_cliente(p),
                  pedido_get_id_hamburguer(p),
                  pedido_get_hora_pedido(p));

        coluna += espacamento;
        if ((count - 1) % colunas == 0) {
            coluna = 2;
            linha += 1;
        }
    }
    wrefresh(win);
}

// Processa o próximo pedido da fila
void processar_proximo_pedido() {
    tp_item ptr;
    if(removeFila(&filaPedidos, &ptr)) {
        Pedido* p = (Pedido*) ptr;
        p->status = EM_PREPARO;
    }
}

// ---------- MAIN ----------
int main() {
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    srand(time(NULL));

    // ---------- INICIALIZA DADOS ----------
    inicializa_dados(); // ingredientes[] e cardapio[] preenchidos

    int altura, largura;
    getmaxyx(stdscr, altura, largura);

    int largura_jogo = (largura * 2) / 5;
    int altura_status = 4;
    int altura_jogo = (altura - altura_status) * 2 / 3;

    // ---------- STATUS ----------
    WINDOW* janela_status = newwin(altura_status, largura_jogo, 0, 0);
    box(janela_status, 0, 0);
    mvwprintw(janela_status, 0, 2, " STATUS ");
    mvwprintw(janela_status, 1, 2, "Pontuacao: 0 | Moedas: 100 | Satisfacao: 50%%");
    mvwprintw(janela_status, 2, 2, "Cronometro: 00:00 | Nivel: 1");
    wrefresh(janela_status);

    // ---------- JANELA DO JOGO ----------
    WINDOW* janela_jogo = newwin(altura_jogo, largura_jogo, altura_status, 0);
    box(janela_jogo, 0, 0);
    mvwprintw(janela_jogo, 0, 2, " JOGO ");
    mvwprintw(janela_jogo, 2, 2, "Area principal do jogo");
    mvwprintw(janela_jogo, 4, 2, "Pressione 'q' para sair");
    mvwprintw(janela_jogo, 6, 2, "[Aqui ficara a montagem do hamburguer]");
    mvwprintw(janela_jogo, altura_jogo - 2, 2, "Aguardando comando...");
    wrefresh(janela_jogo);

    // ---------- PEDIDOS ----------
    int altura_pedidos = altura - altura_status - altura_jogo - 6;
    WINDOW* janela_pedidos = newwin(altura_pedidos, largura_jogo, altura_status + altura_jogo, 0);
    box(janela_pedidos, 0, 0);

    Pedido pedidos[MAX_PEDIDOS];
    inicializar_pedidos();
    gerar_pedidos(pedidos, MAX_PEDIDOS);
    mostrar_pedidos(janela_pedidos);

    // ---------- ESTOQUE ----------
    int altura_estoque = 6;
    WINDOW* janela_estoque = newwin(altura_estoque, largura_jogo, altura_status + altura_jogo + altura_pedidos, 0);
    box(janela_estoque, 0, 0);
    mvwprintw(janela_estoque, 0, 2, " ESTOQUE ");

    int colunas_estoque = 3;
    int espacamento_colunas = 20;
    for(int i = 0; i < MAX_INGREDIENTES; i++) {
        int linha = 1 + i / colunas_estoque;
        int col = 2 + (i % colunas_estoque) * espacamento_colunas;
        if(linha >= altura_estoque - 1) break;
        mvwprintw(janela_estoque, linha, col, "%d.%s(%d)",
                  ingrediente_get_id(&ingredientes[i]),
                  ingrediente_get_nome(&ingredientes[i]),
                  ingrediente_get_quantidade(&ingredientes[i]));
    }
    wrefresh(janela_estoque);

    // ---------- CARDÁPIO ----------
    int largura_cardapio = largura - largura_jogo;
    int altura_cardapio = altura;
    WINDOW* janela_cardapio = newwin(altura_cardapio, largura_cardapio, 0, largura_jogo);
    box(janela_cardapio, 0, 0);
    mvwprintw(janela_cardapio, 0, 2, " CARDAPIO ");

    int col1 = 2, col2 = largura_cardapio/4, col3 = largura_cardapio/2, col4 = (largura_cardapio*3)/4;
    int linha_base = 2;

    for(int i = 0; i < MAX_HAMBURGUERS; i++) {
        int coluna, linha_offset;
        if(i < 3) { coluna = col1; linha_offset = i * 15; }
        else if(i < 6) { coluna = col2; linha_offset = (i - 3) * 15; }
        else if(i < 9) { coluna = col3; linha_offset = (i - 6) * 15; }
        else { coluna = col4; linha_offset = (i - 9) * 15; }

        int linha_hamb = linha_base + linha_offset;
        mvwprintw(janela_cardapio, linha_hamb, coluna, "%d.%s (P$%.1f)",
                  hamburguer_get_id(&cardapio[i]),
                  hamburguer_get_nome(&cardapio[i]),
                  hamburguer_get_preco_venda(&cardapio[i]));

        // Mostra ingredientes na ordem de montagem usando pilha
        Pilha copia = cardapio[i].ingredientes;
        int ing_id, offset = 1;
        while(pop(&copia, &ing_id)) {
            for(int k = 0; k < MAX_INGREDIENTES; k++) {
                if(ingrediente_get_id(&ingredientes[k]) == ing_id) {
                    mvwprintw(janela_cardapio, linha_hamb + offset, coluna, "- %s", ingrediente_get_nome(&ingredientes[k]));
                    offset++;
                    break;
                }
            }
        }
    }
    wrefresh(janela_cardapio);

    // ---------- LOOP PRINCIPAL ----------
    int ch;
    while((ch = wgetch(janela_jogo)) != 'q') {
        mvwprintw(janela_jogo, altura_jogo - 2, 2, "                              ");
        mvwprintw(janela_jogo, altura_jogo - 2, 2, "Tecla pressionada: %c", ch);

        switch(ch) {
            case '1': mvwprintw(janela_jogo, 8, 2, "Selecionado: Hamburguer 1     "); break;
            case '2': mvwprintw(janela_jogo, 8, 2, "Selecionado: Hamburguer 2     "); break;
            case 'p':
                mvwprintw(janela_jogo, 8, 2, "Preparando pedido...          ");
                processar_proximo_pedido();
                mostrar_pedidos(janela_pedidos);
                break;
            case 'r':
                mvwprintw(janela_jogo, 8, 2, "Reiniciando jogo...           ");
                gerar_pedidos(pedidos, MAX_PEDIDOS);
                mostrar_pedidos(janela_pedidos);
                break;
            default: mvwprintw(janela_jogo, 8, 2, "Comando nao reconhecido       ");
        }
        wrefresh(janela_jogo);
    }

    // ---------- LIMPEZA ----------
    delwin(janela_status);
    delwin(janela_jogo);
    delwin(janela_pedidos);
    delwin(janela_estoque);
    delwin(janela_cardapio);
    endwin();

    return 0;
}
