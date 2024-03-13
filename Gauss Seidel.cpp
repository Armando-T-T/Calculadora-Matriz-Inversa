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

    if (!verificarDiagonalDominante(matriz)) {
        cout << "\nLa matriz no es diagonal dominante. El método de Gauss-Seidel podría no converger correctamente." << endl;
        return 1;
    }

    Vector vectorB(tamano);

    cout << "\nIngrese los elementos del vector B:" << endl;
    for (int i = 0; i < tamano; ++i) {
        cout << "Ingrese el elemento en la posicion [" << i + 1 << "]: ";
        cin >> vectorB[i];
    }

    int iteraciones;
    cout << "\nIngrese la cantidad de iteraciones para el método de Gauss-Seidel: ";
    cin >> iteraciones;

    // Resolver el sistema de ecuaciones Ax = B usando Gauss-Seidel
    Vector solucionX = resolverSistemaGaussSeidel(matriz, vectorB, iteraciones);

    cout << "\nLa solucion del sistema de ecuaciones Ax = B es:\n";
    imprimirVector(solucionX);

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

Vector resolverSistemaGaussSeidel(const Matriz& matrizA, const Vector& vectorB, int iteraciones) {
    int n = matrizA.size();

    Vector x(n, 0.0);

    for (int iter = 0; iter < iteraciones; ++iter) {
        Vector xNuevo(x);

        for (int i = 0; i < n; ++i) {
            double suma = 0.0;

            for (int j = 0; j < n; ++j) {
                if (j != i) {
                    suma += matrizA[i][j] * xNuevo[j];
                }
            }

            xNuevo[i] = (vectorB[i] - suma) / matrizA[i][i];
        }

        x = xNuevo;
    }

    return x;
}