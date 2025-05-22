#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void swap_rows(double** A, double* B, int i, int j, int n) {
    double* temp_row = A[i];
    A[i] = A[j];
    A[j] = temp_row;

    double temp_b = B[i];
    B[i] = B[j];
    B[j] = temp_b;
}

double* gauss_elimination(double** A, double* B, int n) {
    for (int i = 0; i < n; i++) {
        int pivot = i;
        for (int row = i + 1; row < n; row++) {
            if (fabs(A[row][i]) > fabs(A[pivot][i])) {
                pivot = row;
            }
        }

        if (fabs(A[pivot][i]) < 1e-12) {
            printf("El sistema no tiene solución única.\n");
            exit(1);
        }

        swap_rows(A, B, i, pivot, n);

        for (int row = i + 1; row < n; row++) {
            double factor = A[row][i] / A[i][i];
            for (int col = i; col < n; col++) {
                A[row][col] -= factor * A[i][col];
            }
            B[row] -= factor * B[i];
        }
    }

    double* x = (double*)malloc(n * sizeof(double));
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < n; j++) {
            sum += A[i][j] * x[j];
        }
        x[i] = (B[i] - sum) / A[i][i];
    }

    return x;
}

void drawHeatMap(double* T, int n, int c) {
    double min = T[0], max = T[0];
    for (int i = 1; i < n; i++) {
        if (T[i] < min) min = T[i];
        if (T[i] > max) max = T[i];
    }

    printf("\nMapa de calor (aproximado):\n");
    for (int i = 0; i < n; i++) {
        double norm = (T[i] - min) / (max - min);
        if (norm < 0.2) printf("░ ");
        else if (norm < 0.4) printf("▒ ");
        else if (norm < 0.6) printf("▓ ");
        else if (norm < 0.8) printf("█ ");
        else printf("■ ");

        if ((i + 1) % c == 0) printf("\n");
    }
}

int main() {
    int n;
    printf("NOTA: el número de nodos debe ser n^2, siendo n un número natural.\n");
    printf("Ingrese el número de nodos: ");
    scanf("%d", &n);

    int c = (int)sqrt(n);
    if (c * c != n) {
        printf("Error: el número ingresado no es un cuadrado perfecto.\n");
        return 1;
    }

    // Crear matriz A
    double** A = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        A[i] = (double*)calloc(n, sizeof(double));
        A[i][i] = 4.0;
    }

    for (int i = 0; i < n - c; i++) {
        A[i][i + c] = -1.0;
        A[i + c][i] = -1.0;
    }

    for (int i = 0; i < n - 1; i++) {
        A[i][i + 1] = -1.0;
        A[i + 1][i] = -1.0;
    }

    for (int i = 1; i < c; i++) {
        int row = i * c - 1;
        int col = i * c;
        A[row][col] = 0.0;
        A[col][row] = 0.0;
    }

    double TN, TS, TE, TO;
    printf("\nIngrese la temperatura (K) para el norte: ");
    scanf("%lf", &TN);
    printf("Ingrese la temperatura (K) para el sur: ");
    scanf("%lf", &TS);
    printf("Ingrese la temperatura (K) para el este: ");
    scanf("%lf", &TE);
    printf("Ingrese la temperatura (K) para el oeste: ");
    scanf("%lf", &TO);

    double* B = (double*)calloc(n, sizeof(double));
    for (int r = 1; r <= c; r++) {
        for (int j = 1; j <= c; j++) {
            int x = (r - 1) * c + j - 1;
            if (r == 1) B[x] += TN;
            if (r == c) B[x] += TS;
            if (j == 1) B[x] += TO;
            if (j == c) B[x] += TE;
        }
    }

    printf("\nLa matriz A es:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.0lf\t", A[i][j]);
        }
        printf("\n");
    }

    printf("\nEl vector B es:\n");
    for (int i = 0; i < n; i++) {
        printf("%.2lf\n", B[i]);
    }

    double* T = gauss_elimination(A, B, n);

    printf("\nSolución nodo por nodo:\n");
    for (int i = 0; i < n; i++) {
        printf("Nodo %d = %.3lf\n", i + 1, T[i]);
    }

    drawHeatMap(T, n, c);

    // Liberar memoria
    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);
    free(B);
    free(T);

    return 0;
}
