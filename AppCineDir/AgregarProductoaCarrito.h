#include <stdio.h>

// Variables del programa original
extern int productos[100][4];
extern int carrito[100][4];
extern int TotalProductos;
extern int TotalProductosCarrito;

//Funcion 
void AgregarProductoaCarrito(int codigo, int cantidad) {
    int i;
    int encontrado = 0;

    //Existencia del producto
    for (i = 0; i < TotalProductos; i++) {
        if (productos[i][0] == codigo) {
            encontrado = 1;
            break;
        }
    }
    //calculo del precio a pagar
    if (encontrado) {
        int precio = productos[i][1];
        int total = precio * cantidad;
            
    //Arreglo para agregar al carrtio 
        carrito[TotalProductosCarrito][0] = codigo;
        carrito[TotalProductosCarrito][1] = precio;
        carrito[TotalProductosCarrito][2] = cantidad;
        carrito[TotalProductosCarrito][3] = total;

        TotalProductosCarrito++;    
        printf("Producto agregado al carrito.\n");
    } else {
        printf("Código de producto no encontrado.\n");
    }
}
