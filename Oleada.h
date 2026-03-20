#ifndef OLEADA_H
#define OLEADA_H

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

//  Nodo de la lista simplemente enlazada circular
struct NodoOleada {
    int          idOleada;
    int          cantidadEnemigos;
    string       tipoEnemigo;
    int          vidaBase;
    int          velocidadBase;
    NodoOleada*  siguiente;   // En la circular, el ultimo apunta al primero

    NodoOleada(int id, int cantidad, const string& tipo, int vida, int vel)
        : idOleada(id), cantidadEnemigos(cantidad), tipoEnemigo(tipo),
          vidaBase(vida), velocidadBase(vel), siguiente(nullptr) {}
};

//  Clase ListaOleadas
//  Lista simplemente enlazada circular con referencia al ULTIMO
//  (el puntero a ultimo->siguiente siempre apunta al primero)

class ListaOleadas {
private:
    NodoOleada* ultimo;       // Puntero al ultimo nodo
    NodoOleada* actual;       // Puntero a la oleada en curso
    int         totalOleadas;
    int         oleadaActualIdx; // Indice para mostrar progreso

public:
    // Constructor
    ListaOleadas()
        : ultimo(nullptr), actual(nullptr),
          totalOleadas(0), oleadaActualIdx(0) {}

    // Destructor
    ~ListaOleadas() {
        if (ultimo == nullptr) return;
        // Romper la circularidad antes de liberar
        NodoOleada* primero = ultimo->siguiente;
        ultimo->siguiente = nullptr;
        NodoOleada* nodo = primero;
        while (nodo != nullptr) {
            NodoOleada* temp = nodo->siguiente;
            delete nodo;
            nodo = temp;
        }
    }

    //  Registrar una nueva oleada (inserta al final)
    void registrarOleada(int id, int cantidad, const string& tipo,
                         int vida, int vel) {
        NodoOleada* nuevo = new NodoOleada(id, cantidad, tipo, vida, vel);
        if (ultimo == nullptr) {
            // Primera oleada: apunta a si misma
            ultimo           = nuevo;
            ultimo->siguiente = nuevo;
            actual           = nuevo;
            oleadaActualIdx  = 1;
        } else {
            // Insertar despues del ultimo y antes del primero
            nuevo->siguiente  = ultimo->siguiente; // nuevo->sig = primero
            ultimo->siguiente = nuevo;             // ultimo->sig = nuevo
            ultimo            = nuevo;             // ultimo = nuevo
        }
        totalOleadas++;
        cout << " ok Oleada " << id << " registrada ("
             << cantidad << " " << tipo << ").\n";
    }

    //  Mostrar todas las oleadas empezando desde la primera

    void mostrarOleadas() const {
        if (ultimo == nullptr) {
            cout << "  (No hay oleadas registradas)\n";
            return;
        }
        NodoOleada* primero = ultimo->siguiente;
        NodoOleada* nodo    = primero;

        cout << left
             << setw(8)  << "ID"
             << setw(10) << "Cantidad"
             << setw(16) << "TipoEnemigo"
             << setw(10) << "VidaBase"
             << setw(12) << "VelBase"
             << "\n";
        cout << string(56, '-') << "\n";
        do {
            // Marcar la oleada actual con un indicador
            string marcador = (nodo == actual) ? " <-- ACTUAL" : "";
            cout << left
                 << setw(8)  << nodo->idOleada
                 << setw(10) << nodo->cantidadEnemigos
                 << setw(16) << nodo->tipoEnemigo
                 << setw(10) << nodo->vidaBase
                 << setw(12) << nodo->velocidadBase
                 << marcador << "\n";
            nodo = nodo->siguiente;
        } while (nodo != primero);
    }
 o
    //  Avanzar a la siguienteleada (aprovecha la circularidad)
    NodoOleada* avanzarSiguienteOleada() {
        if (actual == nullptr) return nullptr;
        actual = actual->siguiente;
        oleadaActualIdx++;
        if (oleadaActualIdx > totalOleadas) oleadaActualIdx = 1;
        return actual;
    }

    //  Reiniciar el ciclo desde la primera oleada
    void reiniciarCiclo() {
        if (ultimo == nullptr) return;
        actual          = ultimo->siguiente; // apunta al primero
        oleadaActualIdx = 1;
        cout << "[OK] Ciclo de oleadas reiniciado desde la primera oleada.\n";
    }

    //  Getters utiles
    NodoOleada* getActual()      const { return actual; }
    int         getTotalOleadas() const { return totalOleadas; }
    bool        hayOleadas()      const { return ultimo != nullptr; }
    int         getIndiceActual() const { return oleadaActualIdx; }
};

#endif 
