#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

typedef struct{
    double radio;
} Circulo;

typedef struct{
    double lado;
} Cuadrado;

typedef struct{
    double base;
    double altura;
} Triangulo;

typedef struct{
    double ladoA;
    double ladoB;
} Rectangulo;

typedef union{
    Circulo circle;
    Cuadrado squert;
    Triangulo triangle;
    Rectangulo rectangle;
} Figura;

struct EntidadGeometrica{
    Figura figura;
    double (*area)();
    double (*perimetro)();
};

double areaCirculo(Circulo *c){
    return PI * (*c).radio * (*c).radio;
}

double perimetroCirculo(Circulo *c){
    return 2 * PI * (*c).radio;
}

double areaCuadrado(Cuadrado *s){
    return (*s).lado * (*s).lado;
}

double perimetroCuadrado(Cuadrado *s){
    return 4 * (*s).lado;
}

double areaTriangulo(Triangulo *t){
    return ((*t).base * (*t).altura)/2;
}

double perimetroTriangulo(Triangulo *t){
    return (*t).base + (*t).altura + sqrt((*t).base * (*t).base + (*t).altura * (*t).altura);
}

double areaRectangulo(Rectangulo *r){
    return (*r).ladoA * (*r).ladoB;
}

double perimetroRectangulo(Rectangulo *r){
    return (*r).ladoA * 2 + (*r).ladoB * 2;
}

struct EntidadGeometrica* crearCirculo(double radio){
    struct EntidadGeometrica *e = calloc(1, sizeof(struct EntidadGeometrica));
    (*e).figura.circle.radio = radio;
    (*e).area = (double (*)()) areaCirculo;
    (*e).perimetro = (double (*)()) perimetroCirculo;
    return e;
}

struct EntidadGeometrica* crearCuadrado(double lado){
    struct EntidadGeometrica *e = calloc(1, sizeof(struct EntidadGeometrica));
    (*e).figura.squert.lado = lado;
    (*e).area = (double (*)()) areaCuadrado;
    (*e).perimetro = (double (*)()) perimetroCuadrado;
    return e;
}

struct EntidadGeometrica* crearTriangulo(double base, double altura){
    struct EntidadGeometrica *e = calloc(1,sizeof(struct EntidadGeometrica));
    (*e).figura.triangle.base = base;
    (*e).figura.triangle.altura = altura;
    (*e).area = (double (*)()) areaTriangulo;
    (*e).perimetro = (double (*)()) perimetroTriangulo;
    return e;
}

struct EntidadGeometrica* crearRectangulo(double ladoA, double ladoB){
    struct EntidadGeometrica *e = calloc(1, sizeof(struct EntidadGeometrica));
    (*e).figura.rectangle.ladoA = ladoA;
    (*e).figura.rectangle.ladoB = ladoB;
    (*e).area = (double (*)()) areaRectangulo;
    (*e).perimetro = (double (*)()) perimetroRectangulo;
    return e;
}

int main(void){
    struct EntidadGeometrica *c = crearCirculo(15);
    struct EntidadGeometrica *s = crearCuadrado(20);
    struct EntidadGeometrica *t = crearTriangulo(15, 20);
    struct EntidadGeometrica *r = crearRectangulo(20, 30);

    printf("Dirección de c: %x\n\r", c);
    printf("Dirección de s: %x\n\r", s);
    printf("Dirección de t: %x\n\r", t);
    printf("Dirección de r: %x\n\r", r);

    printf("Circulo [Area]: %f, [Perímetro]: %f\n\r", (*c).area(&(*c).figura.circle), (*c).perimetro(&(*c).figura.circle));
    printf("Cuadrado [Area]: %f, [Perímetro]: %f\n\r", (*s).area(&(*s).figura.squert), (*s).perimetro(&(*s).figura.squert));
    printf("Triángulo [Area]: %f, [Perímetro]: %f\n\r", (*t).area((*t).figura.triangle), (*t).perimetro((*t).figura.triangle));
    printf("Rectángulo [Area]: %f, [Perímetro]: %f\n\r", (*r).area((*r).figura.rectangle), (*r).perimetro((*r).figura.rectangle));

    free(c);
    free(s);
    free(t);
    free(r);

    printf("Dirección de c: %x\n\r", c);
    printf("Dirección de s: %x\n\r", s);
    printf("Dirección de t: %x\n\r", t);
    printf("Dirección de r: %x\n\r", r);

    return 0;
}