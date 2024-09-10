#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>

using namespace std;

typedef vector<vector<int>> Matrix;

//Funci+on auxiliar para Strassen.
Matrix sum(const Matrix &A, const Matrix &B, int size) {
    Matrix C(size, vector<int>(size));
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

//Funci+on auxiliar para Strassen.
Matrix subtract(const Matrix &A, const Matrix &B, int size) {
    Matrix C(size, vector<int>(size));
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

//Algoritmo Strassen.
Matrix strassen(const Matrix &A, const Matrix &B, int size) {
    if (size == 1) {
        return {{A[0][0] * B[0][0]}};
    }

    int newSize = size / 2;
    Matrix A11(newSize, vector<int>(newSize));
    Matrix A12(newSize, vector<int>(newSize));
    Matrix A21(newSize, vector<int>(newSize));
    Matrix A22(newSize, vector<int>(newSize));
    Matrix B11(newSize, vector<int>(newSize));
    Matrix B12(newSize, vector<int>(newSize));
    Matrix B21(newSize, vector<int>(newSize));
    Matrix B22(newSize, vector<int>(newSize));

// Dividir las matrices en submatrices
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Calcular los productos intermedios
    Matrix M1 = strassen(sum(A11, A22, newSize), sum(B11, B22, newSize), newSize);
    Matrix M2 = strassen(sum(A21, A22, newSize), B11, newSize);
    Matrix M3 = strassen(A11, subtract(B12, B22, newSize), newSize);
    Matrix M4 = strassen(A22, subtract(B21, B11, newSize), newSize);
    Matrix M5 = strassen(sum(A11, A12, newSize), B22, newSize);
    Matrix M6 = strassen(subtract(A21, A11, newSize), sum(B11, B12, newSize), newSize);
    Matrix M7 = strassen(subtract(A12, A22, newSize), sum(B21, B22, newSize), newSize);

    Matrix C(size, vector<int>(size));
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
            C[i][j + newSize] = M3[i][j] + M5[i][j];
            C[i + newSize][j] = M2[i][j] + M4[i][j];
            C[i + newSize][j + newSize] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
        }
    }

    return C;
}

// Función para leer matrices desde un archivo con formato específico
bool readMatricesFromFile(const string& filename, vector<vector<int>>& A, vector<vector<int>>& B) {
    ifstream infile(filename);

    if (!infile.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return false;
    }

    int rowsA, colsA, rowsB, colsB;

    infile >> rowsA >> colsA;
    A.resize(rowsA, vector<int>(colsA));
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsA; ++j) {
            infile >> A[i][j];
        }
    }

    infile >> rowsB >> colsB;
    B.resize(rowsB, vector<int>(colsB));
    for (int i = 0; i < rowsB; ++i) {
        for (int j = 0; j < colsB; ++j) {
            infile >> B[i][j];
        }
    }

    infile.close();

    return (rowsA == colsA && rowsB == colsB && rowsA == rowsB);
}

void printMatrix(const Matrix &mat) {
    for (const auto &row : mat) {
        for (const auto &elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
}

int main() {
    Matrix A, B;

    readMatricesFromFile("matrices.txt", A, B);

// Verificar que el tamaño de las matrices es válido para Strassen, cuadradas y potencia de 2.
    int size = A.size();
    if (size != B.size()) {
        cerr << "Las matrices deben ser del mismo tamaño." << endl;
        cerr << size  << endl;
        cerr << B.size()  << endl;
        return 1;
    }

    if ((size & (size - 1)) != 0) {
        cerr << "El tamaño de las matrices debe ser una potencia de 2." << endl;
        return 1;
    }

// Realizar la multiplicación con Strassen

    auto inicio = std::chrono::high_resolution_clock::now();
    Matrix C = strassen(A, B, size);
    auto fin = std::chrono::high_resolution_clock::now();
    auto duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();

    // Imprimir la matriz resultante, para verla sacar comentario. (no recomendado si la multiplicación es my grande)
    //printMatrix(C);
    std::cout << "\nTiempo de ejecución: " << duracion << " microsegundos." << std::endl;

    return 0;
}