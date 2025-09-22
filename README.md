# Pato Burguer

## Sobre o Projeto
O Pato Burguer é um jogo de terminal que simula a administração de uma hamburgueria. O projeto foi desenvolvido como atividade semestral da disciplina de Algoritmos e Estrutura de Dados no SENAI CIMATEC, sob orientação do professor Márcio Soussa.  

O objetivo do jogo é gerenciar pedidos de clientes, montar hambúrgueres de acordo com o cardápio e controlar o estoque de ingredientes, utilizando conceitos de estruturas de dados como pilha e fila.

## Membros do Projeto
- Pedro Henrique Andrade  
- Pedro Silva Ferreira
- Pedro Prieto  
- Atila Bezerra  
- Yan Fiaz

## Funcionalidades da Primeira Entrega
Até a primeira entrega, o projeto inclui:  
- Um menu principal contendo informações do jogo;  
- Um cardápio completo com todos os hambúrgueres, seus ingredientes e valores;  
- Geração aleatória de pedidos utilizando a estrutura fila;  
- Empilhamento dos ingredientes de cada hambúrguer usando a estrutura pilha, mostrando a ordem correta de montagem;  
- Uma região de status com variáveis que serão usadas futuramente, como paciência dos clientes, cronômetro.  

## O que foi implementado
- Criação dos ingredientes;  
- Criação do cardápio com os hambúrgueres;  
- Geração dos pedidos de um dia da hamburgueria;  
- Estruturas de dados: Pilha para ingredientes e Fila para pedidos;  
- Structs implementadas: Ingrediente, Cliente, Hamburguer, Cardapio e Pedido.

## Ingredientes Utilizados
- Pão  
- Carne  
- Queijo  
- Alface  
- Molho  
- Bacon  
- Tomate  
- Ovo  
- Cebola  
- Pepperoni  

## Hambúrgueres do Cardápio
- Bit and Bacon  
- Duck Cheese  
- Quackteirao  
- Big Pato  
- Pato Deluxe  
- Pato Veggie  
- Pato Chicken  
- Quack Bacon  
- Pato Supreme  
- Cheesy Duck  
- Bacon Egg Duck  
- Pato Especial  

## Tecnologias Utilizadas
- Linguagem C  
- Makefile para facilitar a compilação  

## Como Rodar o Projeto

Windows:
1. Instale o MinGW e adicione o caminho do gcc ao PATH do sistema.
2. Na raiz do projeto, compile com o comando: `gcc -std=c99 -o main.exe main.c src/*.c -Iinclude`
3. Execute o programa com: ./main.exe

### Observação:
O projeto é uma simulação em terminal, com foco em lógica de programação, estruturas de dados e manipulação de informações do jogo. Futuras entregas incluirão interação do jogador, processamento dos pedidos e lógica completa do jogo.