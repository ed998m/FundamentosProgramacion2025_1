#ifndef PAGO_TARJETA_H
#define PAGO_TARJETA_H

///////////////////////////////FUNCION



int PagarTarjeta(int totalventa);

#include <stdio.h>
#include <string.h>

// Simula el pago con tarjeta. Devuelve 1 si es exitoso, 0 si no.
int PagarTarjeta(int totalventa){


  /////////////////////////////////VARIABLES
    char tarjeta[20];

    int fondos = 1500;

    printf("Ingrese número de tarjeta (16 dígitos):\n");




    scanf("%s", tarjeta);


    //////////////////////SOLICITAR TYARJETA

    if(strlen(tarjeta) != 16){
        printf("Número de tarjeta inválido. Debe tener 16 dígitos.\n");
        return 0; }

    if(totalventa > fondos)


    {
        printf("Fondos insuficientes. Tiene disponibles $%i\n", fondos);

        return 0;

        //////PAGO TARJETA
    } else {
        fondos -= totalventa;
        printf("Pago aprobado. Saldo restante: $%i\n", fondos);
        return 1;
    }



}

#endif
