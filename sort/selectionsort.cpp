#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

void selectionSort(int arr[], int n) {              
    for (int i = 0; i < n - 1; i++) {
        int indice = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[indice]) {
                indice = j;
            }
        }
        swap(arr[i], arr[indice]);
    }
}


int main() {
    int n;

    // Pedimos el tamaño del arreglo al usuario
    std::cout << "Introduce el tamaño del arreglo: ";
    std::cin >> n;

    // Crear un arreglo dinámico de tamaño n
    int* dataset = new int[n];

    // Abrimos el archivo para leer los valores
    std::ifstream file("dataset.txt");

    if (file.is_open()) {
        for (int i = 0; i < n; ++i) {
            file >> dataset[i];  // Leer los datos desde el archivo
        }
        file.close();

        /* 
        Mostrar los datos leídos
        std::cout << "Datos leídos: ";
        for (int i = 0; i < n; ++i) {
            std::cout << dataset[i] << " ";
        }
        std::cout << std::endl;
        */

        // Medir el tiempo de ordenación
        auto start = high_resolution_clock::now();
        selectionSort(dataset, n);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start).count();
    
        std::cout << "Tiempo tomado para ordenar un arreglo de tamaño " << n << ": " 
                  << duration << " microsegundos" << std::endl;

         
        /*Mostrar el arreglo ordenado
        for (int i = 0; i < n; ++i) {
            std::cout << dataset[i] << " ";
        }
        std::cout << std::endl;
        */
       
    } else {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
    }

    // Liberar la memoria dinámica
    delete[] dataset;

    return 0;
}