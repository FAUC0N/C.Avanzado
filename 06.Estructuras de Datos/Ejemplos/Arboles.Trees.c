#include <stdio.h>
#include <stdlib.h>

// Definición de un Nodo para el Árbol
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Función para crear un nuevo nodo
Node* NewNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return(node);
}

// Función para imprimir el árbol en un recorrido en orden (izquierda, raíz, derecha)
void printInOrder(Node* node) {
    if (node == NULL)
        return;

    printInOrder(node->left);
    printf("%d ", node->data);
    printInOrder(node->right);
}

/*
Un árbol es una estructura de datos no lineal que simula una jerarquía con conjuntos de
datos en la que cada conjunto de datos está conectado con al menos un otro conjunto de datos.
Un árbol consta de nodos con una relación padre-hijo. Todos los nodos en un árbol se conectan
mediante enlaces/ramas.
Los árboles se usan para almacenar información que tiene una relación de jerarquía natural. 
Por ejemplo, un sistema de archivos en una computadora utiliza ambos, árboles
(para representar la relación de archivos o carpetas) y listas de enlaces
(para representar los archivos en una carpeta).
*/
int main() {
    // Crear la raíz
    Node *root = NewNode(1);
    root->left = NewNode(2);
    root->right = NewNode(3);
    root->left->left = NewNode(4);
    root->left->right = NewNode(5);

    printf("Recorrido en orden del árbol construido es: ");
    printInOrder(root);

    return 0;
}
