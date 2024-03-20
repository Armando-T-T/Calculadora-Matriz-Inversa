#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

typedef vector<vector<double>> Matriz;
typedef vector<double> Vector;

void imprimirMatriz(const Matriz& matriz);
Vector resolverSistemaJacobi(const Matriz& A, const Vector& B, int iteraciones);
bool verificarDiagonalDominante(const Matriz& matriz);
double calcularError(const Vector& X_ant, const Vector& X_act, Vector& errores);

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
        cout << setw(10) << fixed << setprecision(5) << elemento << "\n";
    }

    if (!verificarDiagonalDominante(matrizA)) {
        cout << "\nLa matriz A no es estrictamente diagonal dominante." << endl;
        return 1;
    }

    int numIteraciones;
    cout << "\nIngrese la cantidad de iteraciones para el metodo de Jacobi: ";
    cin >> numIteraciones;

    Vector solucionX = resolverSistemaJacobi(matrizA, vectorB, numIteraciones);

    cout << "\nLa solucion del sistema de ecuaciones Ax = B (metodo Jacobi) es:\n";
    for (int i = 0; i < tamano; ++i) {
        cout << "x[" << i + 1 << "] = " << solucionX[i] << endl;
    }

    return 0;
}

void imprimirMatriz(const Matriz& matriz) {
    for (const auto& fila : matriz) {
        for (const auto& elemento : fila) {
            cout << setw(10) << fixed << setprecision(5) << elemento << " ";
        }
        cout << endl;
    }
}

Vector resolverSistemaJacobi(const Matriz& A, const Vector& B, int iteraciones) {
    int tamano = A.size();
    Vector X(tamano, 0.0);

    Vector X_ant(tamano, 0.0); // Vector para almacenar el valor de X en la iteración anterior

    for (int iteracion = 0; iteracion < iteraciones; ++iteracion) {
        Vector nuevoX(tamano, 0.0);
        Vector errores(tamano, 0.0);

        for (int i = 0; i < tamano; ++i) {
            double suma = 0.0;

            for (int j = 0; j < tamano; ++j) {
                if (i != j) {
                    suma += A[i][j] * X_ant[j];
                }
            }

            nuevoX[i] = (B[i] - suma) / A[i][i];
        }

        double error_total = calcularError(X, nuevoX, errores);

        cout << "Iteracion " << iteracion + 1 << ":" << endl;
        for (int i = 0; i < tamano; ++i) {
            cout << "x[" << i + 1 << "] = " << nuevoX[i] << ", Error Relativo: " << errores[i] << endl;
        }
        cout << "Error Total: " << error_total << endl << endl;

        X_ant = X; // Actualizar el valor de X para la siguiente iteración
        X = nuevoX;
    }

    return X;
}

bool verificarDiagonalDominante(const Matriz& matriz) {
    int n = matriz.size();

    for (int i = 0; i < n; ++i) {
        double sumaFilas = 0.0;
        double sumaColumnas = 0.0;

        for (int j = 0; j < n; ++j) {
            if (j != i) {
                sumaFilas += abs(matriz[i][j]);
                sumaColumnas += abs(matriz[j][i]);
            }
        }

        if (abs(matriz[i][i]) < sumaFilas || abs(matriz[i][i]) < sumaColumnas) {
            return false; // No es estrictamente diagonal dominante
        }
    }

    return true; // Es estrictamente diagonal dominante
}

double calcularError(const Vector& X_ant, const Vector& X_act, Vector& errores) {
    int tamano = X_ant.size();
    double max_error = 0.0;
    double error_total = 0.0;

    for (int i = 0; i < tamano; ++i) {
        errores[i] = abs((X_ant[i] - X_act[i]) / X_act[i]);
        error_total += errores[i];
        if (errores[i] > max_error) {
            max_error = errores[i];
        }
    }

    return error_total;
}
