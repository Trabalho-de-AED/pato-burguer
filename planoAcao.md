# Plano de Ação: Implementação da Loja Patônica

## 1. Introdução

Este plano de ação detalha os passos necessários para implementar o requisito da "Loja Patônica" no projeto Pato Burguer. O objetivo é permitir que o jogador possa **comprar e vender** ingredientes, utilizando uma estrutura de dados de **lista simplesmente encadeada (`ListaSE.c`)** para gerenciar os itens da loja.

Contexto: Logo após, você pode acessar a Loja Patônica, onde é possível comprar novos
ingredientes para o próximo dia ou vender os que ficaram em excesso. Assim, a cada
rodada, o desafio é equilibrar pedidos, estoque e lucro, mantendo a hamburgueria
funcionando sem bugs e sem deixar o chef que não usa touca: Sanval Ebert, decepcionado

---

## 2. Etapas de Implementação

### Etapa 1: Preparação e Integração da Estrutura de Dados (`ListaSE`)

O primeiro passo é integrar o código da lista dinâmica ao projeto para que possa ser utilizado pelos outros módulos.

- **Ação 1.1: Criar Arquivo de Cabeçalho `ListaSE.h`**
  - **Objetivo:** Declarar as funções de `ListaSE.c` para que possam ser chamadas a partir de outros arquivos.
  - **Detalhes:** Criar o arquivo `include/ListaSE.h` e adicionar os protótipos de todas as funções definidas em `src/ListaSE.c` (ex: `inicializa_listase`, `insere_listase_no_fim`, etc.). A estrutura `tp_listase` e o tipo `tp_item` também devem ser definidos neste header.

- **Ação 1.2: Garantir Compilação do Novo Módulo**
  - **Objetivo:** Incluir o novo arquivo `src/ListaSE.c` no processo de compilação do projeto.
  - **Detalhes:** Atualizar o comando de compilação para incluir `src/ListaSE.c`. O novo comando será:
    ```bash
    gcc -std=c99 -o main.exe main.c src/*.c -Iinclude
    ```
    (Assumindo que `src/*.c` já captura `ListaSE.c`). É importante verificar se `ListaSE.c` está de fato no diretório `src`.

### Etapa 2: Refatoração do Módulo `loja`

A estrutura atual da loja precisa ser substituída para usar a lista dinâmica.

- **Ação 2.1: Modificar `include/loja.h`**
  - **Objetivo:** Atualizar a definição da estrutura da loja.
  - **Detalhes:** Incluir `ListaSE.h`. A `struct Loja` atual (se houver uma que armazena ingredientes de forma estática) deve ser alterada para conter um ponteiro `tp_listase*`, que representará a lista de IDs de ingredientes à venda.

- **Ação 2.2: Modificar `src/loja.c`**
  - **Objetivo:** Adaptar toda a lógica da loja para operar sobre a lista dinâmica.
  - **Detalhes:**
    1. **`inicializar_loja`**: A função deverá criar uma lista vazia e preenchê-la com os IDs dos ingredientes que estarão disponíveis para compra.
    2. **`comprar_ingrediente`**: A lógica de compra deve ser ajustada para procurar o item na lista antes de efetuar a transação.
    3. **`destruir_loja`**: A função deve chamar `destroi_listase` para liberar a memória alocada pela lista de ingredientes da loja.

- **Ação 2.3: Implementar Funcionalidade de Venda em `loja.c`**
  - **Objetivo:** Criar a função que permitirá ao jogador vender ingredientes do seu estoque.
  - **Detalhes:** Criar uma nova função `vender_ingrediente(int id_ingrediente, int quantidade)`. Esta função irá:
    1. Verificar se o jogador possui a `quantidade` especificada do `id_ingrediente` no seu estoque (`dados.c`).
    2. Calcular o valor da venda (pode ser uma porcentagem do `preco_compra`).
    3. Incrementar o `saldo_caixa` do jogador.
    4. Decrementar a `quantidade` do ingrediente no estoque do jogador.

### Etapa 3: Atualização da Interface do Usuário (`ui`)

A interface da loja deve refletir as novas funcionalidades de compra e venda.

- **Ação 3.1: Modificar `src/ui.c` - `ui_mostrar_loja`**
  - **Objetivo:** Exibir os itens da loja a partir da lista dinâmica e dar opções de compra/venda.
  - **Detalhes:**
    1. A função `ui_mostrar_loja` deverá iterar sobre a `tp_listase` para exibir os ingredientes disponíveis para compra.
    2. A interface deve ser clara, mostrando como comprar e como iniciar o processo de venda.

- **Ação 3.2: Modificar `src/ui.c` - Criar Interface de Venda**
  - **Objetivo:** Criar uma tela ou prompt para o processo de venda.
  - **Detalhes:**
    1. O jogador primeiro visualiza seu próprio estoque (pode reusar parte de `ui_mostrar_estoque`).
    2. O jogador insere o ID do ingrediente e a quantidade que deseja vender.

- **Ação 3.3: Modificar `src/ui.c` - `ui_mostrar_ajuda`**
  - **Objetivo:** Informar ao jogador sobre os novos comandos.
  - **Detalhes:** Adicionar instruções na ajuda sobre como acessar a loja e como realizar a venda de ingredientes.

### Etapa 4: Integração no Fluxo Principal (`main.c`)

Finalmente, as novas funcionalidades devem ser integradas ao loop principal do jogo.

- **Ação 4.1: Modificar `main.c`**
  - **Objetivo:** Atualizar o loop principal do jogo para incluir a lógica de venda.
  - **Detalhes:**
    1. Na seção do `case 'l'` (loja), o código deve ser expandido para perguntar ao usuário se ele deseja 'c'omprar ou 'v'ender.
    2. Com base na escolha, chamar as funções apropriadas (`ui_mostrar_loja` para compra ou a nova UI de venda).
    3. Processar a entrada do usuário e invocar as funções de backend `comprar_ingrediente` ou `vender_ingrediente`.

---

## 3. Conclusão

Ao final da execução deste plano, o projeto Pato Burguer contará com uma "Loja Patônica" funcional, onde o jogador poderá gerenciar seu estoque comprando e vendendo ingredientes. A implementação utilizará a estrutura de lista dinâmica fornecida, cumprindo o requisito obrigatório do projeto.
