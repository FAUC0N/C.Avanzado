#include <stdio.h>

int main() {
    FILE *file = fopen("C:/Users/jorge/iCloudDrive/8. Code/C.Avanzado/06.Estructuras de Datos/Ejemplos/Ejercicios_HASH__Julio27/01A_Hash_Metodo_Division.c", "r");
    if (file == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    char c;
    while ((c = getc(file)) != EOF) {
        putchar(c);
    }

    fclose(file);
    return 0;
}
