#include <stdio.h>
#include <stdlib.h>

/*
En este código, cada nodo en la lista contiene un puntero al nodo anterior y al siguiente nodo en la lista, de ahí el nombre "Doblemente Enlazada".
Las funciones addNodeToStart(), printLinkedList(), y freeLinkedList() se han adaptado para trabajar con estos nodos doblemente enlazados.
La función addNodeToStart() ahora actualiza el puntero prev del antiguo nodo cabeza para apuntar al nuevo nodo.
La función freeLinkedList() no necesita ser modificada, ya que el procedimiento para liberar la memoria es el mismo.
*/

// Definición de la estructura para los nodos de la lista
typedef struct Node {
    int data;
    struct Node* next; // Apunta al siguiente nodo en la lista
    struct Node* prev; // Apunta al nodo anterior en la lista
} Node;

// Función para crear un nuevo nodo
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Función para añadir un nodo al principio de la lista
void addNodeToStart(Node** head, Node* newNode) {
    newNode->next = *head;
    if (*head != NULL) {
        (*head)->prev = newNode;
    }
    *head = newNode;
}

// Función para imprimir la lista
void printLinkedList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Función para liberar la memoria utilizada por la lista
void freeLinkedList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

/*
Las Listas Doblemente Enlazadas son una estructura de datos que consta de un conjunto de nodos secuencialmente enlazados. Cada nodo contiene datos y dos enlaces que apuntan al nodo anterior y al siguiente en la secuencia. Al tener enlaces en ambas direcciones, las listas doblemente enlazadas pueden ser recorridas tanto en sentido ascendente como descendente.

Son especialmente útiles en situaciones donde es necesario un recorrido bidireccional. Por ejemplo, en una aplicación de reproductor de música, una lista doblemente enlazada podría ser útil para implementar la funcionalidad de avanzar y retroceder entre canciones.

A continuación, se muestran algunas operaciones comunes que se pueden realizar con listas doblemente enlazadas:

1. **Inserción**: Puedes insertar un nuevo nodo al principio, en medio o al final de la lista.

2. **Eliminación**: Puedes eliminar un nodo del principio, en medio o al final de la lista.

3. **Recorrido**: Puedes recorrer la lista en ambas direcciones.

4. **Búsqueda**: Puedes buscar un elemento en la lista.

Además, la eliminación de nodos en una lista doblemente enlazada puede ser más eficiente si se proporciona un puntero al nodo que se va a eliminar, ya que no necesitamos recorrer la lista para encontrar el nodo previo.

Sin embargo, las listas doblemente enlazadas requieren más memoria para almacenar los punteros adicionales y las operaciones como la inserción y la eliminación se vuelven un poco más complejas debido a los punteros adicionales.
*/
int main() {
    Node* head = NULL;

    Node* node1 = createNode(1);
    Node* node2 = createNode(2);
    Node* node3 = createNode(3);

    addNodeToStart(&head, node1);
    addNodeToStart(&head, node2);
    addNodeToStart(&head, node3);

    printLinkedList(head);

    freeLinkedList(head);
    return 0;
}
