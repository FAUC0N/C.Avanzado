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

void saveToFile(struct Node nodes[], int size, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        fwrite(&nodes[i].data, sizeof(struct Data), 1, file);
    }

    fclose(file);
}

void readAndPrintFromFile(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    struct Data data;

    while (fread(&data, sizeof(struct Data), 1, file) == 1) {
        printf("Nombre: %s\n", data.nombre);
        printf("Edad: %d\n", data.edad);
        printf("Teléfono: %s\n", data.telefono);
        printf("\n");
    }

    fclose(file);
}

size_t getNumberOfRecords(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error al abrir el archivo.\n");
        return 0;
    }

    fseek(file, 0, SEEK_END); // Ubica el puntero al final del archivo
    size_t size = ftell(file); // Obtiene la posición actual en bytes
    fclose(file);

    return size / sizeof(struct Data);
}

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

    const char* filename = "C:/data.bin";
    saveToFile(nodes, SIZE, filename);
    readAndPrintFromFile(filename);

    size_t numberOfRecords = getNumberOfRecords(filename);
    printf("Cantidad de registros: %zu\n", numberOfRecords);

    return 0;
}
