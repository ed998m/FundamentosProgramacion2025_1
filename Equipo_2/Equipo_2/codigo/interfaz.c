#include <stdio.h>
#include "interfaz.h"


//Lo que se mostrará en la terminal

void mostrar_estado_terminal(CondicionesISA condiciones, float velocidad, float tiempo) {

//Mando a llamar función

    int altura_terminal = (int)(condiciones.altitud / 100);
    //¿Dónde colocar al CanSat? = Altura terminal. Cada línea equivale a 100 metros.

    if (altura_terminal > 20) altura_terminal = 20;
printf("\n");
    printf("Tiempo: %.1fs | Altitud: %.2f m | Vel: %.2f m/s\n", tiempo, condiciones.altitud, velocidad);
    printf("Temp: %.3f K | Presion: %.2f Pa | Densidad: %.3f kg/m^3\n\n",

    // La cantidad de decimales que queremos que se muestren están dados por %.1 f (aquí solo un decimal).
           condiciones.temperatura, condiciones.presion, condiciones.densidad);

    for (int i = 20; i >= 0; i--) {
        if (i == altura_terminal)

            //La altura terminal es para saber dónde coloar el CanSat.
            //Si cae de 300 metros, el CanSat comenzará a caer de la tercera línea.
            //Solo se pueden dibujar hasta 21 líneas de caída.
            //Si ingresamos, por ejemplo, una altura de 30,000; considerando que cada línea=100 m,
            //Entonces el CanSat aparecerá máximo hasta la última línea (líne 20), que es el tope visual.

            printf("       [##] <-- CanSat\n");
        else
            printf("       |\n");
    }

    printf("=====================================\n");
    printf("     Nivel del mar: 0 m (referencia)\n");
    printf("=====================================\n");
}