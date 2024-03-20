#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

typedef vector<vector<double>> Matriz;
typedef vector<double> Vector;

void imprimirMatriz(const Matriz& matriz);
void imprimirVector(const Vector& vector);
bool verificarDiagonalDominante(const Matriz& matriz);
Vector resolverSistemaGaussSeidel(const Matriz& matrizA, const Vector& vectorB, int iteraciones);
Vector resolverSistemaJacobi(const Matriz& A, const Vector& B, int iteraciones);
double calcularError(const Vector& X_ant, const Vector& X_act);

int main() {
    int tamano;
    cout << "Ingrese el tamano de la matriz (maximo 5): ";
    cin >> tamano;

    if (tamano < 1 || tamano > 5) {
        cout << "Tamano no valido. Debe estar entre 1 y 5." << endl;
        return 1;
    }

    Matriz matrizA(tamano, vector<double>(tamano, 0.0));

    cout << "Ingrese los elementos de la matriz A:" << endl;

    for (int i = 0; i < tamano; ++i) {
        for (int j = 0; j < tamano; ++j) {
            cout << "Ingrese el elemento en la posicion [" << i + 1 << "][" << j + 1 << "]: ";
            cin >> matrizA[i][j];
        }
    }

    cout << "\nMatriz A:" << endl;
    imprimirMatriz(matrizA);

    if (!verificarDiagonalDominante(matrizA)) {
        cout << "\nLa matriz A no es estrictamente diagonal dominante. Los métodos de Jacobi y Gauss-Seidel podrían no converger correctamente." << endl;
        return 1;
    }

    Vector vectorB(tamano);

    cout << "\nIngrese los elementos del vector B:" << endl;
    for (int i = 0; i < tamano; ++i) {
        cout << "Ingrese el elemento en la posicion [" << i + 1 << "]: ";
        cin >> vectorB[i];
    }

    int numIteraciones;
    cout << "\nIngrese la cantidad de iteraciones para los métodos de Jacobi y Gauss-Seidel: ";
    cin >> numIteraciones;

    // Resolver el sistema de ecuaciones Ax = B usando el método de Jacobi
    cout << "\nMétodo de Jacobi:" << endl;
    Vector solucionJacobi = resolverSistemaJacobi(matrizA, vectorB, numIteraciones);

    cout << "\nLa solucion del sistema de ecuaciones Ax = B (metodo Jacobi) es:\n";
    imprimirVector(solucionJacobi);

    // Resolver el sistema de ecuaciones Ax = B usando el método de Gauss-Seidel
    cout << "\nMétodo de Gauss-Seidel:" << endl;
    Vector solucionGaussSeidel = resolverSistemaGaussSeidel(matrizA, vectorB, numIteraciones);

    cout << "\nLa solucion del sistema de ecuaciones Ax = B (metodo Gauss-Seidel) es:\n";
    imprimirVector(solucionGaussSeidel);

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

void imprimirVector(const Vector& vector) {
    for (int i = 0; i < vector.size(); ++i) {
        cout << "x[" << i + 1 << "] = " << vector[i] << "\n";
    }
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

        if (abs(matriz[i][i]) <= sumaFilas || abs(matriz[i][i]) <= sumaColumnas) {
            return false; // No es estrictamente diagonal dominante
        }
    }

    return true; // Es estrictamente diagonal dominante
}

Vector resolverSistemaJacobi(const Matriz& A, const Vector& B, int iteraciones) {
    int tamano = A.size();
    Vector X(tamano, 0.0);

    Vector X_ant(tamano, 0.0); // Vector para almacenar el valor de X en la iteración anterior

    for (int iteracion = 0; iteracion < iteraciones; ++iteracion) {
        Vector nuevoX(tamano, 0.0);
        Vector errores(tamano, 0.0);
        double error_total = 0.0;

        for (int i = 0; i < tamano; ++i) {
            double suma = 0.0;

            for (int j = 0; j < tamano; ++j) {
                if (i != j) {
                    suma += A[i][j] * X_ant[j];
                }
            }

            nuevoX[i] = (B[i] - suma) / A[i][i];
        }

        for (int i = 0; i < tamano; ++i) {
            errores[i] = abs((X[i] - nuevoX[i]) / nuevoX[i]);
            error_total += errores[i];
        }

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

Vector resolverSistemaGaussSeidel(const Matriz& matrizA, const Vector& vectorB, int iteraciones) {
    int n = matrizA.size();

    Vector x(n, 0.0);

    for (int iter = 0; iter < iteraciones; ++iter) {
        Vector xNuevo(x);
        Vector errores(n, 0.0);
        double error_total = 0.0;

        for (int i = 0; i < n; ++i) {
            double suma = 0.0;

            for (int j = 0; j < n; ++j) {
                if (j != i) {
                    suma += matrizA[i][j] * xNuevo[j];
                }
            }

            xNuevo[i] = (vectorB[i] - suma) / matrizA[i][i];
        }

        for (int i = 0; i < n; ++i) {
            errores[i] = abs((x[i] - xNuevo[i]) / xNuevo[i]);
            error_total += errores[i];
        }

        cout << "Iteracion " << iter + 1 << ":" << endl;
        for (int i = 0; i < n; ++i) {
            cout << "x[" << i + 1 << "] = " << xNuevo[i] << ", Error Relativo: " << errores[i] << endl;
        }
        cout << "Error Total: " << error_total << endl << endl;

        x = xNuevo;
    }

    return x;
}