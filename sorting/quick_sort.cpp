#include "quick_sort.h"

    int partition(std::vector<std::string>& v, int inicio, int fin)
    {
        std::string pivote = v[fin];
        int i = inicio -1;

        for (int j = inicio; j < fin; j++) {
            if (v[j] < pivote) {
                i++;
                std::swap(v[i],v[j]);
            }
        }
        std::swap(v[i+1],v[fin]);
        return i+1;

    }

    void quickSortRec(std::vector<std::string>& v, int inicio, int fin) //Si inicio es mayor o igual o fin no hay nada q ordenar,solo devuelve return
    {
        if (inicio >=fin) {
            return;
        }
        int pivotIndex =partition(v,inicio,fin);
        quickSortRec(v,inicio,pivotIndex-1);
        quickSortRec(v,pivotIndex+1,fin);
    }

    void quickSort(std::vector<std::string>& v) {
    quickSortRec(v,0,static_cast<int>(v.size())-1);
    }