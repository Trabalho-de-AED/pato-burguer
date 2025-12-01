# Plano de Ação: Jogo de Memória na Montagem de Pedidos

## 1. Introdução

Este plano de ação descreve as modificações necessárias para implementar uma nova mecânica de "jogo de memória" durante a montagem dos hambúrgueres. Conforme o novo requisito, a receita do pedido será exibida por apenas alguns segundos, forçando o jogador a memorizar os ingredientes para a montagem. Esta revisão do plano **prioriza a edição das estruturas existentes** em vez de criar novas funcionalidades e menus, conforme solicitado.

**Requisito:** *"Os pedidos serão exibidos apenas uma única vez e por poucos segundos, isso porque o nosso querido Chef Sanval Ebert (...) decretou que agora cada atendente tem que prestar atenção de primeira."*

---

## 2. Etapas de Implementação

### Etapa 1: Configuração e Preparação do Ambiente

O primeiro passo é configurar a constante de tempo e garantir que as ferramentas necessárias para a pausa estejam disponíveis.

- **Ação 1.1: Definir a Constante de Tempo de Exibição**
  - **Objetivo:** Centralizar o tempo que a receita ficará visível em uma constante global.
  - **Detalhes:** Editar o arquivo `include/config.h` e adicionar a seguinte linha:
    ```c
    #define TEMPO_EXIBICAO_RECEITA_SEGUNDOS 3
    ```

- **Ação 1.2: Garantir Disponibilidade da Função de Pausa**
  - **Objetivo:** Incluir o cabeçalho do sistema operacional necessário para pausar a execução.
  - **Detalhes:** O projeto é direcionado ao Windows (via MinGW). A função `Sleep()` será usada. Será necessário adicionar `#include <windows.h>` no topo do arquivo que irá gerenciar o fluxo da montagem (`src/gerenciador_pedido.c`). Também será necessário incluir `<stdbool.h>` em `include/ui.h` para usar o tipo `bool`.

### Etapa 2: Modificação da Interface de Montagem (`ui`)

A função `ui_iniciar_tela_montagem` será adaptada para permitir a exibição condicional da receita.

- **Ação 2.1: Modificar `ui_iniciar_tela_montagem` para Exibição Condicional**
  - **Objetivo:** Fazer com que a função `ui_iniciar_tela_montagem` possa ser chamada para exibir a receita completa ou apenas o cabeçalho e as instruções.
  - **Detalhes:**
    1.  **`include/ui.h`:** Alterar a assinatura do protótipo da função `ui_iniciar_tela_montagem` para incluir um parâmetro booleano:
        ```c
        void ui_iniciar_tela_montagem(const Hamburguer* hamburguer_gabarito, bool mostrar_receita);
        ```
    2.  **`src/ui.c`:**
        *   Alterar a assinatura da função.
        *   Usar a variável `mostrar_receita` para controlar condicionalmente a impressão da seção "RECEITA (Ingredientes Necessários):" e a lista de ingredientes associada. O cabeçalho (`HAMBURGUER A SER MONTADO: ...`) e as instruções finais devem ser sempre exibidos.

### Etapa 3: Integração no Fluxo de Processamento de Pedido

A orquestração da exibição temporizada deve ser inserida no local correto do código que gerencia o preparo dos pedidos.

- **Ação 3.1: Modificar o Gerenciador de Pedidos (`src/gerenciador_pedido.c`)**
  - **Objetivo:** Alterar a função `pedido_manager_processar_proximo_pedido()` para orquestrar a exibição temporizada da receita usando a `ui_iniciar_tela_montagem` modificada.
  - **Detalhes:**
    1.  Dentro de `pedido_manager_processar_proximo_pedido` (após obter o `hamburguer_gabarito`):
        *   Chamar `ui_iniciar_tela_montagem(hamburguer_gabarito, true);` (para mostrar a receita).
        *   Pausar a execução: `Sleep(TEMPO_EXIBICAO_RECEITA_SEGUNDOS * 1000);`.
        *   Limpar a tela: `ui_limpar_tela()`.
        *   Chamar `ui_iniciar_tela_montagem(hamburguer_gabarito, false);` (para mostrar apenas o cabeçalho e instruções, sem a receita).
        *   Continuar com a lógica já existente para coletar os ingredientes do jogador e validar o pedido.

---

## 3. Conclusão

Ao final desta implementação, a funcionalidade de montagem de pedidos terá um novo elemento de desafio, exigindo que o jogador memorize a receita em um curto espaço de tempo. Este plano ajustado garante que a nova mecânica seja incorporada editando as funcionalidades existentes, sem a criação de novos menus ou módulos de UI desnecessários, alinhando-se estritamente à sua solicitação.