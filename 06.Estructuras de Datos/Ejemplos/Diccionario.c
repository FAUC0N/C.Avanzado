#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

// Node type (a linked list node)
typedef struct Node {
    char* key;
    char* value;
    struct Node* next;
} Node;

// HashTable type
typedef struct HashTable {
    Node* buckets[TABLE_SIZE];
} HashTable;

// Hash function
unsigned long hash(char* str) {
    unsigned long i = 0;
    for (int j=0; str[j]; j++)
        i += str[j];
    return i % TABLE_SIZE;
}

// Create a key-value pair
Node* createNode(char* key, char* value) {
    Node* newNode;
    newNode = malloc(sizeof(Node));
    newNode->key = strdup(key);
    newNode->value = strdup(value);
    newNode->next = NULL;
    return newNode;
}

// Insert a key-value pair into a hash table
void insert(HashTable* table, char* key, char* value) {
    unsigned long index = hash(key);
    Node* newNode = createNode(key, value);
    
    // If the bucket is empty, insert the node directly
    if (table->buckets[index] == NULL) {
        table->buckets[index] = newNode;
    } else { // Else, find the last node and insert the new node
        Node* currentNode = table->buckets[index];
        while (currentNode->next) {
            currentNode = currentNode->next;
        }
        currentNode->next = newNode;
    }
}

// Fetch a value given a key
char* fetch(HashTable* table, char* key) {
    unsigned long index = hash(key);
    Node* node = table->buckets[index];

    if (node == NULL) {
        return NULL;
    } else {
        while (node) {
            if (strcmp(node->key, key) == 0) {
                return node->value;
            }
            node = node->next;
        }
    }
    return NULL;
}

// Create HashTable
HashTable* createHashTable() {
    HashTable* newTable = malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        newTable->buckets[i] = NULL;
    }
    return newTable;
}

/*
En C, no existe una estructura de datos incorporada llamada "Diccionario" 
como en otros lenguajes de programación como Python. Sin embargo, podemos 
emular un Diccionario utilizando una estructura de datos llamada "Tabla Hash".
Un diccionario es una colección de pares clave-valor, donde cada clave es única 
y se utiliza para encontrar el valor correspondiente. Los diccionarios son 
extremadamente útiles cuando queremos acceder a los elementos de manera eficiente, 
dado un identificador único (la clave).
*/
int main() {
    HashTable* table = createHashTable();
    insert(table, "nombre", "John");
    insert(table, "ocupacion", "programador");
    
    printf("%s es un %s.\n", fetch(table, "nombre"), fetch(table, "ocupacion")); // Prints: "John es un programador."
    return 0;
}
