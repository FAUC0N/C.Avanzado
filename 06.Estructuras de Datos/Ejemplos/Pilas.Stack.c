#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int items[MAX_SIZE];
    int top;
} Stack;

void createStack(Stack *s) {
    s->top = -1;
}

int isFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, int newItem) {
    if (!isFull(s)) {
        s->items[++(s->top)] = newItem;
    } else {
        printf("Stack is full\n");
    }
}

int pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->items[(s->top)--];
    } else {
        printf("Stack is empty\n");
        return -1;
    }
}

/*
Una Pila (Stack en inglés) es una estructura de datos lineal que sigue un 
orden particular en el cual las operaciones se realizan. El orden puede ser 
LIFO (Last In First Out, último en entrar, primero en salir) donde el último 
elemento insertado será el primero en ser accedido. Se trata de una lista 
ordenada o estructura que permite almacenar y recuperar datos, el modo de acceso 
a sus elementos es de tipo LIFO.
*/
int main() {
    Stack s;
    createStack(&s);
    push(&s, 1);
    push(&s, 2);
    push(&s, 3);

    printf("Top element is %d\n", pop(&s));
    printf("Top element is %d\n", pop(&s));
    printf("Top element is %d\n", pop(&s));
    printf("Top element is %d\n", pop(&s));

    return 0;
}
