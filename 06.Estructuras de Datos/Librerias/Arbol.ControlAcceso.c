//#include <xc.h> // include processor files
#include <stdio.h>
#include <stdlib.h> // include standard library
#include <stdbool.h>

typedef struct User {
    int id; // ID del usuario
    int pin; // PIN de acceso del usuario
} User;

typedef struct Node {
    User user; // Información del usuario
    struct Node* left; // Hijo izquierdo
    struct Node* right; // Hijo derecho
} Node;

Node* createUser(int id, int pin) {
    Node* newNode = (Node*)calloc(1, sizeof(Node));
    newNode->user.id = id;
    newNode->user.pin = pin;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insertUser(Node* node, int id, int pin) {
    // Si el árbol está vacío, asignar un nuevo nodo dirección
    if (node == NULL) return createUser(id, pin);

    // Si no está vacío, recorrer el árbol
    if (id < node->user.id)
        node->left  = insertUser(node->left, id, pin);
    else if (id > node->user.id)
        node->right = insertUser(node->right, id, pin);
    else // id es igual a node->user.id
        node->user.pin = pin; // actualizar el PIN

    return node;
}

// Función para verificar el PIN de un usuario dado
bool verifyUser(Node* root, int id, int pin) {
    // Iniciar la búsqueda desde la raíz
    Node* currentNode = root;

    // Mientras el nodo actual no sea NULL
    while(currentNode) {
        if(id == currentNode->user.id) { // Si el ID del usuario coincide
            return (pin == currentNode->user.pin); // Verificar el PIN
        }
        // Si el ID es menor, buscar en el hijo izquierdo
        if(id < currentNode->user.id) currentNode = currentNode->left;
        else currentNode = currentNode->right; // Si no, buscar en el hijo derecho
    }

    // Si no se encuentra el usuario, regresar falso
    return false;
}

void printTree(Node* node) {
    if(node == NULL) return;

    // Primero, imprimir el subárbol izquierdo
    printTree(node->left);

    // Luego, imprimir la información del usuario en el nodo actual
    printf("User ID: %d, PIN: %d\n", node->user.id, node->user.pin);

    // Finalmente, imprimir el subárbol derecho
    printTree(node->right);
}

void freeTree(Node* node) {
    if (node == NULL) return;

    // Primero, eliminar ambos subárboles
    freeTree(node->left);
    freeTree(node->right);

    // Luego, eliminar el nodo
    free(node);
}

int main() {
    // Crear un árbol vacío
    Node* root = NULL;

    // Insertar 10 usuarios
    root = insertUser(root, 1234, 1111);
    insertUser(root, 5678, 2222);
    insertUser(root, 9012, 3333);
    insertUser(root, 3456, 4444);
    insertUser(root, 7890, 5555);
    insertUser(root, 2345, 6666);
    insertUser(root, 6789, 7777);
    insertUser(root, 3456, 8888);
    insertUser(root, 7890, 9999);
    insertUser(root, 2345, 1010);

    // Solicitar ID y PIN al usuario
    int id, pin;
    printf("Por favor ingresa tu ID: ");
    scanf("%d", &id);
    printf("Por favor ingresa tu PIN: ");
    scanf("%d", &pin);

    // Verificar el usuario
    if(verifyUser(root, id, pin)) {
        printf("Acceso concedido\n");
        // Imprimir el árbol
        printTree(root);        
    } else {
        printf("Acceso denegado\n");
    }

    // Liberar la memoria al final
    freeTree(root);
    return 0;
}
