//clase Enemigo 
#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct NodoEnemigo {
    // Datos del enemigo
    int    id;
    string tipo;
    int    vida;
    int    velocidad;
    int    posicion;
    int    recompensa;

    // Punteros de la lista doblemente enlazada
    NodoEnemigo* anterior;
    NodoEnemigo* siguiente;

    // Constructor
    NodoEnemigo(int id, const string& tipo, int vida,
                int velocidad, int posicion, int recompensa)
        : id(id), tipo(tipo), vida(vida), velocidad(velocidad),
          posicion(posicion), recompensa(recompensa),
          anterior(nullptr), siguiente(nullptr) {}
};


class ListaEnemigos { //  Lista doblemente enlazada con punteros a primero y ultimo
private:
    NodoEnemigo* primero;
    NodoEnemigo* ultimo;
    int          cantidad;

public:
    // Constructor
    ListaEnemigos() : primero(nullptr), ultimo(nullptr), cantidad(0) {}

    // libera memoria dinamica
    ~ListaEnemigos() {
        NodoEnemigo* actual = primero;
        while (actual != nullptr) {
            NodoEnemigo* temp = actual->siguiente;
            delete actual;
            actual = temp;
        }
    }

    //  Insertar enemigo al final de la lista
    void insertarAlFinal(int id, const string& tipo, int vida,
                         int velocidad, int posicion, int recompensa) {
        NodoEnemigo* nuevo = new NodoEnemigo(id, tipo, vida,
                                             velocidad, posicion, recompensa);
        if (ultimo == nullptr) {
            // Lista vacia
            primero = nuevo;
            ultimo  = nuevo;
        } else {
            nuevo->anterior  = ultimo;
            ultimo->siguiente = nuevo;
            ultimo           = nuevo;
        }
        cantidad++;
    }

    //  Eliminar enemigo destruido por id
    //  Retorna la recompensa del enemigo eliminado (0 si no existe)
    int eliminarPorId(int id) {
        NodoEnemigo* nodo = buscarPorId(id);
        if (nodo == nullptr) return 0;

        int recompensa = nodo->recompensa;

        // Reconectar nodos vecinos
        if (nodo->anterior != nullptr)
            nodo->anterior->siguiente = nodo->siguiente;
        else
            primero = nodo->siguiente;   // era el primero

        if (nodo->siguiente != nullptr)
            nodo->siguiente->anterior = nodo->anterior;
        else
            ultimo = nodo->anterior;     // era el ultimo

        delete nodo;
        cantidad--;
        return recompensa;
    }

    //  Buscar enemigo por id  
    NodoEnemigo* buscarPorId(int id) const {
        NodoEnemigo* actual = primero;
        while (actual != nullptr) {
            if (actual->id == id) return actual;
            actual = actual->siguiente;
        }
        return nullptr;
    }

    //  Recorrer hacia adelante (primero -> ultimo)
    void recorrerAdelante() const {
        if (primero == nullptr) {
            cout << "  (No hay enemigos activos)\n";
            return;
        }
        cout << left
             << setw(5)  << "ID"
             << setw(14) << "Tipo"
             << setw(7)  << "Vida"
             << setw(6)  << "Vel"
             << setw(6)  << "Pos"
             << setw(10) << "Recompensa"
             << "\n";
        cout << string(48, '-') << "\n";
        NodoEnemigo* actual = primero;
        while (actual != nullptr) {
            cout << left
                 << setw(5)  << actual->id
                 << setw(14) << actual->tipo
                 << setw(7)  << actual->vida
                 << setw(6)  << actual->velocidad
                 << setw(6)  << actual->posicion
                 << setw(10) << actual->recompensa
                 << "\n";
            actual = actual->siguiente;
        }
    }

    //  Recorrer hacia atras (ultimo -> primero)
    void recorrerAtras() const {
        if (ultimo == nullptr) {
            cout << "  (No hay enemigos activos)\n";
            return;
        }
        cout << "[Recorrido inverso]\n";
        NodoEnemigo* actual = ultimo;
        while (actual != nullptr) {
            cout << "  Enemigo id=" << actual->id
                 << " tipo=" << actual->tipo
                 << " pos="  << actual->posicion
                 << " vida=" << actual->vida << "\n";
            actual = actual->anterior;
        }
    }

    //  Actualizar posicion de todos los enemigos en un turno
    //  Retorna cuantos enemigos llegaron al final del camino
    int avanzarEnemigos(int posicionFinal) {
        int llegaron = 0;
        NodoEnemigo* actual = primero;
        while (actual != nullptr) {
            actual->posicion += actual->velocidad;
            if (actual->posicion >= posicionFinal) {
                llegaron++;
            }
            actual = actual->siguiente;
        }
        return llegaron;
    }

    //  Eliminar todos los enemigos que llegaron al final
    //  Retorna cuantos se eliminaron
    int eliminarQueTerminaron(int posicionFinal) {
        int eliminados = 0;
        NodoEnemigo* actual = primero;
        while (actual != nullptr) {
            NodoEnemigo* siguiente = actual->siguiente;
            if (actual->posicion >= posicionFinal) {
                eliminarPorId(actual->id);
                eliminados++;
            }
            actual = siguiente;
        }
        return eliminados;
    }

    //  Getters 
    bool          estaVacia()  const { return primero == nullptr; }
    int           getCantidad() const { return cantidad; }
    NodoEnemigo*  getPrimero()  const { return primero; }
    NodoEnemigo*  getUltimo()   const { return ultimo; }
};

#endif 
