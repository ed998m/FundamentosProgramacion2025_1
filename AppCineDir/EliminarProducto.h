int EliminarProducto(int codigo) {
    int encontrado = 0;
    for (int i = 0; i < TotalProductosCarrito; i++) {
        if (carrito[i][0] == codigo) {
            encontrado = 1;
            // Mover los elementos siguientes una posición hacia arriba
            for (int j = i; j < TotalProductosCarrito - 1; j++) {
                carrito[j][0] = carrito[j + 1][0];
                carrito[j][1] = carrito[j + 1][1];
                carrito[j][2] = carrito[j + 1][2];
                carrito[j][3] = carrito[j + 1][3];
            }
            TotalProductosCarrito--;
            break;
        }
    }

    if (!encontrado) {
        printf("Producto con código %d no encontrado en el carrito.\n", codigo);
    } else {
        printf("Producto eliminado. Productos restantes en el carrito: %d\n", TotalProductosCarrito);
        
        // Mostrar carrito actualizado
        printf("Carrito actualizado:\n");
        printf("Código\tPrecio\tCantidad\tTotalProducto\n");
        for (int i = 0; i < TotalProductosCarrito; i++) {
            printf("%d\t%d\t%d\t\t%d\n", 
                carrito[i][0], carrito[i][1], carrito[i][2], carrito[i][3]);
        }
    }

    return TotalProductosCarrito;
}
