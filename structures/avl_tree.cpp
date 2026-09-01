#include "avl_tree.h" //Trae el strucut NODO AVL y la class AVLTREE con sus metodos Para que el compilador verifique que esta definición coincida con la firma del .h
#include <algorithm> // para std::max

int AVLTree::altura(NodoAVL* nodo) { //Devuelve la altura de un nodo
    if (nodo == nullptr){
        return 0; // por conv {encion,un arbol vacio tiene altura 0)
    }
    return nodo->altura; // si existe,devovlemos la altura guardada
}
    int AVLTree::factorBalance(NodoAVL* nodo) { // Calcula que tan desbalanceado esta un nodo,, difeencia entre la altura de su hijo izq  y derecho
        if (nodo == nullptr) {
            return 0; // nodo vacio, no hay ningun desbalance
        }
        return altura(nodo->izquierda) - altura(nodo->derecha);  //Positivo = pesa mas a la izquierda, negativo pesa mas a la derecha

    }

NodoAVL* AVLTree::rotarDerecha(NodoAVL* nodo) { //Rotacion a la derecha,se usa cunado el subarbol esta pesado a la izquierda.El hhijo izq sube a ser la nueva raiz
    NodoAVL* nuevaRaiz = nodo->izquierda; // Guardamos el hijo izquierdo de este nodo ,subira y se convertira en la nueva raiz del subarbol
    NodoAVL* subArbolTemporal = nuevaRaiz->derecha; //Guarda el hijo derecho de la nueva raiz.

    nuevaRaiz->derecha = nodo; // nodo baja a ser el hhijo derecho de nuevaraiz,nueva razi queda como la nuevaraiz de este pedazo de arbl
    nodo->izquierda = subArbolTemporal; //El subarbol encuentra su nuevo lugar como hijo izquierdo del noddo

    nodo->altura = 1 + std::max(altura(nodo->izquierda), altura(nodo->derecha)); // recalcula la altura del nodo primero,porq quedo mas abajo en el arbol
    nuevaRaiz->altura = 1 + std::max(altura(nuevaRaiz->izquierda), altura(nuevaRaiz->derecha)); // recalcula la altura de nuevaRaiz despues,porq depende d ela altura recien actualizada del nodo
    return nuevaRaiz; //devuelve nuevaraiz,q ahora es laraiz del subbarbol balanceado
}

NodoAVL* AVLTree::rotarIzquierda(NodoAVL* nodo) { //Rotacion a la izquierda,se usa cunado el subarbol esta pesado a la derecha.El hhijo der sube a ser la nueva raiz
    NodoAVL* nuevaRaiz = nodo->derecha; // Guardamos el hijo derecho de este nodo ,subira y se convertira en la nueva raiz del subarbol
    NodoAVL* subArbolTemporal = nuevaRaiz->izquierda; //Guarda el hijo izquierdo de la nueva raiz.

    nuevaRaiz->izquierda = nodo; // nodo baja a ser el hhijo izquierdo de nuevaraiz,nueva razi queda como la nuevaraiz de este pedazo de arbl
    nodo->derecha = subArbolTemporal; //El subarbol encuentra su nuevo lugar como hijo derecho del noddo

    nodo->altura = 1 + std::max(altura(nodo->izquierda), altura(nodo->derecha)); // recalcula la altura del nodo primero,porq quedo mas abajo en el arbol
    nuevaRaiz->altura = 1 + std::max(altura(nuevaRaiz->izquierda), altura(nuevaRaiz->derecha)); // recalcula la altura de nuevaRaiz despues,porq depende d ela altura recien actualizada del nodo
    return nuevaRaiz; //devuelve nuevaraiz,q ahora es laraiz del subbarbol balanceado
}


    NodoAVL* AVLTree::insertar(NodoAVL*nodo, const std::string& valor) { //Version Recursiva de insertar, busca el lugar correcto para valor,inserta y rebalancea,el arbol al vovler de la recursion
        if (nodo==nullptr) {
            //llegamos a un espacio vacio aqui va el nodo nuevo
            NodoAVL* nuevo = new NodoAVL(); // memoria pal heap,por eso es puntero
            nuevo->valor = valor;// Asigna la palabra al nuevo nodo
            nuevo->izquierda = nullptr; // Nodo nuevo s hoja : todavia no tiene hijo izquierdo
            nuevo->derecha = nullptr; // Tampoco tiene hijo derecho
            nuevo->altura = 1; // nodo nuevo =hoja= altura uno
            return nuevo; // devuele el nodo recien creado para q el nivel de recursion anterior lo enlace en el arbol
        }

        //Todavia no llegamos al espacio vacio,decidimos por donde seguir bajando
        if (valor < nodo-> valor) { // Si el valorr es menor que el de nodo actual,hay q bajar por la izquierda
            nodo->izquierda = insertar(nodo->izquierda,valor); // Reasignamos el resultado, insertar() , puede devolver un nodo nuevo o una raiz rotada, ,y hay que enlazarlo de vuelta al árbol
        } else {
            nodo->derecha = insertar(nodo->derecha,valor); //Si no,valor es mayor o igual, bajamos por la derecha
        }
        //algo se agregó debajo de este nodo,asi q su altura pudo cmabiar
        nodo->altura = 1 + std::max(altura(nodo->izquierda), altura(nodo->derecha));
        int balance = factorBalance(nodo); //Calcula q tan desbalanceado quedó este nodo despues de insertar

    if (balance > 1 && valor < nodo->izquierda->valor) {
        return rotarDerecha(nodo); // Desbalance a la izquierda, y el valor insertado quedó a la izquierda todavia,se arregl acon una rotacion a la derecha.
    }
    if (balance < -1 && valor >= nodo->derecha->valor) {
        return rotarIzquierda(nodo); // Desbaalnce a la derecha,yu el valor insertado quedó mas a la derecha todavia, se arregla con una sola rotacion a la izquierda
    }
    if (balance > 1 && valor >= nodo->izquierda->valor){
        nodo -> izquierda = rotarIzquierda(nodo->izquierda);
        return rotarDerecha(nodo); // Desbalance a la izquierda,pero el valor insertado quedó a la derecha del hijo izq,necesita doble rotacion,primero enderezamos el hijo izquierdo, y despues rotamos el  nodo a la derecha
    }
    if (balance < -1 && valor < nodo->derecha->valor) {
        nodo -> derecha = rotarDerecha(nodo->derecha);
        return rotarIzquierda(nodo); //Desbalance a la Derecha, pero el valor insertado quedó a la derecha del hijo der,necesita doble rotacion,primero enderezamos el hijo derecho, y despues rotamos el  nodo a la izquierda

    }
    return nodo; // Si no entró a ningun caso de arriba, el nodo ya estaba balanceado ,se devuelve tal cual entró

    }

    void AVLTree::insertar(const std::string& valor) { //Punto de entrada publico : llama a la version recursiva pasando la raiz actual
        raiz = insertar(raiz,valor); // arranca la recursion desde la raiz y guarda el resultado
    }

    void AVLTree::inorder(NodoAVL* nodo, std::vector<std::string>& resultado) { // Hace un recorrido inOrder , visita izq,luego nodo ,luego derecho, es un arbbol de busqueda entrega el orden alfabeticop
        if (nodo==nullptr) { //caso base : si el nodo es nulo no hay nada q recoger
            return; // nada q recoger
        }
        inorder(nodo->izquierda,resultado); // primero todo lo menor ,osea lo izquierdo
        resultado.push_back(nodo->valor); // luego nodo actual
        inorder(nodo->derecha, resultado); // luego todo lo mayor derecha
    }

    std::vector<std::string> AVLTree::obtenerOrdenado() { // Interfaz  publica: arma un vector vacio y lo llena con inorder,lo retorna ordenado
        std::vector<std::string> resultado; //Vector vacio donde se va a guardar el resultado ordenado
        inorder(raiz,resultado); // llena resultado recorriendo desde el arbol
        return resultado; //Devuelv eel vector ya lleno y ordenado
    }
