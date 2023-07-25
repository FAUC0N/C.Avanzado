#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 10

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

struct QueueData {
    char usuario[10];
    char clave[10];
};

struct Queue {
    int front, rear;
    struct QueueData data[MAX_QUEUE_SIZE];
};

struct Queue* queueInit() {
    struct Queue* queue = malloc(sizeof(struct Queue));
    queue->front = 0;
    queue->rear = -1;
    return queue;
}

void queueFree(struct Queue* queue) {
    free(queue);
}

int enqueue(struct Queue* queue, struct QueueData data) {
    if (queue->rear < MAX_QUEUE_SIZE - 1) {
        queue->data[++queue->rear] = data;
        return 0;
    } else {
        return -1; // error: cola llena
    }
}

struct QueueData dequeue(struct Queue* queue) {
    if (queue->front <= queue->rear) {
        return queue->data[queue->front++];
    } else {
        struct QueueData errorData = {"Error","Cola"};
        return errorData;
    }
}

void readData(struct QueueData* data) {
    printf(BRIGHT_WHITE"Introduce el usuario: "BRIGHT_BLUE);
    scanf("%9s", data->usuario);

    printf(BRIGHT_WHITE"Introduce la clave: "BRIGHT_BLUE);
    scanf("%9s", data->clave);
}

void printData(struct QueueData data) {
    printf(YELLOW"%s %s\n"RESET, data.usuario, data.clave);
}

int main() {
    struct Queue* queue = queueInit();

    char command[10];

    while (1) {
        printf(BRIGHT_WHITE"Introduce un comando (enq, deq, exit): "BRIGHT_GREEN);
        scanf("%9s", command);

        if (strcmp(command, "enq") == 0) {
            if (queue->rear >= MAX_QUEUE_SIZE - 1) {
                printf(BRIGHT_RED"Error: Cola llena.\n"RESET);
                continue;
            }

            struct QueueData dato;
            readData(&dato);

            enqueue(queue, dato);
        } else if (strcmp(command, "deq") == 0) {
            struct QueueData dato = dequeue(queue);

            if (strcmp(dato.usuario, "Error") == 0) {
                printf(BRIGHT_RED"Cola vacía.\n"RESET);
            } else {
                printData(dato);
            }
        } else if (strcmp(command, "deq.a") == 0) {
            if (queue->front > queue->rear) {
                printf(BRIGHT_RED"No hay más registros.\n"RESET);
            }
            while (queue->front <= queue->rear) {
                struct QueueData dato = dequeue(queue);
                printData(dato);
            }
        } else if (strcmp(command, "exit") == 0) {
            break;
        } else {
            printf(BRIGHT_RED"Comando desconocido: %s\n"RESET, command);
        }
    }

    queueFree(queue);
    printf(RESET);
    return 0;
}
