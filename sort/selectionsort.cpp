#include <iostream>
#include <vector>
#include <fstream>
#include <chrono> 

using namespace std;
using namespace std::chrono;

// Función para realizar el algoritmo Selection Sort.
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 0; i < n - 1; i++) {
// Encontrar el índice del valor mínimo en la parte no ordenada.
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
// Intercambiar el valor mínimo con el valor en la posición i.
        swap(arr[i], arr[minIndex]);
    }
}


void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    ifstream inputFile("dataset.txt");
    if (!inputFile) {
        cerr << "No se pudo abrir el archivo dataset.txt" << endl;
        return 1;
    }

    vector<int> arr;
    int value;
    
    while (inputFile >> value) {
        arr.push_back(value);
    }

    inputFile.close();

    if (arr.empty()) {
        cerr << "El archivo está vacío o no contiene datos válidos" << endl;
        return 1;
    }

    // Llama al algoritmo Selection Sort y toma el tiempo de ejecución.
    auto start = high_resolution_clock::now();
    selectionSort(arr);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);


    //Para ver el arreglo resultante desmarcar aca abajo(no recomiendo si es muy grande):
    //printArray(arr);
    cout << "Tiempo de ejecución: " << duration.count() << " microsegundos" << endl;

    return 0;
}