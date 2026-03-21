
#include "Juego.h"
#include <iostream>
#include <limits>
using namespace std;


//  Funcion auxiliar: limpiar buffer de entrada

void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//  Funcion auxiliar: mostrar el menu principal

void mostrarMenu() {
    cout << "\n";
    cout << "+--------------------------------------+\n";
    cout << "¦       TOWER DEFENSE   MENU           ¦\n";
    cout << "¦--------------------------------------¦\n";
    cout << "¦  --- Torres ---                       ¦\n";
    cout << "¦  1. Registrar torre defensiva         ¦\n";
    cout << "¦  2. Mostrar torres registradas        ¦\n";
    cout << "¦  3. Eliminar torre                    ¦\n";
    cout << "¦  --- Oleadas ---                      ¦\n";
    cout << "¦  4. Registrar oleada                  ¦\n";
    cout << "¦  5. Mostrar oleadas                   ¦\n";
    cout << "¦  6. Iniciar siguiente oleada          ¦\n";
    cout << "¦  --- Juego ---                        ¦\n";
    cout << "¦  7. Avanzar turno                     ¦\n";
    cout << "¦  8. Mostrar enemigos activos          ¦\n";
    cout << "¦  9. Mostrar estado general            ¦\n";
    cout << "¦  0. Salir                             ¦\n";
    cout << "+--------------------------------------+\n";
    cout << "  Opcion: ";
}


//  Funcion auxiliar: cargar datos del caso de prueba

void cargarCasoPrueba(Juego& juego) {
    // Esta funcion simula el ingreso manual para la demostracion

    cout << "\n[DEMO] Cargando caso de prueba del documento...\n";

    // Insercion directa a traves del objeto Juego no es posible sin
    // acceso directo a las listas; se usa un metodo publico especial.
    // Por eso se agrega el metodo cargarDemostracion() en Juego.h.
    // Ver implementacion abajo.
    cout << "[DEMO] Use las opciones del menu para ingresar los datos.\n";
    cout << "       Sugerencia de datos:\n";
    cout << "       Torre 1 -> Arquero, tipo Flecha, pos 3, danio 20, rango 2, costo 50\n";
    cout << "       Torre 2 -> Canon,   tipo Explosion, pos 8, danio 35, rango 3, costo 80\n";
    cout << "       Oleada 1 -> id 1, Basico,  3 enemigos, vida 50, vel 1\n";
    cout << "       Oleada 2 -> id 2, Rapido,  2 enemigos, vida 40, vel 2\n";
    cout << "       Vidas iniciales del jugador: 3\n";
}

//  MAIN

int main() {
    cout << "+--------------------------------------+\n";
    cout << "¦  BIENVENIDO A TOWER DEFENSE          ¦\n";
    cout << "+--------------------------------------+\n";

    Juego juego;
    cargarCasoPrueba(juego);

    int opcion;
    do {
        mostrarMenu();

        // Lectura segura de opcion
        if (!(cin >> opcion)) {
            limpiarBuffer();
            cout << "[ERROR] Opcion invalida. Ingrese un numero.\n";
            continue;
        }

        switch (opcion) {
            // --- Torres ---
            case 1:
                juego.registrarTorre();
                break;
            case 2:
                juego.mostrarTorres();
                break;
            case 3:
                juego.eliminarTorre();
                break;

            // --- Oleadas ---
            case 4:
                juego.registrarOleada();
                break;
            case 5:
                juego.mostrarOleadas();
                break;
            case 6:
                juego.iniciarSiguienteOleada();
                break;

            // --- Juego ---
            case 7:
                if (juego.partidaTerminada()) {
                    cout << "[INFO] La partida ya termino. Reinicia el programa.\n";
                } else {
                    juego.avanzarTurno();
                }
                break;
            case 8:
                juego.mostrarEnemigosActivos();
                break;
            case 9:
                juego.mostrarEstadoGeneral();
                break;

            case 0:
                cout << "\nSaliendo del juego. Hasta la proxima!\n";
                break;

            default:
                cout << "[ERROR] Opcion no valida. Elija entre 0 y 9.\n";
                break;
        }

    } while (opcion != 0 && !juego.partidaTerminada());

    if (juego.partidaTerminada()) {
        cout << "\n[FIN] Partida terminada. Hasta la proxima!\n";
    }

    return 0;
}
