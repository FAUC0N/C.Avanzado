#ifndef SENSORS_H
#define SENSORS_H

#define PIC_CODE_
#ifdef PIC_CODE
    #include <xc.h>
#else
    #include <stdlib.h>
    #include <time.h>
#endif

#define NUM_SENSORS 3

#ifdef PIC_CODE
    #define TEMP_SENSOR_PORT   PORTBbits.RB0
    #define HUMIDITY_SENSOR_PORT PORTBbits.RB1
    #define AIR_QUALITY_SENSOR_PORT PORTBbits.RB2
#else
    #define TEMP_SENSOR_PORT   (rand() % 100)
    #define HUMIDITY_SENSOR_PORT (rand() % 100)
    #define AIR_QUALITY_SENSOR_PORT (rand() % 100)
#endif

int readTemperature();
int readHumidity();
int readAirQuality();

typedef struct Sensor {
    int (*read)();
} Sensor;

#endif 
