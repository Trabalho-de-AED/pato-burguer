# Checklist de Implementação: Loja Patônica

## Etapa 1: Preparação e Integração da Estrutura de Dados (`ListaSE`)
- [x] **Ação 1.1:** Criar Arquivo de Cabeçalho `include/ListaSE.h`.
- [x] **Ação 1.2:** Garantir Compilação do Novo Módulo `src/ListaSE.c`.

## Etapa 2: Refatoração do Módulo `loja`
- [x] **Ação 2.1:** Modificar `include/loja.h` para usar `tp_listase`.
- [x] **Ação 2.2:** Modificar `src/loja.c` para usar a lista dinâmica.
- [x] **Ação 2.3:** Implementar `vender_ingrediente` em `src/loja.c`.

## Etapa 3: Atualização da Interface do Usuário (`ui`)
- [x] **Ação 3.1:** Modificar `ui_mostrar_loja` em `src/ui.c`.
- [x] **Ação 3.2:** Criar Interface de Venda em `src/ui.c`.
- [x] **Ação 3.3:** Modificar `ui_mostrar_ajuda` em `src/ui.c`.

## Etapa 4: Integração no Fluxo Principal (`main.c`)
- [x] **Ação 4.1:** Modificar `main.c` para incluir a lógica de compra e venda.