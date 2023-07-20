#include <stdio.h>
#include <stdlib.h>

// Estructura base para la tarjeta
struct Tarjeta {
    void *datos;
    void (*configure)(void *datos);
    void (*setRelay)(void *datos, int puerto, int relevador, int estado);
    void (*setPort)(void *datos, int puerto, int estado);
};

// Estructuras específicas para cada tarjeta
struct TarjetaA {
    // datos específicos de la tarjeta A
};

struct TarjetaB {
    // datos específicos de la tarjeta B
};

struct TarjetaC {
    // datos específicos de la tarjeta C
};

struct TarjetaD {
    // datos específicos de la tarjeta D
};

// Funciones específicas para la tarjeta A
void configureA(struct TarjetaA *t) {
    // Implementación específica para la tarjeta A
}

void setRelayA(struct TarjetaA *t, int puerto, int relevador, int estado) {
    // Implementación específica para la tarjeta A
}

void setPortA(struct TarjetaA *t, int puerto, int estado) {
    // Implementación específica para la tarjeta A
}

// Funciones específicas para la tarjeta B, C, D...

// Funciones para crear las tarjetas
struct Tarjeta* crearTarjetaA() {
    struct Tarjeta *t = calloc(1, sizeof(struct Tarjeta));
    struct TarjetaA *a = calloc(1, sizeof(struct TarjetaA));
    // inicializar datos de a
    t->datos = a;
    t->configure = (void (*)(void*)) configureA;
    t->setRelay = (void (*)(void*, int, int, int)) setRelayA;
    t->setPort = (void (*)(void*, int, int)) setPortA;
    return t;
}

// Crear tarjeta B, C, D...

int main() {
    struct Tarjeta *t = crearTarjetaA();
    t->configure(t->datos);
    t->setRelay(t->datos, 1, 1, 1);
    t->setPort(t->datos, 1, 1);
    free(t->datos);
    free(t);
    return 0;
}
