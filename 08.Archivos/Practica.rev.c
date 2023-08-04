#include <stdio.h>
#include <stdlib.h>

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

void deleteList(struct Node** head) {
    struct Node* current = *head;
    struct Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}

void populateFromFile(struct Node** head, const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    struct Node* current = NULL;

    struct Data data;
    while (fread(&data, sizeof(struct Data), 1, file) == 1) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = data;
        newNode->next = NULL;

        if (*head == NULL) {
            *head = newNode;
        } else {
            current->next = newNode;
        }

        current = newNode;
    }

    fclose(file);
}

// ... Resto de las funciones (sin cambios) ...

int main() {
    struct Node* head = NULL;

    // Crear los valores de la lista
    for (int i = 0; i < SIZE; i++) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        sprintf(newNode->data.nombre, "Usuario_%02d", i+1);
        newNode->data.edad = 20 + i;
        sprintf(newNode->data.telefono, "123456789%d", i+1);
        newNode->next = head;
        head = newNode;
    }

    // Guardar los datos de la lista en el archivo .bin
    const char* filename = "C:/data.bin";
    saveToFile(head, SIZE, filename);

    // Borrar la lista
    deleteList(&head);

    // Leer el archivo .bin y guardar los datos en la estructura de datos
    populateFromFile(&head, filename);

    // Imprimir el contenido de la lista
    struct Node* current = head;
    while (current != NULL) {
        printf("Nombre: %s\n", current->data.nombre);
        printf("Edad: %d\n", current->data.edad);
        printf("Teléfono: %s\n", current->data.telefono);
        printf("\n");
        current = current->next;
    }

    deleteList(&head); // Liberar la memoria antes de salir

    return 0;
}
