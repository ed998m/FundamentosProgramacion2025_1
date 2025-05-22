#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "simrandom.h"
#include <Windows.h>

#include "simulacion.h"
#include "atmósfera.h"
#include "interfaz.h"


// Este es para definir las fórmulas.

// Constantes
#define G 9.81f
#define MASA 0.7f //Masa del Cansat en kg (700 gramos)
#define AREA 0.02f // En m^2. Es el área frontal, es decir 10x20 cm
#define CD 1.73f

//Coefciente de arrastre fijo sin considerar autogiro (1.3)
//¿Y si queremos considerar autogiro y que  llegue a 18 m/s?
// El CD debe de ser igual a 1.73
//El autogiro genera algo de sustentación, pero no tanto como un ala.
//La estructura sigue siendo voluminosa y no muy aerodinámica o las palas son muy eficientes.


// Función: velocidad media
float velocidad_media(float h1, float h2, float t1, float t2) {
    if (t2 - t1 == 0) return 0;
    return (h1 - h2) / (t2 - t1);
}

// Función: estimación de tiempo restante
float predecir_tiempo_restante(float altura_actual, float vmedia) {
    if (vmedia <= 0) return -1;
    // Si la velocidad media es menor o igual a cero, no puede calcularse el tiempo retante,
    //Porque no hay velocidades negativas y en caída nunca será cero, aparte de que marcaría error.
    return altura_actual / vmedia;
}

void ejecutar_simulacion(float altura_inicial) {
    float h = altura_inicial;
    float v = 0.0f;
    float t = 0.0f;
    float dt = 0.1f;
    float desplazamiento_horizontal = 0.0f;

    srand(time(NULL));

    // === Abrir puerto serial ===
    HANDLE hSerial;
    DCB dcbSerialParams = {0};
    COMMTIMEOUTS timeouts = {0};

    hSerial = CreateFile("\\\\.\\COM1", GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hSerial == INVALID_HANDLE_VALUE) {
        printf("Error al abrir puerto\n");
        return;
    }

    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    GetCommState(hSerial, &dcbSerialParams);
    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity   = NOPARITY;
    SetCommState(hSerial, &dcbSerialParams);

    // === Simulación de caída ===
    while (h > 0) {
        CondicionesISA condiciones = Condiciones_ISA(h);

        float fuerza_drag = 0.5f * CD * condiciones.densidad * AREA * v * v;
        float aceleracion = G - (fuerza_drag / MASA);

        v += aceleracion * dt;
        h -= v * dt;
        if (h < 0) h = 0;

        float vmedia = 0.0f;
        float tiempo_restante = -1.0f;

        if (t > 0) {
            vmedia = velocidad_media(altura_inicial, h, 0, t);
            tiempo_restante = predecir_tiempo_restante(h, vmedia);
        }

        float viento = ((rand() % 5) - 2);
        desplazamiento_horizontal += viento * dt;

        mostrar_estado_terminal(condiciones, v, t);
        printf("Viento actual: %.2f m/s\n", viento);
        if (tiempo_restante >= 0)
            printf("Tiempo restante estimado: %.2f s\n", tiempo_restante);
        else
            printf("Tiempo restante estimado: --\n");

        // Conversión de unidades antes de enviar
        float temp_c = condiciones.temperatura - 273.15f;
        float pres_kpa = condiciones.presion / 1000.0f;

        const char* trama = generar_trama_completa(
            temp_c,
            pres_kpa,
            v,
            condiciones.altitud
        );

        DWORD bytesWritten;
        WriteFile(hSerial, trama, strlen(trama), &bytesWritten, NULL);
        printf("%s\n", trama);

        usleep(100000); // espera 0.1 segundos
        t += dt;
    }

    CloseHandle(hSerial);

    // Resumen
    printf("\n===============================\n");
    printf(" El CanSat ha tocado el suelo. \n");
    printf(" Tiempo total de caida: %.2f s\n", t);
    printf(" Desviacion horizontal estimada: %.2f metros\n", desplazamiento_horizontal);
    printf(" Nota: Direccion variable del tiempo (simulada)\n");
    printf("===============================\n");
}