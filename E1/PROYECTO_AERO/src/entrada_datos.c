#include <stdio.h>
#include "entrada_datos.h"

DatosEntrada leer_datos() {
    DatosEntrada d;

    printf("Ingrese el numero NACA de 4 digitos (ej. 2412): ");
    scanf("%4s", d.tipo);

    printf("Ingrese la velocidad del aire (m/s): ");
    scanf("%f", &d.velocidad);

    printf("Ingrese la densidad del aire (kg/m^3): ");
    scanf("%f", &d.densidad);

    printf("Ingrese el angulo de ataque (grados): ");
    scanf("%f", &d.angulo_ataque);

    printf("Ingrese CD0 (resistencia parasita): ");
    scanf("%f", &d.cd0);

    printf("Ingrese eficiencia aerodinamica (e): ");
    scanf("%f", &d.e);

    printf("Ingrese la relacion de aspecto (AR): ");
    scanf("%f", &d.AR);

    return d;
}
