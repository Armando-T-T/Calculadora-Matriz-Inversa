#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

typedef vector<vector<double>> Matriz;

void imprimirMatriz(const Matriz& matriz) {
    for (const auto& fila : matriz) {
        for (const auto& elemento : fila) {
            cout << setw(10) << fixed << setprecision(2) << elemento << " ";
        }
        cout << endl;
    }
}

Matriz matrizIdentidad(int n) {
    Matriz identidad(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i) {
        identidad[i][i] = 1.0;
    }
    return identidad;
}

Matriz multiplicarMatrices(const Matriz& matriz1, const Matriz& matriz2) {
    int filas1 = matriz1.size();
    int columnas1 = matriz1[0].size();
    int filas2 = matriz2.size();
    int columnas2 = matriz2[0].size();

    Matriz resultado(filas1, vector<double>(columnas2, 0.0));

    for (int i = 0; i < filas1; ++i) {
        for (int j = 0; j < columnas2; ++j) {
            for (int k = 0; k < columnas1; ++k) {
                resultado[i][j] += matriz1[i][k] * matriz2[k][j];
            }
        }
    }

    return resultado;
}

// Funciones para operaciones basicas de filas
void intercambiarFilas(Matriz& matriz, int fila1, int fila2) {
    swap(matriz[fila1], matriz[fila2]);
}

void multiplicarFila(Matriz& matriz, int fila, double escalar) {
    for (double& elemento : matriz[fila]) {
        elemento *= escalar;
    }
}

void sumarFilas(Matriz& matriz, int filaObjetivo, int filaFuente, double escalar) {
    for (size_t i = 0; i < matriz[0].size(); ++i) {
        matriz[filaObjetivo][i] += escalar * matriz[filaFuente][i];
    }
}

Matriz inversaGaussJordan(Matriz matriz) {
    int n = matriz.size();
    Matriz matrizInversa = matrizIdentidad(n);

    for (int i = 0; i < n; ++i) {
        // Hacer el pivote de la fila i igual a 1
        double pivote = matriz[i][i];
        multiplicarFila(matriz, i, 1 / pivote);
        multiplicarFila(matrizInversa, i, 1 / pivote);

        // Eliminacion hacia adelante
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                double factor = matriz[j][i];
                sumarFilas(matriz, j, i, -factor);
                sumarFilas(matrizInversa, j, i, -factor);
            }
        }
    }

    return matrizInversa;
}

int main() {
    int tamano;
    cout << "Ingrese el tamano de la matriz (maximo 5): ";
    cin >> tamano;

    if (tamano < 1 || tamano > 5) {
        cout << "Tamano no valido. Debe estar entre 1 y 5." << endl;
        return 1;
    }

    Matriz matriz(tamano, vector<double>(tamano, 0.0));

    cout << "Ingrese los elementos de la matriz:" << endl;

    for (int i = 0; i < tamano; ++i) {
        for (int j = 0; j < tamano; ++j) {
            cout << "Ingrese el elemento en la posicion [" << i + 1 << "][" << j + 1 << "]: ";
            cin >> matriz[i][j];
        }
    }

    cout << "\nMatriz Original:" << endl;
    imprimirMatriz(matriz);

    Matriz matrizInversa = inversaGaussJordan(matriz);

    cout << "\nMatriz Inversa:" << endl;
    imprimirMatriz(matrizInversa);

    return 0;
}