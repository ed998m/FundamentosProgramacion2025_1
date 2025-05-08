// pagos.h
#ifndef PAGOS_H
#define PAGOS_H

#include <stdio.h>

extern int carrito[100][4];
extern int TotalProductosCarrito;
extern int TotalProductos;
extern int productos[100][4];

#include "Pagoefectivo.h"
#include "pago_tarjeta.h"
//int PagarEfectivo(int total);
//int PagarTarjeta(int total);
void Pagar(int totalventa);


/*int PagarEfectivo(int total) {
    int monto;
    printf("\n=== PAGO EN EFECTIVO ===\n");
    printf("Total a pagar: $%d\n", total);
    printf("Ingrese el monto recibido: ");
    scanf("%d", &monto);
    
    if(monto >= total) {
        printf("Cambio: $%d\n", monto - total);
        printf("Pago realizado con éxito\n");
        return 1;
    } else {
        printf("Monto insuficiente. Faltan $%d\n", total - monto);
        return 0;
    }
}*/

/*int PagarTarjeta(int total) {
    char respuesta[2];
    printf("\n=== PAGO CON TARJETA ===\n");
    printf("Total a pagar: $%d\n", total);
    printf("¿Desea procesar el pago? (s/n): ");
    scanf("%s", respuesta);
    
    if(respuesta[0] == 's' || respuesta[0] == 'S') {
        printf("Procesando pago...\n");
        printf("Pago realizado con éxito\n");
        return 1;
    } else {
        printf("Pago cancelado\n");
        return 0;
    }
}*/

void Pagar(int totalventa) {
    char metodo[2];
    int resultado = 0;
    
    if(totalventa <= 0) {
        printf("\nNo hay productos en el carrito\n");
        return;
    }
    
    printf("\n=== TOTAL DE LA COMPRA ===\n");
    printf("Monto total: $%d\n", totalventa);
    
    do {
        printf("\nSeleccione método de pago:\n");
        printf("1. Efectivo\n");
        printf("2. Tarjeta\n");
        printf("Opción: ");
        scanf("%s", metodo);
        
        switch(metodo[0]) {
            case '1':
                resultado = PagarEfectivo(totalventa);
                break;
            case '2':
                resultado = PagarTarjeta(totalventa);
                break;
            default:
                printf("Opción no válida\n");
                resultado = 0;
        }
        
        if(!resultado) {
            printf("\nIntente nuevamente o seleccione otro método\n");
        }
        
    } while(!resultado);
    
    if(resultado) {
        for(int i = 0; i < TotalProductosCarrito; i++) {
            for(int j = 0; j < TotalProductos; j++) {
                if(carrito[i][0] == productos[j][0]) {
                    productos[j][2] -= carrito[i][2]; // Restar del inventario
                    productos[j][3] += carrito[i][2]; // Sumar a ventas
                }
            }
        }
        TotalProductosCarrito = 0;
        printf("\n¡Gracias por su compra!\n");
    }
}

#endif