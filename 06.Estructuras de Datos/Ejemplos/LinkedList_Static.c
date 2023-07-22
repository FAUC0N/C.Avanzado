#include <stdio.h>

#define SIZE 10

struct Data {
    char nombre[100];
    int edad;
    char telefono[15];
};

struct Node {
    struct Data data;
    struct Node* next;
};

int main() {
    struct Node nodes[SIZE];

    for (int i = 0; i < SIZE; i++) {
        sprintf(nodes[i].data.nombre, "Usuario_%02d", i+1);
        nodes[i].data.edad = 20 + i;
        sprintf(nodes[i].data.telefono, "123456789%d", i+1);

        if (i < SIZE - 1) {
            nodes[i].next = &nodes[i+1];
        } else {
            nodes[i].next = NULL;
        }
    }

    struct Node* currentNode = &nodes[0];
    while (currentNode != NULL) {
        printf("Nombre: %s\n", (*currentNode).data.nombre);
        printf("Edad: %d\n", (*currentNode).data.edad);
        printf("Teléfono: %s\n", (*currentNode).data.telefono);
        printf("\n");

        currentNode = (*currentNode).next;
    }

    return 0;
}
