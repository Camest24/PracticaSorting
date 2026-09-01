#include "quick_sort.h" // Trae la declaración de quickSort() Para que el compilador verifique que esta definición confirme con la firma del .h
    int partition(std::vector<std::string>& v, int inicio, int fin) // Partiition reorganiza v, de inicio a fin , alrededor de un piivote:,todo lo menor queda a la izquierda,todo mayor a la derecha y devuelve la posicion de donde quedo el pivote
    {
        std::string pivote= v[fin]; // Hacemos una copia del ultmo elemento del rango actual [inicio,fin] como pivote de referencia, se copia,no lo referenciamos, pa que no cambie si  luego movemos elementos
        int i = inicio-1; // i marca el limite de la región de elemtnos ya confirmados menores al pivote,arranca en iinicio-1 porque esa parte empieza vacia

        for (int j = inicio; j < fin; j++) { //Creamos un bucle for con la variable j, j recorre cada elemento ,justo antes de que llegue a fin porq, justo en fin es donde quedo guardado el pivote
            if (v[j] < pivote) { //Verifica si v[j] pertenece a la región de menores al pivote,si es el caso, hay que moverlo dentro de nuestra región
                i++; // Al confirmar la idea pasada, osea el elemento nuevo al pivote, la region de menores confirmados crece en uno, preparando la posición donde el elemento va a caer
                std::swap(v[i],v[j]); // e intercambiamos los valores, poniendo  los elementos nuevs dentro de la región
            }
        }
        std::swap(v[i+1],v[fin]); //Este intercambia lo que hay en la posicion i+1 por lo q hay en fin(pivote).Eso deja al pivote exactamente en la posicion final yaorrdenada porq i+1 es el punt odonde termino lo menor y emppezo lo mayor
        return i+1; // devuuelve ese numero,la posicion dodne quedo el pivote,a quien llamo a portition,solo informa

    }

    void quickSortRec(std::vector<std::string>& v, int inicio, int fin) // Aqui tratamos la recursion del quickSort,Este ordena recursivamente  v[inicio..fin]: usa partition, para ubicar el pivote y se llama asi misma sobre cada mitad
    {
        if (inicio >=fin) {  //El caso base, 0 o 1  elemento ya esta ordenado
            return;
        }
        int pivotIndex =partition(v,inicio,fin); // Guardamos la posicion final del pivote. Particiona v[inicio,fin] alrededor de u pivote y guarda la posicion
        quickSortRec(v,inicio,pivotIndex-1);  // Ordena recursivamnte todo lo que quedóa la derechá del pivote
        quickSortRec(v,pivotIndex+1,fin); //  LLama a quickSortRec,  sobre todo el vector(0 a size()-1).
    }

    void quickSort(std::vector<std::string>& v) {
    quickSortRec(v,0,static_cast<int>(v.size())-1); // Llama a quickSortRec con todo elvector,desde 0 hasta el ultimo.Convertido a int para evitar el problema de unsigned
    }