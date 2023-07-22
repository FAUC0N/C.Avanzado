#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define USERS 1

struct Info{
    char Nombre[50];
    int Edad;
    char Telefono[10];
    char Correo[25];
};

struct Node{
    struct Info;
    struct Node *Next;
    struct Node *Prev;
};

void toLCase(char *str){
    for(int i=0; str[i]; i++){
        str[i] = tolower(str[i]);
    }
}

void imprimir(const char* formato, ...) {
    va_list args;
    va_start(args, formato);
    vprintf(formato, args);
    va_end(args);
    printf("\n");
}

int main(void){
    struct Node *n = (struct Node*)calloc(USERS, sizeof(struct Node));
    srand(time(NULL));
    for(int i = 0; i < USERS; i++){
        sprintf(n[i].Nombre,"USER_%02d", i+1);
        n[i].Edad = rand() % 16 + 20;
        int digitos = rand() % 10000 + 23000;
        sprintf(n[i].Telefono, "(915) %03d-%04d", digitos / 10000, digitos % 10000);
        char correo[25];
        strcat(correo, n[i].Nombre);
        toLCase(correo);
        strcat(correo, "@inventes.com");
        sprintf(n[i].Correo, correo);
    }

    for(int i = 0; i < USERS; i++){
        imprimir("Nombre: %s de %d años con Tel: %s y correo: %s", n[i].Nombre, n[i].Edad, n[i].Telefono, n[i].Correo);
    }

    free(n);
    return 0;
}