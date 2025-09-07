#ifndef NODO_H
#define NODO_H

#include <iostream>

template <class T>
class Nodo {
private:
    T x;
    Nodo* sig;

public:
    // Constructors
    Nodo();
    Nodo(T value);

    // Member functions
    void print() const;
    void modificarElem(T e);
    void modificarSig(Nodo* n);

    // Overloaded assignment operator
    Nodo& operator=(const Nodo& p);

    T consultarE() const;
    Nodo* consultarSig() const;

    // Friend class declaration for Lista
    template <class U> friend class Lista;
};

template <class T>
Nodo<T>::Nodo() : x(), sig(nullptr) {}

template <class T>
Nodo<T>::Nodo(T value) : x(value), sig(nullptr) {}

template <class T>
void Nodo<T>::print() const {
    std::cout << "||" << x << "||" << "->";
}

template <class T>
T Nodo<T>::consultarE() const {
    return x;
}

template <class T>
Nodo<T>* Nodo<T>::consultarSig() const {
    return sig;
}

template <class T>
void Nodo<T>::modificarElem(T e) {
    x = e;
}

template <class T>
void Nodo<T>::modificarSig(Nodo<T>* n) {
    sig = n;
}

template <class T>
Nodo<T>& Nodo<T>::operator=(const Nodo<T>& p) {
    if (this != &p) {
        x = p.x;
        sig = p.sig;
    }
    return *this;
}

#endif // NODO_H