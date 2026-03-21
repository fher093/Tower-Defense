#ifndef JUEGO_H
#define JUEGO_H

#include "Torre.h"
#include "Enemigo.h"
#include "Oleada.h"
#include <iostream>
#include <string>
using namespace std;

//Clase juego
class Juego {
private:
    ListaTorres   torres;
    ListaEnemigos enemigos;
    ListaOleadas  oleadas;

    int vidasJugador;
    int turnoActual;
    int oroPosesido;
    int siguienteIdEnemigo;

    static const int POS_FINAL    = 20;
    static const int VIDAS_INICIO = 3;

public:
    Juego()
        : vidasJugador(VIDAS_INICIO), turnoActual(0),
          oroPosesido(200), siguienteIdEnemigo(1) {}


    //  Gestion de Torres  


    void registrarTorre() {
        int    id, pos, danio, rango, costo;
        string nombre, tipo;

        cout << "\n--- Registrar Torre ---\n";
        cout << "ID        : "; cin >> id;
        cin.ignore();
        cout << "Nombre    : "; getline(cin, nombre);
        cout << "Tipo      : "; getline(cin, tipo);
        cout << "Posicion (0-" << POS_FINAL << "): "; cin >> pos;
        cout << "Danio     : "; cin >> danio;
        cout << "Rango     : "; cin >> rango;
        cout << "Costo     : "; cin >> costo;

        if (costo > oroPosesido) {
            cout << "[ERROR] No tienes suficiente oro ("
                 << oroPosesido << "). La torre cuesta " << costo << ".\n";
            return;
        }
        if (torres.insertarTorre(id, nombre, tipo, pos, danio, rango, costo)) {
            oroPosesido -= costo;
            cout << "  Oro restante: " << oroPosesido << "\n";
        }
    }

    void mostrarTorres() {
        cout << "\n--- Torres Registradas (" << torres.contarTorres() << ") ---\n";
        torres.mostrarTorres();
    }

    void eliminarTorre() {
        int id;
        cout << "\n--- Eliminar Torre ---\n";
        cout << "ID de la torre a eliminar: "; cin >> id;
        torres.eliminarTorrePorId(id);
    }


    //  Gestion de Oleadas  (Autor principal: LESLIE)


    void registrarOleada() {
        int    id, cantidad, vida, vel;
        string tipo;

        cout << "\n--- Registrar Oleada ---\n";
        cout << "ID oleada          : "; cin >> id;
        cin.ignore();
        cout << "Tipo de enemigo    : "; getline(cin, tipo);
        cout << "Cantidad enemigos  : "; cin >> cantidad;
        cout << "Vida base          : "; cin >> vida;
        cout << "Velocidad base     : "; cin >> vel;

        oleadas.registrarOleada(id, cantidad, tipo, vida, vel);
    }

    void mostrarOleadas() {
        cout << "\n--- Oleadas Registradas ---\n";
        oleadas.mostrarOleadas();
    }

    void iniciarSiguienteOleada() {
        if (!oleadas.hayOleadas()) {
            cout << "[ERROR] No hay oleadas registradas.\n";
            return;
        }
        NodoOleada* oleadaActual = oleadas.getActual();
        if (oleadaActual == nullptr) {
            cout << "[ERROR] No hay oleada activa.\n";
            return;
        }

        cout << "\n[OLEADA " << oleadaActual->idOleada
             << "] Lanzando " << oleadaActual->cantidadEnemigos
             << " " << oleadaActual->tipoEnemigo << "...\n";

        for (int i = 0; i < oleadaActual->cantidadEnemigos; i++) {
            int posInicial = -(i * 2);
            enemigos.insertarAlFinal(
                siguienteIdEnemigo++,
                oleadaActual->tipoEnemigo,
                oleadaActual->vidaBase,
                oleadaActual->velocidadBase,
                posInicial,
                oleadaActual->vidaBase / 5 + 10
            );
        }

        oleadas.avanzarSiguienteOleada();
        cout << "[OK] Oleada activa: " << oleadas.getIndiceActual()
             << " / " << oleadas.getTotalOleadas() << "\n";
    }


    //   Logica de turno 


    void avanzarTurno() {
        turnoActual++;
        cout << "\n========== TURNO " << turnoActual << " ==========\n";

        if (enemigos.estaVacia()) {
            cout << "  No hay enemigos activos en este turno.\n";
            return;
        }

        // Paso 1: Mover todos los enemigos
        NodoEnemigo* e = enemigos.getPrimero();
        while (e != nullptr) {
            e->posicion += e->velocidad;
            e = e->siguiente;
        }
        cout << "[1] Enemigos movidos segun su velocidad.\n";

        // Paso 2: Torres atacan a enemigos en rango
        cout << "[2] Fase de ataque de torres:\n";
        int total = torres.contarTorres();
        for (int t = 0; t < total; t++) {
            const Torre& torre = torres.getTorre(t);
            NodoEnemigo* en = enemigos.getPrimero();
            while (en != nullptr) {
                int dist = en->posicion - torre.posicion;
                if (dist >= 0 && dist <= torre.rango) {
                    en->vida -= torre.danio;
                    cout << "    Torre [" << torre.nombre << "] (pos "
                         << torre.posicion << ") ataca a Enemigo "
                         << en->id << " -- vida restante: "
                         << max(0, en->vida) << "\n";
                }
                en = en->siguiente;
            }
        }

        // Paso 3: Eliminar enemigos con vida <= 0
        cout << "[3] Bajas del turno:\n";
        NodoEnemigo* actual = enemigos.getPrimero();
        while (actual != nullptr) {
            NodoEnemigo* sig = actual->siguiente;
            if (actual->vida <= 0) {
                cout << "    Enemigo " << actual->id
                     << " (" << actual->tipo << ") destruido. +"
                     << actual->recompensa << " oro\n";
                oroPosesido += actual->recompensa;
                enemigos.eliminarPorId(actual->id);
            }
            actual = sig;
        }

        // Paso 4: Enemigos que llegaron al final
        cout << "[4] Enemigos que alcanzaron la base:\n";
        actual = enemigos.getPrimero();
        while (actual != nullptr) {
            NodoEnemigo* sig = actual->siguiente;
            if (actual->posicion >= POS_FINAL) {
                vidasJugador--;
                cout << "    [!] Enemigo " << actual->id
                     << " (" << actual->tipo
                     << ") alcanzo la base! Vidas restantes: "
                     << vidasJugador << "\n";
                enemigos.eliminarPorId(actual->id);
            }
            actual = sig;
        }

        // Resumen
        cout << "\n  >> Fin del turno " << turnoActual
             << "  |  Enemigos vivos: " << enemigos.getCantidad()
             << "  |  Vidas: "          << vidasJugador
             << "  |  Oro: "            << oroPosesido << "\n";

        if (vidasJugador <= 0) {
            cout << "\n*** GAME OVER *** Todas las vidas perdidas.\n";
        }
    }


    // Consultas y estado general


    void mostrarEnemigosActivos() {
        cout << "\n--- Enemigos Activos (" << enemigos.getCantidad() << ") ---\n";
        cout << "[Recorrido adelante]\n";
        enemigos.recorrerAdelante();
        cout << "\n";
        enemigos.recorrerAtras();
    }

    void mostrarEstadoGeneral() {
        cout << "\n========= ESTADO GENERAL =========\n";
        cout << "  Turno actual   : " << turnoActual           << "\n";
        cout << "  Vidas          : " << vidasJugador          << "\n";
        cout << "  Oro            : " << oroPosesido           << "\n";
        cout << "  Torres activas : " << torres.contarTorres() << "\n";
        cout << "  Enemigos vivos : " << enemigos.getCantidad()<< "\n";
        if (oleadas.hayOleadas()) {
            cout << "  Oleada en curso: "
                 << oleadas.getIndiceActual()
                 << " / " << oleadas.getTotalOleadas() << "\n";
        }
        cout << "  Camino         : posicion 0 --> " << POS_FINAL << "\n";
        cout << "===================================\n";
    }

    bool partidaTerminada() const {
        return vidasJugador <= 0;
    }
};

#endif 
