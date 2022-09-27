
#include "Conjunto.h"

template <class T>
Conjunto<T>::Conjunto() : _raiz(nullptr), _cardinal(0) {

}

template <class T>
Conjunto<T>::~Conjunto() { 
    destruir(this->_raiz);
}




template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    Nodo* n = this->_raiz;
    while (n != nullptr && clave != n->valor) {
        if (clave < n->valor) {
            n = n->izq;
        } else {
            n = n->der;
        }
    }
    return n != nullptr;
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    if (!this->pertenece(clave)){
        _cardinal++;
        Nodo* n = new Nodo(clave);
        this->insertar(n);
    }
}

template <class T>
void Conjunto<T>::remover(const T& elem) {
    if (pertenece(elem)) {
        _cardinal--;
        borrar(buscar(this->_raiz, elem));
    }
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    Nodo* n = this->sucesor(this->buscar(this->_raiz,clave));
    return n->valor;
}

template <class T>
const T& Conjunto<T>::minimo() const {
    Nodo* n = this->_raiz;
    while (n->izq != nullptr) {
        n = n->izq;
    }
    return n->valor;
}

template <class T>
const T& Conjunto<T>::maximo() const {
    Nodo* n = this->_raiz;
    while (n->der != nullptr) {
        n = n->der;
    }
    return n->valor;
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return this->_cardinal;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream& o) const {
    o << "{";
    Nodo* min = minimo(this->_raiz);
    Nodo* sig = sucesor(min);
    for (int i = 1; i <= this->_cardinal; ++i) {
        o << sig << ",";
        min = sig;
        sig = sucesor(min);
    }
    o << "}";
}

template<class T>
typename Conjunto<T>::Nodo* Conjunto<T>::buscar(Conjunto::Nodo *n, T v) {
    while (n != nullptr && v != n->valor) {
        if (v < n->valor) {
            n = n->izq;
        } else {
            n = n->der;
        }
    }
    return n;
}

template<class T>
typename Conjunto<T>::Nodo* Conjunto<T>::minimo(Conjunto::Nodo *n) {
    while (n->izq != nullptr) {
        n = n->izq;
    }
    return n;
}

template<class T>
typename Conjunto<T>::Nodo* Conjunto<T>::sucesor(Conjunto::Nodo *n) {
    if (n->der != nullptr) {
        return this->minimo(n->der);
    }
    Nodo* aux = n->padre;
    while (aux != nullptr && n == aux->der) {
        n = aux;
        aux = aux->padre;
    }
    return aux;
}

template<class T>
void Conjunto<T>::insertar(Conjunto::Nodo *n) {
    Nodo* y = nullptr;
    Nodo* x = this->_raiz;
    while (x != nullptr) {
        y = x;
        if (n->valor < x->valor) {
            x = x->izq;
        } else {
            x = x->der;
        }
    }
    n->padre = y;
    if (y == nullptr) {
        this->_raiz = n;
    } else if (n->valor < y->valor) {
        y->izq = n;
    } else {
        y->der = n;
    }
}

template <class T>
void Conjunto<T>::transplantar(Nodo *u, Nodo *v) {
    if (u->padre == nullptr){
        this->_raiz = v;
    } else if (u == u->padre->izq) {
        u->padre->izq = v;
    } else {
        u->padre->der = v;
    }
    if (v != nullptr) {
        v->padre = u->padre;
    }
}

template<class T>
void Conjunto<T>::borrar(Conjunto::Nodo *n) {
    if (n->izq == nullptr) {
        this->transplantar(n,n->der);
    } else if (n->der == nullptr) {
        this->transplantar(n, n->izq);
    } else {
        Nodo* aux = minimo(n->der);
        if (aux->padre != n) {
            this->transplantar(aux,aux->der);
            aux->der = n->der;
            aux->der->padre = aux;
        }
        this->transplantar(n,aux);
        aux->izq = n->izq;
        aux->izq->padre = aux;
    }
    delete n;
}

template <class T>
void Conjunto<T>::destruir(Nodo *n) {
    if (n != nullptr) {
        this->destruir(n->izq);
        this->destruir(n->der);
        delete n;
    }
}

template <class T>
Conjunto<T>::Nodo::Nodo(const T &v) : padre(nullptr), valor(v), izq(nullptr), der(nullptr) {}

template <class T>
Conjunto<T>::Nodo::~Nodo() {}
