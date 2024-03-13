#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

typedef vector<vector<double>> Matriz;
typedef vector<double> Vector;

void imprimirMatriz(const Matriz& matriz);
Vector resolverSistemaJacobi(const Matriz& A, const Vector& B, int iteraciones);
double determinante(const Matriz& matriz);

int main() {
    int tamano;
    cout << "Ingrese el tamano de la matriz (maximo 5): ";
    cin >> tamano;

    if (tamano < 1 || tamano > 5) {
        cout << "Tamano no valido. Debe estar entre 1 y 5." << endl;
        return 1;
    }

    Matriz matrizA(tamano, vector<double>(tamano, 0.0));
    Vector vectorB(tamano);

    cout << "Ingrese los elementos de la matriz A:" << endl;

    for (int i = 0; i < tamano; ++i) {
        for (int j = 0; j < tamano; ++j) {
            cout << "Ingrese el elemento en la posicion [" << i + 1 << "][" << j + 1 << "]: ";
            cin >> matrizA[i][j];
        }
    }

    cout << "\nIngrese los elementos del vector B:" << endl;
    for (int i = 0; i < tamano; ++i) {
        cout << "Ingrese el elemento en la posicion [" << i + 1 << "]: ";
        cin >> vectorB[i];
    }

    cout << "\nMatriz A:" << endl;
    imprimirMatriz(matrizA);

    cout << "\nVector B:" << endl;
    for (const auto& elemento : vectorB) {
        cout << setw(10) << fixed << setprecision(2) << elemento << "\n";
    }

    if (determinante(matrizA) == 0.0) {
        cout << "\nLa matriz A no tiene inversa." << endl;
        return 1;
    }
    else {
        cout << "\nLa matriz A si tiene inversa." << endl;
    }

    int numIteraciones;
    cout << "\nIngrese la cantidad de iteraciones para el metodo de Jacobi: ";
    cin >> numIteraciones;

    Vector solucionX = resolverSistemaJacobi(matrizA, vectorB, numIteraciones);

    cout << "\nLa solucion del sistema de ecuaciones Ax = B (metodo Jacobi) es:\n";
    for (int i = 0; i < tamano; ++i) {
        cout << "x[" << i + 1 << "] = " << solucionX[i] << "\n";
    }

    return 0;
}

void imprimirMatriz(const Matriz& matriz) {
    for (const auto& fila : matriz) {
        for (const auto& elemento : fila) {
            cout << setw(10) << fixed << setprecision(2) << elemento << " ";
        }
        cout << endl;
    }
}

Vector resolverSistemaJacobi(const Matriz& A, const Vector& B, int iteraciones) {
    int tamano = A.size();
    Vector X(tamano, 0.0);  

    for (int iteracion = 0; iteracion < iteraciones; ++iteracion) {
        Vector nuevoX(tamano, 0.0);

        for (int i = 0; i < tamano; ++i) {
            double suma = 0.0;

            for (int j = 0; j < tamano; ++j) {
                if (i != j) {
                    suma += A[i][j] * X[j];
                }
            }

            nuevoX[i] = (B[i] - suma) / A[i][i];
        }

        X = nuevoX;  
    }

    return X;
}

double determinante(const Matriz& matriz) {
    int n = matriz.size();

    // Caso base: matriz 1x1
    if (n == 1) {
        return matriz[0][0];
    }

    double det = 0.0;

    for (int i = 0; i < n; ++i) {
        Matriz submatriz(n - 1, vector<double>(n - 1, 0.0));

        // Construir submatriz eliminando la fila 0 y columna i
        for (int j = 1; j < n; ++j) {
            for (int k = 0, l = 0; k < n; ++k) {
                if (k != i) {
                    submatriz[j - 1][l++] = matriz[j][k];
                }
            }
        }

        // Determinante es la suma de los cofactores
        if (i % 2 == 0) {
            det += matriz[0][i] * determinante(submatriz);
        }
        else {
            det -= matriz[0][i] * determinante(submatriz);
        }
    }

    return det;
}