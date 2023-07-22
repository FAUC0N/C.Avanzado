#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

<<<<<<< HEAD
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
=======
#define USERS 15

//#define NO_LABEL

struct Info{
    char Nombre[8];
    int Edad;
    char Telefono[15];
    char Correo[25];
};

#ifdef NO_LABEL
struct Node{
    struct Node *Next;
    struct Node *Prev;

    // Declaración de una estructura anónima
    // los campos de la estructura anónima se
    // convierten en miembors directos de la
    // estructura que los contiene.
    struct Info; // No es una buena práctica
};
#else
struct Node{
    struct Info Datos;
    struct Node *Next;
    struct Node *Prev;
};
#endif

void imprimir(const char *formato, ...) {
>>>>>>> dev
    va_list args;
    va_start(args, formato);
    vprintf(formato, args);
    va_end(args);
    printf("\n");
}

<<<<<<< HEAD
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
=======
void toLCase(char *str){
    for(int i=0; str[i]; i++){
        str[i] = tolower(str[i]);
    }
}

int main(void){

    #ifdef NO_LABEL
 
        struct Node *n = (struct Node*)calloc(USERS, sizeof(struct Node));
        srand(time(NULL));
        for(int i = 0; i < USERS; i++){
            sprintf(n[i].Nombre,"USER_%02d", i+1);
            n[i].Edad = rand() % 16 + 20;
            int digitos = rand() % 10000 + 23000;
            sprintf(n[i].Telefono, "(915) %03d-%04d", digitos / 10000, digitos % 10000);
            char correo[25];
            strcpy(correo, n[i].Nombre);
            toLCase(correo);
            strcat(correo, "@inventes.com");
            sprintf(n[i].Correo, correo);
        }

        for(int i = 0; i < USERS; i++){
            imprimir("Nombre: %s de %d años con Tel: %s y correo: %s", n[i].Nombre, n[i].Edad, n[i].Telefono, n[i].Correo);
        }
 
    #else
 
        struct Node *n = (struct Node*)calloc(USERS, sizeof(struct Node));
        srand(time(NULL));
        for(int i = 0; i < USERS; i++){
            sprintf(n[i].Datos.Nombre,"USER_%02d", i+1);
            n[i].Datos.Edad = rand() % 16 + 20;
            int digitos = rand() % 10000 + 23000;
            sprintf(n[i].Datos.Telefono, "(915) %03d-%04d", digitos / 10000, digitos % 10000);
            char correo[25];
            strcpy(correo, n[i].Datos.Nombre);
            toLCase(correo);
            strcat(correo, "@inventes.com");
            sprintf(n[i].Datos.Correo, correo);
        }

        for(int i = 0; i < USERS; i++){
            imprimir("Nombre: %s de %d años con Tel: %s y correo: %s", n[i].Datos.Nombre, n[i].Datos.Edad, n[i].Datos.Telefono, n[i].Datos.Correo);
        }
 
    #endif
>>>>>>> dev

    free(n);
    return 0;
}