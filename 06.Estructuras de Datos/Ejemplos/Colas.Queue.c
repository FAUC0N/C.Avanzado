#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int items[MAX_SIZE];
    int front;
    int rear;
} Queue;

void createQueue(Queue *q) {
    q->front = q->rear = -1;
}

int isFull(Queue *q) {
    return q->rear == MAX_SIZE - 1;
}

int isEmpty(Queue *q) {
    return q->front == -1 || q->front > q->rear;
}

void enqueue(Queue *q, int newItem) {
    if (!isFull(q)) {
        if (isEmpty(q)) {
            q->front = 0;
        }
        q->items[++(q->rear)] = newItem;
    } else {
        printf("Queue is full\n");
    }
}

int dequeue(Queue *q) {
    if (!isEmpty(q)) {
        return q->items[(q->front)++];
    } else {
        printf("Queue is empty\n");
        return -1;
    }
}

/*
Una Cola (Queue en inglés) es una estructura de datos, caracterizada por ser 
una secuencia de elementos en la que la operación de inserción push se realiza 
por un extremo y la operación de extracción pop por el otro. También se le 
conoce como estructura FIFO (First In First Out, primero en entrar, primero en 
salir), debido a que el primer elemento en entrar será también el primero en salir.
*/
int main() {
    Queue q;
    createQueue(&q);
    enqueue(&q, 1);
    enqueue(&q, 2);
    enqueue(&q, 3);

    printf("Front element is %d\n", dequeue(&q));
    printf("Front element is %d\n", dequeue(&q));
    printf("Front element is %d\n", dequeue(&q));
    printf("Front element is %d\n", dequeue(&q));

    return 0;
}
