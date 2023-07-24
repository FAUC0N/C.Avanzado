/*
 * ------------------------------------------------------------------------
 *  Programa: Arnés (SIMULADOR)
 *  Autor: JVARELA
 *  (C) INVENTSE CORP 2023
 * 
 *  Descripción: 
 *  Este programa modela un conjunto de conectores y sus respectivas terminales. 
 *  Permite crear, manipular y liberar una estructura de arnés que representa 
 *  a los conectores, terminales y sus conexiones en un arnés de cables. 
 *
 *  Historial de Revisiones:
 *      24-07-2023: Versión inicial
 * ------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
USUARIO Y PASSWORD
*/
#define USERNAME "JV"
#define PASSWORD "56364"

#define MAX_CONNECTORS 4
#define MAX_TERMINALS 8
#define MAX_CONNECTIONS 3

//#define SERIAL_COMM_CONFIG  // Para configuración de conexiones a través de comunicación serial
//#define SD_CARD_CONFIG      // Para configuración de conexiones a través de una tarjeta SD
#define SIMULATION_CONFIG   // Para generar la configuración de conexiones localmente para simulación


/// @brief Estructura que representa una conexión entre dos terminales.
///
/// Cada conexión consta de un conector y una terminal a los que está conectada.
typedef struct Connection {
    struct Connector* connector;  // Conector al que está conectado
    struct Terminal* terminal;  // Terminal a la que está conectado
} Connection;

/// @brief Estructura que representa una terminal en un conector.
///
/// Cada terminal tiene una identificación única y puede tener múltiples conexiones a otras terminales.
typedef struct Terminal {
    int id;  // ID único de la terminal
    Connection* connections[MAX_CONNECTIONS];  // Conexiones a otras terminales
} Terminal;

/// @brief Estructura que representa un conector en el arnés.
///
/// Cada conector tiene una identificación única y puede contener múltiples terminales.
typedef struct Connector {
    int id;  // ID único del conector
    Terminal* terminals[MAX_TERMINALS];  // Terminales en este conector
} Connector;

/// @brief Estructura que representa un arnés.
///
/// Un arnés consta de múltiples conectores.
typedef struct Harness {
    Connector* connectors[MAX_CONNECTORS];  // Conectores en este arnés
} Harness;

/// @brief Conecta dos terminales entre sí en ambos sentidos.
///
/// Esta función toma dos terminales, cada uno perteneciente a un conector distinto, 
/// y establece una conexión mutua entre ellos. La conexión se realiza de manera bidireccional,
/// es decir, cada terminal registra la conexión con el otro.
///
/// @param c1 Conector al que pertenece la primera terminal.
/// @param t1 Primera terminal a conectar.
/// @param c2 Conector al que pertenece la segunda terminal.
/// @param t2 Segunda terminal a conectar. 
void connectTerminals(Connector* c1, Terminal* t1, Connector* c2, Terminal* t2) {
    int i;
    // Buscar una conexión vacía en t1
    for (i = 0; i < MAX_CONNECTIONS; i++) {
        if (t1->connections[i] == NULL) {
            t1->connections[i] = malloc(sizeof(Connection));
            if (t1->connections[i] == NULL) {
                printf("Error! memory not allocated.\n");
                exit(0);
            }
            t1->connections[i]->connector = c2;
            t1->connections[i]->terminal = t2;
            break;
        } else if (t1->connections[i]->terminal == NULL) {
            t1->connections[i]->connector = c2;
            t1->connections[i]->terminal = t2;
            break;
        }
    }
    // Lo mismo para t2
    for (i = 0; i < MAX_CONNECTIONS; i++) {
        if (t2->connections[i] == NULL) {
            t2->connections[i] = malloc(sizeof(Connection));
            if (t2->connections[i] == NULL) {
                printf("Error! memory not allocated.\n");
                exit(0);
            }
            t2->connections[i]->connector = c1;
            t2->connections[i]->terminal = t1;
            break;
        } else if (t2->connections[i]->terminal == NULL) {
            t2->connections[i]->connector = c1;
            t2->connections[i]->terminal = t1;
            break;
        }
    }
}


/// @brief Crea un nuevo arnés con conectores, terminales y conexiones predefinidos.
///
/// La función crea un nuevo arnés, y para cada conector en el arnés, crea nuevas terminales. 
/// Para cada terminal, también crea nuevas conexiones. Todos los elementos creados se inicializan en cero.
/// @return Retorna un puntero al nuevo arnés creado.
Harness* createHarness() {
    // Crear el arnés
    Harness* newHarness = (Harness*)calloc(1, sizeof(Harness));

    // Crear y conectar todos los conectores y terminales
    for (int i = 0; i < MAX_CONNECTORS; i++) {
        // Crear un nuevo conector
        Connector* newConnector = (Connector*)calloc(1, sizeof(Connector));
        (*newConnector).id = i;  // Cambia i + 1 a i
        (*newHarness).connectors[i] = newConnector;
        
        // Crear las terminales para este conector
        for (int j = 0; j < MAX_TERMINALS; j++) {
            Terminal* newTerminal = (Terminal*)calloc(1, sizeof(Terminal));
            (*newTerminal).id = j;  // Cambia j + 1 a j
            (*newConnector).terminals[j] = newTerminal;

            // Crear las conexiones para esta terminal
            for (int k = 0; k < MAX_CONNECTIONS; k++) {
                (*newTerminal).connections[k] = (Connection*)calloc(1, sizeof(Connection));
            }
        }
    }

    return newHarness;
}

/// @brief Imprime las conexiones del arnés.
/// 
/// Esta función recorre todos los conectores y terminales en el arnés dado, 
/// e imprime todas las conexiones para cada terminal. 
/// El número base puede ser ajustado para imprimir con base 0 o base 1.
///
/// @param harness Es el arnés cuyas conexiones se van a imprimir. 
/// Debe ser un puntero válido a un arnés previamente inicializado.
///
/// @param base Es la base que se usará para la impresión. 
/// Si es 0, los índices de los conectores y terminales se imprimirán con base 0.
/// Si es 1, los índices de los conectores y terminales se imprimirán con base 1.
void printHarnessConnections(Harness* harness, int base) {
    for (int i = 0; i < MAX_CONNECTORS; i++) {
        for (int j = 0; j < MAX_TERMINALS; j++) {
            printf("Conector %d Terminal %d conectado a: \n", i+base, j+base);
            for (int k = 0; k < MAX_CONNECTIONS; k++) {
                if ((*(*(*harness).connectors[i]).terminals[j]).connections[k] != NULL && 
                    (*(*(*(*harness).connectors[i]).terminals[j]).connections[k]).terminal != NULL) {
                    int connectedConnectorID = (*(*(*(*harness).connectors[i]).terminals[j]).connections[k]).connector->id;
                    int connectedTerminalID = (*(*(*(*harness).connectors[i]).terminals[j]).connections[k]).terminal->id;
                    printf("    Conector %d Terminal %d\n", connectedConnectorID+base, connectedTerminalID+base);
                }
            }
        }
    }
}

/// @brief Libera la memoria ocupada por un arnés.
/// 
/// Esta función recorre todos los conectores, terminales y conexiones en el arnés dado 
/// y libera la memoria que cada uno ocupa. También libera la memoria ocupada por el propio arnés.
///
/// @param harness Es el arnés que se va a liberar. 
/// Debe ser un puntero válido a un arnés previamente inicializado. 
/// Después de llamar a esta función, harness no debe ser utilizado ya que su memoria habrá sido liberada. 
void freeHarness(Harness* harness) {
    for (int i = 0; i < MAX_CONNECTORS; i++) {
        for (int j = 0; j < MAX_TERMINALS; j++) {
            for (int k = 0; k < MAX_CONNECTIONS; k++) {
                free((*(*(*harness).connectors[i]).terminals[j]).connections[k]);
            }
            free((*(*harness).connectors[i]).terminals[j]);
        }
        free((*harness).connectors[i]);
    }
    free(harness);
}

#ifdef SERIAL_COMM_CONFIG
void getSerialConfig(Harness* harness) {
    // Este espacio estará reservado para la implementación de la configuración de conexiones via comunicación serial
}
#endif

#ifdef SD_CARD_CONFIG
void getSDCardConfig(Harness* harness) {
    // Este espacio estará reservado para la implementación de la configuración de conexiones via lectura de una SD card
}
#endif

#ifdef SIMULATION_CONFIG
void getSimulationConfig(Harness* harness) {
    // Conexiones DEMO
    // Este espacio estará reservado para la implementación de la configuración de conexiones para simular localmente

    // C1T1 a C1T8 y C2T8
    connectTerminals((*harness).connectors[0], (*(*harness).connectors[0]).terminals[0], (*harness).connectors[0], (*(*harness).connectors[0]).terminals[7]);
    connectTerminals((*harness).connectors[0], (*(*harness).connectors[0]).terminals[0], (*harness).connectors[1], (*(*harness).connectors[1]).terminals[7]);

    // C1T2 a C2T4, C2T5 y C3T1
    connectTerminals((*harness).connectors[0], (*(*harness).connectors[0]).terminals[1], (*harness).connectors[1], (*(*harness).connectors[1]).terminals[3]);
    connectTerminals((*harness).connectors[0], (*(*harness).connectors[0]).terminals[1], (*harness).connectors[1], (*(*harness).connectors[1]).terminals[4]);
    connectTerminals((*harness).connectors[0], (*(*harness).connectors[0]).terminals[1], (*harness).connectors[2], (*(*harness).connectors[2]).terminals[0]);

    // C1T3 a C3T7, C3T8 y C4T3
    connectTerminals((*harness).connectors[0], (*(*harness).connectors[0]).terminals[2], (*harness).connectors[2], (*(*harness).connectors[2]).terminals[6]);
    connectTerminals((*harness).connectors[0], (*(*harness).connectors[0]).terminals[2], (*harness).connectors[2], (*(*harness).connectors[2]).terminals[7]);
    connectTerminals((*harness).connectors[0], (*(*harness).connectors[0]).terminals[2], (*harness).connectors[3], (*(*harness).connectors[3]).terminals[2]);

    // C1T4 a C4T8
    connectTerminals((*harness).connectors[0], (*(*harness).connectors[0]).terminals[3], (*harness).connectors[3], (*(*harness).connectors[3]).terminals[7]);

    // C2T1 a C3T1, C3T2 y C4T5
    connectTerminals((*harness).connectors[1], (*(*harness).connectors[1]).terminals[0], (*harness).connectors[2], (*(*harness).connectors[2]).terminals[0]);
    connectTerminals((*harness).connectors[1], (*(*harness).connectors[1]).terminals[0], (*harness).connectors[2], (*(*harness).connectors[2]).terminals[1]);
    connectTerminals((*harness).connectors[1], (*(*harness).connectors[1]).terminals[0], (*harness).connectors[3], (*(*harness).connectors[3]).terminals[4]);
}
#endif

// Definimos el tipo de puntero a función
typedef void (*ConfigFunc)(Harness*);

// Definimos una variable para almacenar la función de configuración que vamos a usar
// Establecemos el puntero a la función de configuración que queremos usar
#ifdef SERIAL_COMM_CONFIG
ConfigFunc getConfig = &getSerialConfig;
#endif

#ifdef SD_CARD_CONFIG
ConfigFunc getConfig = &getSDCardConfig;
#endif

#ifdef SIMULATION_CONFIG
ConfigFunc getConfig = &getSimulationConfig;
#endif

// Definición de la función para validar el nombre de usuario y la contraseña
int access_granted() {
    char username[50];
    char password[50];

    // Solicitar al usuario que introduzca el nombre de usuario y la contraseña
    printf("Ingrese nombre de usuario: ");
    scanf("%s", username);
    printf("Ingrese contraseña: ");
    scanf("%s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        return 1;
    } else {
        return 0;
    }
}

/// @brief Función principal para probar la funcionalidad del arnés y sus conexiones.
///
/// Esta función crea un arnés y establece varias conexiones entre sus terminales. 
/// Luego imprime todas las conexiones en el arnés y finalmente libera la memoria que el arnés ocupa.
/// @return Retorna 0 al finalizar la ejecución exitosamente. 
int main() {

    if(!access_granted()) return -1;

    // Creamos el esqueleto del arnés.
    Harness* harness = createHarness();

    // Obtiene las configuraciones de conexión utilizando la función apuntada por getConfig.
    getConfig(harness);

    // Imprimir y liberar memoria
    printHarnessConnections(harness, 1);
    freeHarness(harness);

    return 0;
}