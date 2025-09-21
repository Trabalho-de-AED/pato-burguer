#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_HAMBURGUERS 12
#define MAX_INGREDIENTES 12
#define MAX_PEDIDOS 6


typedef struct {
    int id;
    char nome[50];
    float preco;
    char ingredientes[12][20];
    int qtd_ingredientes;
} Hamburguer;

typedef struct {
    int id;
    char nome[20];
    int quantidade;
} Ingrediente;

typedef struct {
    int cliente_id;
    int hamburguer_id;
} Pedido;

// ---------- FUNÇÕES ----------
void gerar_pedidos(Pedido pedidos[], int n) {
    for(int i = 0; i < n; i++) {
        pedidos[i].cliente_id = rand() % 999 + 1;
        pedidos[i].hamburguer_id = rand() % MAX_HAMBURGUERS + 1;
    }
}

void mostrar_pedidos(WINDOW* win, Pedido pedidos[], int n) {
    werase(win);
    box(win,0,0);
    mvwprintw(win,0,2," Pedidos do Dia ");
    int linha = 2;
    int coluna = 2;
    int colunas = 3; // número de colunas na visualização

    for(int i = 0; i < n; i++) {
        mvwprintw(win, linha, coluna, "%d.Cliente#%03d-H%d", i+1, pedidos[i].cliente_id, pedidos[i].hamburguer_id);
        coluna += 25; // largura entre colunas
        if((i+1) % colunas == 0) {
            coluna = 2;
            linha += 2; // pula para a próxima linha após preencher as colunas
        }
    }
    wrefresh(win);
}

int main() {
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    srand(time(NULL));

    int altura, largura;
    getmaxyx(stdscr, altura, largura);
    int dia = 1;

    // ---------- DIMENSÕES ----------
    int largura_jogo = (largura * 2) / 5;
    int altura_status = 4; // altura fixa do status
    int altura_jogo = (altura - altura_status) * 2 / 3;

    // ---------- STATUS ----------
    WINDOW *janela_status = newwin(altura_status, largura_jogo, 0, 0);
    box(janela_status,0,0);
    mvwprintw(janela_status,0,2," STATUS ");
    mvwprintw(janela_status,1,2,"Pontuacao: 0 | Moedas: 100 | Satisfacao: 50%%");
    mvwprintw(janela_status,2,2,"Cronometro: 00:00 | Nivel: 1");
    wrefresh(janela_status);

    // ---------- INGREDIENTES ----------
    Ingrediente ingredientes[MAX_INGREDIENTES] = {
        {1,"Pao",50},{2,"Carne",50},{3,"Queijo",40},{4,"Alface",40},
        {5,"Molho",30},{6,"Bacon",30},{7,"Tomate",25},{8,"Ovo",20},
        {9,"Cebola",20},{10,"Pepperoni",15},{11,"Ketchup",10},{12,"Mostarda",10}
    };

    // ---------- CARDAPIO ----------
    Hamburguer cardapio[MAX_HAMBURGUERS];
    const char* nomes_hamb[12] = {
        "Bit and Bacon","Duck Cheese","Quackteirao","Big Pato",
        "Pato Deluxe","Pato Veggie","Pato Chicken","Quack Bacon",
        "Pato Supreme","Cheesy Duck","Bacon Egg Duck","Pato Especial"
    };

    for(int i=0;i<MAX_HAMBURGUERS;i++){
        cardapio[i].id = i+1;
        strcpy(cardapio[i].nome, nomes_hamb[i]);
        cardapio[i].preco = 10.0 + i;
        cardapio[i].qtd_ingredientes = 3 + rand() % 10; // 3 a 12 ingredientes
        for(int j=0;j<cardapio[i].qtd_ingredientes;j++){
            strcpy(cardapio[i].ingredientes[j], ingredientes[j % MAX_INGREDIENTES].nome);
        }
    }

    // ---------- JANELA DO JOGO ----------
    WINDOW *janela_jogo = newwin(altura_jogo, largura_jogo, altura_status, 0);
    box(janela_jogo,0,0);
    mvwprintw(janela_jogo,0,2," JOGO ");
    mvwprintw(janela_jogo,2,2,"Area principal do jogo");
    mvwprintw(janela_jogo,4,2,"Pressione 'q' para sair");
    mvwprintw(janela_jogo,6,2,"[Aqui ficara a montagem do hamburguer]");
    wrefresh(janela_jogo);

    // ---------- PEDIDOS ----------
    int altura_pedidos = altura - altura_status - altura_jogo - 6;
    WINDOW *janela_pedidos = newwin(altura_pedidos, largura_jogo, altura_status + altura_jogo, 0);
    box(janela_pedidos,0,0);
    Pedido pedidos[MAX_PEDIDOS];
    gerar_pedidos(pedidos, MAX_PEDIDOS);
    mostrar_pedidos(janela_pedidos,pedidos,MAX_PEDIDOS);

    // ---------- ESTOQUE ----------
    int altura_estoque = 6;
WINDOW *janela_estoque = newwin(altura_estoque, largura_jogo, altura_status + altura_jogo + altura_pedidos,0);
box(janela_estoque,0,0);
mvwprintw(janela_estoque,0,2," ESTOQUE ");

int colunas_estoque = 3;
int espacamento_colunas = 20; // Aumenta o espaçamento horizontal entre os ingredientes

for(int i=0;i<MAX_INGREDIENTES;i++){
    int linha = 1 + i / colunas_estoque;
    int col = 2 + (i % colunas_estoque) * espacamento_colunas;
    if(linha >= altura_estoque-1) break;
    mvwprintw(janela_estoque,linha,col,"%d.%s(%d)",ingredientes[i].id,ingredientes[i].nome,ingredientes[i].quantidade);
}

wrefresh(janela_estoque);

    // ---------- CARDÁPIO ----------
    int largura_cardapio = largura - largura_jogo;
    int altura_cardapio = altura;
    WINDOW *janela_cardapio = newwin(altura_cardapio, largura_cardapio, 0, largura_jogo);
    box(janela_cardapio,0,0);
    mvwprintw(janela_cardapio,0,2," CARDAPIO ");

    int col1 = 2, col2 = largura_cardapio/4, col3 = largura_cardapio/2, col4 = (largura_cardapio*3)/4;
    int linha_base = 2;
    for(int i=0;i<MAX_HAMBURGUERS;i++){
        int coluna, linha_offset;
        if(i<3){ coluna=col1; linha_offset=i*15; }
        else if(i<6){ coluna=col2; linha_offset=(i-3)*15; }
        else if(i<9){ coluna=col3; linha_offset=(i-6)*15; }
        else{ coluna=col4; linha_offset=(i-9)*15; }

        int linha_hamb = linha_base + linha_offset;
        if(linha_hamb + cardapio[i].qtd_ingredientes >= altura_cardapio-1) continue;

        mvwprintw(janela_cardapio, linha_hamb, coluna,"%d.%s (P$%.1f)",cardapio[i].id,cardapio[i].nome,cardapio[i].preco);
        for(int j=0;j<cardapio[i].qtd_ingredientes;j++){
            if(linha_hamb+1+j >= altura_cardapio-1) break;
            mvwprintw(janela_cardapio, linha_hamb+1+j, coluna,"- %s",cardapio[i].ingredientes[j]);
        }
    }
    wrefresh(janela_cardapio);

    // ---------- LOOP PRINCIPAL ----------
    int ch;
    mvwprintw(janela_jogo, altura_jogo-2,2,"Aguardando comando...");
    wrefresh(janela_jogo);

    while((ch = wgetch(janela_jogo)) != 'q'){
        mvwprintw(janela_jogo, altura_jogo-2,2,"                              ");
        mvwprintw(janela_jogo, altura_jogo-2,2,"Tecla pressionada: %c", ch);

        switch(ch){
            case '1':
                mvwprintw(janela_jogo,8,2,"Selecionado: Hamburguer 1     ");
                break;
            case '2':
                mvwprintw(janela_jogo,8,2,"Selecionado: Hamburguer 2     ");
                break;
            case 'p':
                mvwprintw(janela_jogo,8,2,"Preparando pedido...          ");
                break;
            case 'r':
                mvwprintw(janela_jogo,8,2,"Reiniciando jogo...           ");
                gerar_pedidos(pedidos,MAX_PEDIDOS);
                mostrar_pedidos(janela_pedidos,pedidos,MAX_PEDIDOS);
                break;
            default:
                mvwprintw(janela_jogo,8,2,"Comando nao reconhecido       ");
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
