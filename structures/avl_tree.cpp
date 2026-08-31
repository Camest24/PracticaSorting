#include "avl_tree.h"
#include <algorithm> // para std:max

int AVLTree::altura(NodoAVL* nodo) {
    if (nodo == nullptr) {
        return 0; // arbol vacio si tiene altura 0
    }
    return nodo->altura; // si existe,devovlemos la altura guardada
}
    int AVLTree::factorBalance(NodoAVL* nodo) {
        if (nodo == nullptr) {
            return 0; // nodo vacio, no hay ningun ddesbalance
        }
        return altura(nodo->izquierda) - altura(nodo->derecha);
        //Positivo = pesa mas a la izquierda, negativo pesa mas a la derecha
    }

NodoAVL* AVLTree::rotarDerecha(NodoAVL* nodo) {
    NodoAVL* nuevaRaiz = nodo->izquierda;
    NodoAVL* subArbolTemporal = nuevaRaiz->derecha;

    nuevaRaiz->derecha = nodo;
    nodo->izquierda = subArbolTemporal;

    nodo->altura = 1 + std::max(altura(nodo->izquierda), altura(nodo->derecha));
    nuevaRaiz->altura = 1 + std::max(altura(nuevaRaiz->izquierda), altura(nuevaRaiz->derecha));
    return nuevaRaiz;
}

NodoAVL* AVLTree::rotarIzquierda(NodoAVL* nodo) {
    NodoAVL* nuevaRaiz = nodo->derecha;
    NodoAVL* subArbolTemporal = nuevaRaiz->izquierda;

    nuevaRaiz->izquierda = nodo;
    nodo->derecha = subArbolTemporal;

    nodo->altura = 1 + std::max(altura(nodo->izquierda), altura(nodo->derecha));
    nuevaRaiz->altura = 1 + std::max(altura(nuevaRaiz->izquierda), altura(nuevaRaiz->derecha));
    return nuevaRaiz;
}



    NodoAVL* AVLTree::insertar(NodoAVL*nodo, const std::string& valor) {
        if (nodo==nullptr) {
            //llegamos a un espacio vacio aqui va el nodo nuevo
            NodoAVL* nuevo = new NodoAVL(); // memoria pal heap,por eso es puntero
            nuevo->valor = valor;
            nuevo->izquierda = nullptr;
            nuevo->derecha = nullptr;
            nuevo->altura = 1; // modo nueva= hoja= altura uno
            return nuevo;
        }

        //Todavia no llegamos al espacio vacio,decidimos por donde seguir bajando
        if (valor < nodo-> valor) {
            nodo->izquierda = insertar(nodo->izquierda,valor); // reasignamos yasi el arbol por si asi decirlo,recuerda el nod onuevo
        } else {
            nodo->derecha = insertar(nodo->derecha,valor);
        }
        //algo se agregó debajo de este nodo,asi q su altura pudo cmabiar
        nodo->altura = 1 + std::max(altura(nodo->izquierda), altura(nodo->derecha));
        int balance = factorBalance(nodo);

    if (balance > 1 && valor < nodo->izquierda->valor) {
        return rotarDerecha(nodo);
    }
    if (balance < -1 && valor >= nodo->derecha->valor) {
        return rotarIzquierda(nodo);
    }
    if (balance > 1 && valor >= nodo->izquierda->valor){
        nodo -> izquierda = rotarIzquierda(nodo->izquierda);
        return rotarDerecha(nodo);
    }
    if (balance < -1 && valor < nodo->derecha->valor) {
        nodo -> derecha = rotarDerecha(nodo->derecha);
        return rotarIzquierda(nodo);
    }
    return nodo;

    }

    void AVLTree::insertar(const std::string& valor) {
        raiz = insertar(raiz,valor); // arranca la recursion desde la raiz y guarda el resultado
    }

    void AVLTree::inorder(NodoAVL* nodo, std::vector<std::string>& resultado) {
        if (nodo==nullptr) {
            return; // nada q recoger
        }
        inorder(nodo->izquierda,resultado); // primero todo lo menor ,osea lo izquierdo
        resultado.push_back(nodo->valor); // luego nodo actual
        inorder(nodo->derecha, resultado); // luego todo lo mayor derecha
    }

    std::vector<std::string> AVLTree::obtenerOrdenado() {
        std::vector<std::string> resultado;
        inorder(raiz,resultado); // llena resultado recorriendo desde el arbol
        return resultado;
    }
