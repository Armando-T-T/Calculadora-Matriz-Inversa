#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

typedef vector<vector<double>> Matriz;
typedef vector<double> Vector;

void imprimirMatriz(const Matriz& matriz);
Matriz matrizIdentidad(int n);
void multiplicarFila(Matriz& matriz, int fila, double escalar);
void sumarFilas(Matriz& matriz, int filaObjetivo, int filaFuente, double escalar);
Matriz inversaGaussJordan(Matriz matriz);
Vector multiplicarMatrizPorVector(const Matriz& matriz, const Vector& vector);
double determinante(const Matriz& matriz);

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

    if (determinante(matriz) == 0.0) {
        cout << "\nLa matriz no tiene inversa." << endl;
        return 1;
    }
    else {
        cout << "\nLa matriz si tiene inversa." << endl;
    }

    Matriz matrizInversa = inversaGaussJordan(matriz);

    cout << "\nMatriz Inversa:" << endl;
    imprimirMatriz(matrizInversa);

    Vector vectorB(tamano);

    cout << "\nIngrese los elementos del vector B:" << endl;
    for (int i = 0; i < tamano; ++i) {
        cout << "Ingrese el elemento en la posicion [" << i + 1 << "]: ";
        cin >> vectorB[i];
    }

    // Resolver el sistema de ecuaciones Ax = B
    Vector solucionX = multiplicarMatrizPorVector(matrizInversa, vectorB);

    cout << "\nLa solucion del sistema de ecuaciones Ax = B es:\n";
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

Matriz matrizIdentidad(int n) {
    Matriz identidad(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i) {
        identidad[i][i] = 1.0;
    }
    return identidad;
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
        double pivote = matriz[i][i];

        multiplicarFila(matriz, i, 1 / pivote);
        multiplicarFila(matrizInversa, i, 1 / pivote);

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

Vector multiplicarMatrizPorVector(const Matriz& matriz, const Vector& vector) {
    int filas = matriz.size();
    int columnas = matriz[0].size();

    Vector resultado(filas, 0.0);

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            resultado[i] += matriz[i][j] * vector[j];
        }
    }

    return resultado;
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