#include <stdlib.h>

// Primero, definamos una estructura para representar un pixel.
typedef struct {
    int r, g, b;  // valores de los componentes de color Rojo, Verde, Azul.
} Pixel;

// Luego, definamos la estructura del nodo del Cuadtree.
typedef struct QuadTreeNode {
    int level;  // nivel del nodo en el árbol.
    int x, y;  // posición del nodo (pixel) en la imagen.
    int width, height;  // tamaño del nodo (region de la imagen).
    Pixel color;  // color promedio de la región que el nodo representa.
    struct QuadTreeNode* children[4];  // punteros a los hijos del nodo.
} QuadTreeNode;

// Función para crear un nuevo nodo.
QuadTreeNode* createNode(int level, int x, int y, int width, int height, Pixel color) {
    QuadTreeNode* node = (QuadTreeNode*)malloc(sizeof(QuadTreeNode));
    node->level = level;
    node->x = x;
    node->y = y;
    node->width = width;
    node->height = height;
    node->color = color;
    for(int i = 0; i < 4; i++) {
        node->children[i] = NULL;
    }
    return node;
}

// A continuación, podría implementar funciones para construir el árbol a partir de una imagen, recorrer el árbol para analizar la imagen, y liberar la memoria del árbol cuando haya terminado.
