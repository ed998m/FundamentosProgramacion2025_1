#ifndef ESTRUCTURA_H
#define ESTRUCTURA_H

typedef struct {
    float altitud;     // en metros
    float temperatura; // en Kelvin
    float presion;     // en Pascales
    float densidad;    // en kg/m^3
} CondicionesISA;

//Cajita "condiciones" con varias variables y para mandar a llamarlas donde quiera, solo uso, por ejemplo,
//Condiciones.altitud

#endif