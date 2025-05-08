//
// Created by EQUIPO1: ALDO, MATEO, ANDRES, EZEQUIEL.
//
#ifndef EQUIPO1_H
#define EQUIPO1_H
#include <stdio.h>

// Variables externas necesarias para el funcionamiento
extern int carrito[100][4];
extern int TotalProductosCarrito; // Total de productos en el carrito

//modificar la cantidad de un producto en el carrito
void ModificarCarrito(int codigo, int nuevacantidad) {
    int encontrado = 0;

    // Buscar el producto en el carrito por su código
    for (int i = 0; i < TotalProductosCarrito; i++) {
        if (carrito[i][0] == codigo) {
            carrito[i][2] = nuevacantidad;
            carrito[i][3] = carrito[i][1] * nuevacantidad;
            printf("Cantidad del producto con código %d modificada a %d.\n", codigo, nuevacantidad);
            encontrado = 1;
            break;
        }
    }
}

#endif // EQUIPO1_H