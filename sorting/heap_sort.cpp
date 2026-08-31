#include "heap_sort.h"

void heapify(std::vector<std::string>& v, int n, int i) {
    int mayor = i;
    int izquierda = 2 * i + 1;
    int derecha = 2 * i + 2;

    if (izquierda < n && v[izquierda] > v[mayor]) {
        mayor = izquierda;
    }
    if (derecha < n && v[derecha] > v[mayor]) {
        mayor = derecha;
    }

    if (mayor != i) {
        std::swap(v[i], v[mayor]);
        heapify(v, n, mayor);
    }
}

void heapSort(std::vector<std::string>& v) {
    int n = static_cast<int>(v.size());

    // Fase 1: construir el max-heap. Se arranca en n/2-1 porque
    // todo lo que está después de ese índice ya es hoja (no tiene hijos que ordenar).
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(v, n, i);
    }

    // Fase 2: extraer el máximo (índice 0) repetidamente.
    // Se reduce el "tamaño activo" del heap (i) en cada vuelta, pero
    // el vector completo sigue existiendo — solo se deja de tocar la cola.
    for (int i = n - 1; i > 0; i--) {
        std::swap(v[0], v[i]);
        heapify(v, i, 0);
    }
}