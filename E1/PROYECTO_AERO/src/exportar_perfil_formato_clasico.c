#include <stdio.h>
#include "estructura.h"

void exportar_perfil_clasico(Perfil perfil, const char* codigo_naca) {
    FILE* out = fopen("perfil_clasico.txt", "w");

    if (!out) {
        printf("Error al crear el archivo perfil_clasico.txt\n");
        return;
    }

    fprintf(out, "NACA %s\n", codigo_naca);

    // Parte superior (de borde de salida a borde de ataque)
    for (int i = perfil.n - 1; i >= 0; i--) {
        fprintf(out, "%.4f     %.5f     0.0000\n", perfil.x[i], perfil.y_extrado[i]);
    }

    // Parte inferior (de borde de ataque a borde de salida)
    for (int i = 1; i < perfil.n; i++) {
        fprintf(out, "%.4f     %.5f     0.0000\n", perfil.x[i], perfil.y_intrado[i]);
    }

    fclose(out);
}
