#include <stdio.h>
#include <ctype.h>

int main() {
    const char *path = "C:/Users/jorge/iCloudDrive/8. Code/C.Avanzado/06.Estructuras de Datos/Ejemplos/Ejercicios_HASH__Julio27/01A_Hash_Metodo_Division.exe";
    FILE *file = fopen(path, "rb");

    if (file == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    int c;
    while ((c = getc(file)) != EOF) {
        if (isprint(c)) {
            putchar(c);
        } else {
            putchar('.');
        }
    }

    fclose(file);
    return 0;
}
