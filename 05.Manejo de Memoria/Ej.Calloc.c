/*
`calloc` es una función en C que también asigna memoria dinámica en el heap. 
El nombre 'calloc' viene de 'contiguous allocation'.

A diferencia de `malloc`, `calloc` toma dos argumentos: el número de elementos 
que se van a asignar y el tamaño de cada elemento. `calloc` luego asigna 
suficiente memoria para acomodar esa cantidad de elementos.

Otra diferencia clave es que `calloc` inicializa todos los bytes de la memoria 
asignada a cero, por lo que no contendrá basura o datos aleatorios.

Al igual que con `malloc`, la memoria asignada con `calloc` debe liberarse con 
`free` cuando ya no sea necesaria para evitar fugas de memoria.

La memoria reservada con `calloc` también está en el Heap.
*/

#include <stdio.h>
#include <stdlib.h>

typedef unsigned char byte;

void printPointer(void *ptr) {
    printf("El puntero apunta a la dirección de memoria: %x\n", ptr);
}

int main() {
    // Crear 3 bloques de memoria
    void *ptr1 = calloc(10, 1);  // Primer bloque = calloc(10, sizeof(byte))
    void *ptr2 = calloc(20, sizeof(byte));// Segundo bloque = calloc(20, 1)
    void *ptr3 = calloc(30, 1);  // Tercer bloque

    // Imprimir las direcciones de memoria
    printPointer(ptr1);
    printPointer(ptr2);
    printPointer(ptr3);

    // Liberar el segundo bloque de memoria
    free(ptr2);
    printf("Se ha liberado el segundo bloque de memoria.\n");

    // Crear otro bloque de memoria ligeramente más pequeño que el segundo
    void *ptr4 = calloc(15, sizeof(byte));
    printPointer(ptr4);
    printf("Se ha creado un nuevo bloque de memoria después de liberar el segundo bloque.\n");

    // Liberar el nuevo bloque de memoria
    free(ptr4);
    printf("Se ha liberado el nuevo bloque de memoria.\n");

    // Crear otro bloque de memoria mayor
    void *ptr5 = calloc(40, sizeof(byte));
    printPointer(ptr5);
    printf("Se ha creado un bloque de memoria mayor.\n");

    // Liberar el nuevo bloque de memoria
    free(ptr5);
    printf("Se ha liberado el nuevo bloque de memoria.\n");

    // Crear otro bloque de memoria menor
    void *ptr6 = calloc(16, sizeof(byte));
    printPointer(ptr6);
    printf("Se ha creado un bloque de memoria menor.\n");

    // Liberar el resto de los bloques de memoria
    free(ptr1);
    free(ptr3);
    free(ptr6);

    return 0;
}
