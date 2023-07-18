#include <stdio.h>

int v = 50;

int main(void){
    int i = 100;
    printf("El valor de v e i respectivamente es: %d, %d", v, i);

    printf("\n\r");
    printf("Ingresa el nuevo valor de v: ");
    scanf("%d", &v);
    printf("Ingresa el nuevo valor de i: ");
    scanf("%d", &i);
    printf("El valor de v e i respectivamente es: %d, %d", v, i);

    return 0;
}