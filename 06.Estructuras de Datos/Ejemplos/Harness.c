/*
* En este código, estoy modelando un conjunto de conectores y sus respectivas terminales. 
* 
* 'Connector': Esta estructura representa un conector individual. Cada conector contiene un 
* arreglo de punteros a sus terminales.
*
* 'Terminal': Esta estructura representa una terminal individual. Cada terminal contiene un 
* arreglo de punteros a los conectores a los que está conectada. Esto permite representar
* las conexiones que una terminal puede tener con el mismo conector en otro puerto y/o con
* otros conectores en cualquiera de sus puertos.
*
* 'Harness': Esta estructura representa el conjunto completo de conectores y contiene un 
* arreglo de punteros a los conectores. Esta es la estructura de datos principal que vamos a usar 
* para representar y manipular el conjunto completo de conectores y sus conexiones.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_CONNECTORS 4
#define MAX_TERMINALS 8
#define MAX_CONNECTIONS 3

typedef struct Connector Connector;
typedef struct Terminal Terminal;

typedef struct Connection {
    Connector* connector;
    Terminal* terminal;
} Connection;

struct Terminal {
    int id;
    Connection* connections[MAX_CONNECTIONS];
};

struct Connector {
    int id;
    Terminal* terminals[MAX_TERMINALS];
};

typedef struct Harness {
    Connector* connectors[MAX_CONNECTORS];
} Harness;

Harness* createHarness() {
    Harness* newHarness = (Harness*)calloc(1, sizeof(Harness));

    // Crear e inicializar los conectores y las terminales
    for (int i = 0; i < MAX_CONNECTORS; i++) {
        Connector* newConnector = (Connector*)calloc(1, sizeof(Connector));
        (*newConnector).id = i + 1;
        (*newHarness).connectors[i] = newConnector;
        for (int j = 0; j < MAX_TERMINALS; j++) {
            Terminal* newTerminal = (Terminal*)calloc(1, sizeof(Terminal));
            (*newTerminal).id = j + 1;
            (*newConnector).terminals[j] = newTerminal;
            for (int k = 0; k < MAX_CONNECTIONS; k++) {
                (*newTerminal).connections[k] = (Connection*)calloc(1, sizeof(Connection));
            }
        }
    }

    // Configurar las conexiones según los requerimientos del caso de uso.
    // C1T1 a C1T8 y C2T8
    (*(*(*(*newHarness).connectors[0]).terminals[0]).connections[0]).connector = (*newHarness).connectors[0];
    (*(*(*(*newHarness).connectors[0]).terminals[0]).connections[0]).terminal = (*(*newHarness).connectors[0]).terminals[7];
    (*(*(*(*newHarness).connectors[0]).terminals[0]).connections[1]).connector = (*newHarness).connectors[1];
    (*(*(*(*newHarness).connectors[0]).terminals[0]).connections[1]).terminal = (*(*newHarness).connectors[1]).terminals[7];

    // C1T2 a C2T4, C2T5 y C3T1
    (*(*(*(*newHarness).connectors[0]).terminals[1]).connections[0]).connector = (*newHarness).connectors[1];
    (*(*(*(*newHarness).connectors[0]).terminals[1]).connections[0]).terminal = (*(*newHarness).connectors[1]).terminals[3];
    (*(*(*(*newHarness).connectors[0]).terminals[1]).connections[1]).connector = (*newHarness).connectors[1];
    (*(*(*(*newHarness).connectors[0]).terminals[1]).connections[1]).terminal = (*(*newHarness).connectors[1]).terminals[4];
    (*(*(*(*newHarness).connectors[0]).terminals[1]).connections[2]).connector = (*newHarness).connectors[2];
    (*(*(*(*newHarness).connectors[0]).terminals[1]).connections[2]).terminal = (*(*newHarness).connectors[2]).terminals[0];

    // C1T3 a C3T7, C3T8 y C4T3
    (*(*(*(*newHarness).connectors[0]).terminals[2]).connections[0]).connector = (*newHarness).connectors[2];
    (*(*(*(*newHarness).connectors[0]).terminals[2]).connections[0]).terminal = (*(*newHarness).connectors[2]).terminals[6];
    (*(*(*(*newHarness).connectors[0]).terminals[2]).connections[1]).connector = (*newHarness).connectors[2];
    (*(*(*(*newHarness).connectors[0]).terminals[2]).connections[1]).terminal = (*(*newHarness).connectors[2]).terminals[7];
    (*(*(*(*newHarness).connectors[0]).terminals[2]).connections[2]).connector = (*newHarness).connectors[3];
    (*(*(*(*newHarness).connectors[0]).terminals[2]).connections[2]).terminal = (*(*newHarness).connectors[3]).terminals[2];

    // C1T4 a C4T8
    (*(*(*(*newHarness).connectors[0]).terminals[3]).connections[0]).connector = (*newHarness).connectors[3];
    (*(*(*(*newHarness).connectors[0]).terminals[3]).connections[0]).terminal = (*(*newHarness).connectors[3]).terminals[7];

    // C2T1 a C3T1, C3T2 y C4T5
    (*(*(*(*newHarness).connectors[1]).terminals[0]).connections[0]).connector = (*newHarness).connectors[2];
    (*(*(*(*newHarness).connectors[1]).terminals[0]).connections[0]).terminal = (*(*newHarness).connectors[2]).terminals[0];
    (*(*(*(*newHarness).connectors[1]).terminals[0]).connections[1]).connector = (*newHarness).connectors[2];
    (*(*(*(*newHarness).connectors[1]).terminals[0]).connections[1]).terminal = (*(*newHarness).connectors[2]).terminals[1];
    (*(*(*(*newHarness).connectors[1]).terminals[0]).connections[2]).connector = (*newHarness).connectors[3];
    (*(*(*(*newHarness).connectors[1]).terminals[0]).connections[2]).terminal = (*(*newHarness).connectors[3]).terminals[4];

    return newHarness;
}

void printHarnessConnections(Harness* harness) {
    for (int i = 0; i < MAX_CONNECTORS; i++) {
        for (int j = 0; j < MAX_TERMINALS; j++) {
            printf("C%dT%d ", i+1, j+1);
            for (int k = 0; k < MAX_CONNECTIONS; k++) {
                Connection* connection = (*(*(*harness).connectors[i]).terminals[j]).connections[k];
                if (connection->connector != NULL) {
                    printf("> C%dT%d ", connection->connector->id, connection->terminal->id);
                }
            }
            printf("\n");
        }
    }
}

void freeHarness(Harness* harness) {
    for (int i = 0; i < MAX_CONNECTORS; i++) {
        for (int j = 0; j < MAX_TERMINALS; j++) {
            for (int k = 0; k < MAX_CONNECTIONS; k++) {
                free((*(*harness).connectors[i]).terminals[j]->connections[k]);
            }
            free((*harness).connectors[i]->terminals[j]);
        }
        free(harness->connectors[i]);
    }
    free(harness);
}

int main() {
    Harness* myHarness = createHarness();
    printHarnessConnections(myHarness);
    freeHarness(myHarness);
    return 0;
}