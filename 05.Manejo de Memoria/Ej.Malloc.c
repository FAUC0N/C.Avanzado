#include <stdio.h>
#include <stdlib.h>

void printPointer(void *ptr) {
    printf("El puntero apunta a la dirección de memoria: %x\n", ptr);
}

int main() {
    // Crear 3 bloques de memoria
    void *ptr1 = malloc(10);  // Primer bloque
    void *ptr2 = malloc(20);  // Segundo bloque
    void *ptr3 = malloc(30);  // Tercer bloque

    // Imprimir las direcciones de memoria
    printPointer(ptr1);
    printPointer(ptr2);
    printPointer(ptr3);

    // Liberar el segundo bloque de memoria
    free(ptr2);
    printf("Se ha liberado el segundo bloque de memoria.\n");

    // Crear otro bloque de memoria ligeramente más pequeño que el segundo
    void *ptr4 = malloc(15);
    printPointer(ptr4);
    printf("Se ha creado un nuevo bloque de memoria después de liberar el segundo bloque.\n");

    // Liberar el nuevo bloque de memoria
    free(ptr4);
    printf("Se ha liberado el nuevo bloque de memoria.\n");

    // Crear otro bloque de memoria mayor
    void *ptr5 = malloc(40);
    printPointer(ptr5);
    printf("Se ha creado un bloque de memoria mayor.\n");

    // Liberar el nuevo bloque de memoria
    free(ptr5);
    printf("Se ha liberado el nuevo bloque de memoria.\n");

    // Crear otro bloque de memoria menor
    void *ptr6 = malloc(16);
    printPointer(ptr6);
    printf("Se ha creado un bloque de memoria menor.\n");

    // Liberar el resto de los bloques de memoria
    free(ptr1);
    free(ptr3);
    free(ptr6);

    return 0;
}
