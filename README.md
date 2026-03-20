# Tower Defense — Estructura de Datos en C++

---

## Integrantes 

Fernando Llerena(Lider)
Leslie Coello (Colaborador) 
Shirley Amaguaña (Colaborador)
---

## Estructura del Proyecto

```
TowerDefense/
├── Torre.h       # Lista secuencial manual (arreglo) para torres
├── Enemigo.h     # Lista doblemente enlazada para enemigos activos
├── Oleada.h      # Lista simplemente enlazada circular para oleadas
├── Juego.h       # Lógica del juego (coordina las 3 estructuras)
├── main.cpp      # Menú principal — punto de entrada
└── README.md     # Este archivo
```

---

## Estructuras de Datos Implementadas

### 1. Lista Secuencial — Torres Defensivas (`Torre.h`)

Implementa un **arreglo estático manual** de tamaño máximo 50 sin usar `std::vector`.

**Struct Torre:**
```cpp
struct Torre {
    int    id;
    string nombre;
    string tipo;
    int    posicion;
    int    danio;
    int    rango;
    int    costo;
};
```

**Operaciones implementadas en `ListaTorres`:**

| Operación | Método | Descripción |
|-----------|--------|-------------|
| Insertar | `insertarTorre(...)` | Agrega al final, valida ID duplicado |
| Eliminar | `eliminarTorrePorId(id)` | Elimina por ID y desplaza el arreglo |
| Buscar | `buscarPorId(id)` | Retorna puntero a Torre o `nullptr` |
| Mostrar | `mostrarTorres()` | Imprime tabla formateada |
| Contar | `contarTorres()` | Retorna cantidad de torres activas |

---

### 2. Lista Doblemente Enlazada — Enemigos Activos (`Enemigo.h`)

Implementa una **lista doblemente enlazada** con punteros `primero` y `ultimo`. Cada nodo tiene punteros `anterior` y `siguiente`.

**Struct NodoEnemigo:**
```cpp
struct NodoEnemigo {
    int    id;
    string tipo;
    int    vida;
    int    velocidad;
    int    posicion;
    int    recompensa;
    NodoEnemigo* anterior;
    NodoEnemigo* siguiente;
};
```

**Operaciones implementadas en `ListaEnemigos`:**

| Operación | Método | Descripción |
|-----------|--------|-------------|
| Insertar al final | `insertarAlFinal(...)` | Crea nodo y reconecta `ultimo` |
| Eliminar | `eliminarPorId(id)` | Reconecta vecinos y libera memoria |
| Buscar | `buscarPorId(id)` | Recorrido lineal O(n) |
| Recorrer adelante | `recorrerAdelante()` | primero → ultimo |
| Recorrer atrás | `recorrerAtras()` | ultimo → primero |
| Actualizar posiciones | `avanzarEnemigos(posFinal)` | Suma velocidad a cada enemigo |

**Diagrama de la estructura:**
```
nullptr ← [E1] ⇆ [E2] ⇆ [E3] → nullptr
          ↑                 ↑
        primero           ultimo
```

---

### 3. Lista Simplemente Enlazada Circular — Oleadas (`Oleada.h`)

Implementa una **lista circular** con referencia únicamente al **último nodo**. `ultimo->siguiente` siempre apunta al primer nodo, permitiendo ciclo continuo.

**Struct NodoOleada:**
```cpp
struct NodoOleada {
    int    idOleada;
    int    cantidadEnemigos;
    string tipoEnemigo;
    int    vidaBase;
    int    velocidadBase;
    NodoOleada* siguiente;
};
```

**Operaciones implementadas en `ListaOleadas`:**

| Operación | Método | Descripción |
|-----------|--------|-------------|
| Registrar oleada | `registrarOleada(...)` | Inserta al final, mantiene circularidad |
| Mostrar oleadas | `mostrarOleadas()` | Recorre desde primero hasta volver |
| Avanzar oleada | `avanzarSiguienteOleada()` | Mueve puntero `actual` al siguiente |
| Reiniciar ciclo | `reiniciarCiclo()` | Resetea `actual` al primer nodo |

**Diagrama de la estructura:**
```
        ┌─────────────────────────────┐
        ↓                             │
      [O1] → [O2] → [O3] → [O4] ────┘
                             ↑
                           ultimo
```

---

## Reglas del Juego

- El campo es una ruta de posiciones **0 a 20**.
- Los enemigos aparecen en posición **0** y avanzan según su velocidad.
- Las torres atacan automáticamente a enemigos dentro de su **rango**.
- Un enemigo muere cuando su **vida llega a 0** → se elimina de la lista y otorga oro.
- Si un enemigo llega a la posición **20** → el jugador pierde **1 vida**.
- La partida termina cuando el jugador pierde sus **3 vidas**.

---

## Menú del Programa

```
╔══════════════════════════════════════╗
║       TOWER DEFENSE — MENU           ║
╠══════════════════════════════════════╣
║  --- Torres ---                       ║
║  1. Registrar torre defensiva         ║
║  2. Mostrar torres registradas        ║
║  3. Eliminar torre                    ║
║  --- Oleadas ---                      ║
║  4. Registrar oleada                  ║
║  5. Mostrar oleadas                   ║
║  6. Iniciar siguiente oleada          ║
║  --- Juego ---                        ║
║  7. Avanzar turno                     ║
║  8. Mostrar enemigos activos          ║
║  9. Mostrar estado general            ║
║  0. Salir                             ║
╚══════════════════════════════════════╝
```

---

## Caso de Prueba (Sección 10 del documento)

Ingrese los siguientes datos para demostrar el funcionamiento completo:

**Torres:**
| # | Nombre | Tipo | Posición | Daño | Rango | Costo |
|---|--------|------|----------|------|-------|-------|
| 1 | Arquero | Flecha | 3 | 20 | 2 | 50 |
| 2 | Cañón | Explosion | 8 | 35 | 3 | 80 |

**Oleadas:**
| # | Tipo | Cantidad | Vida | Velocidad |
|---|------|----------|------|-----------|
| 1 | Basico | 3 | 50 | 1 |
| 2 | Rapido | 2 | 40 | 2 |

**Jugador:** 3 vidas · 200 oro inicial

**Secuencia sugerida para la demo:**
```
1. Opción 1 → Registrar Torre Arquero
2. Opción 1 → Registrar Torre Cañón
3. Opción 4 → Registrar Oleada 1 (Básicos)
4. Opción 4 → Registrar Oleada 2 (Rápidos)
5. Opción 6 → Iniciar Oleada 1 (genera enemigos)
6. Opción 7 → Avanzar turno (repetir varias veces)
7. Opción 8 → Ver enemigos activos
8. Opción 9 → Ver estado general
```

---

## 📊 Diagrama de Clases (Simplificado)

```
┌────────────┐     ┌─────────────────┐     ┌────────────────┐
│  ListaTorres│     │  ListaEnemigos  │     │  ListaOleadas  │
│────────────│     │─────────────────│     │────────────────│
│ datos[]    │     │ *primero        │     │ *ultimo        │
│ cantidad   │     │ *ultimo         │     │ *actual        │
│────────────│     │ cantidad        │     │ totalOleadas   │
│ insertar() │     │─────────────────│     │────────────────│
│ eliminar() │     │ insertarFinal() │     │ registrar()    │
│ buscar()   │     │ eliminar()      │     │ mostrar()      │
│ mostrar()  │     │ buscar()        │     │ avanzar()      │
│ contar()   │     │ recorrerFwd()   │     │ reiniciar()    │
└────────────┘     │ recorrerBwd()   │     └────────────────┘
      ↑            └─────────────────┘            ↑
      │                    ↑                       │
      └────────────────────┴───────────────────────┘
                           │
                     ┌─────┴──────┐
                     │   Juego    │
                     │────────────│
                     │ torres     │
                     │ enemigos   │
                     │ oleadas    │
                     │ vidas      │
                     │ turno      │
                     │ oro        │
                     │────────────│
                     │ regTorre() │
                     │ regOleada()│
                     │ avTurno()  │
                     │ estado()   │
                     └────────────┘
                           ↑
                     ┌─────┴──────┐
                     │   main()   │
                     │  (menú)    │
                     └────────────┘
```

---

## ✅ Restricciones técnicas cumplidas

- [x] Lenguaje: C++ puro
- [x] Sin `std::vector`, `std::list`, `std::queue`, `std::deque`
- [x] Listas implementadas manualmente con nodos y arreglos
- [x] Se permite: `iostream`, `string`, `iomanip`
- [x] Código organizado en clases y archivos separados
- [x] Compilable con `g++ -std=c++11`

---


