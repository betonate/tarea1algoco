#include <bits/stdc++.h>
#include <chrono>  
#include <cstdlib> 
#include <ctime>   
#include <algorithm>
using namespace std;
using ll = long long;
using ld = long double;
using namespace std::chrono;

void printVector(vector<int>& arr)
{
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
    cout << endl;
}
//Codigo muy simple ya que es la funcióin sort de C++.

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


    auto start = high_resolution_clock::now();
    sort(arr.begin(), arr.end());
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    
    std::cout << "Tiempo tomado para ordenar un arreglo de tamaño " << arr.size() << ": " 
        << duration << " microsegundos" << std::endl;


    //Para ver el arreglo resultante desmarcar aca abajo(no recomiendo si es muy grande):
    //printVector(arr);
    return 0;
}