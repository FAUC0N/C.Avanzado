#include <stdio.h>
#include <stdlib.h>

/*
Este ejemplo NO utiliza UNION
*/

#define PI 3.14159

// Estructura base Figura
struct Figura {
    void *datos;
    double (*area)();
    double (*perimetro)();
};

// Estructuras específicas
struct Circulo {
    double radio;
};

struct Cuadrado {
    double lado;
};

// Funciones de cálculo para el círculo
double areaCirculo(struct Circulo *c) {
    return PI * c->radio * c->radio;
}

double perimetroCirculo(struct Circulo *c) {
    return 2 * PI * c->radio;
}

// Funciones de cálculo para el cuadrado
double areaCuadrado(struct Cuadrado *c) {
    return c->lado * c->lado;
}

double perimetroCuadrado(struct Cuadrado *c) {
    return 4 * c->lado;
}

// Funciones para crear las figuras
struct Figura* crearCirculo(double radio) {
    struct Figura *f = malloc(sizeof(struct Figura));
    struct Circulo *c = malloc(sizeof(struct Circulo));
    c->radio = radio;
    f->datos = c;
    f->area = (double (*)()) areaCirculo;
    f->perimetro = (double (*)()) perimetroCirculo;
    return f;
}

struct Figura* crearCuadrado(double lado) {
    struct Figura *f = malloc(sizeof(struct Figura));
    struct Cuadrado *c = malloc(sizeof(struct Cuadrado));
    c->lado = lado;
    f->datos = c;
    f->area = (double (*)()) areaCuadrado;
    f->perimetro = (double (*)()) perimetroCuadrado;
    return f;
}

int main() {
    struct Figura *c = crearCirculo(5);
    struct Figura *q = crearCuadrado(5);

    printf("Área del círculo: %f\n", c->area(c->datos));
    printf("Perímetro del círculo: %f\n", c->perimetro(c->datos));
    printf("Área del cuadrado: %f\n", q->area(q->datos));
    printf("Perímetro del cuadrado: %f\n", q->perimetro(q->datos));

    free(c->datos);
    free(c);
    free(q->datos);
    free(q);

    return 0;
}
