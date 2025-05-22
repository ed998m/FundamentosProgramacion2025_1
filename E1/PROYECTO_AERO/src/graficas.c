#include <stdio.h>
#include "graficas.h"

void graficar_perfil(Perfil perfil, const char* naca_code, float cl, float cd) {
    FILE *f = fopen("perfil.dat", "w");
    if (!f) {
        printf("Error al crear el archivo perfil.dat\n");
        return;
    }

    // Parte superior (extradós)
    for (int i = 0; i < perfil.n; i++) {
        fprintf(f, "%f %f\n", perfil.x[i], perfil.y_extrado[i]);
    }

    // Parte inferior (intradós), en orden inverso para cerrar el perfil
    for (int i = perfil.n - 1; i >= 0; i--) {
        fprintf(f, "%f %f\n", perfil.x[i], perfil.y_intrado[i]);
    }

    fclose(f);

    FILE *gp = popen("gnuplot -persistent", "w");
    if (gp) {
        fprintf(gp,
            "set title 'Perfil NACA %s | Cl = %.3f | Cd = %.3f'\n"
            "set xlabel 'x'\n"
            "set ylabel 'y'\n"
            "set grid\n"
            "set size ratio -1\n"
            "plot 'perfil.dat' with lines title 'Perfil Aerodinamico'\n",
            naca_code, cl, cd
        );
        pclose(gp);
    } else {
        printf("No se pudo abrir Gnuplot.\n");
    }
}
