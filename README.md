# Práctica I — Sorting Large Dataset

**Estructuras de Datos y Algoritmos (ST0245) — EAFIT**
Equipo: Camilo Estrada, Smith  Tobon

## Descripción

Programa en C++17 que ordena una colección de 100,000 palabras usando tres estrategias implementadas desde cero (sin `std::sort` ni ninguna librería externa de ordenamiento):

1. **QuickSort** — sobre `std::vector<std::string>`, partición de Lomuto (pivote = último elemento).
2. **HeapSort** — con un Binary Heap propio (sin usar `std::priority_queue`).
3. **Árbol AVL** — inserción balanceada + recorrido inorder para obtener el orden final.

Cada estrategia mide su tiempo real de ejecución (`std::chrono`) y su uso aproximado de memoria (`sizeof`), y los resultados se comparan contra la complejidad Big O teórica de cada una.

## El problema del dataset (UTF-16 → UTF-8)

El dataset (`data/dataset.txt`) fue entregado por el profesor en **UTF-16** (codificación típica del Notepad de Windows). Un `ifstream` normal en C++ lo interpreta mal — aparece un byte nulo (`0x00`) intercalado entre cada letra, porque en UTF-16LE los caracteres ASCII ocupan 2 bytes (el byte útil + un byte en 0).

Para solucionarlo se escribió `tools/convertir_utf8.cpp`, que:
- Lee el archivo en modo binario (`std::ios::binary`).
- Detecta y descarta el BOM (`0xFF 0xFE`).
- Toma solo el byte bajo de cada par de 2 bytes (para caracteres ASCII, el byte alto en UTF-16LE siempre es `0x00`).
- Elimina los `\r` sobrantes (el archivo original tiene saltos de línea `CRLF`).
- Escribe el resultado limpio en `data/dataset_utf8.txt`, en UTF-8 estándar, listo para ser leído con un `ifstream` normal.

El dataset ya viene con las 100,000 palabras en orden aleatorio (no alfabético), así que no fue necesario aleatorizarlo aparte.

## Estructura del proyecto

```
PracticaSorting/
├── CMakeLists.txt
├── main.cpp                     # corre las 3 estrategias, mide tiempo y memoria
├── data/
│   ├── dataset.txt              # original, UTF-16
│   └── dataset_utf8.txt         # convertido, UTF-8
├── tools/
│   └── convertir_utf8.cpp       # conversor UTF-16 -> UTF-8
├── sorting/
│   ├── quick_sort.h / .cpp      # QuickSort (partición de Lomuto)
│   └── heap_sort.h / .cpp       # HeapSort (heap binario propio)
├── structures/
│   └── avl_tree.h / .cpp        # Árbol AVL con rebalanceo automático
├── documentation/
│   └── Informe_PracticaSorting_final.pdf
└── visualizador.html            # herramienta interactiva de repaso (no es parte del entregable evaluado)
```

## Cómo compilar y correr (CLion)

1. Abrir el proyecto en CLion (requiere C++17, CMake ≥ 3.x).
2. Correr primero la configuración **Convertidor** — genera `data/dataset_utf8.txt` a partir de `data/dataset.txt`.
3. Correr la configuración **PracticaSorting** — ejecuta las 3 estrategias sobre el dataset ya convertido, imprime tiempos y memoria en consola.

> Cada Run Configuration necesita su *Working Directory* apuntando a la raíz del proyecto, para que las rutas relativas a `data/` funcionen.

## Algoritmos

### QuickSort

`partition` recorre el subarreglo con dos punteros (`i`, `j`), usa el último elemento como pivote, y reorganiza el arreglo para que todo lo menor o igual al pivote quede a su izquierda y todo lo mayor a su derecha — devolviendo la posición final del pivote. `quickSortRec` llama a `partition` y se invoca recursivamente sobre las dos mitades resultantes.

- **Mejor/caso promedio:** O(n log n) — con datos aleatorios, el pivote fijo (último elemento) tiende a caer cerca del centro del rango de valores, dando particiones balanceadas.
- **Peor caso:** O(n²) — ocurre si el arreglo ya está ordenado (o en orden inverso), porque el pivote fijo termina siendo siempre el extremo, dando la partición más desbalanceada posible en cada llamada.
- **Memoria:** ordena in-place sobre el mismo `std::vector<std::string>`, sin estructuras extra (aparte de la pila de recursión).

### HeapSort

El arreglo se trata como un árbol binario completo, usando aritmética de índices: el nodo en la posición `i` tiene hijos en `2i+1` y `2i+2`. `heapify` compara un nodo con sus dos hijos y, si alguno es mayor, lo sube (swap) y repite el proceso en la nueva posición (sift-down). `heapSort` tiene dos fases:

1. **Construcción del heap máximo:** llama `heapify` desde `n/2-1` (el último nodo con hijos) hasta la raíz, para que cada nodo procesado ya tenga sus hijos como heaps válidos.
2. **Extracción repetida:** intercambia la raíz (el máximo) con el último elemento del heap activo, reduce el tamaño del heap en 1, y vuelve a llamar `heapify` sobre la raíz.

- **Complejidad:** O(n log n) garantizado, sin peor caso — a diferencia de QuickSort, no depende del orden de entrada.
- **Memoria:** ordena in-place, sin estructura adicional.
- **Nota de rendimiento:** en la práctica resultó ser el más lento de los tres pese a su garantía de Big O, por localidad de memoria — accede a posiciones dispersas del arreglo (`2i+1`, `2i+2`), generando más *cache misses* que un recorrido secuencial.

### Árbol AVL

`NodoAVL` guarda la palabra, dos punteros a sus hijos, y su propia altura. `AVLTree::insertar` es recursiva: baja por el árbol comparando valores (igual que un BST normal), inserta el nuevo nodo, y al volver de la recursión recalcula altura y factor de balance (`altura(izquierda) - altura(derecha)`) en cada nodo del camino. Si el balance se rompe (`> 1` o `< -1`), se identifica uno de los 4 casos de rebalanceo (Izquierda-Izquierda, Derecha-Derecha, Izquierda-Derecha, Derecha-Izquierda) y se aplica la rotación correspondiente (`rotarDerecha`, `rotarIzquierda`, o ambas). `obtenerOrdenado` hace un recorrido inorder (izquierda-nodo-derecha) para devolver las palabras ya ordenadas.

- **Complejidad:** O(log n) por inserción garantizado (altura del árbol siempre acotada), O(n) el recorrido inorder final.
- **Memoria:** requiere un nodo por palabra (puntero izquierda + puntero derecha + altura + la palabra), más overhead que un `std::vector` plano.
- **Por qué AVL y no un BST simple:** un BST sin balanceo puede degenerarse en una lista enlazada en el peor caso (por ejemplo, si los datos llegaran en orden), volviendo las operaciones O(n). AVL garantiza O(log n) siempre, rebalanceándose automáticamente tras cada inserción.
- **Por qué AVL y no Red-Black:** AVL mantiene un balance más estricto (diferencia de altura máxima de 1, contra hasta 2 en Red-Black), dando búsquedas/recorridos ligeramente más rápidos a cambio de más rotaciones en la inserción — conveniente aquí porque se inserta una vez y se consulta con el inorder al final.

## Resultados (promedio de 5 corridas)

| Estrategia | Tiempo promedio | Memoria aproximada |
|---|---|---|
| QuickSort | 187 ms | 3,200,000 bytes (100,000 × `sizeof(std::string)`=32B) |
| Árbol AVL | 130 ms | 5,600,000 bytes (100,000 × `sizeof(NodoAVL)`=56B) |
| HeapSort | 297 ms | 3,200,000 bytes (mismo vector, in-place) |

Entorno de pruebas: Intel Core i5-11400H (11a gen, 6 núcleos, 2.70GHz), 24GB RAM, Windows, GCC 15.2.0 (MinGW-w64) vía CLion.

Las tres estrategias produjeron el mismo orden final correcto (`std::is_sorted` = true), desde `"a"` hasta `"zyzzogeton"`.

## Comparación teoría vs práctica

Aunque HeapSort tiene la mejor garantía teórica (O(n log n) sin peor caso), fue el más lento en la práctica. La razón no está en el Big O sino en el hardware: QuickSort accede al arreglo de forma mayormente secuencial (aprovecha el *prefetching* del CPU y la caché), mientras que HeapSort salta constantemente entre índices lejanos (`i` → `2i+1` → `2i+2`), generando muchos más *cache misses*. El AVL, aunque también usa punteros dispersos, gana porque cada inserción solo recorre un camino angosto (~17 niveles para 100,000 palabras, log₂(100,000)) y las rotaciones son eventos poco frecuentes — mucho menos trabajo total que las repetidas extracciones de HeapSort.

## Informe

El análisis completo (enfoque de implementación, mediciones detalladas, comparación teoría vs práctica, y conclusiones) está en [`documentation/Informe_PracticaSorting_final.pdf`](documentation/Informe_PracticaSorting_final.pdf).
