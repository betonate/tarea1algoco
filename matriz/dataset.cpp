#include<bits/stdc++.h>
#include <chrono>  
#include <cstdlib> 
#include <ctime>   
#include <algorithm>
using namespace std;
using ll = long long;
using ld = long double;
using namespace std::chrono;

void generateMatrix(int rows, int cols, std::ofstream &file) {
    file << rows << " " << cols << "\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file << rand() % 10 << " "; // Genera números aleatorios entre 0 y 9
        }
        file << "\n";
    }
}
bool esPotenciaDeDos(int n) {
    return (n & (n - 1)) == 0 && n > 0;
}

int main() {
    srand(time(0)); // Inicializa la semilla para la generación de números aleatorios

    int rows1, cols1, rows2, cols2, r1,r2,r3,r4,n;
    char squareChoice;

    std::cout << "Elige una opción para la matriz:\n";
    std::cout << "A) Cuadrada\n";
    std::cout << "B) Rectangular\n";
    std::cout << "C) Para Strassen (n es potencia de 2)\n";
    std::cin >> squareChoice;

    if (squareChoice == 'A' || squareChoice == 'a') {
        std::cout << "Ingrese el tamaño de la matriz cuadrada:";
        std::cin >> rows1;
        cols1=rows2;
        r1=rows1;
        r2=rows1;
        r3=rows1;
        r4=rows1;
        //r1 = pow(10,rows1;
        //r2 = pow(10,rows1);
        //r3 = pow(10,rows1); 
        //r4 = pow(10,rows1);  // Las matrices serán cuadradas
    } else if (squareChoice == 'B' || squareChoice == 'b') {  
        std::cout << "Ingrese el número de filas y columnas para la primera matriz:";
        std::cin >> rows1 >> cols1;
        //r1 = pow(10,rows1);
        //r2 = pow(10,cols1);
        r1=rows1;
        r2=cols1;

        std::cout << "Ingrese el número de filas y columnas para la segunda matriz:";
        std::cin >> rows2 >> cols2;
        //r3 = pow(10,rows2);
        //r4 = pow(10,cols2);
        r3=rows2;
        r4=cols2;
    } else if (squareChoice == 'c' || squareChoice == 'C') {  
        do {
            cout << "Ingrese el tamaño de la matriz (debe ser una potencia de 2): ";
            cin >> n;
            if (!esPotenciaDeDos(n)) {
                cout << "El tamaño debe ser una potencia de 2. Intente nuevamente." << endl;
            }
        } while (!esPotenciaDeDos(n));
        cols1=n;
        rows2=n;
        r1 = n;
        r2 = n;
        r3 = n;
        r4 = n;

    // Crear la matriz de tamaño n x n
    }

    // Verifica si las matrices son multiplicables
    if (cols1 != rows2) {
        std::cerr << "Error: El número de columnas de la primera matriz debe ser igual al número de filas de la segunda matriz.\n";
        return 1;
    }

    // Abre el archivo para escribir
    std::ofstream file("matrices.txt");

    if (!file) {
        std::cerr << "Error al abrir el archivo.\n";
        return 1;
    }

    // Genera y escribe las dos matrices en el archivo
    generateMatrix(r1, r2, file);

    generateMatrix(r3, r4, file);

    file.close();
    std::cout << "Matrices generadas y guardadas en matrices.txt.\n";

    return 0;
}