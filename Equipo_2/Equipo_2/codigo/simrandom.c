#include <stdio.h>
#include <stdlib.h>
#include "simrandom.h"

static char trama[256];

float random_float(float min, float max) {
    return min + ((float)rand() / RAND_MAX) * (max - min);
}

// Solo simula lo que no proviene de la simulación real
const char* generar_trama_completa(float temp, float presion, float velocidad, float altitud) {
    int co2 = rand() % 1000 + 400;

    float ax = random_float(-2.0f, 2.0f);
    float ay = random_float(-2.0f, 2.0f);
    float az = random_float(-2.0f, 2.0f);

    float mx = random_float(-50.0f, 50.0f);
    float my = random_float(-50.0f, 50.0f);
    float mz = random_float(-50.0f, 50.0f);

    float gx = random_float(-180.0f, 180.0f);
    float gy = random_float(-180.0f, 180.0f);
    float gz = random_float(-180.0f, 180.0f);

    snprintf(trama, sizeof(trama),
        "A%.2fB%.2fC%.2fD%.2fE%dF%.2fG%.2fH%.2fI%.2fJ%.2fK%.2fL%.2fM%.2fN%.2fO",
        temp, presion, velocidad, altitud, co2, ax, ay, az, mx, my, mz, gx, gy, gz
    );

    return trama;
}
