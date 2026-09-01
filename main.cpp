#include <algorithm>// para std::is_sorted, usado en las verificaciones
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>// para medir tiempos de ejecución
#include "sorting/quick_sort.h"
#include "structures/avl_tree.h"
#include "sorting/heap_sort.h"

int main()  {
    std::ifstream archivo("data/dataset_utf8.txt"); //Abre el archiivo ya convertido a UTF -8
    std::vector<std::string> palabras; //Aqui guardamoos las 100k palabras leidas


    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo" << std::endl;
        return 1; //si no se pudo abrir, avisa y termina
    }

    std::string linea;
    while (std::getline(archivo,linea)) { //lee el archivo linea por linea
        palabras.push_back(linea); // cada linea es una palabra
    }

    std::cout << palabras.size() << std::endl; //verificacion , deberia dar 100K
    std::vector<std::string> palabrasOriginal = palabras; // copia sin ordenarr antes que el quickSort modifique palabras

    auto inicio = std::chrono::high_resolution_clock::now();
    quickSort(palabras); //Ordena in-place,palabras queda modficiado desde aqui en adelante
    auto fin = std::chrono::high_resolution_clock::now();

    auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(fin- inicio);
    std::cout << "Tiempo Quicksort: " << duracion.count() << "ms" << std::endl;

    std::cout << "Esta ordenado: " <<std::is_sorted(palabras.begin(),palabras.end()) << std::endl; //Verificacion de que quedo bien ordenado
    std::cout << "Primera Palabra: " << palabras.front() << std::endl;
    std::cout << "Ultima Palabra: " << palabras.back() << std::endl;

    AVLTree arbol;
    auto inicioAVL = std::chrono::high_resolution_clock::now();
    for (const auto& palabra : palabras) {  // ya está ordenado en este punto (quickSort corrió antes)
        arbol.insertar(palabra);
    }

    std::vector<std::string> resultadoAVL = arbol.obtenerOrdenado(); // inorder, entrega todo ya ordenado
    auto finAVL = std::chrono::high_resolution_clock::now();

    auto duracionAVL = std::chrono::duration_cast<std::chrono::milliseconds>(finAVL- inicioAVL);
    std::cout << "Tiempo AVL: " << duracionAVL.count() << "ms" << std::endl;
    std::cout << "AVL Esta ordenado: " <<std::is_sorted(resultadoAVL.begin(),resultadoAVL.end()) << std::endl;
    std::cout << "AVL Primera: " << resultadoAVL.front() << std::endl;
    std::cout << "AVL Ultima: " << resultadoAVL.back() << std::endl;

    //Estimación de Memoria
    std::cout <<"sizeof(std:string):" <<sizeof(std::string) << "bytes" << std::endl;  // tamaño de UN objeto string
    std::cout <<"sizeof(NodoAVL):" <<sizeof(NodoAVL) << "bytes" << std::endl;  // tamaño de UN nodo (string + 2 punteros + altura)

    size_t memoriaVector = palabras.size() * sizeof(std::string); // cantidad de palabras × tamaño de cada string
    std::cout <<"Memoria aproximada del vector (QuickSort)" << memoriaVector << "bytes" << std::endl;

    size_t memoriaAVL = palabras.size() * sizeof(NodoAVL); // cantidad de nodos × tamaño de cada nodo
    std::cout <<"Memoria aproximada del arbol AVL" << memoriaAVL << "bytes" << std::endl;

    std::vector<std::string> palabrasHeap = palabrasOriginal; // copia de la original sin ordenar
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