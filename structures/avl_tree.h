#pragma once // header guard,evita q el archivo se incluya 2 veces por accidente y rompa la compilación.
#include <vector> //incluye el header que define std::vector,define la plantilla std:vector
#include <string> //incluye el header que define std::string,osea el tipo de dato que guarda cada palabra dentro del vector

// Un nodo del árbol: guarda la palabra, sus dos hijos, y su altura.
// Es un struct por convencioin de c++, struct y class son casi iguales,pero usamos structu porq es un contenedor simple donde toddo debe ser acceible directamente
struct NodoAVL {
    std:: string valor; // la palabra q guarda este nodo
    NodoAVL* izquierda; // puntero al hijo izquierdo
    NodoAVL* derecha; // puntero al hijo derecho
    int altura; //altua del subarbol q cuelga de este nodo
    // Guardar la altrua acá, permite oonsultarla en O(1) : lo q realmente garantisa O(Log n) es que las rotacionews mantienen el arbol balanceado
};

class AVLTree { //Arbol AVL autobalanceado : inserta palabras y las entrega via recorrer in order
public:
    //Interfaz publica: lo unico q main.cpp usa
    void insertar(const std::string& valor); // mete una palabra al arbol
    std::vector<std::string> obtenerOrdenado();// devuelve todo ya ordenado

private:
    NodoAVL* raiz = nullptr; // la cabeza del arbol, arranca vacio por el nullptr
    // version recusriva de insertar: recibe el nodo actual y hace el trabajo real
    // version recursiva de insertar:  sobrecarga de funión, mismo nombre, distintos pparametros
NodoAVL* insertar(NodoAVL* nodo,const std::string& valor);

    int altura(NodoAVL* nodo); // Devuelve la altura del nodo, si es nullptr devuelve 0 en vez de fallar ,asi otras funciones pueden usarla sin revisar
    int factorBalance(NodoAVL* nodo); // altura izquierda- altura dereecha

    NodoAVL *rotarDerecha(NodoAVL* nodo); // reacomoda punteros cuando se desbalancea a la izquierda
    NodoAVL *rotarIzquierda(NodoAVL* nodo); // reacomoda punteros cuando se desbalancea a la derecha

    void inorder(NodoAVL* nodo,std::vector<std::string>& resultado); //recorrido izq-nodo-der


};