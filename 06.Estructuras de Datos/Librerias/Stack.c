#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 10

#define BLACK   "\x1B[30m"
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"
#define WHITE   "\x1B[37m"
#define BRIGHT_BLACK   "\x1B[90m"
#define BRIGHT_RED     "\x1B[91m"
#define BRIGHT_GREEN   "\x1B[92m"
#define BRIGHT_YELLOW  "\x1B[93m" // También puede parecer naranja dependiendo de la terminal
#define BRIGHT_BLUE    "\x1B[94m"
#define BRIGHT_MAGENTA "\x1B[95m"
#define BRIGHT_CYAN    "\x1B[96m"
#define BRIGHT_WHITE   "\x1B[97m"
#define RESET   "\x1B[0m"

/// @brief Estructura para almacenar la información del usuario.
struct StackData{
    char usuario[10];
    char clave[10];
};

/// @brief Estructura para la pila (stack), que almacenará elementos de tipo StackData.
struct Stack{
    int top;
    struct StackData data[MAX_STACK_SIZE];
};

/// @brief Inicializa la pila, asignándole memoria y estableciendo el top a -1.
/// @return Un puntero a la pila recién creada.
struct Stack* stackInit() {
    struct Stack* stack = malloc(sizeof(struct Stack));
    stack->top = -1;
    return stack;
}

/// @brief Libera la memoria asignada a la pila.
/// @param stack Un puntero a la pila a liberar.
void stackFree(struct Stack* stack) {
    free(stack);
}

/// @brief Agrega (push) un elemento al top de la pila.
/// @param stack Un puntero a la pila donde se agregará el dato.
/// @param data El dato para agregar a la pila.
/// @return 0 si el dato se agregó con éxito, -1 si la pila estaba llena.
int push(struct Stack* stack, struct StackData data) {
    if (stack->top < MAX_STACK_SIZE - 1) {
        stack->data[++stack->top] = data;
        return 0;
    } else {
        return -1; // error: pila llena
    }
}

/// @brief Elimina (pop) el elemento del top de la pila y lo devuelve.
/// @param stack Un puntero a la pila de donde se eliminará el dato.
/// @return El dato eliminado, o un dato de error si la pila estaba vacía.
struct StackData pop(struct Stack* stack) {
    if (stack->top >= 0) {
        return stack->data[stack->top--];
    } else {
        struct StackData errorData = {"Error","Pila llena"}; // Definir un valor de retorno de error
        return errorData;
    }
}

/// @brief Lee los datos de un usuario desde la entrada estándar.
/// @param data Un puntero al dato donde se almacenarán los datos leídos.
void readData(struct StackData* data) {
    printf(BRIGHT_WHITE"Introduce el usuario: "BRIGHT_BLUE);
    scanf("%9s", data->usuario);

    printf(BRIGHT_WHITE"Introduce la clave: "BRIGHT_BLUE);
    scanf("%9s", data->clave);
}

/// @brief Imprime los datos de un usuario a la salida estándar.
/// @param data El dato para imprimir.
void printData(struct StackData data) {
    printf(YELLOW"%s %s\n"RESET, data.usuario, data.clave);
}

/// @brief El punto de entrada principal del programa.
/// @return El código de estado con el que termina el programa.
int main() {
    struct Stack* stack = stackInit();

    char command[10];

    while (1) {
        printf(BRIGHT_WHITE"Introduce un comando (push, pop, exit): "BRIGHT_GREEN);
        scanf("%9s", command);

        if (strcmp(command, "push") == 0) {
            if (stack->top >= MAX_STACK_SIZE - 1) {
                printf(BRIGHT_RED"Error: Pila llena.\n"RESET);
                continue;
            }

            struct StackData dato;
            readData(&dato);

            push(stack, dato);
        } else if (strcmp(command, "pop") == 0) {
            struct StackData dato = pop(stack);

            if (strcmp(dato.usuario, "Error") == 0) {
                printf(BRIGHT_RED"Pila vacía.\n"RESET);
            } else {
                printData(dato);
            }
        } else if (strcmp(command, "pop.a") == 0) {
            if (stack->top == -1) {
                printf(BRIGHT_RED"No hay más personas registradas.\n"RESET);
            }
            while (stack->top != -1) {
                struct StackData dato = pop(stack);
                printData(dato);
            }
        } else if (strcmp(command, "exit") == 0) {
            break;
        } else {
            printf(BRIGHT_RED"Comando desconocido: %s\n"RESET, command);
        }
    }

    stackFree(stack);
    printf(RESET);
    return 0;
}