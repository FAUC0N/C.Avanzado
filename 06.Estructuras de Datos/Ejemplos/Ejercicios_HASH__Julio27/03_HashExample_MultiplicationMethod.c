#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define TABLE_SIZE 1000
#define A 0.6180339887 // Constante a usar en el hash de multiplicación

typedef struct HashNode {
    int key;
    int value;
    struct HashNode* next;
} HashNode;

unsigned int multiplicationHash(int key) {
    return floor(TABLE_SIZE * fmod((key * A), 1.0));
}

HashNode* createNode(int key, int value) {
    HashNode* node = (HashNode*)malloc(sizeof(HashNode));
    node->key = key;
    node->value = value;
    node->next = NULL;
    return node;
}

void insert(HashNode** hashTable, int key, int value) {
    int index = multiplicationHash(key);
    HashNode* newNode = createNode(key, value);
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

void printHashTable(HashNode** hashTable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index %d: ", i);
        HashNode* current = hashTable[i];
        while (current != NULL) {
            printf("(%d, %d) -> ", current->key, current->value);
            current = current->next;
        }
        printf("NULL\n");
    }
}

#ifdef _WIN64
void printHashTableToCSV(HashNode** hashTable, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file != NULL) {
        fprintf(file, "Index,Key,Value\n"); // Encabezados de columna

        for (int i = 0; i < TABLE_SIZE; i++) {
            HashNode* current = hashTable[i];
            while (current != NULL) {
                fprintf(file, "%d,%d,%d\n", i, current->key, current->value);
                current = current->next;
            }
        }

        fclose(file);
        printf("Los datos se han escrito en %s\n", filename);
    } else {
        perror("No se pudo abrir el archivo");
    }
}
#endif

int main() {
    HashNode* hashTable[TABLE_SIZE] = {NULL};

    // Sembrar la función aleatoria
    srand(time(NULL));

    // Insertar 1000 valores aleatorios en el rango de 0 a 9999
    for (int i = 0; i < 1000; i++) {
        int key = rand() % 1000;
        int value = rand() % 100000;
        insert(hashTable, key, value);
    }

    printHashTable(hashTable);

#ifdef _WIN64
    printHashTableToCSV(hashTable, "C:/Users/jorge/iCloudDrive/8. Code/C.Avanzado/06.Estructuras de Datos/Ejemplos/Ejercicios_HASH__Julio27/hash_multiplication_table.csv");
#endif

    return 0;
}
