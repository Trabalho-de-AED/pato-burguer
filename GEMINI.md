
# Pato Burguer Analysis

## Project Overview
Pato Burguer is a terminal-based game that simulates the administration of a hamburger restaurant. The project is developed in C and uses fundamental data structures like stacks and queues to manage game elements. The main goal of the game is to manage customer orders, assemble hamburgers according to the menu, and control the inventory of ingredients.

The project is well-structured, with a clear separation of concerns between different modules. The `src` directory contains the implementation of the game's logic, while the `include` directory contains the header files with the data structure definitions and function prototypes.

## Building and Running
The project is built and run using the GCC compiler. The following commands can be used to compile and run the project on Windows:

1. **Install MinGW** and add the path to the `gcc` compiler to the system's PATH.
2. **Compile the project:**
```bash
gcc -std=c99 -o main.exe main.c src/*.c -Iinclude
```
3. **Run the executable:**
```bash
./main.exe
```

## Development Conventions
The project follows standard C programming conventions. The code is well-commented, and the variable and function names are descriptive. The use of header files to define data structures and function prototypes promotes modularity and code reusability.

The project also uses a `Makefile` to facilitate the compilation process, although the `Makefile` itself is not present in the provided file list.

## Key Data Structures
The project uses two main data structures:

*   **Queue:** A circular queue is used to manage customer orders. The `fila.h` header file defines the `Fila` struct and the operations for manipulating the queue.
*   **Stack:** A stack is used to manage the ingredients of a hamburger. The `pilha.h` header file defines the `Pilha` struct and the operations for manipulating the stack.

## Core Components
The game's core components are defined in the following header files:

*   **`ingrediente.h`:** Defines the `Ingrediente` struct, which represents an ingredient in the game.
*   **`hamburguer.h`:** Defines the `Hamburguer` struct, which represents a hamburger on the menu.
*   **`pedido.h`:** Defines the `Pedido` struct, which represents a customer's order.
*   **`cliente.h`:** Defines the `Cliente` struct, which represents a customer.

## Game Logic
The main game loop is located in the `main.c` file. It handles user input, processes game events, and updates the game's state. The game's logic is implemented in the various source files in the `src` directory.
