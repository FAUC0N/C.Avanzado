#include <stdio.h>
#include <stdint.h>

#pragma pack(push, 1)
typedef struct {
    uint16_t signature; // Tipo de archivo, debe ser "BM" para archivos BMP
    uint32_t filesize;  // Tamaño del archivo en bytes
    uint32_t reserved;  // Reservado, debe ser 0
    uint32_t dataoffset;// Offset desde el comienzo del archivo hasta los datos de la imagen
} BMPHeader;
#pragma pack(pop)

int main() {
    FILE* file = fopen("C:\\Users\\jorge\\iCloudDrive\\8. Code\\C.Avanzado\\08.Archivos\\img.bmp", "rb");
    if (file == NULL) {
        fprintf(stderr, "No se pudo abrir el archivo.\n");
        return 1;
    }

    BMPHeader header;
    fread(&header, sizeof(BMPHeader), 1, file);

    if (header.signature != 0x4D42) { // "BM" en hexadecimal
        fprintf(stderr, "No es un archivo BMP válido.\n");
        return 1;
    }

    printf("Signature: %c%c\n", (header.signature >> 8) & 0xFF, header.signature & 0xFF);
    printf("File Size: %u bytes\n", header.filesize);
    printf("Reserved: %u\n", header.reserved);
    printf("Data Offset: %u bytes\n", header.dataoffset);

    fclose(file);

    return 0;
}
