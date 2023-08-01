#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct Node {
    char* key;
    char* value;
    struct Node* next;
} Node;

typedef struct HashTable {
    Node* buckets[TABLE_SIZE];
} HashTable;

unsigned long hash(char* str) {
    unsigned long i = 0;
    for (int j=0; str[j]; j++)
        i += str[j];
    return i % TABLE_SIZE;
}

Node* createNode(char* key, char* value) {
    Node* newNode;
    newNode = malloc(sizeof(Node));
    newNode->key = strdup(key);
    newNode->value = strdup(value);
    newNode->next = NULL;
    return newNode;
}

void insert(HashTable* table, char* key, char* value) {
    unsigned long index = hash(key);
    Node* newNode = createNode(key, value);
    
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

HashTable* createHashTable() {
    HashTable* newTable =(HashTable*)calloc(1,sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        newTable->buckets[i] = NULL;
    }
    return newTable;
}

int main() {
    HashTable* table = createHashTable();
    insert(table, "nombre", "Emilio");
    insert(table, "ocupacion", "Estuduinate de Medicina");
    insert(table, "nombre", "Iram");
    insert(table, "ocupacion", "Estudicante de Contaduria");
    
    printf("%s es un %s.\n", fetch(table, "nombre"), fetch(table, "ocupacion"));

    return 0;
}
