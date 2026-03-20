//clase Torre 
#ifndef TORRE_H
#define TORRE_H

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

//  Estructura Torre
//  Representa una estructura defensiva colocada en el mapa

struct Torre {
    int    id;
    string nombre;
    string tipo;
    int    posicion;
    int    danio;
    int    rango;
    int    costo;
};


//  Clase ListaTorres
//  Lista secuencial

class ListaTorres {
private:
    static const int CAPACIDAD_MAX = 50;
    Torre datos[CAPACIDAD_MAX];
    int   cantidad;

public:
    // Constructor
    ListaTorres() : cantidad(0) {}


    //  Insertar una torre al final de la lista

    bool insertarTorre(int id, const string& nombre, const string& tipo,
                       int posicion, int danio, int rango, int costo) {
        if (cantidad >= CAPACIDAD_MAX) {
            cout << "[ERROR] Lista de torres llena.\n";
            return false;
        }
        // Verificar id duplicado
        if (buscarIndicePorId(id) != -1) {
            cout << "[ERROR] Ya existe una torre con id=" << id << ".\n";
            return false;
        }
        datos[cantidad] = {id, nombre, tipo, posicion, danio, rango, costo};
        cantidad++;
        cout << "[OK] Torre '" << nombre << "' registrada en posicion " << posicion << ".\n";
        return true;
    }


    //  Eliminar torre por id

    bool eliminarTorrePorId(int id) {
        int idx = buscarIndicePorId(id);
        if (idx == -1) {
            cout << "[ERROR] No se encontro torre con id=" << id << ".\n";
            return false;
        }
        // Desplazar elementos hacia la izquierda
        for (int i = idx; i < cantidad - 1; i++) {
            datos[i] = datos[i + 1];
        }
        cantidad--;
        cout << "[OK] Torre con id=" << id << " eliminada.\n";
        return true;
    }


    //  Buscar torre por id — devuelve puntero (nullptr si no existe)

    Torre* buscarPorId(int id) {
        int idx = buscarIndicePorId(id);
        if (idx == -1) return nullptr;
        return &datos[idx];
    }


    //  Mostrar todas las torres registradas

    void mostrarTorres() const {
        if (cantidad == 0) {
            cout << "  (No hay torres registradas)\n";
            return;
        }
        cout << left
             << setw(5)  << "ID"
             << setw(14) << "Nombre"
             << setw(12) << "Tipo"
             << setw(6)  << "Pos"
             << setw(7)  << "Danio"
             << setw(7)  << "Rango"
             << setw(7)  << "Costo"
             << "\n";
        cout << string(58, '-') << "\n";
        for (int i = 0; i < cantidad; i++) {
            const Torre& t = datos[i];
            cout << left
                 << setw(5)  << t.id
                 << setw(14) << t.nombre
                 << setw(12) << t.tipo
                 << setw(6)  << t.posicion
                 << setw(7)  << t.danio
                 << setw(7)  << t.rango
                 << setw(7)  << t.costo
                 << "\n";
        }
    }


    //  Contar torres activas

    int contarTorres() const {
        return cantidad;
    }


    //  Acceso al arreglo para la logica del juego

    const Torre& getTorre(int idx) const { return datos[idx]; }

private:
    // Devuelve el indice interno o -1 si no existe
    int buscarIndicePorId(int id) const {
        for (int i = 0; i < cantidad; i++) {
            if (datos[i].id == id) return i;
        }
        return -1;
    }
};

#endif 
