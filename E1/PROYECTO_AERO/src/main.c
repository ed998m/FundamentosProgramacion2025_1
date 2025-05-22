#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructura.h"
#include "entrada_datos.h"
#include "naca.h"
#include "graficas.h"
#include "aerodinamica.h"
#include "exportar_perfil_formato_clasico.h"

// Función para leer y graficar un perfil desde archivo .dat
void graficar_desde_archivo(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("\n  Error: El archivo \"%s\" no fue encontrado o no se pudo abrir.\n", filename);
        printf(" Asegurate de que el archivo esté en la misma carpeta que el ejecutable.\n");
        printf(" Formato esperado: primera línea encabezado (ej. \"NACA 0010\"), seguido de coordenadas x y\n\n");
        return;
    }


    Perfil perfil;
    perfil.n = 0;

    char linea[100];
    fgets(linea, sizeof(linea), f);  // Saltar encabezado (ej. "NACA 0010")

    float x_temp[MAX_PUNTOS];
    float y_temp[MAX_PUNTOS];

    while (fgets(linea, sizeof(linea), f)) {
        float x, y;
        if (sscanf(linea, "%f %f", &x, &y) == 2) {
            x_temp[perfil.n] = x;
            y_temp[perfil.n] = y;
            perfil.n++;
            if (perfil.n >= MAX_PUNTOS) break;
        }
    }

    fclose(f);

    int mitad = perfil.n / 2;
    perfil.n = mitad;

    for (int i = 0; i < mitad; i++) {
        perfil.x[i] = x_temp[i];
        perfil.y_extrado[i] = y_temp[i];
        perfil.y_intrado[i] = y_temp[mitad + i];
    }

    graficar_perfil(perfil, "Desde archivo", 0.0f, 0.0f);
}

int main() {
    int opcion;

    printf("Seleccione una opcion:\n");
    printf("1. Analizar perfil NACA de 4 digitos\n");
    printf("2. Graficar perfil desde archivo .dat\n");
    printf("Opcion: ");
    scanf("%d", &opcion);

    if (opcion == 1) {
        DatosEntrada datos = leer_datos();
        Perfil perfil = generar_perfil_naca(datos.tipo);
        Resultados r = calcular_coeficientes(datos);

        graficar_perfil(perfil, datos.tipo, r.cl, r.cd);
        exportar_perfil_clasico(perfil, datos.tipo);

        printf("\n=== Resultados Aerodinamicos ===\n");
        printf("Cl = %.3f\n", r.cl);
        printf("Cd = %.3f\n", r.cd);

    } else if (opcion == 2) {
        char archivo[50];
        printf("Nombre del archivo .dat (incluye la extension): ");
        scanf("%s", archivo);
        graficar_desde_archivo(archivo);
    } else {
        printf("Opcion no válida.\n");
    }

    return 0;
}
