#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <ctime>
#include <chrono> 

using namespace std;

// Función para multiplicar dos matrices.
vector<vector<int>> multiplicar(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int fila1 = A.size();
    int col1 = A[0].size();
    int fila2 = B.size();
    int col2 = B[0].size();

// Verifica si las matrices se pueden multiplicar.
    if (col1 != fila2) {
        throw invalid_argument("El número de columnas de la primera matriz debe ser igual al número de filas de la segunda matriz.");
    }

// Crear la matriz resultante con ceros.
    vector<vector<int>> result(fila1, vector<int>(col2, 0));

// Realizar la multiplicación.
    for (int i = 0; i < fila1; ++i) {
        for (int j = 0; j < col2
; ++j) {
            for (int k = 0; k < col1; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return result;
}

void print(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int valor : row) {
            cout << valor << " ";
        }
        cout << endl;
    }
}

// Función para leer una matriz desde un archivo
vector<vector<int>> leerMatriz(ifstream& file) {
    int filas, columnas;
    file >> filas >> columnas;  // Leer las dimensiones de la matriz
    vector<vector<int>> matrix(filas, vector<int>(columnas));

    // Leer los valores de la matriz
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            file >> matrix[i][j];
        }
    }

    return matrix;
}

int main() {
    ifstream inputFile("matrices.txt");
    
    if (!inputFile) {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }

    try {

        vector<vector<int>> A = leerMatriz(inputFile);
        vector<vector<int>> B = leerMatriz(inputFile);

        // Multiplicar las matrices y toma el tiempo de ejecución de algoritmo.
        auto start = chrono::high_resolution_clock::now();
        vector<vector<int>> C = multiplicar(A, B);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

        // Imprimir la matriz resultante, para verla sacar comentario. (no recomendado si la multiplicación es my grande)
        //print(C);
        cout << "Tiempo de ejecución: " << duration.count() << " microsegundos." << endl;

    } catch (const invalid_argument& e) {
        cerr << e.what() << endl;
    }

    inputFile.close();

    return 0;
}