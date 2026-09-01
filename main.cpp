#include <algorithm>// para std::is_sorted, usado en las verificaciones
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>// para medir tiempos de ejecución
#include "sorting/quick_sort.h"
#include "structures/avl_tree.h"
#include "sorting/heap_sort.h"

// Imprime los resultados de una estrategia de ordenamiento en una caja prolija
void imprimirResultado(const std::string& nombre, long long tiempoMs, bool ordenado,
                        const std::string& primera, const std::string& ultima) {
    std::cout << "+------------------------------+\n";
    std::cout << "| " << nombre << std::string(31 - nombre.size(), ' ') << "|\n";
    std::cout << "+------------------------------+\n";
    std::cout << "| Tiempo:    " << tiempoMs << " ms\n";
    std::cout << "| Ordenado:  " << (ordenado ? "Si" : "No") << "\n";
    std::cout << "| Primera:   " << primera << "\n";
    std::cout << "| Ultima:    " << ultima << "\n";
    std::cout << "+------------------------------+\n\n";
}

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

    std::cout << "Palabras leidas: " << palabras.size() << "\n\n"; //verificacion , deberia dar 100K
    std::vector<std::string> palabrasOriginal = palabras; // copia sin ordenarr antes que el quickSort modifique palabras

    // --- QuickSort ---
    auto inicio = std::chrono::high_resolution_clock::now();
    quickSort(palabras); //Ordena in-place,palabras queda modficiado desde aqui en adelante
    auto fin = std::chrono::high_resolution_clock::now();
    auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);

    imprimirResultado("QuickSort", duracion.count(),
                       std::is_sorted(palabras.begin(), palabras.end()),
                       palabras.front(), palabras.back());

    // --- AVL ---
    AVLTree arbol;
    auto inicioAVL = std::chrono::high_resolution_clock::now();
    for (const auto& palabra : palabras) {  // ya está ordenado en este punto (quickSort corrió antes)
        arbol.insertar(palabra);
    }
    std::vector<std::string> resultadoAVL = arbol.obtenerOrdenado(); // inorder, entrega todo ya ordenado
    auto finAVL = std::chrono::high_resolution_clock::now();
    auto duracionAVL = std::chrono::duration_cast<std::chrono::milliseconds>(finAVL - inicioAVL);

    imprimirResultado("AVL", duracionAVL.count(),
                       std::is_sorted(resultadoAVL.begin(), resultadoAVL.end()),
                       resultadoAVL.front(), resultadoAVL.back());

    // --- HeapSort ---
    std::vector<std::string> palabrasHeap = palabrasOriginal; // copia de la original sin ordenar
    auto inicioHeap = std::chrono::high_resolution_clock::now();
    heapSort(palabrasHeap);
    auto finHeap = std::chrono::high_resolution_clock::now();
    auto duracionHeap = std::chrono::duration_cast<std::chrono::milliseconds>(finHeap - inicioHeap);

    imprimirResultado("HeapSort", duracionHeap.count(),
                       std::is_sorted(palabrasHeap.begin(), palabrasHeap.end()),
                       palabrasHeap.front(), palabrasHeap.back());

    // --- Estimación de Memoria ---
    size_t memoriaVector = palabras.size() * sizeof(std::string); // cantidad de palabras × tamaño de cada string
    size_t memoriaAVL = palabras.size() * sizeof(NodoAVL); // cantidad de nodos × tamaño de cada nodo

    std::cout << "+------------------------------+\n";
    std::cout << "| Memoria                       |\n";
    std::cout << "+------------------------------+\n";
    std::cout << "| sizeof(std::string): " << sizeof(std::string) << " bytes\n";
    std::cout << "| sizeof(NodoAVL):     " << sizeof(NodoAVL) << " bytes\n";
    std::cout << "| Vector (QuickSort/HeapSort): " << memoriaVector << " bytes\n";
    std::cout << "| Arbol AVL:                   " << memoriaAVL << " bytes\n";
    std::cout << "+------------------------------+\n";

    return 0;
}