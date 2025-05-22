#include <stdio.h>
#include "entrada_datos.h"
#include "simulacion.h"
#include "atmósfera.h"
#include "interfaz.h"

int main() {
    float h_inicial = Ingresar_altura_inicial();

    // Caso especial: altitud inicial = 0 m

    if (h_inicial == 0.0f) {
        CondicionesISA condiciones = Condiciones_ISA(0.0f);
        mostrar_estado_terminal(condiciones, 0.0f, 0.0f);
        printf ("\nEl CanSat ya se encuentra en el suelo.\n");
        return 0;
    }

    ejecutar_simulacion(h_inicial);
}