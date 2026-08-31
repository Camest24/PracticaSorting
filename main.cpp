#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include "sorting/quick_sort.h"
#include "structures/avl_tree.h"
#include "sorting/heap_sort.h"

int main()  {
    std::ifstream archivo("data/dataset_utf8.txt");
    std::vector<std::string> palabras;


    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo" << std::endl;
        return 1;
    }

    std::string linea;
    while (std::getline(archivo,linea)) {
        palabras.push_back(linea);
    }

    std::cout << palabras.size() << std::endl;

    auto inicio = std::chrono::high_resolution_clock::now();
    quickSort(palabras);
    auto fin = std::chrono::high_resolution_clock::now();
    std::vector<std::string> palabrasOriginal = palabras;


    auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(fin- inicio);
    std::cout << "Tiempo Quicksort: " << duracion.count() << "ms" << std::endl;

    std::cout << "Esta ordenado: " <<std::is_sorted(palabras.begin(),palabras.end()) << std::endl;
    std::cout << "Primera Palabra: " << palabras.front() << std::endl;
    std::cout << "Ultima Palabra: " << palabras.back() << std::endl;

    AVLTree arbol;
    auto inicioAVL = std::chrono::high_resolution_clock::now();
    for (const auto& palabra : palabras) {
        arbol.insertar(palabra);
    }

    std::vector<std::string> resultadoAVL = arbol.obtenerOrdenado();
    auto finAVL = std::chrono::high_resolution_clock::now();



    auto duracionAVL = std::chrono::duration_cast<std::chrono::milliseconds>(finAVL- inicioAVL);
    std::cout << "Tiempo AVL: " << duracionAVL.count() << "ms" << std::endl;
    std::cout << "AVL Esta ordenado: " <<std::is_sorted(resultadoAVL.begin(),resultadoAVL.end()) << std::endl;
    std::cout << "AVL Primera: " << resultadoAVL.front() << std::endl;
    std::cout << "AVL Ultima: " << resultadoAVL.back() << std::endl;

    //Estimación de Memoria
    std::cout <<"sizeof(std:string):" <<sizeof(std::string) << "bytes" << std::endl;
    std::cout <<"sizeof(NodoAVL):" <<sizeof(NodoAVL) << "bytes" << std::endl;

    size_t memoriaVector = palabras.size() * sizeof(std::string);
    std::cout <<"Memoria aproximada del vector (QuickSort)" << memoriaVector << "bytes" << std::endl;

    size_t memoriaAVL = palabras.size() * sizeof(NodoAVL);
    std::cout <<"Memoria aproximada del arbol AVL" << memoriaAVL << "bytes" << std::endl;

    std::vector<std::string> palabrasHeap = palabrasOriginal; // OJO: copia de la ORIGINAL sin ordenar
    auto inicioHeap = std::chrono::high_resolution_clock::now();
    heapSort(palabrasHeap);
    auto finHeap = std::chrono::high_resolution_clock::now();
    auto duracionHeap = std::chrono::duration_cast<std::chrono::milliseconds>(finHeap - inicioHeap);
    std::cout << "Tiempo HeapSort: " << duracionHeap.count() << "ms" << std::endl;
    std::cout << "HeapSort Esta ordenado: " << std::is_sorted(palabrasHeap.begin(), palabrasHeap.end()) << std::endl;
    std::cout << "HeapSort Primera: " << palabrasHeap.front() << std::endl;
    std::cout << "HeapSort Ultima: " << palabrasHeap.back() << std::endl;



return 0;
}