#include "atmósfera.h"

//Condiciones atmosféricas ISA de 0 a 10,000 metros

#define NUM_NIVELES_ISA 11
static const float ISA_altitud[NUM_NIVELES_ISA] = {
    0,     1000,  2000,  3000,  4000, 
    5000,  6000,  7000,  8000,  9000, 10000
};
static const float ISA_temp[NUM_NIVELES_ISA] = {
    288.15, 281.65, 275.15, 268.65, 262.15,
    255.65, 249.15, 242.65, 236.15, 229.65, 223.15
};
static const float ISA_presion[NUM_NIVELES_ISA] = {
    101325, 89876, 79498, 70112, 61660,
    54048, 47181, 41018, 35496, 30479, 25900
};
static const float ISA_densidad[NUM_NIVELES_ISA] = {
    1.225, 1.112, 1.007, 0.909, 0.819,
    0.736, 0.660, 0.590, 0.526, 0.467, 0.413
};

CondicionesISA Condiciones_ISA(float altitud_m) {
    CondicionesISA condiciones;

    if (altitud_m <= ISA_altitud[0]) {
        condiciones.temperatura = ISA_temp[0];
        condiciones.presion = ISA_presion[0];
        condiciones.densidad = ISA_densidad[0];
        condiciones.altitud = ISA_altitud[0];
        return condiciones;
    }
    if (altitud_m >= ISA_altitud[NUM_NIVELES_ISA - 1]) {
        condiciones.temperatura = ISA_temp[NUM_NIVELES_ISA - 1];
        condiciones.presion = ISA_presion[NUM_NIVELES_ISA - 1];
        condiciones.densidad = ISA_densidad[NUM_NIVELES_ISA - 1];
        condiciones.altitud = ISA_altitud[NUM_NIVELES_ISA - 1];
        return condiciones;
    }

    // Interpolación lineal

    for (int i = 0; i < NUM_NIVELES_ISA - 1; i++) {
        if (altitud_m >= ISA_altitud[i] && altitud_m < ISA_altitud[i + 1]) {
            float frac = (altitud_m - ISA_altitud[i]) / (ISA_altitud[i + 1] - ISA_altitud[i]);
            condiciones.altitud = altitud_m;
            condiciones.temperatura = ISA_temp[i] + frac * (ISA_temp[i + 1] - ISA_temp[i]);
            condiciones.presion = ISA_presion[i] + frac * (ISA_presion[i + 1] - ISA_presion[i]);
            condiciones.densidad = ISA_densidad[i] + frac * (ISA_densidad[i + 1] - ISA_densidad[i]);
            return condiciones;
        }
    }

    condiciones.altitud = altitud_m;
    condiciones.temperatura = 0;
    condiciones.presion = 0;
    condiciones.densidad = 0;
    return condiciones;
}