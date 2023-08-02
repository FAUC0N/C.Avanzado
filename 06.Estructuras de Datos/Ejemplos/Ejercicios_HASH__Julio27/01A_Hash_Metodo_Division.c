#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TABLE_SIZE 10000

int HashDivision(int key, int n){
    int value;
    value = key % n;
    return value;
}

int HashKnuth(int key, int n){
    int value;
    value = (key * (key + 3)) % n;
    return value;
}

int main(void){
    srand(time(NULL));
    int tablaDivision[TABLE_SIZE];
    int tablaKnuth[TABLE_SIZE];
    int i;
    int key;
    int hash;
    int countDiv;
    int countKnuth;

    printf("----------------------\r\n");
    countDiv = 0;
    countKnuth = 0;
    memset(tablaDivision, 0, sizeof(int));
    memset(tablaKnuth, 0, sizeof(int));

    for(i = 0; i < TABLE_SIZE; i++){
        key = abs(rand());
        hash = HashDivision(key, 1000);
        if(tablaDivision[hash] != 1){
            countDiv++;
        }
        tablaDivision[hash] = 1;
    }

    for(i = 0; i < TABLE_SIZE; i++){
        key = abs(rand());
        hash = HashDivision(key, 1000);
        if(tablaDivision[hash] != 1){
            countKnuth++;
        }    
        tablaDivision[hash] = 1;
    }

    printf("Colisions: %d\n", count);
    printf("Rate: %d \\%\n", count*100/TABLE_SIZE);

    return 0;
}