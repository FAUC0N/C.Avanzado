#include <stdio.h>
#include "sensores.h"

int readTemperature() {
#ifdef PIC_CODE
    TRISBbits.TRISB0 = 1; 
#endif
    return TEMP_SENSOR_PORT; 
}

int readHumidity() {
#ifdef PIC_CODE
    TRISBbits.TRISB1 = 1; 
#endif
    return HUMIDITY_SENSOR_PORT;
}

int readAirQuality() {
#ifdef PIC_CODE
    TRISBbits.TRISB2 = 1; 
#endif
    return AIR_QUALITY_SENSOR_PORT;
}

void main() {
    int sensorValues[NUM_SENSORS];
    char* sensorNames[NUM_SENSORS] = {"Temperature", "Humidity", "Air Quality"};

    Sensor sensors[NUM_SENSORS] = {
        {readTemperature},
        {readHumidity},
        {readAirQuality}
    };

#ifndef PIC_CODE
    srand(time(0)); 
#endif

    while (1) {
        for (int i = 0; i < NUM_SENSORS; i++) {
            sensorValues[i] = sensors[i].read();
            printf("%s: %d\n", sensorNames[i], sensorValues[i]);
        }
    }
}
