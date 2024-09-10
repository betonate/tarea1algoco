#include <iostream>
#include <vector>
#include <fstream>
#include <chrono> 

// Función para leer matrices desde un archivo.
std::vector<std::vector<int>> leerMatriz(std::ifstream& archivo, int& filas, int& columnas) {
    archivo >> filas >> columnas;
    std::vector<std::vector<int>> matriz(filas, std::vector<int>(columnas));

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            archivo >> matriz[i][j];
        }
    }
    return matriz;
}

// Función para trasponer una matriz.
std::vector<std::vector<int>> transponer(const std::vector<std::vector<int>>& matriz) {
    int filas = matriz.size();
    int columnas = matriz[0].size();
    std::vector<std::vector<int>> traspuesta(columnas, std::vector<int>(filas));

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            traspuesta[j][i] = matriz[i][j];
        }
    }
    return traspuesta;
}

// Función para multiplicar dos matrices.
std::vector<std::vector<int>> multiplicarMatrices(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    int filasA = A.size();
    int columnasA = A[0].size();
    int columnasB = B[0].size();

    std::vector<std::vector<int>> C(filasA, std::vector<int>(columnasB, 0));

// Trasponemos la segunda matriz B.
    std::vector<std::vector<int>> B_T = transponer(B);

// Multiplicamos A por la traspuesta de B.
    for (int i = 0; i < filasA; i++) {
        for (int j = 0; j < columnasB; j++) {
            for (int k = 0; k < columnasA; k++) {
                C[i][j] += A[i][k] * B_T[j][k];
            }
        }
    }
    return C;
}

// Función para imprimir una matriz
void imprimirMatriz(const std::vector<std::vector<int>>& matriz) {
    for (const auto& fila : matriz) {
        for (int valor : fila) {
            std::cout << valor << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::ifstream archivo("matrices.txt");

    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo matrices.txt" << std::endl;
        return 1;
    }

    int filasA, columnasA, filasB, columnasB;


    std::vector<std::vector<int>> A = leerMatriz(archivo, filasA, columnasA);
    std::vector<std::vector<int>> B = leerMatriz(archivo, filasB, columnasB);

    archivo.close();


    // Verificar que las matrices sean multiplicables
    if (columnasA != filasB) {
        std::cerr << "Error: Las dimensiones no permiten la multiplicación (columnas de A deben ser iguales a filas de B)." << std::endl;
        return 1;
    }

    // Inicia la multiplicacion y toma el tiempo del algortimo.
    auto inicio = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<int>> resultado = multiplicarMatrices(A, B);
    auto fin = std::chrono::high_resolution_clock::now();
    auto duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();

    // Imprimir la matriz resultante, para verla sacar comentario. (no recomendado si la multiplicación es my grande)
    //imprimirMatriz(resultado);

    std::cout << "\nTiempo de ejecución: " << duracion << " microsegundos." << std::endl;

    return 0;
}