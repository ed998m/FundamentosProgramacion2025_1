#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <algorithm>

using namespace std;

// Función para resolver el sistema lineal Ax = B usando eliminación gaussiana con pivoteo parcial.
vector<double> gaussElimination(vector<vector<double>> A, vector<double> B) {
    int n = B.size();
    
    // Etapa de eliminación
    for (int i = 0; i < n; i++) {
        // Pivoteo parcial: buscar el elemento máximo en columna i a partir de la fila i
        int pivot = i;
        for (int row = i + 1; row < n; row++) {
            if (fabs(A[row][i]) > fabs(A[pivot][i])) {
                pivot = row;
            }
        }
        
        // Si el pivote es cero, el sistema puede no ser solvable.
        if (fabs(A[pivot][i]) < 1e-12) {
            cerr << "El sistema no tiene solución única." << endl;
            exit(EXIT_FAILURE);
        }
        
        // Intercambiar la fila i con la fila pivot
        swap(A[i], A[pivot]);
        swap(B[i], B[pivot]);
        
        // Hacer ceros debajo del pivote
        for (int row = i + 1; row < n; row++) {
            double factor = A[row][i] / A[i][i];
            for (int col = i; col < n; col++) {
                A[row][col] -= factor * A[i][col];
            }
            B[row] -= factor * B[i];
        }
    }
    
    // Sustitución hacia atrás
    vector<double> x(n);
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < n; j++) {
            sum += A[i][j] * x[j];
        }
        x[i] = (B[i] - sum) / A[i][i];
    }
    
    return x;
}

// ANSI escape codes para colores
string colorForTemp(double norm) {
    if (norm < 0.2) return "\033[48;5;21m  \033[0m";     // Azul oscuro
    else if (norm < 0.4) return "\033[48;5;33m  \033[0m"; // Azul medio
    else if (norm < 0.6) return "\033[48;5;226m  \033[0m";// Amarillo
    else if (norm < 0.8) return "\033[48;5;202m  \033[0m";// Naranja
    else return "\033[48;5;196m  \033[0m";                // Rojo fuerte
}

// Función para dibujar mapa de calor con colores ANSI
void drawColorHeatMap(const vector<double>& T, int c) {
    double minT = *min_element(T.begin(), T.end());
    double maxT = *max_element(T.begin(), T.end());

    cout << "\nMapa de calor en colores (valores normalizados):\n";
    for (int i = 0; i < T.size(); i++) {
        double norm = (T[i] - minT) / (maxT - minT);
        cout << colorForTemp(norm);
        if ((i + 1) % c == 0) cout << "\n";
    }
}

int main() {
    // NOTA: El número de nodos debe ser n^2, siendo n un número natural.
    cout << "NOTA: el número de nodos debe ser n^2, siendo n un número natural." << endl;
    
    int n;
    cout << "Ingrese el número de nodos: ";
    cin >> n;
    
    // Calcular c, siendo c la raíz cuadrada de n.
    int c = static_cast<int>(sqrt(n));
    if (c * c != n) {
        cerr << "Error: El número ingresado no es un cuadrado perfecto." << endl;
        return 1;
    }
    
    // --- Creación de la matriz A (de tamaño n x n) ---
    vector<vector<double>> A(n, vector<double>(n, 0.0));
    
    // Diagonal principal con 4.
    for (int i = 0; i < n; i++) {
        A[i][i] = 4;
    }
    
    // Diagonales verticales: -1 (con offset de c)
    for (int i = 0; i < n - c; i++) {
        A[i][i + c] = -1;
        A[i + c][i] = -1;
    }
    
    // Vecinos horizontales: -1
    for (int i = 0; i < n - 1; i++) {
        A[i][i + 1] = -1;
        A[i + 1][i] = -1;
    }
    
    // Corregir conexiones que cruzan filas (nodos al final de una fila no deben conectarse con el comienzo de la siguiente)
    for (int i = 1; i < c; i++) {
        int row = i * c - 1;   // Último nodo de la fila
        int col = i * c;       // Primer nodo de la siguiente fila
        A[row][col] = 0;
        A[col][row] = 0;
    }
    
    // --- Lectura de las temperaturas de frontera ---
    double TN, TS, TE, TO;
    cout << "\nIngrese la temperatura (K) para el norte: ";
    cin >> TN;
    cout << "Ingrese la temperatura (K) para el sur: ";
    cin >> TS;
    cout << "Ingrese la temperatura (K) para el este: ";
    cin >> TE;
    cout << "Ingrese la temperatura (K) para el oeste: ";
    cin >> TO;
    
    // --- Construcción del vector B ---
    vector<double> B(n, 0.0);
    // Recorremos la cuadrícula de c x c (r filas y j columnas)
    for (int r = 1; r <= c; r++) {
        for (int j = 1; j <= c; j++) {
            int x = (r - 1) * c + j - 1;  // Convertir a índice 0
            if (r == 1)   B[x] += TN;  // Borde NORTE
            if (r == c)   B[x] += TS;  // Borde SUR
            if (j == 1)   B[x] += TO;  // Borde OESTE
            if (j == c)   B[x] += TE;  // Borde ESTE
        }
    }
    
    // Mostrar la matriz A.
    cout << "\nLa matriz A es:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << A[i][j] << "\t";
        }
        cout << "\n";
    }
    
    // Mostrar el vector B.
    cout << "\nEl vector B es:" << endl;
    for (int i = 0; i < n; i++) {
        cout << B[i] << "\n";
    }
    
    // --- Resolver el sistema A*T = B ---
    vector<double> T = gaussElimination(A, B);
    
    // Mostrar la solución nodo por nodo.
    cout << "\nSolución nodo por nodo:" << endl;
    for (int k = 0; k < n; k++) {
        cout << "Nodo " << k + 1 << " = " << T[k] << "\n";
    }
    
    cout << "\nLa solución T (temperaturas en cada nodo) es:" << endl;
    for (double temp : T) {
        cout << temp << "\n";
    }

    // --- Graficado en mapa de calor ---
    drawColorHeatMap(T, c);

    return 0;
}
