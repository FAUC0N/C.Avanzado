#include <stdio.h>
#include <stdlib.h>

#define MAX_CONNECTORS 4
#define MAX_TERMINALS 8
#define MAX_CONNECTIONS 3

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

typedef struct Connection {
    struct Connector* connector;
    struct Terminal* terminal;
} Connection;

typedef struct Terminal {
    int id;
    Connection* connections[MAX_CONNECTIONS];
} Terminal;

typedef struct Connector {
    int id;
    Terminal* terminals[MAX_TERMINALS];
} Connector;

typedef struct Harness {
    Connector* connectors[MAX_CONNECTORS];
} Harness;

// Función para conectar dos terminales
void connectTerminals(Connector* c1, Terminal* t1, Connector* c2, Terminal* t2) {
    int i;
    // Buscar una conexión vacía en t1
    for (i = 0; i < MAX_CONNECTIONS; i++) {
        if ((*t1).connections[i]->terminal == NULL) {
            (*t1).connections[i]->connector = c2;
            (*t1).connections[i]->terminal = t2;
            break;
        }
    }
    // Lo mismo para t2
    for (i = 0; i < MAX_CONNECTIONS; i++) {
        if ((*t2).connections[i]->terminal == NULL) {
            (*t2).connections[i]->connector = c1;
            (*t2).connections[i]->terminal = t1;
            break;
        }
    }
}

Harness* createHarness() {
    // Crear el arnés
    Harness* newHarness = (Harness*)calloc(1, sizeof(Harness));

    // Crear y conectar todos los conectores y terminales
    for (int i = 0; i < MAX_CONNECTORS; i++) {
        // Crear un nuevo conector
        Connector* newConnector = (Connector*)calloc(1, sizeof(Connector));
        (*newConnector).id = i + 1;
        (*newHarness).connectors[i] = newConnector;
        
        // Crear las terminales para este conector
        for (int j = 0; j < MAX_TERMINALS; j++) {
            Terminal* newTerminal = (Terminal*)calloc(1, sizeof(Terminal));
            (*newTerminal).id = j + 1;
            (*newConnector).terminals[j] = newTerminal;

            // Crear las conexiones para esta terminal
            for (int k = 0; k < MAX_CONNECTIONS; k++) {
                (*newTerminal).connections[k] = (Connection*)calloc(1, sizeof(Connection));
            }
        }
    }

    return newHarness;
}

// Función para imprimir las conexiones del arnés
void printHarnessConnections(Harness* myHarness) {
    for (int i = 0; i < MAX_CONNECTORS; i++) {
        for (int j = 0; j < MAX_TERMINALS; j++) {
            printf("Conector %d Terminal %d conectado a: \n", i+1, j+1);
            for (int k = 0; k < MAX_CONNECTIONS; k++) {
                if ((*(*(*myHarness).connectors[i]).terminals[j]).connections[k] != NULL && 
                    (*(*(*(*myHarness).connectors[i]).terminals[j]).connections[k]).terminal != NULL) {
                    int connectedConnectorID = (*(*(*(*myHarness).connectors[i]).terminals[j]).connections[k]).connector->id;
                    int connectedTerminalID = (*(*(*(*myHarness).connectors[i]).terminals[j]).connections[k]).terminal->id;
                    printf("    Conector %d Terminal %d\n", connectedConnectorID+1, connectedTerminalID+1);
                }
            }
        }
    }
}

// Función para liberar la memoria asignada al arnés
void freeHarness(Harness* myHarness) {
    for (int i = 0; i < MAX_CONNECTORS; i++) {
        for (int j = 0; j < MAX_TERMINALS; j++) {
            for (int k = 0; k < MAX_CONNECTIONS; k++) {
                free((*(*(*myHarness).connectors[i]).terminals[j]).connections[k]);
            }
            free((*(*myHarness).connectors[i]).terminals[j]);
        }
        free((*myHarness).connectors[i]);
    }
    free(myHarness);
}

int main() {
    Harness* myHarness = createHarness();

    // C1T1 a C1T8 y C2T8
    connectTerminals((*(*myHarness).connectors[0]).terminals[0], (*(*myHarness).connectors[0]).terminals[7]);
    connectTerminals((*(*myHarness).connectors[0]).terminals[0], (*(*myHarness).connectors[1]).terminals[7]);

    // C1T2 a C2T4, C2T5 y C3T1
    connectTerminals((*(*myHarness).connectors[0]).terminals[1], (*(*myHarness).connectors[1]).terminals[3]);
    connectTerminals((*(*myHarness).connectors[0]).terminals[1], (*(*myHarness).connectors[1]).terminals[4]);
    connectTerminals((*(*myHarness).connectors[0]).terminals[1], (*(*myHarness).connectors[2]).terminals[0]);

    // C1T3 a C3T7, C3T8 y C4T3
    connectTerminals((*(*myHarness).connectors[0]).terminals[2], (*(*myHarness).connectors[2]).terminals[6]);
    connectTerminals((*(*myHarness).connectors[0]).terminals[2], (*(*myHarness).connectors[2]).terminals[7]);
    connectTerminals((*(*myHarness).connectors[0]).terminals[2], (*(*myHarness).connectors[3]).terminals[2]);

    // C1T4 a C4T8
    connectTerminals((*(*myHarness).connectors[0]).terminals[3], (*(*myHarness).connectors[3]).terminals[7]);

    // C2T1 a C3T1, C3T2 y C4T5
    connectTerminals((*(*myHarness).connectors[1]).terminals[0], (*(*myHarness).connectors[2]).terminals[0]);
    connectTerminals((*(*myHarness).connectors[1]).terminals[0], (*(*myHarness).connectors[2]).terminals[1]);
    connectTerminals((*(*myHarness).connectors[1]).terminals[0], (*(*myHarness).connectors[3]).terminals[4]);

    // Imprimir y liberar la memoria
    printHarnessConnections(myHarness);
    freeHarness(myHarness);

    return 0;
}