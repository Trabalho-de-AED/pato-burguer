import re
import os

file_paths = [
    r'C:\Users\5by5\Documents\Pessoal\AED\pato-burguer\src\ui.c',
    r'C:\Users\5by5\Documents\Pessoal\AED\pato-burguer\src\gerenciador_pedido.c',
    r'C:\Users\5by5\Documents\Pessoal\AED\pato-burguer\src\ingrediente.c',
    r'C:\Users\5by5\Documents\Pessoal\AED\pato-burguer\main.c',
    r'C:\Users\5by5\Documents\Pessoal\AED\pato-burguer\src\loja.c',
    r'C:\Users\5by5\Documents\Pessoal\AED\pato-burguer\src\caixa.c',
    r'C:\Users\5by5\Documents\Pessoal\AED\pato-burguer\src\dados.c',
    r'C:\Users\5by5\Documents\Pessoal\AED\pato-burguer\src\pilha_ingredientes.c',
    r'C:\Users\5by5\Documents\Pessoal\AED\pato-burguer\src\pilha.c',
    r'C:\Users\5by5\Documents\Pessoal\AED\pato-burguer\src\pedido.c',
    r'C:\Users\5by5\Documents\Pessoal\AED\pato-burguer\src\hamburguer.c',
    r'C:\Users\5by5\Documents\Pessoal\AED\pato-burguer\src\fila_clientes.c',
    r'C:\Users\5by5\Documents\Pessoal\AED\pato-burguer\src\clientes.c',
    r'C:\Users\5by5\Documents\Pessoal\AED\pato-burguer\src\cardapio.c',
    r'C:\Users\5by5\Documents\Pessoal\AED\pato-burguer\src\fila.c',
    r'C:\Users\5by5\Documents\Pessoal\AED\pato-burguer\include\ingrediente.h',
    r'C:\Users\5by5\Documents\Pessoal\AED\pato-burguer\include\caixa.h',
    r'C:\Users\5by5\Documents\Pessoal\AED\pato-burguer\include\dados.h',
    r'C:\Users\5by5\Documents\Pessoal\AED\pato-burguer\include\loja.h',
    r'C:\Users\5by5\Documents\Pessoal\AED\pato-burguer\include\pilha_ingredientes.h',
    r'C:\Users\5by5\Documents\Pessoal\AED\pato-burguer\include\pilha.h',
    r'C:\Users\5by5\Documents\Pessoal\AED\pato-burguer\include\pedido.h',
    r'C:\Users\5by5\Documents\Pessoal\AED\pato-burguer\include\config.h',
    r'C:\Users\5by5\Documents\Pessoal\AED\pato-burguer\include\hamburguer.h',
    r'C:\Users\5by5\Documents\Pessoal\AED\pato-burguer\include\gerenciador_pedido.h',
    r'C:\Users\5by5\Documents\Pessoal\AED\pato-burguer\include\fila_clientes.h',
    r'C:\Users\5by5\Documents\Pessoal\AED\pato-burguer\include\clientes.h',
    r'C:\Users\5by5\Documents\Pessoal\AED\pato-burguer\include\cardapio.h',
    r'C:\Users\5by5\Documents\Pessoal\AED\pato-burguer\include\fila.h'
]

def remove_comments(content):
    # Remove single-line comments
    content = re.sub(r'//.*', '', content)
    # Remove multi-line comments that don't contain '@brief'
    content = re.sub(r'/\*([^*]|\*+[^*/])*?\*/', lambda m: m.group(0) if '@brief' in m.group(0) else '', content, flags=re.DOTALL)
    return content

for file_path in file_paths:
    try:
        with open(file_path, 'r+', encoding='utf-8') as f:
            content = f.read()
            content = remove_comments(content)
            f.seek(0)
            f.write(content)
            f.truncate()
        print(f'Processed {file_path}')
    except Exception as e:
        print(f'Error processing {file_path}: {e}')
