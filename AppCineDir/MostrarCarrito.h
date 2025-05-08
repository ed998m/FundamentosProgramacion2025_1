
int MostrarCarrito() {
    int totalCompra = 0;
    int totalProductos = 0;

    printf("------ Carrito de Compras ------\n");
    printf("Código\tPrecio\tCantidad\tTotal Producto\n");
    for (int i = 0; i < TotalProductosCarrito; i++) {
        int codigo = carrito[i][0];
        int precio = carrito[i][1];
        int cantidad = carrito[i][2];
        int totalProducto = carrito[i][3];

        printf("%d\t$%d\t%d\t\t$%d\n", codigo, precio, cantidad, totalProducto);

        totalCompra += totalProducto;
        totalProductos += cantidad;
    }
    printf("---------------------------------\n");
    printf("Total de productos: %d\n", totalProductos);
    printf("Total a pagar: $%d\n", totalCompra);
    return totalCompra;
}