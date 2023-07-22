#include <stdio.h>
#include <stdlib.h>

#define PUERTOS 256

struct Segmento{
    unsigned char Puerto;
};

struct Puerto{
    struct Puerto* prev;
    struct Segmento segemento;
    struct Puerto* next;
};

// Función para asignar un segmento de 8 bits con un orden binario aleatorio
void asignarSegmentoAleatorio(struct Segmento* segmento) {
    unsigned char valor = 0;
    for (int i = 0; i < 8; i++) {
        valor = valor << 1; // Hacer espacio para el siguiente bit
        valor |= rand() % 2; // Establecer el siguiente bit como 0 o 1 de forma aleatoria
    }
    (*segmento).Puerto = valor;
}

// Función para imprimir un número en formato binario
void imprimirBinario(unsigned char numero) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (numero >> i) & 1);
    }
    printf("\n");
}

int main(void){
    struct Puerto* p = (struct Puerto*)calloc(PUERTOS, sizeof(struct Puerto));
    if(p == NULL){
        printf("Memoria no asignada!.");
        return -1;
    }

    for(int i = 0; i < PUERTOS; i++){
        // asignarSegmentoAleatorio(&p[i].segemento);
        p[i].segemento.Puerto = i;

        if(i < (PUERTOS - 1)){
            p[i].next = &p[i+1];
        }else{
            p[i].next = NULL;
        }

        if(i > 0){
            p[i].prev = &p[i-1];
        }else{
            p[i].prev = NULL;
        }
    }

    void stop(){}

    printf("Despliegue NEXT >>>\n");
    struct Puerto *nodo = &p[0];
    while(nodo != NULL){
        imprimirBinario((*nodo).segemento.Puerto);
        nodo = (*nodo).next;
    }

    printf("Despliegue <<< PREV\n");
    nodo = &p[PUERTOS - 1];
    while(nodo != NULL){
        imprimirBinario((*nodo).segemento.Puerto);
        nodo = (*nodo).prev;
    }   

    free(p);
    return 0;
}