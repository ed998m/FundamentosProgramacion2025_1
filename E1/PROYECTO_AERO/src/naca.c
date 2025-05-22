#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "naca.h"

#ifndef PI
#define PI 3.14159265359
#endif

Perfil generar_perfil_naca(const char* naca) {
    Perfil perfil;
    perfil.n = MAX_PUNTOS;

    // Extraer valores desde el código NACA
    int m_digito = naca[0] - '0';
    int p_digito = naca[1] - '0';
    int t_digitos = atoi(naca + 2);  // últimos dos dígitos

    // Convertir a valores relativos
    float m = m_digito / 100.0f;
    float p = p_digito / 10.0f;
    float t = t_digitos / 100.0f;

    for (int i = 0; i < MAX_PUNTOS; i++) {
        float x = (float)i / (MAX_PUNTOS - 1);  // 0 a 1 distribuido uniformemente

        // Espesor simétrico
        float yt = 5.0f * t * (0.2969f * sqrtf(x) - 0.1260f * x
                            - 0.3516f * powf(x, 2) + 0.2843f * powf(x, 3)
                            - 0.1015f * powf(x, 4));

        // Línea media (camber)
        float yc = 0.0f;
        float dyc_dx = 0.0f;

        if (p != 0) {
            if (x < p) {
                yc = (m / (p * p)) * (2 * p * x - x * x);
                dyc_dx = (2 * m / (p * p)) * (p - x);
            } else {
                yc = (m / ((1 - p) * (1 - p))) * ((1 - 2 * p) + 2 * p * x - x * x);
                dyc_dx = (2 * m / ((1 - p) * (1 - p))) * (p - x);
            }
        }

        float theta = atanf(dyc_dx);  // Ángulo local del perfil

        perfil.x[i] = x;
        perfil.y_extrado[i] = yc + yt * cosf(theta);  // Parte superior
        perfil.y_intrado[i] = yc - yt * cosf(theta);  // Parte inferior
    }

    return perfil;
}
