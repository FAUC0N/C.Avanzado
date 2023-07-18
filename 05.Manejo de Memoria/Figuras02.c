#include <stdio.h>
#include <stdlib.h>

/*
Este ejemplo SI utiliza UNION
*/

#define PI 3.14159

// Estructuras específicas
typedef struct {
    double radio;
} Circulo;

typedef struct {
    double lado;
} Cuadrado;

typedef union {
    Circulo circulo;
    Cuadrado cuadrado;
} DatosFigura;

// Estructura base Figura
struct Figura {
    DatosFigura datos;
    double (*area)();
    double (*perimetro)();
};

// Funciones de cálculo para el círculo
double areaCirculo(Circulo *c) {
    return PI * c->radio * c->radio;
}

double perimetroCirculo(Circulo *c) {
    return 2 * PI * c->radio;
}

// Funciones de cálculo para el cuadrado
double areaCuadrado(Cuadrado *c) {
    return c->lado * c->lado;
}

double perimetroCuadrado(Cuadrado *c) {
    return 4 * c->lado;
}

// Funciones para crear las figuras
struct Figura* crearCirculo(double radio) {
    struct Figura *f = malloc(sizeof(struct Figura));
    f->datos.circulo.radio = radio;
    f->area = (double (*)()) areaCirculo;
    f->perimetro = (double (*)()) perimetroCirculo;
    return f;
}

struct Figura* crearCuadrado(double lado) {
    struct Figura *f = malloc(sizeof(struct Figura));
    f->datos.cuadrado.lado = lado;
    f->area = (double (*)()) areaCuadrado;
    f->perimetro = (double (*)()) perimetroCuadrado;
    return f;
}

int main() {
    struct Figura *c = crearCirculo(5);
    struct Figura *q = crearCuadrado(5);

    printf("Área del círculo: %f\n", c->area(&c->datos.circulo));
    printf("Perímetro del círculo: %f\n", c->perimetro(&c->datos.circulo));
    printf("Área del cuadrado: %f\n", q->area(&q->datos.cuadrado));
    printf("Perímetro del cuadrado: %f\n", q->perimetro(&q->datos.cuadrado));

    free(c);
    free(q);

    return 0;
}
