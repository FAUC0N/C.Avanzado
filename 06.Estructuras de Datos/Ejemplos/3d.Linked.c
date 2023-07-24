#include <stdio.h>
#include <stdlib.h>

#define COLUMNAS 10
#define RENGONES 10
#define CAPAS 10

struct Coordenadas{
    unsigned int X;
    unsigned int Y;
    unsigned int Z;
};

struct Nodo{
    struct Coordenadas Ubicacion;
    struct Nodo* NextCol;
    struct Nodo* PrevCol;
    struct Nodo* NextRow;
    struct Nodo* PrevRow;
    struct Nodo* NextCapa;
    struct Nodo* PrevCapa;
};

int main(void){
    // Asignar memoria para la matriz tridimensional
    struct Nodo*** matriz = (struct Nodo***)calloc(CAPAS, sizeof(struct Nodo**));
    for(int k = 0; k < CAPAS; k++){
        matriz[k] = (struct Nodo**)calloc(RENGONES, sizeof(struct Nodo*));
        for(int j = 0; j < RENGONES; j++){
            matriz[k][j] = (struct Nodo*)calloc(COLUMNAS, sizeof(struct Nodo));
        }
    }

    // Inicializar datos
    for(int z = 0; z < CAPAS; z++){
        for(int y = 0; y < RENGONES; y++){
            for(int x = 0; x < COLUMNAS; x++){
                matriz[z][y][x].Ubicacion.X = x + 1;
                matriz[z][y][x].Ubicacion.Y = y + 1;
                matriz[z][y][x].Ubicacion.Z = z + 1;

                // Establecer punteros
                matriz[z][y][x].NextCol = (x < COLUMNAS - 1) ? &matriz[z][y][x + 1] : NULL;
                matriz[z][y][x].PrevCol = (x > 0) ? &matriz[z][y][x - 1] : NULL;
                matriz[z][y][x].NextRow = (y < RENGONES - 1) ? &matriz[z][y + 1][x] : NULL;
                matriz[z][y][x].PrevRow = (y > 0) ? &matriz[z][y - 1][x] : NULL;
                matriz[z][y][x].NextCapa = (z < CAPAS - 1) ? &matriz[z + 1][y][x] : NULL;
                matriz[z][y][x].PrevCapa = (z > 0) ? &matriz[z - 1][y][x] : NULL;
            }
        }
    }

    // Imprimir las coordenadas
    for(int z = 0; z < CAPAS; z++){
        for(int y = 0; y < RENGONES; y++){
            struct Nodo* nodo = &matriz[z][y][0];
            while(nodo != NULL){
                printf("Coordenadas: X = %d, Y = %d, Z = %d\n", nodo->Ubicacion.X, nodo->Ubicacion.Y, nodo->Ubicacion.Z);
                nodo = nodo->NextCol;
            }
        }
    }

    // Liberar memoria
    for(int k = 0; k < CAPAS; k++){
        for(int j = 0; j < RENGONES; j++){
            free(matriz[k][j]);
        }
        free(matriz[k]);
    }
    free(matriz);

    return 0;
}