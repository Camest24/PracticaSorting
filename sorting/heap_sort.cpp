#include "heap_sort.h"  //Trae la declaración del heapSort() Para que el compilador verifique que esta definición confirme con la firma del .h

void heapify(std::vector<std::string>& v, int n, int i) { //Acomoda el valor de la posicion i bajandolo a su lugar si hace falta,asumiendo que  los hijos ya son heaps validos
    int mayor = i; //Arranca asumiiendo quie el nodo actual es el mas grande de los 3
    int izquierda = 2 * i + 1; //  la formula para encontrar el hijo izquierdo en el array
    int derecha = 2 * i + 2;  //  la formula para encontrar el hijo derecho en el array

    if (izquierda < n && v[izquierda] > v[mayor]) { //Si el hijo izquierdo existe y es mayor q el actual "mayor", pasa a ser el nuevo candidato
        mayor = izquierda;
    }
    if (derecha < n && v[derecha] > v[mayor]) { //Igual que el caso de arriba pero compara contra "mayor" ya actualizado, no contra i directamente
        mayor = derecha;
    }

    if (mayor != i) {
        std::swap(v[i], v[mayor]); // Intercambia i con el hijo mas grande, bajando el valor pequeño un nivelk
        heapify(v, n, mayor); //Vuelve a llamar heapify en la nueva posicion del valor movido,por sii en caaso sigue violando la regla del heap mas abajo
    }
}

void heapSort(std::vector<std::string>& v) { //Orsdena el vector completo en 2 fases,construye un max-hheap luego extrae el maximo para armar el orden
    int n = static_cast<int>(v.size()); //Convierte el tamaño del vector a int, igual q en quickSort, para evitar posibles unsigned

    // Fase 1: construen ir el max-heap. Se arranca en n/2-1 porque
    // todo lo que está después de ese índice ya es hoja
    for (int i = n / 2 - 1; i >= 0; i--) { // Recorre los nodos internos, de atras hacia adelante hasta llegar a la raiz
        heapify(v, n, i);// Arregla el heap en el nodo i, asumiendo q sus hijos ya son heaps validos
    }

    // Fase 2: extraer el máximo (índice 0) repetidamente.
    // Se reduce el "tamaño activo" del heap (i) en cada vuelta, pero
    // el vector completo sigue existiendo — solo se deja de tocar la cola.
    for (int i = n - 1; i > 0; i--) { // Recorre desde el final hasta el indice 1 , cuando solo queda 1 elemento activo,todo esta en su lugar, por descarte no hay con q otra cosa compararlo
        std::swap(v[0], v[i]);  // Intercambia el maximo actual con el ultimo elemento, v0 con vi,dejandolo ordenado
        heapify(v, i, 0); // Vuelve a acomodar el heap desde la raiz con tamaño activo i
    }
}