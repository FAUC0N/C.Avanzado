#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* left;
    struct node* right;
};

// Crea un nuevo nodo con la información dada
struct node* newNode(int data) {
    struct node* node = (struct node*) malloc(sizeof(struct node));

    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return(node);
}

/* Inserta un nodo en un árbol binario de búsqueda.
   La función retorna un nuevo nodo si el nodo padre es NULL, 
   de lo contrario retorna el nodo padre */
struct node* insert(struct node* node, int data) {
    // 1. Si el árbol está vacío, asignar un nuevo nodo dirección
    if (node == NULL) {
        return(newNode(data));
    }
    else {
        // 2. De lo contrario, recorrer el árbol
        if (data <= node->data)
            node->left = insert(node->left, data);
        else
            node->right = insert(node->right, data);

        return(node); // retornar el nodo (sin cambios)
    }
}

/* Imprime el árbol en orden (izquierda, raíz, derecha) */
void printInOrder(struct node* node) {
    if (node == NULL)
        return;

    printInOrder(node->left);
    printf("%d ", node->data);
    printInOrder(node->right);
}

/* Imprime el árbol en preorden (raíz, izquierda, derecha) */
void printPreOrder(struct node* node) {
    if (node == NULL)
        return;

    printf("%d ", node->data);
    printPreOrder(node->left);
    printPreOrder(node->right);
}

/* Imprime el árbol en postorden (izquierda, derecha, raíz) */
void printPostOrder(struct node* node) {
    if (node == NULL)
        return;

    printPostOrder(node->left);
    printPostOrder(node->right);
    printf("%d ", node->data);
}

int main() {
    struct node* root = NULL;

    root = insert(root, 5);
    insert(root, 8);
    insert(root, 7);
    insert(root, 9);
    insert(root, 1);
    insert(root, 6);
    insert(root, 2);
    insert(root, 5);
    insert(root, 6);

    printf("Impresión en orden: ");
    printInOrder(root);

    printf("\nImpresión en preorden: ");
    printPreOrder(root);

    printf("\nImpresión en postorden: ");
    printPostOrder(root);

    return 0;
}
