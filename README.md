# Práctica I — Sorting Large Dataset

ST0245 - Estructuras de Datos y Algoritmos, EAFIT.

Ordena 100,000 palabras con 3 estrategias implementadas desde cero (sin `std::sort`): QuickSort, HeapSort, y Árbol AVL. Mide tiempo de ejecución (`std::chrono`) y memoria aproximada de cada una.

## Estructura
- `sorting/` — QuickSort y HeapSort
- `structures/` — Árbol AVL
- `tools/convertir_utf8.cpp` — convierte el dataset de UTF-16 a UTF-8
- `main.cpp` — ejecuta y mide las 3 estrategias

## Cómo correr
1. Abrir en CLion (C++17).
2. Correr `Convertidor` primero (genera `dataset_utf8.txt`).
3. Correr `PracticaSorting`.

## Equipo
Camilo Estrada — Smith Tobon
