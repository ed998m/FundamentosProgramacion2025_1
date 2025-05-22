#include <math.h>
#include "aerodinamica.h"

Resultados calcular_coeficientes(DatosEntrada d) {
    Resultados r;
    float angulo_rad = d.angulo_ataque * M_PI / 180.0;

    r.cl = 2 * M_PI * angulo_rad;
    r.cd = d.cd0 + (powf(r.cl, 2) / (M_PI * d.e * d.AR));

    return r;
}
