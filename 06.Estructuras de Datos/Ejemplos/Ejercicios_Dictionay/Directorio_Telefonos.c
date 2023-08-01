#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    char name[50];
    char phoneNumber[20];
} Dictionary;

Dictionary dic[MAX_SIZE];
int size = 0;

void insertValue(char name[], char phoneNumber[]) {
    strcpy(dic[size].name, name);
    strcpy(dic[size].phoneNumber, phoneNumber);
    size++;
}

void searchValue(char name[]) {
    for (int i = 0; i < size; i++) {
        if (strcmp(dic[i].name, name) == 0) {
            printf("Número de teléfono para %s: %s\n", name, dic[i].phoneNumber);
            return;
        }
    }
    printf("Nombre no encontrado.\n");
}

void printDictionary(int order) {
    if (order == 1) {
        printf("Diccionario en orden ascendente:\n");
    } else if (order == -1) {
        printf("Diccionario en orden descendente:\n");
    } else {
        printf("Diccionario:\n");
    }

    for (int i = 0; i < size; i++) {
        int idx = (order == -1) ? size - i - 1 : i;
        printf("Nombre: %s, Número de teléfono: %s\n", dic[idx].name, dic[idx].phoneNumber);
    }
}

void printToCSV() {
    FILE* file = fopen("C:/Users/jorge/iCloudDrive/8. Code/C.Avanzado/06.Estructuras de Datos/Ejemplos/Ejercicios_HASH__Julio27/dictionary_phones.csv", "w");
    fprintf(file, "Name,PhoneNumber\n");

    for (int i = 0; i < size; i++) {
        fprintf(file, "%s,%s\n", dic[i].name, dic[i].phoneNumber);
    }

    fclose(file);
    printf("Los datos se han escrito en C:/dictionary.csv\n");
}

int main() {
    char choice[3];

    while (1) {
        printf("Seleccione una opción:\nI - Ingresar Valores\nS - Buscar Valores\nP - Desplegar Diccionario\nPU - Desplegar en orden ascendente\nPD - Desplegar en orden descendente\n");

        #ifdef _WIN64
        printf("PF - Imprimir CSV\n");
        #endif

        printf("Q - Salir\n");
        scanf("%2s", choice); // Leer hasta 2 caracteres
        while (getchar() != '\n'); // Limpiar el búfer

        // Declaraciones de variables fuera del switch
        char name[50], phoneNumber[15];

        if (strcmp(choice, "I") == 0) {
            if (size >= MAX_SIZE) {
                printf("Diccionario lleno.\n");
                continue;
            }
            printf("Ingrese el nombre: ");
            fgets(name, sizeof(name), stdin); // Leer hasta una nueva línea
            strtok(name, "\n"); // Eliminar el carácter de nueva línea
            printf("Ingrese el número de teléfono: ");
            fgets(phoneNumber, sizeof(phoneNumber), stdin); // Leer hasta una nueva línea
            strtok(phoneNumber, "\n"); // Eliminar el carácter de nueva línea
            insertValue(name, phoneNumber);
        } else if (strcmp(choice, "S") == 0) {
            printf("Ingrese el nombre para buscar: ");
            fgets(name, sizeof(name), stdin);
            strtok(name, "\n"); // Eliminar el carácter de nueva línea
            searchValue(name);
        } else if (strcmp(choice, "P") == 0) {
            printDictionary(0);
        } else if (strcmp(choice, "PU") == 0) {
            printDictionary(1);
        } else if (strcmp(choice, "PD") == 0) {
            printDictionary(-1);
        }
        #ifdef _WIN64
        else if (strcmp(choice, "PF") == 0) {
            printToCSV();
        }
        #endif
        else if (strcmp(choice, "Q") == 0) {
            exit(0);
        } else {
            printf("Opción inválida.\n");
        }
    }

    return 0;
}