#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>  

using namespace std;
using namespace std::chrono;


void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        // Mueve los elementos que son mayores que el key hacia adelante
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void printArray(const vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}


int main() {
    //Abre el archivo llamado en este caso dataset.txt (cambiar si es requerido)
    ifstream inputFile("dataset.txt");
    vector<int> arr;

    if (!inputFile) {
        cerr << "Error al abrir el archivo 'dataset.txt'" << endl;
        return 1;
    }

    int num;
    // Leer el archivo y almacenar los números en el vector
    while (inputFile >> num) {
        arr.push_back(num);
    }

    inputFile.close();



//Calcula el tiempo de ejecucion del algoritmo.
    auto start = high_resolution_clock::now();
    insertionSort(arr);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    //Para ver el arreglo resultante desmarcar aca abajo(no recomiendo si es muy grande):
    //printArray(arr);

    // Mostrar el tiempo de ejecución en nanosegundos
    cout << "Tiempo de ejecución: " << duration.count() << " microseconds" << endl;

    return 0;
}