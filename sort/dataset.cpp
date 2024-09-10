#include <iostream>
#include <fstream>
#include <cstdlib>  
#include <ctime>   
#include <algorithm>  

int main() {
    int n;
    char opcion;

    std::cout << "Introduce el tamaño del arreglo: ";
    std::cin >> n;

    std::cout << "Elige una opción para el arreglo:\n";
    std::cout << "A) Completamente aleatorio\n";
    std::cout << "B) Semiordenado\n";
    std::cout << "C) Decreciente\n";
    std::cout << "D) Pivote Extremos (Quick Sort)\n";
    std::cout << "E) Pivote Medio (Quick Sort)\n";
    std::cin >> opcion;

    int* dataset = new int[n];

    srand(time(0));

    // Generar el arreglo basado en la opción del usuario
    if (opcion == 'A' || opcion == 'a') {     // Arreglo completamente aleatorio

        for (int i = 0; i < n; ++i) {
            dataset[i] = rand() % 100; 
        }
    } else if (opcion == 'B' || opcion == 'b') {     // Arreglo semiordenado

        for (int i = 0; i < n; ++i) {
            dataset[i] = rand() % 100;  
        }

        std::sort(dataset, dataset + n / 2);  // Ordenamos la primera mitad del arreglo

    } else if (opcion == 'C' || opcion == 'c') {     // Arreglo ordenado de forma decreciente.

        for (int i = 0; i < n; ++i) {
            dataset[i] = rand() % 100;  
        }

        // Ordenar el arreglo de forma decreciente
        std::sort(dataset, dataset + n, std::greater<int>());  // Ordenar de mayor a menor
    } else if (opcion == 'D' || opcion == 'd') {     // Arreglo ordenado de forma decreciente.

        for (int i = 0; i < n; ++i) {
            dataset[i] = rand() % 100;  
        }


        std::sort(dataset, dataset + n, std::greater<int>());  
        dataset[n-1]=100;
        } else if (opcion == 'E' || opcion == 'e') {     // Arreglo ordenado de forma decreciente.

        for (int i = 0; i < n; ++i) {
            dataset[i] = rand() % 100;  
        }


        std::sort(dataset, dataset + n, std::greater<int>());  
        dataset[n-1]=50;
    } else {

        std::cerr << "Opción no válida." << std::endl;
        for (int i = 0; i < n; ++i) {
            dataset[i] = rand() % 100;
        }
    }

    std::ofstream file("dataset.txt");

    if (file.is_open()) {
        for (int i = 0; i < n; ++i) {
            file << dataset[i] << " ";  
        }
        file.close();
        std::cout << "Datos guardados en el archivo de texto." << std::endl;
    } else {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
    }

    delete[] dataset;

    return 0;
}