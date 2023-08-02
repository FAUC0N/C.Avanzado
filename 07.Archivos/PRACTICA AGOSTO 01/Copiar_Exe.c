#include <stdio.h>

int main() {
    const char *originalPath = "C:/Users/jorge/iCloudDrive/8. Code/C.Avanzado/06.Estructuras de Datos/Ejemplos/Ejercicios_HASH__Julio27/01A_Hash_Metodo_Division.exe";
    const char *copyPath = "C:/Users/jorge/iCloudDrive/8. Code/C.Avanzado/06.Estructuras de Datos/Ejemplos/Ejercicios_HASH__Julio27/01A_Hash_Metodo_Division_Copia.exe";

    FILE *originalFile = fopen(originalPath, "rb");
    FILE *copyFile = fopen(copyPath, "wb");

    if (originalFile == NULL || copyFile == NULL) {
        printf("No se pudo abrir uno de los archivos.\n");
        return 1;
    }

    int c;
    while ((c = getc(originalFile)) != EOF) {
        putc(c, copyFile);
    }

    printf("Copia completada con éxito.\n");

    fclose(originalFile);
    fclose(copyFile);

    return 0;
}
