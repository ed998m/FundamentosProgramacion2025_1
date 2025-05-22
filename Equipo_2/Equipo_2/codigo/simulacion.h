#ifndef SIMULACION_H
#define SIMULACION_H

void ejecutar_simulacion(float altura_inicial);

float velocidad_media(float h1, float h2, float t1, float t2);
float predecir_tiempo_restante(float altura_actual, float vmedia);

#endif