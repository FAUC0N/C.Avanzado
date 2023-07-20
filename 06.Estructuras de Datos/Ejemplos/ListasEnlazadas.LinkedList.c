#include <stdio.h>
#include <stdlib.h>

// Definimos la estructura para un nodo de la lista enlazada
typedef struct nodo {
    int dato;
    struct nodo *siguiente;
} nodo;

// Función para crear un nuevo nodo
nodo* crearNodo(int dato) {
    nodo* nuevo = malloc(sizeof(nodo));
    if(nuevo == NULL) {
        printf("No hay suficiente espacio en la memoria.\n");
        exit(1);
    }
    nuevo->dato = dato;
    nuevo->siguiente = NULL;
    return nuevo;
}

// Función para añadir un nodo al final de la lista enlazada
void agregarNodo(nodo** cabecera, int dato) {
    nodo* nuevo = crearNodo(dato);
    if(*cabecera == NULL) {
        *cabecera = nuevo;
    } else {
        nodo* actual = *cabecera;
        while(actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
}

// Función para imprimir los elementos de la lista enlazada
void imprimirLista(nodo* cabecera) {
    nodo* actual = cabecera;
    while(actual != NULL) {
        printf("%d ", actual->dato);
        actual = actual->siguiente;
    }
    printf("\n");
}

// Función para liberar la memoria de la lista enlazada
void liberarLista(nodo* cabecera) {
    nodo* actual = cabecera;
    nodo* siguiente;
    while (actual != NULL) {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
}

/*
Una "Linked List" o "Lista Enlazada" es una estructura de datos lineal y dinámica. Se compone de nodos, donde cada nodo contiene un campo de datos y un enlace (referencia) al siguiente nodo en la secuencia. Esto permite una variedad de operaciones, como inserciones y eliminaciones eficientes, que se pueden realizar usando solo unas pocas modificaciones de enlaces.

Aquí están las funciones principales explicadas en nuestro código:

1. `createNode()`: Esta función se utiliza para crear un nuevo nodo. Reserva memoria dinámicamente utilizando la función `malloc()` y configura los campos de datos y next.

2. `addNodeToStart()`: Esta función se utiliza para insertar un nodo al principio de la lista enlazada. Modifica el puntero del nuevo nodo para que apunte al primer nodo de la lista, y luego cambia el puntero de la cabeza para que apunte al nuevo nodo.

3. `addNodeToEnd()`: Esta función se utiliza para insertar un nodo al final de la lista enlazada. Recorre la lista hasta encontrar el último nodo, y luego modifica el puntero del último nodo para que apunte al nuevo nodo.

4. `printLinkedList()`: Esta función se utiliza para imprimir los datos de todos los nodos de la lista enlazada. Recorre la lista y va imprimiendo el valor de los datos en cada nodo.

5. `freeLinkedList()`: Esta función se utiliza para liberar la memoria ocupada por la lista enlazada. Recorre la lista y va liberando la memoria de cada nodo utilizando la función `free()`.
*/
int main() {
    nodo* cabecera = NULL;
    agregarNodo(&cabecera, 1);
    agregarNodo(&cabecera, 2);
    agregarNodo(&cabecera, 3);
    agregarNodo(&cabecera, 4);
    imprimirLista(cabecera);
    liberarLista(cabecera);
    return 0;
}
