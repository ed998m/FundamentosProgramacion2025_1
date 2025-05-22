#ifndef SIMRANDOM_H
#define SIMRANDOM_H

float random_float(float min, float max);

// Genera la trama para el puerto serial, que va a ser enviado a labview
const char* generar_trama_completa(float temp, float presion, float velocidad, float altitud);

#endif
