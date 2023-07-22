#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define USERS 10

struct Entidad{
    char Nombre[10];
    char Telefono[15];
    char Correo[25];
};

struct Medidas{
    int Edad;
    float Peso;
    float Altura;
    float (* porcentajeGrasa)(struct Medidas *);
};

// NODO => USUARIO
struct Usuario{
    struct Usuario *prev;
    struct Entidad Datos;
    struct Medidas InfoMedidas;
    struct Usuario *next;    
};

float calcularPorcentajeGrasa(struct Medidas* medidas) {
    if ((*medidas).Altura <= 0 || (*medidas).Peso <= 0) {
        printf("Error: La altura y el peso deben ser valores positivos y diferentes de cero.\n");
        return -1.0;
    }
    // Fórmula para calcular el porcentaje de grasa corporal
    // Usamos la fórmula de la "fórmula de Faulkner"
    float densidadCorporal = 1.097 - (0.00041 * (*medidas).Peso) + (0.0000099 * (*medidas).Peso * (*medidas).Peso) - (0.000755 * (*medidas).Edad);
    float porcentajeGrasa = ((4.95 / densidadCorporal) - 4.5) * 100;
    return porcentajeGrasa;
}

float GetEstatura(){
    int random = rand() % 300;
    float estatura = 1.65 + (random/1000);
    return estatura;
}

float GetPeso(){
    int random = rand() % 65000;
    float peso = 65 + (random / 1000);
    return peso;
}

void SetCorreo(struct Entidad* entidad) {
    char correo[25];
    strcpy(correo, entidad->Nombre);
    // Convertir el nombre a minúsculas
    for (int i = 0; correo[i]; i++) {
        correo[i] = tolower(correo[i]);
    }
    strcat(correo, "@inventse.com");
    strcpy((*entidad).Correo, correo);
}

void SetTelefono(struct Entidad* entidad) {
    int digitos = rand() % 10000;
    sprintf((*entidad).Telefono, "(915) 235-%04d", digitos);
}

int main(void){
    struct Usuario *usuario = (struct Usuario*)calloc(USERS, sizeof(struct Usuario));
    if(usuario == NULL){
        printf("Memoria no asignada!.");
        return -1;
    }

    srand(time(NULL));
    for(int i = 0; i < USERS; i++){
        sprintf(usuario[i].Datos.Nombre, "USER_%02d", i+1);
        SetCorreo(&usuario[i].Datos);
        SetTelefono(&usuario[i].Datos);
        usuario[i].InfoMedidas.Edad = rand() % 16 + 20;
        usuario[i].InfoMedidas.Altura = GetEstatura();
        usuario[i].InfoMedidas.Peso = GetPeso();
        usuario[i].InfoMedidas.porcentajeGrasa = calcularPorcentajeGrasa;

        if(i <USERS - 1){
            usuario[i].next = &usuario[i+1];
        }else{
            usuario[i].next = NULL;
        }

        if(i >0){
            usuario[i].prev = &usuario[i-1];
        }else{
            usuario[i].prev = NULL;
        }
    }

    struct Usuario *nodo = &usuario[0];
    while(nodo != NULL) {
        printf("Nombre: %s, Edad: %d, Altura: %.2f m, Peso: %.2f kg, Telefono: %s, Correo: %s, Porcentaje de grasa: %.2f%%\n", 
            (*nodo).Datos.Nombre, 
            (*nodo).InfoMedidas.Edad, 
            (*nodo).InfoMedidas.Altura, 
            (*nodo).InfoMedidas.Peso, 
            (*nodo).Datos.Telefono,
            (*nodo).Datos.Correo,
            (*nodo).InfoMedidas.porcentajeGrasa(&(*nodo).InfoMedidas));
            nodo = (*nodo).next;
    }

    nodo = &usuario[USERS - 1];
    while(nodo != NULL) {
        printf("Nombre: %s, Edad: %d, Altura: %.2f m, Peso: %.2f kg, Telefono: %s, Correo: %s, Porcentaje de grasa: %.2f%%\n", 
            (*nodo).Datos.Nombre, 
            (*nodo).InfoMedidas.Edad, 
            (*nodo).InfoMedidas.Altura, 
            (*nodo).InfoMedidas.Peso, 
            (*nodo).Datos.Telefono,
            (*nodo).Datos.Correo,
            (*nodo).InfoMedidas.porcentajeGrasa(&(*nodo).InfoMedidas));
            nodo = (*nodo).prev;
    }

    free(usuario);
    return 0;
}