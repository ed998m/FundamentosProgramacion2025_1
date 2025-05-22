#ifndef ESTRUCTURA_H
#define ESTRUCTURA_H

#define MAX_PUNTOS 100

typedef struct {
    float x[MAX_PUNTOS];
    float y_extrado[MAX_PUNTOS];  // Parte superior del perfil
    float y_intrado[MAX_PUNTOS];  // Parte inferior del perfil
    int n;
} Perfil;

typedef struct {
    char tipo[5];
    float velocidad;
    float densidad;
    float angulo_ataque;
    float cd0;
    float e;
    float AR;
} DatosEntrada;

typedef struct {
    float cl;
    float cd;
} Resultados;

#endif
