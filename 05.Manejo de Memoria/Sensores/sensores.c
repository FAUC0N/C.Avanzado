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
