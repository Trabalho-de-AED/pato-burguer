# Plano de Ação: Implementação da Loja de Ingredientes

## Objetivo
Implementar um sistema de loja que permita a compra de ingredientes para reabastecer o estoque, utilizando o saldo disponível no caixa do restaurante.

## Passos

### 1. Estrutura de Dados da Loja
- **Ação:** Criar os arquivos `loja.h` e `loja.c`.
- **Detalhes:**
    - Em `loja.h`, definir a `struct IngredienteLoja` com `nome`, `preco` e `estoqueInicial`.
    - Definir a `struct Loja` que conterá um array dinâmico de `IngredienteLoja`.
    - Declarar as funções: `inicializar_loja`, `adicionar_ingrediente_loja`, `comprar_ingrediente` e `exibir_loja`.
- **Arquivos a serem criados:** `include/loja.h`, `src/loja.c`.

### 2. Integração com Dados Globais
- **Ação:** Integrar a `Loja` ao módulo de dados principal.
- **Detalhes:**
    - Em `dados.h`, declarar uma variável global para a `Loja`.
    - Em `dados.c`, chamar `inicializar_loja` dentro da função `inicializa_dados` para carregar a loja com ingredientes e preços predefinidos.
- **Arquivos a serem modificados:** `include/dados.h`, `src/dados.c`.

### 3. Funcionalidade do Caixa
- **Ação:** Adicionar uma função para debitar valores do caixa.
- **Detalhes:**
    - Em `caixa.h`, declarar a função `debitar_do_caixa(float valor)`.
    - Em `caixa.c`, implementar a lógica que subtrai o valor do saldo, verificando se há fundos suficientes.
- **Arquivos a serem modificados:** `include/caixa.h`, `src/caixa.c`.

### 4. Atualização do Estoque Principal
- **Ação:** Conectar a compra de ingredientes à atualização do estoque principal.
- **Detalhes:**
    - A função `comprar_ingrediente` (em `loja.c`) receberá o ID do ingrediente e a quantidade.
    - Ela usará a função `buscar_ingrediente_por_id` (de `dados.c`) para encontrar o ingrediente no estoque principal e aumentar sua quantidade.
- **Arquivos a serem modificados:** `src/loja.c`.

### 5. Interface do Usuário (UI) para a Loja
- **Ação:** Desenvolver a interface de usuário para o menu da loja.
- **Detalhes:**
    - Em `ui.h`, declarar a função `ui_mostrar_loja(Loja* loja, float saldo_caixa)`.
    - Em `ui.c`, implementar a função para exibir os ingredientes da loja, seus preços e o saldo do caixa. A função também deve solicitar ao usuário qual item e quantidade deseja comprar.
- **Arquivos a serem modificados:** `include/ui.h`, `src/ui.c`.

### 6. Integração com o Menu Principal
- **Ação:** Adicionar a opção de acessar a loja no menu principal.
- **Detalhes:**
    - Em `main.c`, adicionar um `case 'l':` no `switch` do menu.
    - A seleção dessa opção chamará a `ui_mostrar_loja`.
    - Implementar o fluxo que recebe os dados da UI e chama `comprar_ingrediente` e `debitar_do_caixa`, exibindo mensagens de sucesso ou falha na compra.
- **Arquivos a serem modificados:** `main.c`.

### 7. Gerenciamento de Memória
- **Ação:** Garantir a liberação da memória alocada para a loja.
- **Detalhes:**
    - Criar uma função `destruir_loja` em `loja.c`.
    - Chamar `destruir_loja` no final da execução do `main.c` para evitar vazamentos de memória.
- **Arquivos a serem modificados:** `src/loja.c`, `main.c`.