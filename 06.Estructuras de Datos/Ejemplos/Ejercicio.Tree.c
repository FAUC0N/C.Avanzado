#include <stdio.h>
#include <stdlib.h>

struct Node{
    int dato;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int value){
    struct Node* newNode = (struct Node*)calloc(1, sizeof(struct Node));
    newNode->dato = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* insertValue(struct Node* node, int value){
    if(node == NULL) return createNode(value);

    if(value < node->dato){
        node->left = insertValue(node->left, value);
    }else{
        node->right = insertValue(node->right, value);
    }

    return node;
}

void printPostOrder(struct Node* node) {
    if(node == NULL) return;

    printPostOrder(node->left);
    printPostOrder(node->right);
    printf("%d ", node->dato);
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

    root = insertValue(root, 5);
    insertValue(root, 8);
    insertValue(root, 7);
    insertValue(root, 9);
    insertValue(root, 1);
    insertValue(root, 6);
    insertValue(root, 2);
    insertValue(root, 5);
    insertValue(root, 6);

    // Imprimir el árbol en post-order
    printPostOrder(root);
    printf("\n");

    // Liberar la memoria
    freeTree(root);

    return 0;
}