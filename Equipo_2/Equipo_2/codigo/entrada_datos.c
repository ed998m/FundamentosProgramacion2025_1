#include <stdio.h>
#include "entrada_datos.h"

// Este es para la interacción con el usuario, es decir, lo que él definirá.

float Ingresar_altura_inicial() {
    //Aquí estoy llamando la función.
    float h = 0.0f;
    //Aquí defino la altura inicial como cero y con decimales. Tipo float

    printf("========================================\n");
    printf("  SIMULADOR DE CAIDA LIBRE DE CANSAT\n");
    printf("========================================\n");
    printf("Ingrese la altura inicial del CanSat (en metros): ");

    // Bucle while para que solo se acepten alturas positivas

    while (scanf("%f", &h) != 1 || h < 0) {
        printf("Por favor ingrese un valor valido: ");
        while (getchar() != '\n');

        //¿Para qué me sirve el getchar?
        //Es una manera segura y eficaz de evitar que scanf vuelva a leer basura del búfer
        //si el usuario cometió un error.
        //Si uso scanf, se guardarán los datos si el usuario mete letras en ligar de números, por ejemplo.
        //Y eso dificultará su lectura del siguiente scanf.
    }

    return h;
}