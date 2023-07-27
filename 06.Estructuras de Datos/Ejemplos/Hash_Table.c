#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HASH_SIZE 21
#define NUM_ELEMENTS 10

struct Node {
    int key;
    struct Node *next;
};

// función para crear un nuevo nodo
struct Node *newNode(int key) {
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->next = NULL;
    return node;
}

// función hash: aquí simplemente usamos el módulo del tamaño del hash
int hash(int key) {
    return key % HASH_SIZE;
}

// insertar un valor en la tabla hash
int insert(struct Node **hashTable, int key) {
    int index = hash(key);
    struct Node *node = newNode(key);
    
    // comprobar si el valor ya existe
    struct Node *temp = hashTable[index];
    while(temp) {
        if(temp->key == key) {
            return -1; // valor duplicado
        }
        temp = temp->next;
    }

    // insertar el nuevo nodo al inicio de la lista
    node->next = hashTable[index];
    hashTable[index] = node;

    return 0;
}

// buscar un valor en la tabla hash
struct Node *search(struct Node **hashTable, int key) {
    int index = hash(key);
    struct Node *node = hashTable[index];
    while(node) {
        if(node->key == key) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

// liberar la memoria
void freeHashTable(struct Node **hashTable) {
    for(int i=0; i<HASH_SIZE; i++) {
        struct Node *node = hashTable[i];
        while(node) {
            struct Node *temp = node;
            node = node->next;
            free(temp);
        }
    }
}

int main(void) {
    // inicializar tabla hash
    struct Node *hashTable[HASH_SIZE] = {NULL};

    // generar y almacenar valores aleatorios
    srand(time(0));
    int values[NUM_ELEMENTS];
    printf("Los valores generados son:\n");
    for(int i=0; i<NUM_ELEMENTS; i++) {
        values[i] = rand() % HASH_SIZE;
        printf("%d ", values[i]);
        if(insert(hashTable, values[i]) == -1) {
            printf("(Duplicado)");
        }
    }
    printf("\n");

    // buscar cada valor en la tabla hash
    printf("\nBúsqueda de los valores:\n");
    for(int i=0; i<NUM_ELEMENTS; i++) {
        struct Node *node = search(hashTable, values[i]);
        if(node) {
            printf("%d está presente en la tabla hash.\n", values[i]);
        } else {
            printf("%d no está presente en la tabla hash.\n", values[i]);
        }
    }

    // liberar la memoria
    freeHashTable(hashTable);

    return 0;
}
