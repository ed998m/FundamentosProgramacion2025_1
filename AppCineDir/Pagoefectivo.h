#ifndef PAGOEFECTIVO_H
#define PAGOEFECTIVO_H

int PagarEfectivo(int totalventa);

// Pago en efectivo_Equipo 2
//Integrantes:
// Bianca Michelle Poot López
// Edgar Eduardo León López
// Cárolin Hernández Otero

#include <stdio.h>

int PagarEfectivo(int totalventa){
    char billete[10];
    int billeteint = 0;
    int cantidadIngresada = 0;
    int cambio = 0;
    int pagoCompleto = 0;

    printf("El total a pagar es: $%i\n", totalventa);

    while(pagoCompleto == 0){
        printf("Ingresa billete (uno por uno):\n");
        scanf("%s", billete);
        billeteint = ConvertirCharaNum(billete);  // Función ya definida en el originaaal :)

        if(billeteint > 0){
            cantidadIngresada = cantidadIngresada + billeteint;
            printf("Total ingresado: $%i\n", cantidadIngresada);

            if(cantidadIngresada < totalventa){
                printf("Faltan $%i por ingresar.\n", totalventa - cantidadIngresada);
            }
            else{
                pagoCompleto = 1;
            }
        }
        else{
            printf("Cantidad no válida. Intenta nuevamente.\n");
        }
    }

    cambio = cantidadIngresada - totalventa;
    printf("Pago realizado con éxito.\n");

    if(cambio > 0){
        printf("Su cambio es: $%i\n", cambio);
    }

    return 1;
}
#endif