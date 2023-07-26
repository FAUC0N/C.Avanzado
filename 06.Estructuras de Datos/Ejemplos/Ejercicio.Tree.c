#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Found;

struct Node{
    int dato;
    struct Node* left;
    struct Node* right;
    char route[256];
};

struct Node* createNode(int value, const char* route){
    struct Node* newNode = (struct Node*)calloc(1, sizeof(struct Node));
    newNode->dato = value;
    newNode->left = newNode->right = NULL;
    strncpy(newNode->route, route, sizeof(newNode->route) - 1);
    return newNode;
}

struct Node* insertValue(struct Node* node, int value, char* route){
    if(node == NULL) return createNode(value, route);

    if(value < node->dato){
        char newRoute[256];
        snprintf(newRoute, sizeof(newRoute), "%sL", route);
        node->left = insertValue(node->left, value, newRoute);
    }else{
        char newRoute[256];
        snprintf(newRoute, sizeof(newRoute), "%sR", route);
        node->right = insertValue(node->right, value, newRoute);
    }

    return node;
}

void printInOrder(struct Node* node) {
    if(node == NULL) return;

    printInOrder(node->left);
    printf("%d ", node->dato);
    printInOrder(node->right);
}

void printPreOrder(struct Node* node) {
    if(node == NULL) return;

    printf("%d ", node->dato);
    printPreOrder(node->left);
    printPreOrder(node->right);
}

void printPostOrder(struct Node* node) {
    if(node == NULL) return;

    printPostOrder(node->left);
    printPostOrder(node->right);
    printf("%d ", node->dato);
}

void searchAndPrint(struct Node* root, int value) {
    if(root == NULL) return;

    if(root->dato == value) {
        Found = 1;
        printf("Nodo: %d, Ruta: %s\n", root->dato, root->route);
    }

    searchAndPrint(root->left, value);
    searchAndPrint(root->right, value);
}

void searchNode(struct Node* root, int value) {
    Found = 0;
    searchAndPrint(root, value);
    if(!Found)
        printf("El nodo con el valor %d, no existe en el árbol", value);
}


void freeTree(struct Node* node) {
    if (node == NULL) return;

    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

int main(void){
    // Crear un árbol vacío
    struct Node* root = NULL;

    root = insertValue(root, 5, "Root");
    insertValue(root, 8, "Root");
    insertValue(root, 7, "Root");
    insertValue(root, 9, "Root");
    insertValue(root, 1, "Root");
    insertValue(root, 6, "Root");
    insertValue(root, 2, "Root");
    insertValue(root, 5, "Root");
    insertValue(root, 6, "Root");

    printf("Impresión In-Order\n");
    printInOrder(root);
    printf("\nImpresión Post-Order\n");
    printPostOrder(root);
    printf("\nImpresión Pre-Order\n");
    printPostOrder(root);
    printf("\n");

    // agregué algunas porpiedades, tan solo como ejercicio para validar la ruta de nodo
    searchNode(root, 9);
    searchNode(root, 6);
    searchNode(root, 2);
    searchNode(root, 10);

    // Liberar la memoria
    freeTree(root);

    return 0;
}
