#pragma once
#include <string>
#include <vector>

// Un nodo del árbol: guarda la palabra, sus dos hijos, y su altura.
// Es un simple contenedor de datos, por eso es struct y no class (no necesita métodos).
struct NodoAVL {
    std:: string valor; // la palabra q guarda este nodo
    NodoAVL* izquierda; // puntero al hijo izquierdo
    NodoAVL* derecha; // puntero al hijo derecho
    int altura; //altua del subarbol q cuelga de este nodo
    // Con esto tenemos las bases para q sea O(Log n)
};

class AVLTree {
public:
    //Interfaz publica: lo unico q main.cpp usa
    void insertar(const std::string& valor); // mete una palabra al arbol
    std::vector<std::string> obtenerOrdenado();// devuelve todo ya ordenado

private:
    NodoAVL* raiz = nullptr; // la cabeza del arbol, arranca vacio por el nullptr
    // version recusriva de insertar: recibe el nodo actual y hace el trabajo real
    //la publica q pusimos arriba es solo la puerta de entrada,1 argumento
NodoAVL* insertar(NodoAVL* nodo,const std::string& valor);

    int altura(NodoAVL* nodo); // leemos la altura del nodo
    int factorBalance(NodoAVL* nodo); // altura izquierda- altura dereecha

    NodoAVL *rotarDerecha(NodoAVL* nodo); // reacomoda punteros cuando se desbalancea a la izquierda
    NodoAVL *rotarIzquierda(NodoAVL* nodo); // reacomoda punteros cuando se desbalancea a la derecha

    void inorder(NodoAVL* nodo,std::vector<std::string>& resultado); //recorrido izq-nodo-der


};