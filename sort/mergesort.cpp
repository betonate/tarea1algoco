#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

//Función que fusiona 2 partes del arreglo, requerida para el Merge Sort.
void merge(vector<int>& arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Algortimo Merge Sort.
void mergeSort(vector<int>& arr, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void printVector(vector<int>& arr)
{
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main()
{

    vector<int> arr;
    int n;
    ifstream archivo("dataset.txt");
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return 1;
    }
    while (archivo >> n) {
        arr.push_back(n);
    }
    
    archivo.close();



    // Ejecutar el algortimo y toma el tiempo de ejecución.
    auto start = high_resolution_clock::now();
    mergeSort(arr, 0, arr.size() - 1);  
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    
    std::cout << "Tiempo tomado para ordenar un arreglo de tamaño " << arr.size() << ": " 
        << duration << " microsegundos" << std::endl;
        
    //Para ver el arreglo resultante desmarcar aca abajo(no recomiendo si es muy grande):
    //printVector(arr);
    return 0;
}