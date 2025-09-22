# -----------------------
# Makefile para Pato Burguer
# -----------------------

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -g -Iinclude
LDFLAGS = -lncurses

# Diretório de fontes
SRC_DIR = src

# Arquivos fonte
SRCS = main.c \
       $(SRC_DIR)/hamburguer.c \
       $(SRC_DIR)/ingrediente.c \
       $(SRC_DIR)/pedido.c \
       $(SRC_DIR)/fila.c \
       $(SRC_DIR)/dados.c \
       $(SRC_DIR)/pilha.c

# Arquivos objeto
OBJS = $(SRCS:.c=.o)

# Executável
TARGET = main

# -----------------------
# Regras
# -----------------------

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

# Compila os .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -f $(OBJS) $(TARGET)

# Rodar o programa
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
